#include "light/ambient.h"

AmbientLight::AmbientLight ( ) : m_colour ( ColourRGB ( 1.0f, 1.0f, 1.0f ) ), m_coeff ( 1.0f ) { }

ColourRGB AmbientLight::radiance ( )
{
	return m_coeff * m_colour;
}

Vector3 AmbientLight::get_direction ( )
{
	return Vector3 ( 0.0, 0.0, 0.0 );
}
