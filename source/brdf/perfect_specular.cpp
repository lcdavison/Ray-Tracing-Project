#include "brdf/perfect_specular.h"

PerfectSpecular::PerfectSpecular ( ) { }

PerfectSpecular::PerfectSpecular ( const ColourRGB& p_colour, float p_coeff ) : m_colour ( p_colour ), m_coeff ( p_coeff ) { }

ColourRGB PerfectSpecular::function ( const HitResult& p_hitdata, const Vector3& p_incoming, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

ColourRGB PerfectSpecular::sample_function ( const HitResult& p_hitdata, Vector3& p_incoming, const Vector3& p_outgoing )
{
	p_incoming = 2.0 * dot ( p_hitdata.m_normal, p_outgoing ) * p_hitdata.m_normal - p_outgoing;
	p_incoming.normalize ( );

	return m_colour * m_coeff;	
}

ColourRGB PerfectSpecular::reflectance ( const HitResult& p_hitdata, const Vector3& p_outgoing )
{
	return m_colour * m_coeff;
}
