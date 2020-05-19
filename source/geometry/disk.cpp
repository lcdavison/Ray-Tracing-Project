#include "geometry/disk.h"

const double Disk::m_EPSILON = 0.00001;

Disk::Disk ( ) : m_center ( Point3 ( 0.0, 0.0, 0.0 ) ), m_normal ( Vector3 ( 0.0, 0.0, 1.0 ) ), m_radius ( 30.0 ) { }

Disk::Disk ( const Point3& p_center, const Vector3& p_normal, double p_radius ) : m_center ( p_center ), m_normal ( p_normal ), m_radius ( p_radius ) { }

void Disk::rayhit ( const Ray& p_ray, HitResult& p_hitresult )
{
	//	Perform plane intersection
	double distance = dot ( m_center - p_ray.get_origin ( ), this->m_normal ) / dot ( p_ray.get_direction ( ), this->m_normal );

	Point3 hitpoint = p_ray.get_point ( distance );

	//	Check if point is inside circle in plane
	if ( distance > m_EPSILON && dot ( hitpoint - m_center, hitpoint - m_center ) <= m_radius * m_radius )
	{
		p_hitresult.m_hit 		= true;
		p_hitresult.m_distance 		= distance;
		p_hitresult.m_hitpoint 		= hitpoint;
		p_hitresult.m_normal 		= this->m_normal;
		p_hitresult.m_material_ptr	= this->m_material_ptr;	
	}
}

bool Disk::shadow_rayhit ( const Ray& p_ray, double& p_distance )
{
	//	Plane intersection
	p_distance = dot ( m_center - p_ray.get_origin ( ), this->m_normal ) / dot ( p_ray.get_direction ( ), this->m_normal );

	Point3 hitpoint = p_ray.get_point ( p_distance );

	//	Check if point is inside circle in plane
	if ( p_distance > m_EPSILON && dot ( hitpoint - m_center, hitpoint - m_center ) <= m_radius * m_radius )
	{
		return true;
	}

	return false;
}

void Disk::set_material ( IMaterial* p_material )
{
	m_material_ptr = p_material;
}
