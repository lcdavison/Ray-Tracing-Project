#include "maths/point3.h"

Point3::Point3 ( ) : x ( 0.0 ), y ( 0.0 ), z ( 0.0 ) { }
Point3::Point3 ( double p_x, double p_y, double p_z ) : x ( p_x ), y ( p_y ), z ( p_z ) { }

Vector3 operator - ( const Point3& l, const Point3& r )
{
	return Vector3 ( l.x - r.x, l.y - r.y, l.z - r.z );
}

Point3 operator + ( const Point3& l, const Vector3& r )
{
	return Point3 ( l.x + r.x, l.y + r.y, l.z + r.z );
}
