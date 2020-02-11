#include "maths/vector3.h"

Vector3::Vector3 ( ) : x ( 0.0 ), y ( 0.0 ), z ( 0.0 ) { }
Vector3::Vector3 ( double p_x, double p_y, double p_z ) : x ( p_x ), y ( p_y ), z ( p_z ), m_length ( std::sqrt ( x * x + y * y + z * z ) ) { }

double Vector3::length ( )
{
	double length_sqrd = this->x * this->x + this->y * this->y + this->z * this->z;

	if ( length_sqrd == ( m_length * m_length ) )
		return m_length;

	return std::sqrt ( length_sqrd );
}

void Vector3::normalize ( )
{
	length ( );

	x /= m_length;
	y /= m_length;
	z /= m_length;	
}

/*
 *	OPERATORS
 * */
Vector3 operator + ( const Vector3& l, const Vector3& r )
{
	return Vector3 ( l.x + r.x, l.y + r.y, l.z + r.z );
}

Vector3 operator - ( const Vector3& l, const Vector3& r )
{
	return Vector3 ( l.x - r.x, l.y - r.y, l.z - r.z );
}

Vector3 operator * ( const Vector3& v, double s )
{
	return Vector3 ( v.x * s, v.y * s, v.z * s );
}

Vector3 operator * ( double s, const Vector3& v )
{
	return Vector3 ( v.x * s, v.y * s, v.z * s );
}

double dot ( const Vector3& l, const Vector3& r )
{
	return l.x * r.x + l.y * r.y + l.z * r.z;
}

Vector3 cross ( const Vector3& l, const Vector3& r )
{
	return Vector3 ( l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x );
}
