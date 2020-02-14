#ifndef CYLINDER_H
#define CYLINDER_H

#include "geometry.h"
#include "material/material.h"

/*
 *	This is used to render an open cylinder
 * */
class Cylinder : public IGeometry 
{
	public:

		Cylinder ( );
		Cylinder ( const Point3&, double, double );

		bool 		rayhit ( const Ray&, HitResult& );

		void 		set_material ( IMaterial* );

	private:

		IMaterial* 	m_material_ptr = nullptr;

		Point3 		m_center;
		double 		m_radius;
		double 		m_height;
};
#endif
