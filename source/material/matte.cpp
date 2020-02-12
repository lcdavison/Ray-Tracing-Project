#include "material/matte.h"

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
