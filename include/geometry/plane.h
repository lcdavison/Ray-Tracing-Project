#ifndef PLANE_H
#define PLANE_H

#include "geometry.h"

class Plane : public IGeometry
{
	public:
		Plane ( );
		Plane ( const Point3&, const Vector3& );

		bool 		rayhit ( const Ray&, HitResult& );

	private:

		Point3 		m_point;
		Vector3 	m_normal;
};
#endif
