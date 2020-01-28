#ifndef RAY_H
#define RAY_H

#include "point3.h"
#include "vector3.h"

class Ray 
{
	public:
		
		Ray ( );
		Ray ( const Point3&, const Vector3& );
		Ray ( const Ray& ) = default;
		Ray ( Ray&& ) = default;

		Point3 		get_origin ( );
		Vector3 	get_direction ( );

		Point3 		get_point ( double );	//	Returns a point along the ray

	private:

		Point3 		m_origin;	//	Position of ray
		Vector3 	m_direction;	//	Direction ray is pointing
};
#endif
