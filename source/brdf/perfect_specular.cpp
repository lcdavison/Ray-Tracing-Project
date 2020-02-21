#include "brdf/perfect_specular.h"

PerfectSpecular::PerfectSpecular ( ) { }

PerfectSpecular::PerfectSpecular ( const ColourRGB& p_colour, float p_coeff ) : m_colour ( p_colour ), m_coeff ( p_coeff ) { }

ColourRGB PerfectSpecular::function ( const HitResult& p_hitdata, const Vector3& p_incoming, const Vector3& p_outgoing )
{
	return reflectance ( p_hitdata, p_outgoing );
}

ColourRGB PerfectSpecular::reflectance ( const HitResult& p_hitdata, const Vector3& p_outgoing )
{
	return m_colour * m_coeff;
}
