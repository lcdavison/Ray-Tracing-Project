#include "light/directional.h"

DirectionalLight::DirectionalLight ( ) : m_direction ( Vector3 ( 0.0, -1.0, 0.0 ) ), m_colour ( ColourRGB ( 1.0f, 1.0f, 1.0f ) ), m_coeff ( 1.0f ) { }

DirectionalLight::DirectionalLight ( const Vector3& p_direction, const ColourRGB& p_colour, float p_coeff ) : m_direction ( p_direction ), m_colour ( p_colour ), m_coeff ( p_coeff ) { }

ColourRGB DirectionalLight::radiance ( )
{
	return m_coeff * m_colour;
}

bool DirectionalLight::in_shadow ( const Ray& p_ray, const HitResult& p_hitdata )
{
	for ( IGeometry* geometry : *p_hitdata.m_geometry_ptr )
	{
		double distance = 0;

		if ( geometry->shadow_rayhit ( p_ray, distance ) )
			return true;
	}

	return false;
}

Vector3 DirectionalLight::get_direction ( const Point3& m_hitpoint )
{
	return -1.0 * m_direction;	
}
