#include "material/phong.h"

Phong::Phong ( ) { }

Phong::Phong ( const ColourRGB& p_colour, float p_ambient_coeff, float p_diffuse_coeff, float p_specular_coeff, float p_specular_exponent )
{
	m_ambient_brdf 		= new Lambertian 	( p_colour, p_ambient_coeff );
	m_diffuse_brdf 		= new Lambertian 	( p_colour, p_diffuse_coeff );
	m_specular_brdf 	= new PhongSpecular 	( p_colour, p_specular_coeff, p_specular_exponent );
}

Phong::~Phong ( )
{
	delete m_ambient_brdf;
	m_ambient_brdf = nullptr;

	delete m_diffuse_brdf;
	m_diffuse_brdf = nullptr;

	delete m_specular_brdf;
	m_specular_brdf = nullptr;
}

ColourRGB Phong::shade ( const HitResult& p_hitdata, const Ray& p_ray )
{
	Vector3 outgoing = -1.0 * p_ray.get_direction ( );

	//	Ambient Light
	ColourRGB radiance = m_ambient_brdf->reflectance ( p_hitdata, outgoing ) * p_hitdata.m_ambient_light_ptr->radiance ( );

	for ( ILight* light : *p_hitdata.m_lights_ptr )
	{
		double normal_dot_dir = dot ( p_hitdata.m_normal, light->get_direction ( p_hitdata.m_hitpoint ) );

		if ( normal_dot_dir > 0.0 )
		{
			bool shadow = false;

			if ( light->casts_shadows ( ) )
			{
				Ray ray ( p_hitdata.m_hitpoint, light->get_direction ( p_hitdata.m_hitpoint ) );
				shadow = light->in_shadow ( ray, p_hitdata );
			}

			if ( !shadow )
			{
				ColourRGB brdf_sum = m_diffuse_brdf->function  ( p_hitdata, light->get_direction ( p_hitdata.m_hitpoint ), outgoing )
						   + m_specular_brdf->function ( p_hitdata, light->get_direction ( p_hitdata.m_hitpoint ), outgoing );

				radiance = radiance + ( brdf_sum * light->radiance ( ) * std::max ( normal_dot_dir, 0.0 ) );
			}
		}
	}

	return radiance;
}

ColourRGB Phong::shade_arealight ( const HitResult& p_hitdata, const Ray& p_ray )
{
	Vector3 outgoing = -1.0 * p_ray.get_direction ( );

	//	Ambient Light
	ColourRGB radiance = m_ambient_brdf->reflectance ( p_hitdata, outgoing ) * p_hitdata.m_ambient_light_ptr->radiance ( );

	for ( ILight* light : *p_hitdata.m_lights_ptr )
	{
		for ( int i = 0; i < light->get_num_samples ( ); ++i )
		{
			double normal_dot_dir = dot ( p_hitdata.m_normal, light->get_direction ( p_hitdata.m_hitpoint ) );

			if ( normal_dot_dir > 0.0 )
			{
				bool shadow = false;

				if ( light->casts_shadows ( ) )
				{
					Ray ray ( p_hitdata.m_hitpoint, light->get_direction ( p_hitdata.m_hitpoint ) );
					shadow = light->in_shadow ( ray, p_hitdata );
				}

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

	return radiance;
}

IBRDF* Phong::get_diffuse_brdf ( )
{
	return m_diffuse_brdf;
}

IBRDF* Phong::get_specular_brdf ( )
{
	return m_specular_brdf;
}

PhongReflective::PhongReflective ( ) { }

PhongReflective::PhongReflective ( const ColourRGB& p_colour, float p_ambient_coeff, float p_diffuse_coeff, float p_specular_coeff, float p_specular_exponent, const ColourRGB& p_reflection_colour, float p_reflection_coeff ) 
	: Phong ( p_colour, p_ambient_coeff, p_diffuse_coeff, p_specular_coeff, p_specular_exponent )
{
	m_flags |= RT_REFLECTIVE;

	m_perfect_specular_brdf = new PerfectSpecular ( p_reflection_colour, p_reflection_coeff );
}

PhongReflective::~PhongReflective ( )
{
	delete m_perfect_specular_brdf;
	m_perfect_specular_brdf = nullptr;
}

ColourRGB PhongReflective::shade ( const HitResult& p_hitdata, const Ray& p_ray )
{
	ColourRGB direct_illumination = Phong::shade ( p_hitdata, p_ray );

	return direct_illumination + p_hitdata.m_reflection_radiance;
}

ColourRGB PhongReflective::shade_arealight ( const HitResult& p_hitdata, const Ray& p_ray )
{
	ColourRGB direct_illumination = Phong::shade_arealight ( p_hitdata, p_ray );

	return direct_illumination + p_hitdata.m_reflection_radiance;	
}

IBRDF* PhongReflective::get_diffuse_brdf ( )
{
	return m_diffuse_brdf;
}

IBRDF* PhongReflective::get_specular_brdf ( )
{
	return m_perfect_specular_brdf;
}
