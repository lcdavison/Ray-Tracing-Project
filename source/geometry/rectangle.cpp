#include "geometry/rectangle.h"

#include <iostream>

const double Rectangle::m_EPSILON = 0.00001;

Rectangle::Rectangle ( ) : m_lower_left ( Point3 ( 0.0, 0.0, 0.0 ) ), m_width ( Vector3 ( 10.0, 0.0, 0.0 ) ), m_height ( 0.0, 10.0, 0.0 ) { }

Rectangle::Rectangle ( const Point3& p_lower_left, const Vector3& p_width, const Vector3& p_height ) : m_lower_left ( p_lower_left ), m_width ( p_width ), m_height ( p_height ), m_normal ( cross ( m_width, m_height ) ) 
{
	m_normal.normalize ( );
	m_inverse_area = 1.0 / ( m_width.length ( ) * m_height.length ( ) );
}

void Rectangle::rayhit ( const Ray& p_ray, HitResult& p_hitresult )
{
	//	Plane Intersection
	Vector3 origin_to_plane = m_lower_left - p_ray.get_origin ( );

	double distance = dot ( origin_to_plane, m_normal ) / dot ( p_ray.get_direction ( ), m_normal );

	if ( distance > m_EPSILON )
	{
		p_hitresult.m_hitpoint = p_ray.get_point ( distance );

		Vector3 corner_to_point = p_hitresult.m_hitpoint - m_lower_left;

		Vector3 width = m_width;
		width.normalize ( );

		double width_projection = dot ( corner_to_point, width );

		//	Check if point X is within bounds
		if ( width_projection * width_projection < dot ( m_width, m_width ) )
		{
			Vector3 height = m_height;
			height.normalize ( );

			double height_projection = dot ( corner_to_point, height );

			//	Check if point Y is within bounds
			if ( height_projection * height_projection < dot ( m_height, m_height ) )
			{
				p_hitresult.m_hit 		= true;
				p_hitresult.m_distance 		= distance;
				p_hitresult.m_normal 		= this->m_normal;
				p_hitresult.m_material_ptr 	= this->m_material_ptr;			
			}
		}
	}
}

bool Rectangle::shadow_rayhit ( const Ray& p_ray, double& p_distance )
{
	//	Plane intersection
	Vector3 origin_to_plane = m_lower_left - p_ray.get_origin ( );

	double distance = dot ( origin_to_plane, m_normal ) / dot ( p_ray.get_direction ( ), m_normal );

	if ( distance > m_EPSILON )
	{
		Point3 hitpoint = p_ray.get_point ( distance );

		Vector3 corner_to_point = hitpoint - m_lower_left;

		Vector3 width = m_width;
		width.normalize ( );

		double width_projection = dot ( corner_to_point, width );

		//	Check if point X is within bounds
		if ( width_projection * width_projection < dot ( m_width, m_width ) )
		{
			Vector3 height = m_height;
			height.normalize ( );

			double height_projection = dot ( corner_to_point, height );

			//	Check if point Y is within bounds
			if ( height_projection * height_projection < dot ( m_height, m_height ) )
			{
				p_distance = distance;
				return true;
			}
		}
	}

	return false;
}

Point3 Rectangle::sample ( )
{
	Point3 sample_point = m_sampler_ptr->sample_square ( );
	return m_lower_left + sample_point.x * m_width + sample_point.y * m_height;
}

Vector3	Rectangle::sample_normal ( const Point3& )
{
	return m_normal;
}

void Rectangle::set_material ( IMaterial* p_material )
{
	m_material_ptr = p_material;
}
