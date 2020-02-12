#ifndef SPHERE_H
#define SPHERE_H

#include "geometry.h"
#include "maths/maths.h"

class Sphere : public IGeometry 
{
	public:
		Sphere ( );
		Sphere ( const Point3&, double );

		bool 		rayhit ( const Ray&, HitResult& );

	private:

		Point3		m_center;
		double		m_radius;
};
#endif
