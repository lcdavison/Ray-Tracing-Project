#ifndef PLANE_H
#define PLANE_H

#include "geometry.h"

class Plane : public IGeometry
{
	public:
		Plane ( );

		bool rayhit ( const Ray&, HitResult& );

	private:

		Point3 m_point;
		Vector3 m_normal;
};
#endif
