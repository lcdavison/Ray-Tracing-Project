#include "material/matte.h"

#include <iostream>

Matte::Matte ( ) 
{
	ColourRGB colour ( 0.8f, 0.8f, 0.2f );

	m_ambient_brdf = new Lambertian ( colour, 0.1f );
	m_diffuse_brdf = new Lambertian ( colour, 1.0f );
}

Matte::Matte ( const ColourRGB& p_colour, float p_ambient_coeff, float p_diffuse_coeff ) 
{
	m_ambient_brdf = new Lambertian ( p_colour, p_ambient_coeff );
	m_diffuse_brdf = new Lambertian ( p_colour, p_diffuse_coeff );
}

Matte::~Matte ( )
{
	delete m_ambient_brdf;
	m_ambient_brdf = nullptr;

	delete m_diffuse_brdf;
	m_diffuse_brdf = nullptr;
}

ColourRGB Matte::shade ( const HitResult& p_hitdata, const Ray& p_ray )
{
	//	Crudely simulate ambient radiance
	ColourRGB radiance = m_ambient_brdf->reflectance ( p_hitdata, Vector3 ( 0.0, 0.0, 0.0 ) ) * p_hitdata.m_ambient_light_ptr->radiance ( );

	//	Compute incoming radiance
	for ( ILight* light : *p_hitdata.m_lights_ptr )
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
				radiance = radiance + ( m_diffuse_brdf->function ( p_hitdata, light->get_direction ( p_hitdata.m_hitpoint ), Vector3 ( 0.0, 0.0, 0.0 ) ) * light->radiance ( ) * std::max ( normal_dot_dir, 0.0 ) );
			}
		}
	}

	return radiance;
}

ColourRGB Matte::shade_arealight ( const HitResult& p_hitdata, const Ray& p_ray )
{
	//	Crudely simulate ambient radiance
	ColourRGB radiance = m_ambient_brdf->reflectance ( p_hitdata, Vector3 ( 0.0, 0.0, 0.0 ) ) * p_hitdata.m_ambient_light_ptr->radiance ( );

	//	Compute incoming radiance
	for ( ILight* light : *p_hitdata.m_lights_ptr )
	{
		//	Monte Carlo integration
		for ( int i = 0; i < light->get_num_samples ( ); ++i )
		{
			Vector3 light_direction = light->get_direction ( p_hitdata.m_hitpoint );

			double normal_dot_dir = dot ( p_hitdata.m_normal, light_direction );

			//	Check if light effects hit point
			if ( normal_dot_dir > 0.0 )
			{
				bool shadow = false;

				//	Check for shadows
				if ( light->casts_shadows ( ) )
				{
					Ray ray ( p_hitdata.m_hitpoint, light_direction );
					shadow = light->in_shadow ( ray, p_hitdata );
				}

				//	Only render radiance when not in shadow
				if ( !shadow )
				{
					ColourRGB brdf = m_diffuse_brdf->function ( p_hitdata, light_direction, Vector3 ( 0.0, 0.0, 0.0 ) );

					radiance = radiance + ( brdf * light->radiance ( ) * std::max ( normal_dot_dir, 0.0 ) * ( light->geometric_factor ( ) / light->probability_density_function ( ) ) );
				}
			}
		}

		//	Average the radiance
		radiance = radiance * ( 1.0 / light->get_num_samples ( ) );
	}

	return radiance;
}

void Matte::set_ambient_coeff ( float p_coeff )
{
	m_ambient_brdf->set_coeff ( p_coeff );
}

void Matte::set_diffuse_coeff ( float p_coeff )
{
	m_diffuse_brdf->set_coeff ( p_coeff );
}

void Matte::set_colour ( const ColourRGB& p_colour )
{
	m_ambient_brdf->set_colour ( p_colour );
	m_diffuse_brdf->set_colour ( p_colour );
}
