#include "material/phong.h"

Phong::Phong ( ) { }

Phong::Phong ( const ColourRGB& p_colour, float p_ambient_coeff, float p_diffuse_coeff, float p_specular_coeff, float p_specular_exponent )
{
	m_reflective = false;

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
	ColourRGB radiance = m_ambient_brdf->reflectance ( p_hitdata, outgoing ) * p_hitdata.m_pambient_light->radiance ( );

	for ( ILight* light : *p_hitdata.m_plights )
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

PhongReflective::PhongReflective ( ) { }

PhongReflective::PhongReflective ( const ColourRGB& p_colour, float p_ambient_coeff, float p_diffuse_coeff, float p_specular_coeff, float p_specular_exponent, const ColourRGB& p_reflection_colour, float p_reflection_coeff ) 
				 : Phong ( p_colour, p_ambient_coeff, p_diffuse_coeff, p_specular_coeff, p_specular_exponent )
{
	m_reflective = true;

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

	return direct_illumination + ( m_perfect_specular_brdf->function ( p_hitdata, Vector3 ( 0.0, 0.0, 0.0 ), Vector3 ( 0.0, 0.0, 0.0 ) ) * p_hitdata.m_reflection_radiance );
}
