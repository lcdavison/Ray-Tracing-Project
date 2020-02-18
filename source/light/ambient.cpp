#include "light/ambient.h"

AmbientLight::AmbientLight ( ) : m_colour ( ColourRGB ( 1.0f, 1.0f, 1.0f ) ), m_coeff ( 1.0f ) { }

ColourRGB AmbientLight::radiance ( )
{
	return m_coeff * m_colour;
}

bool AmbientLight::in_shadow ( const Ray& p_ray, const HitResult& p_hitdata )
{
	return false;
}

Vector3 AmbientLight::get_direction ( const Point3& m_hitpoint )
{
	return Vector3 ( 0.0, 0.0, 0.0 );
}
