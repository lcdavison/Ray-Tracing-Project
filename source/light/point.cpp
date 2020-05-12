#include "light/point.h"

PointLight::PointLight ( ) : m_position ( Point3 ( 0.0, 0.0, 0.0 ) ), m_colour ( 1.0f, 1.0f, 1.0f ), m_coeff ( 1.0f ) { }

PointLight::PointLight ( const Point3& p_position, const ColourRGB& p_colour, float p_coeff ) : m_position ( p_position ), m_colour ( p_colour ), m_coeff ( p_coeff ) { }

ColourRGB PointLight::radiance ( )
{
	return m_colour * m_coeff;
}

bool PointLight::in_shadow ( const Ray& p_ray, const HitResult& p_hitdata )
{
	double point_dist = ( m_position - p_ray.get_origin ( ) ).length ( );

	//	Check for shadow ray intersections
	for ( IGeometry* geometry : *p_hitdata.m_geometry_ptr )
	{
		double distance;
		if ( geometry->shadow_rayhit ( p_ray, distance ) && distance < point_dist )
		{
			return true;
		}
	}

	return false;
}

Vector3 PointLight::get_direction ( const Point3& p_hitpoint ) 
{
	Vector3 light_dir = m_position - p_hitpoint;
	light_dir.normalize ( );

	return light_dir;
}
