#ifndef SPHERE_H
#define SPHERE_H

#include "geometry.h"
#include "maths/maths.h"

class Sphere : public IGeometry 
{
	public:
		Sphere ( );

		bool rayhit ( const Ray&, HitResult& );

	private:

		Point3		m_center;
		float		m_radius;
};
#endif
