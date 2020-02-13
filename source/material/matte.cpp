#include "material/matte.h"

#include <iostream>

Matte::Matte ( ) { }

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

ColourRGB Matte::shade ( const HitResult& p_hitdata )
{
	ColourRGB radiance = m_ambient_brdf->reflectance ( p_hitdata, Vector3 ( 0.0, 0.0, 0.0 ) ) * p_hitdata.m_pambient_light->radiance ( );

	for ( ILight* light : *p_hitdata.m_plights )
	{
		double normal_dot_dir = dot ( p_hitdata.m_normal, light->get_direction ( p_hitdata.m_hitpoint ) );

		if ( normal_dot_dir > 0.0 )
		{
			radiance = radiance + ( m_diffuse_brdf->function ( p_hitdata, light->get_direction ( p_hitdata.m_hitpoint ), Vector3 ( 0.0, 0.0, 0.0 ) ) * light->radiance ( ) * normal_dot_dir );
		}
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
