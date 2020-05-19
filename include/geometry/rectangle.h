#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "geometry.h"
#include "light_geometry.h"
#include "material/material.h"

/*
 *	Used for rendering a flat rectangle
 * */
class Rectangle : public IGeometry, public ILightGeometry 
{
	public:
		Rectangle ( );
		Rectangle ( const Point3&, const Vector3&, const Vector3& );

		void 			rayhit ( const Ray&, HitResult& );
		bool			shadow_rayhit ( const Ray&, double& );

		void 			set_material ( IMaterial* );

		Point3 			sample ( );
		Vector3			sample_normal ( const Point3& );

	private:

		IMaterial*		m_material_ptr = nullptr;

		Point3			m_lower_left;

		Vector3			m_width;
		Vector3			m_height;
		Vector3 		m_normal;

		static const double 	m_EPSILON;
};
#endif
