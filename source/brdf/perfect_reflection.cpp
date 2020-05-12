#include "brdf/perfect_reflection.h"

PerfectReflection::PerfectReflection ( ) : m_colour ( ColourRGB::WHITE ), m_coeff ( 1.0f ) { }

PerfectReflection::PerfectReflection ( const ColourRGB& p_colour, float p_coeff ) : m_colour ( p_colour ), m_coeff ( p_coeff ) { }

ColourRGB PerfectReflection::function ( const HitResult& p_hitdata, const Vector3& p_incoming, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

ColourRGB PerfectReflection::sample_function ( const HitResult& p_hitdata, Vector3& p_incoming, const Vector3& p_outgoing )
{
	//	Compute reflection vector
	p_incoming = 2.0 * dot ( p_hitdata.m_normal, p_outgoing ) * p_hitdata.m_normal - p_outgoing;
	p_incoming.normalize ( );

	return m_colour * m_coeff;	
}

ColourRGB PerfectReflection::reflectance ( const HitResult& p_hitdata, const Vector3& p_outgoing )
{
	return m_colour * m_coeff;
}

void PerfectReflection::set_colour ( const ColourRGB& p_colour )
{
	m_colour = p_colour;
}

void PerfectReflection::set_coeff ( float p_coeff )
{
	m_coeff = p_coeff;
}
