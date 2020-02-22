#include "geometry/rectangle.h"

const double Rectangle::m_EPSILON = 0.00001;

Rectangle::Rectangle ( ) { }

Rectangle::Rectangle ( const Point3& p_center, const Vector3& p_normal, double p_width, double p_height ) : m_center ( p_center ), m_normal ( p_normal ), m_width ( p_width ), m_height ( p_height ) { }

void Rectangle::rayhit ( const Ray& p_ray, HitResult& p_hitresult )
{
	//	Plane Intersection
	Vector3 origin_to_plane = m_center - p_ray.get_origin ( );

	double distance = dot ( origin_to_plane, m_normal ) / dot ( p_ray.get_direction ( ), m_normal );

	if ( distance > m_EPSILON )
	{
		//	Check if it hits the inside of the rectangle
		p_hitresult.m_hitpoint = p_ray.get_point ( distance );

		if ( std::abs ( p_hitresult.m_hitpoint.x - m_center.x ) < m_width * 0.5 && std::abs ( p_hitresult.m_hitpoint.y - m_center.y ) < m_height * 0.5 )
		{
			p_hitresult.m_hit = true;
			p_hitresult.m_distance = distance;
			p_hitresult.m_normal = this->m_normal;
			p_hitresult.m_pmaterial = this->m_material_ptr;
		}
	}
}

bool Rectangle::shadow_rayhit ( const Ray& p_ray, double& p_distance )
{
	Vector3 origin_to_plane = m_center - p_ray.get_origin ( );

	double distance = dot ( origin_to_plane, m_normal ) / dot ( p_ray.get_direction ( ), m_normal );

	if ( distance > m_EPSILON )
	{
		//	Check if it hits the inside of the rectangle
		Point3 hitpoint = p_ray.get_point ( distance );

		if ( std::abs ( hitpoint.x - m_center.x ) < m_width * 0.5 && std::abs ( hitpoint.y - m_center.y ) < m_height * 0.5 )
		{
			p_distance = distance;
			return true;
		}
	}

	return false;
}

void Rectangle::set_material ( IMaterial* p_material )
{
	m_material_ptr = p_material;
}
