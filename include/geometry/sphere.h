#ifndef SPHERE_H
#define SPHERE_H

#include "geometry.h"
#include "material/material.h"

class Sphere : public IGeometry 
{
	public:
		Sphere ( );
		Sphere ( const Point3&, double );

		bool 		rayhit ( const Ray&, HitResult& );

		void		set_material ( IMaterial* p_material );

	private:

		IMaterial*	m_pmaterial = nullptr;

		Point3		m_center;
		double		m_radius;
};
#endif
