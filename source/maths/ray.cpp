#include "maths/ray.h"

Ray::Ray ( ) : m_origin ( 0.0, 0.0, 0.0 ), m_direction ( 0.0, 0.0, 1.0 ) { }

Ray::Ray ( const Point3& p_origin, const Vector3& p_direction ) : m_origin ( p_origin ), m_direction ( p_direction ) { }

Point3 Ray::get_origin ( ) const
{
	return m_origin;
}

Vector3 Ray::get_direction ( ) const
{
	return m_direction;
}

Point3 Ray::get_point ( double p_length ) const
{
	return m_origin + ( m_direction * p_length );
}
