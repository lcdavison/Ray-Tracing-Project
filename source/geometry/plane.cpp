#include "geometry/plane.h"

const double Plane::m_EPSILON = 0.00001;

Plane::Plane ( ) : m_point ( 0.0, 0.0, 0.0 ), m_normal ( 0.0, 1.0, 0.0 ) { }

Plane::Plane ( const Point3& p_point, const Vector3& p_normal ) : m_point ( p_point ), m_normal ( p_normal ) { }

void Plane::rayhit ( const Ray& p_ray, HitResult& p_hitresult )
{
	Vector3 origin_to_plane = this->m_point - p_ray.get_origin ( );

	double distance = dot ( origin_to_plane, this->m_normal ) / dot ( p_ray.get_direction ( ), this->m_normal );

	if ( distance > m_EPSILON )
	{
		p_hitresult.m_hit 	= true;
		p_hitresult.m_distance 	= distance;
		p_hitresult.m_normal 	= this->m_normal;
		p_hitresult.m_pmaterial = this->m_pmaterial;
	}
}

bool Plane::shadow_rayhit ( const Ray& p_ray, double& p_distance )
{
	Vector3 origin_to_plane = this->m_point - p_ray.get_origin ( );

	p_distance = dot ( origin_to_plane, this->m_normal ) / dot ( p_ray.get_direction ( ), this->m_normal );

	if ( p_distance > m_EPSILON )
	{
		return true;
	}

	return false;
}

void Plane::set_material ( IMaterial* p_material ) 
{
	m_pmaterial = p_material;
}
