#ifndef SPHERE_H
#define SPHERE_H

#include "geometry.h"
#include "material/material.h"

/*
 *	Used to render a sphere
 * */
class Sphere : public IGeometry 
{
	public:
		Sphere ( );
		Sphere ( const Point3&, double );

		void 			rayhit ( const Ray&, HitResult& );
		bool			shadow_rayhit ( const Ray&, double& );

		void			set_material ( IMaterial* );

	private:

		IMaterial*		m_material_ptr = nullptr;

		Point3			m_center;
		double			m_radius;

		static const double 	m_EPSILON;
};
#endif
