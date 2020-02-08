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

		Point3 		get_origin ( ) 		const;
		Vector3 	get_direction ( ) 	const;

		Point3 		get_point ( double ) 	const;	//	Returns a point along the ray

	private:

		Point3 		m_origin;	//	Position of ray
		Vector3 	m_direction;	//	Direction ray is pointing
};
#endif
