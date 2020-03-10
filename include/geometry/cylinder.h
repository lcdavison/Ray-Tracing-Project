#ifndef CYLINDER_H
#define CYLINDER_H

#include <algorithm>

#include "geometry.h"
#include "material/material.h"

/*
 * 	Used for rendering a capped cylinder	
 * */
class Cylinder : public IGeometry 
{
	public:

		Cylinder ( );
		Cylinder ( const Point3&, double, double );

		void			rayhit ( const Ray&, HitResult& );
		bool			shadow_rayhit ( const Ray&, double& );

		void 			set_material ( IMaterial* );

	private:

		void 			test_caps ( const Ray&, HitResult& );
		bool			shadow_test_caps ( const Ray& );

		IMaterial* 		m_material_ptr = nullptr;

		Point3 			m_center;
		double 			m_radius;
		double 			m_height;

		static const double 	m_EPSILON;
};
#endif
