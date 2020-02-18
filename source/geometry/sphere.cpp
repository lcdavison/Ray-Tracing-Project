#include "geometry/sphere.h"

const double Sphere::m_EPSILON = 0.00001;

Sphere::Sphere ( ) { }

Sphere::Sphere ( const Point3& p_center, double p_radius ) : m_center ( p_center ), m_radius ( p_radius ) { }

void Sphere::rayhit ( const Ray& p_ray, HitResult& p_hitresult )
{
	Vector3 center_to_origin = p_ray.get_origin ( ) - m_center;

	//	Uses Quadratic formula to compute intersection points
	double dir_sqrd 	= dot ( p_ray.get_direction ( ), p_ray.get_direction ( ) );
	double v_dot_dir 	= dot ( 2.0 * center_to_origin, p_ray.get_direction ( ) );
	double v_sqrd 		= dot ( center_to_origin, center_to_origin ) - ( m_radius * m_radius );

	double discriminant = v_dot_dir * v_dot_dir - 4.0 * dir_sqrd * v_sqrd;	//	Determines how many roots there are for the equation, i.e the num of intersections

	if ( discriminant < 0.0 )
	{
		return;
	}

	double sqrt 		= std::sqrt ( discriminant );
	double denominator 	= 2.0 * dir_sqrd;
	double distance 	= ( -v_dot_dir - sqrt ) / denominator;	//	Quadratic formula - shorter distance 

	double inv_radius = 1.0 / m_radius;

	if ( distance > m_EPSILON )
	{
		p_hitresult.m_hit = true;
		p_hitresult.m_distance = distance;
		p_hitresult.m_normal = ( center_to_origin + distance * p_ray.get_direction ( ) ) * inv_radius;
		p_hitresult.m_pmaterial = this->m_pmaterial;
		return;
	}

	distance = ( -v_dot_dir + sqrt ) / denominator;	//	Quadratic formula - further distance

	if ( distance > m_EPSILON )
	{
		p_hitresult.m_hit = true;
		p_hitresult.m_distance = distance;
		p_hitresult.m_normal = ( center_to_origin + distance * p_ray.get_direction ( ) ) * inv_radius;
		p_hitresult.m_pmaterial = this->m_pmaterial;
	}
}

bool Sphere::shadow_rayhit ( const Ray& p_ray, double& p_distance )
{
	Vector3 center_to_origin = p_ray.get_origin ( ) - m_center;

	//	Uses Quadratic formula to compute intersection points
	double dir_sqrd 	= dot ( p_ray.get_direction ( ), p_ray.get_direction ( ) );
	double v_dot_dir 	= dot ( 2.0 * center_to_origin, p_ray.get_direction ( ) );
	double v_sqrd 		= dot ( center_to_origin, center_to_origin ) - ( m_radius * m_radius );

	double discriminant = v_dot_dir * v_dot_dir - 4.0 * dir_sqrd * v_sqrd;	//	Determines how many roots there are for the equation, i.e the num of intersections

	if ( discriminant < 0.0 )
	{
		return false;
	}

	double sqrt 		= std::sqrt ( discriminant );
	double denominator 	= 2.0 * dir_sqrd;
	p_distance 		= ( -v_dot_dir - sqrt ) / denominator;	//	Quadratic formula - shorter distance 

	double inv_radius = 1.0 / m_radius;

	if ( p_distance > m_EPSILON )
	{
		return true;
	}

	p_distance = ( -v_dot_dir + sqrt ) / denominator;	//	Quadratic formula - further distance

	if ( p_distance > m_EPSILON )
	{
		return true;
	}

	return false;
}

void Sphere::set_material ( IMaterial* p_material ) 
{
	m_pmaterial = p_material;
}
