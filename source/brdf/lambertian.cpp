#include "brdf/lambertian.h"

Lambertian::Lambertian ( ) : m_colour ( ColourRGB ( 0.0f, 1.0f, 0.0f ) ), m_coeff ( 1.0f ) { }

Lambertian::Lambertian ( const ColourRGB& p_colour, float p_coeff ) : m_colour ( p_colour ), m_coeff ( p_coeff ) { }

ColourRGB Lambertian::function ( const HitResult& p_hitdata, const Vector3& p_incoming, const Vector3& p_outgoing ) 
{
	return m_colour * m_coeff * INV_PI;
}

ColourRGB Lambertian::sample_function ( const HitResult& p_hitdata, Vector3& p_incoming, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

ColourRGB Lambertian::reflectance ( const HitResult& p_hitdata, const Vector3& p_outgoing )
{
	return m_colour * m_coeff;
}

void Lambertian::set_colour ( const ColourRGB& p_colour )
{
	m_colour = p_colour;
}

void Lambertian::set_coeff ( float p_coeff )
{
	m_coeff = p_coeff;
}
