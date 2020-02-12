#include "geometry/sphere.h"

Sphere::Sphere ( ) { }

Sphere::Sphere ( const Point3& p_center, double p_radius ) : m_center ( p_center ), m_radius ( p_radius ) { }

bool Sphere::rayhit ( const Ray& p_ray, HitResult& p_hitresult )
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
	double t 		= -v_dot_dir + sqrt / denominator;	//	Quadratic formula 

	double inv_radius = 1.0 / m_radius;

	if ( t > 0.0 )
	{
		p_hitresult.m_hit = true;
		p_hitresult.m_distance = t;
		p_hitresult.m_normal = ( center_to_origin + t * p_ray.get_direction ( ) ) * inv_radius;
		p_hitresult.m_pmaterial = this->m_pmaterial;
		return true;
	}

	t = -v_dot_dir - sqrt / denominator;

	if ( t > 0.0 )
	{
		p_hitresult.m_hit = true;
		p_hitresult.m_distance = t;
		p_hitresult.m_normal = ( center_to_origin + t * p_ray.get_direction ( ) ) * inv_radius;
		p_hitresult.m_pmaterial = this->m_pmaterial;
		return true;
	}

	return false;
}
