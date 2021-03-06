#include "material/phong.h"

Phong::Phong ( ) { }

Phong::Phong ( const ColourRGB& p_colour, float p_ambient_coeff, float p_diffuse_coeff, float p_specular_coeff, float p_specular_exponent, unsigned char p_flags )
{
	m_flags = p_flags;

	m_ambient_brdf 	= new Lambertian 	( p_colour, p_ambient_coeff );
	m_diffuse_brdf 	= new Lambertian 	( p_colour, p_diffuse_coeff );
	m_specular_brdf	= new PhongSpecular 	( p_colour, p_specular_coeff, p_specular_exponent );

	if ( m_flags & RT_REFLECTIVE )
		m_reflection_brdf = new PerfectReflection ( ColourRGB::WHITE, 1.0f );

	if ( m_flags & RT_REFRACTIVE )
	{
		m_reflection_brdf = new PerfectReflection ( ColourRGB::WHITE, 0.2f );
		m_refraction_btdf = new PerfectRefraction ( 1.33f, 0.8f );
	}

	if ( m_flags & RT_GLOSSY )
		m_glossy_brdf = new GlossyReflection ( p_colour, 0.8f, p_specular_exponent );
}

Phong::~Phong ( )
{
	delete m_ambient_brdf;
	m_ambient_brdf = nullptr;

	delete m_diffuse_brdf;
	m_diffuse_brdf = nullptr;

	delete m_specular_brdf;
	m_specular_brdf = nullptr;

	if ( m_reflection_brdf )
	{
		delete m_reflection_brdf;
		m_reflection_brdf = nullptr;
	}

	if ( m_refraction_btdf )
	{
		delete m_refraction_btdf;
		m_refraction_btdf = nullptr;
	}

	if ( m_glossy_brdf )
	{
		delete m_glossy_brdf;
		m_glossy_brdf = nullptr;
	}
}

ColourRGB Phong::shade ( const HitResult& p_hitdata, const Ray& p_ray )
{
	//	Reverse ray direction
	Vector3 outgoing = -1.0 * p_ray.get_direction ( );

	//	Ambient Light
	ColourRGB radiance = m_ambient_brdf->reflectance ( p_hitdata, outgoing ) * p_hitdata.m_ambient_light_ptr->radiance ( );

	//	Compute incoming radiance
	for ( ILight* light : *p_hitdata.m_lights_ptr )
	{
		double normal_dot_dir = dot ( p_hitdata.m_normal, light->get_direction ( p_hitdata.m_hitpoint ) );

		//	Check if lights effects hit point
		if ( normal_dot_dir > 0.0 )
		{
			bool shadow = false;

			//	Check for shadows
			if ( light->casts_shadows ( ) )
			{
				Ray ray ( p_hitdata.m_hitpoint, light->get_direction ( p_hitdata.m_hitpoint ) );
				shadow = light->in_shadow ( ray, p_hitdata );
			}

			//	Only render radiance when not in shadow
			if ( !shadow )
			{
				ColourRGB brdf_sum = m_diffuse_brdf->function  ( p_hitdata, light->get_direction ( p_hitdata.m_hitpoint ), outgoing )
						   + m_specular_brdf->function ( p_hitdata, light->get_direction ( p_hitdata.m_hitpoint ), outgoing );

				radiance = radiance + ( brdf_sum * light->radiance ( ) * std::max ( normal_dot_dir, 0.0 ) );
			}
		}
	}

	return radiance + p_hitdata.m_indirect_radiance;
}

ColourRGB Phong::shade_arealight ( const HitResult& p_hitdata, const Ray& p_ray )
{
	//	Reverse ray direction
	Vector3 outgoing = -1.0 * p_ray.get_direction ( );

	//	Ambient Light
	ColourRGB radiance = m_ambient_brdf->reflectance ( p_hitdata, outgoing ) * p_hitdata.m_ambient_light_ptr->radiance ( );

	//	Compute incoming radiance
	for ( ILight* light : *p_hitdata.m_lights_ptr )
	{
		for ( int i = 0; i < light->get_num_samples ( ); ++i )
		{
			double normal_dot_dir = dot ( p_hitdata.m_normal, light->get_direction ( p_hitdata.m_hitpoint ) );

			//	Check if light effects hit point
			if ( normal_dot_dir > 0.0 )
			{
				bool shadow = false;

				//	Check for shadows
				if ( light->casts_shadows ( ) )
				{
					Ray ray ( p_hitdata.m_hitpoint, light->get_direction ( p_hitdata.m_hitpoint ) );
					shadow = light->in_shadow ( ray, p_hitdata );
				}

				//	Only render radiance when not in shadow
				if ( !shadow )
				{
					ColourRGB brdf_sum = m_diffuse_brdf->function  ( p_hitdata, light->get_direction ( p_hitdata.m_hitpoint ), outgoing )
							   + m_specular_brdf->function ( p_hitdata, light->get_direction ( p_hitdata.m_hitpoint ), outgoing );

					radiance = radiance + ( brdf_sum * light->radiance ( ) * std::max ( normal_dot_dir, 0.0 ) * ( light->geometric_factor ( ) / light->probability_density_function ( ) ) );
				}
			}
		}

		radiance = radiance * ( 1.0 / light->get_num_samples ( ) );
	}

	return radiance + p_hitdata.m_indirect_radiance;
}
