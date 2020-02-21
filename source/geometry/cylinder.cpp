#include "geometry/cylinder.h"

const double Cylinder::m_EPSILON = 0.00001;

Cylinder::Cylinder ( ) { }

Cylinder::Cylinder ( const Point3& p_center, double p_radius, double p_height ) : m_center ( p_center ), m_radius ( p_radius ), m_height ( p_height ) { }

void Cylinder::rayhit ( const Ray& p_ray, HitResult& p_hitresult )
{
	//	Similar to sphere intersection, except y axis is used for height
	double cx_to_ox 	= p_ray.get_origin ( ).x - m_center.x;
	double cz_to_oz 	= p_ray.get_origin ( ).z - m_center.z;

	double dir_sqrd 	= ( p_ray.get_direction ( ).x * p_ray.get_direction ( ).x ) + ( p_ray.get_direction ( ).z * p_ray.get_direction ( ).z );
	double v_dot_dir 	= 2.0 * ( p_ray.get_direction ( ).x * cx_to_ox + p_ray.get_direction ( ).z * cz_to_oz );
	double v_sqr 		= ( cx_to_ox * cx_to_ox + cz_to_oz * cz_to_oz ) - ( m_radius * m_radius );

	double discriminant 	= v_dot_dir * v_dot_dir - 4.0 * dir_sqrd * v_sqr;

	p_hitresult.m_distance 	= std::numeric_limits < double >::max ( );

	//	Doesn't hit sides of cylinder, so just test caps
	if ( discriminant < 0.0 )
	{
		HitResult cap_result;
		cap_result.m_distance = p_hitresult.m_distance;
		test_caps ( p_ray, cap_result );

		if ( cap_result.m_distance < p_hitresult.m_distance )
			p_hitresult = cap_result;

		return;
	}

	double sqrt 		= std::sqrt ( discriminant );
	double denominator 	= 2.0 * dir_sqrd;

	double half_height 	= m_height * 0.5;
	double inv_radius 	= 1.0 / m_radius;

	double distance 	= ( -v_dot_dir - sqrt ) / denominator;

	if ( distance > m_EPSILON && distance < p_hitresult.m_distance )
	{
		if ( p_ray.get_point ( distance ).y >= m_center.y - half_height && p_ray.get_point ( distance ).y <= m_center.y + half_height )
		{
			p_hitresult.m_hit 	= true;
			p_hitresult.m_distance 	= distance;
			p_hitresult.m_normal 	= Vector3 ( cx_to_ox + distance * p_ray.get_direction ( ).x, 0.0, cz_to_oz + distance * p_ray.get_direction ( ).z ) * inv_radius;

			if ( dot ( p_hitresult.m_normal, -1.0 * p_ray.get_direction ( ) ) < 0.0 )
			{
				p_hitresult.m_normal = p_hitresult.m_normal * -1.0;	
			}

			p_hitresult.m_pmaterial = this->m_material_ptr;
		}
	}

	distance = ( -v_dot_dir + sqrt ) / denominator;

	if ( distance > m_EPSILON && distance < p_hitresult.m_distance )
	{
		if ( p_ray.get_point ( distance ).y >= m_center.y - half_height && p_ray.get_point ( distance ).y <= m_center.y + half_height )
		{
			p_hitresult.m_hit 	= true;
			p_hitresult.m_distance 	= distance;
			p_hitresult.m_normal 	= Vector3 ( cx_to_ox + distance * p_ray.get_direction ( ).x, 0.0, cz_to_oz + distance * p_ray.get_direction ( ).z ) * inv_radius;

			if ( dot ( p_hitresult.m_normal, -1.0 * p_ray.get_direction ( ) ) < 0.0 )
			{
				p_hitresult.m_normal = p_hitresult.m_normal * -1.0;	
			}

			p_hitresult.m_pmaterial = this->m_material_ptr;
		}
	}

	HitResult cap_result;
	cap_result.m_distance = p_hitresult.m_distance;
	test_caps ( p_ray, cap_result );

	if ( cap_result.m_distance < p_hitresult.m_distance )
		p_hitresult = cap_result;
}

void Cylinder::test_caps ( const Ray& p_ray, HitResult& p_hitresult )
{
	double 	half_height 	= m_height * 0.5;

	//	Check top cap
	Vector3 plane_normal 	= Vector3 ( 0.0, 1.0, 0.0 );
	Point3 	cap_center 	= Point3 ( m_center.x, m_center.y + half_height, m_center.z );
	double distance 	= dot ( cap_center - p_ray.get_origin ( ), plane_normal ) / dot ( p_ray.get_direction ( ), plane_normal );

	if ( distance > m_EPSILON && distance < p_hitresult.m_distance )
	{
		Vector3 center_to_point = p_ray.get_point ( distance ) - cap_center;

		if ( dot ( center_to_point, center_to_point ) < m_radius * m_radius )
		{
			p_hitresult.m_hit 	= true;
			p_hitresult.m_distance 	= distance;
			p_hitresult.m_normal 	= plane_normal;
			p_hitresult.m_pmaterial = this->m_material_ptr;	
		}
	}

	//	Check bottom cap
	plane_normal 	= Vector3 ( 0.0, -1.0, 0.0 );
	cap_center 	= Point3 ( m_center.x, m_center.y - half_height, m_center.z );
	distance	= dot ( cap_center - p_ray.get_origin ( ), plane_normal ) / dot ( p_ray.get_direction ( ), plane_normal );

	if ( distance > m_EPSILON && distance < p_hitresult.m_distance )
	{
		Vector3 center_to_point = p_ray.get_point ( distance ) - cap_center;

		if ( dot ( center_to_point, center_to_point ) < m_radius * m_radius )
		{
			p_hitresult.m_hit 	= true;
			p_hitresult.m_distance 	= distance;
			p_hitresult.m_normal 	= plane_normal;
			p_hitresult.m_pmaterial	= this->m_material_ptr;
		}
	}
}

bool Cylinder::shadow_rayhit ( const Ray& p_ray, double& p_distance )
{
	//	Similar to sphere intersection, except y axis is used for height
	double cx_to_ox 	= p_ray.get_origin ( ).x - m_center.x;
	double cz_to_oz 	= p_ray.get_origin ( ).z - m_center.z;

	double dir_sqrd 	= ( p_ray.get_direction ( ).x * p_ray.get_direction ( ).x ) + ( p_ray.get_direction ( ).z * p_ray.get_direction ( ).z );
	double v_dot_dir 	= 2.0 * ( p_ray.get_direction ( ).x * cx_to_ox + p_ray.get_direction ( ).z * cz_to_oz );
	double v_sqr 		= ( cx_to_ox * cx_to_ox + cz_to_oz * cz_to_oz ) - ( m_radius * m_radius );

	double discriminant 	= v_dot_dir * v_dot_dir - 4.0 * dir_sqrd * v_sqr;

	//	Doesn't hit sides of cylinder, so just test caps
	if ( discriminant < 0.0 )
	{
		//	Check top cap
		double 	half_height 	= m_height * 0.5;
		Vector3 plane_normal 	= Vector3 ( 0.0, 1.0, 0.0 );
		Point3 	cap_center 	= Point3 ( m_center.x, m_center.y + half_height, m_center.z );
		p_distance 		= dot ( cap_center - p_ray.get_origin ( ), plane_normal ) / dot ( p_ray.get_direction ( ), plane_normal );

		if ( p_distance > m_EPSILON )
		{
			Vector3 center_to_point = p_ray.get_point ( p_distance ) - cap_center;

			if ( dot ( center_to_point, center_to_point ) < m_radius * m_radius )
			{
				return true;
			}
		}

		//	Check bottom cap
		plane_normal 	= Vector3 ( 0.0, -1.0, 0.0 );
		cap_center 	= Point3 ( m_center.x, m_center.y - half_height, m_center.z );
		p_distance	= dot ( cap_center - p_ray.get_origin ( ), plane_normal ) / dot ( p_ray.get_direction ( ), plane_normal );

		if ( p_distance > m_EPSILON )
		{
			Vector3 center_to_point = p_ray.get_point ( p_distance ) - cap_center;

			if ( dot ( center_to_point, center_to_point ) < m_radius * m_radius )
			{
				return true;
			}
		}

		return false;
	}

	double sqrt 		= std::sqrt ( discriminant );
	double denominator 	= 2.0 * dir_sqrd;
	p_distance 		= ( -v_dot_dir - sqrt ) / denominator;

	double half_height 	= m_height * 0.5;
	double inv_radius 	= 1.0 / m_radius;

	if ( p_distance > m_EPSILON )
	{
		if ( p_ray.get_point ( p_distance ).y >= m_center.y - half_height && p_ray.get_point ( p_distance ).y <= m_center.y + half_height )
		{
			return true;
		}
	}

	p_distance = ( -v_dot_dir + sqrt ) / denominator;

	if ( p_distance > m_EPSILON )
	{
		if ( p_ray.get_point ( p_distance ).y >= m_center.y - half_height && p_ray.get_point ( p_distance ).y <= m_center.y + half_height )
		{
			return true;
		}
	}

	return false;
}

void Cylinder::set_material ( IMaterial* p_material )
{
	m_material_ptr = p_material;
}
