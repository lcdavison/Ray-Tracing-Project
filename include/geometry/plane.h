#ifndef PLANE_H
#define PLANE_H

#include "geometry.h"

class Plane : public Geometry
{
	public:
		Plane ( );

		bool rayhit ( const Ray&, HitResult& ) override;

	private:

		Point3 m_point;
		Vector3 m_normal;
};
#endif
