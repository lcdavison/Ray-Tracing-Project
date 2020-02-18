#include "material/blinn-phong.h"

BlinnPhong::BlinnPhong ( ) { }

BlinnPhong::BlinnPhong ( const ColourRGB& p_colour, float p_ambient_coeff, float p_diffuse_coeff, float p_specular_coeff, float p_specular_exponent )
{
	m_ambient_brdf 	= new Lambertian 	( p_colour, p_ambient_coeff );
	m_diffuse_brdf 	= new Lambertian 	( p_colour, p_diffuse_coeff );
	m_specular_brdf = new BlinnPhongSpecular 	( p_colour, p_ambient_coeff, p_specular_exponent );
}

BlinnPhong::~BlinnPhong ( )
{
	delete m_ambient_brdf;
	m_ambient_brdf = nullptr;

	delete m_diffuse_brdf;
	m_diffuse_brdf = nullptr;

	delete m_specular_brdf;
	m_specular_brdf = nullptr;
}

ColourRGB BlinnPhong::shade ( const HitResult& p_hitdata, const Ray& p_ray )
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

				radiance = radiance + ( brdf_sum * light->radiance ( ) * normal_dot_dir );
			}
		}
	}

	return radiance;
}

