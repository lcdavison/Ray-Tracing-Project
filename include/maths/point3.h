#ifndef POINT_H
#define POINT_H

#include "vector3.h"

/*
 *	Point3 represents a point in 3D Cartesian space.
 * */
struct Point3 
{
	double x, y, z;		//	3D coordinates
	
	Point3 ( );
	Point3 ( double, double, double );
	Point3 ( const Point3& ) = default;
};

Vector3 operator - ( const Point3&, const Point3& );	//	Get vector between two points
Point3 operator + ( const Point3&, const Vector3& );	//	Get point by adding vector to point

#endif
