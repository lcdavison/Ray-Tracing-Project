#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

/*
 *	Vector3 represents a displacement in 3D Cartesian space
 * */
class Vector3 
{
	public:

		double x, y, z;

		Vector3 ( );
		Vector3 ( double, double, double );
		Vector3 ( const Vector3& ) = default;

		double 		length ( );
		void 		normalize ( );

	private:

		double 		m_length;
};

//	Declare operations
Vector3 operator + ( const Vector3&, const Vector3& );
Vector3 operator - ( const Vector3&, const Vector3& );
Vector3 operator * ( const Vector3&, double );
Vector3 operator * ( double, const Vector3& );

double  dot   ( const Vector3&, const Vector3& );
Vector3 cross ( const Vector3&, const Vector3& );
#endif
