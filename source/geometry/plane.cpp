#include "geometry/plane.h"

#include <iostream>

Plane::Plane ( ) : m_point ( 0.0, 0.0, 0.0 ), m_normal ( 0.0, 1.0, 0.0 ) { }

Plane::Plane ( const Point3& p_point, const Vector3& p_normal ) : m_point ( p_point ), m_normal ( p_normal ) { }

bool Plane::rayhit ( const Ray& p_ray, HitResult& p_hitresult )
{
	Vector3 plane_to_origin = this->m_point - p_ray.get_origin ( );

	double distance = dot ( plane_to_origin, this->m_normal ) / dot ( p_ray.get_direction ( ), this->m_normal );

	if ( distance > 0.0 )
	{
		p_hitresult.m_hit = true;
		p_hitresult.m_distance = distance;
	}
}
