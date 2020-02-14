#include "geometry/cylinder.h"

#include <iostream>

Cylinder::Cylinder ( ) { }

Cylinder::Cylinder ( const Point3& p_center, double p_radius, double p_height ) : m_center ( p_center ), m_radius ( p_radius ), m_height ( p_height ) { }

bool Cylinder::rayhit ( const Ray& p_ray, HitResult& p_hitresult )
{
	//	Similar to sphere intersection, except y axis is used for height
	double cx_to_ox 	= p_ray.get_origin ( ).x - m_center.x;
	double cz_to_oz 	= p_ray.get_origin ( ).z - m_center.z;

	double dir_sqrd 	= ( p_ray.get_direction ( ).x * p_ray.get_direction ( ).x ) + ( p_ray.get_direction ( ).z * p_ray.get_direction ( ).z );
	double v_dot_dir 	= 2.0 * ( p_ray.get_direction ( ).x * cx_to_ox + p_ray.get_direction ( ).z * cz_to_oz );
	double v_sqr 		= ( cx_to_ox * cx_to_ox + cz_to_oz * cz_to_oz ) - ( m_radius * m_radius );

	double discriminant 	= v_dot_dir * v_dot_dir - 4.0 * dir_sqrd * v_sqr;

	//	No hits
	if ( discriminant < 0.0 )
	{
		//	TODO: Just check the caps

		return false;
	}

	double sqrt 		= std::sqrt ( discriminant );
	double denominator 	= 2.0 * dir_sqrd;
	double distance 	= ( -v_dot_dir - sqrt ) / denominator;

	double half_height 	= m_height * 0.5;
	double inv_radius 	= 1.0 / m_radius;

	if ( distance > 0.0 && p_ray.get_point ( distance ).y >= m_center.y - half_height && p_ray.get_point ( distance ).y <= m_center.y + half_height )
	{
		p_hitresult.m_hit = true;
		p_hitresult.m_distance = distance;
		p_hitresult.m_normal = Vector3 ( cx_to_ox + distance * p_ray.get_direction ( ).x, 0.0, cz_to_oz + distance * p_ray.get_direction ( ).z ) * inv_radius;

		if ( dot ( p_hitresult.m_normal, -1.0 * p_ray.get_direction ( ) ) < 0.0 )
		{
			p_hitresult.m_normal = p_hitresult.m_normal * -1.0;	
		}

		p_hitresult.m_pmaterial = this->m_material_ptr;
	}

	distance = ( -v_dot_dir + sqrt ) / denominator;

	if ( distance > 0.0 && p_ray.get_point ( distance ).y >= m_center.y - half_height && p_ray.get_point ( distance ).y <= m_center.y + half_height && distance < p_hitresult.m_distance )
	{
		p_hitresult.m_hit = true;
		p_hitresult.m_distance = distance;
		p_hitresult.m_normal = Vector3 ( cx_to_ox + distance * p_ray.get_direction ( ).x, 0.0, cz_to_oz + distance * p_ray.get_direction ( ).z ) * inv_radius;

		if ( dot ( p_hitresult.m_normal, -1.0 * p_ray.get_direction ( ) ) < 0.0 )
		{
			p_hitresult.m_normal = p_hitresult.m_normal * -1.0;	
		}

		p_hitresult.m_pmaterial = this->m_material_ptr;
	}

	Vector3 plane_normal = Vector3 ( 0.0, 1.0, 0.0 );
	distance = dot ( Point3 ( m_center.x, m_center.y + half_height, m_center.z ) - p_ray.get_origin ( ), plane_normal ) / dot ( p_ray.get_direction ( ), plane_normal );

	if ( distance > 0.0 
	     && dot ( p_ray.get_point ( distance ) - m_center, p_ray.get_point ( distance ) - m_center ) <= m_radius * m_radius 
	     && distance < p_hitresult.m_distance )
	{
		p_hitresult.m_hit = true;
		p_hitresult.m_distance = distance;
		p_hitresult.m_normal = plane_normal;
		p_hitresult.m_pmaterial = this->m_material_ptr;
	}

	plane_normal = Vector3 ( 0.0, -1.0, 0.0 );
	distance = dot ( Point3 ( m_center.x, m_center.y - half_height, m_center.z ) - p_ray.get_origin ( ), plane_normal ) / dot ( p_ray.get_direction ( ), plane_normal );

	if ( distance > 0.0 
	     && dot ( p_ray.get_point ( distance ) - m_center, p_ray.get_point ( distance ) - m_center ) <= m_radius * m_radius 
	     && distance < p_hitresult.m_distance )
	{
		p_hitresult.m_hit = true;
		p_hitresult.m_distance = distance;
		p_hitresult.m_normal = plane_normal;
		p_hitresult.m_pmaterial = this->m_material_ptr;
	}

	return false;
}

void Cylinder::set_material ( IMaterial* p_material )
{
	m_material_ptr = p_material;
}
