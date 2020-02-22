#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "geometry.h"
#include "material/material.h"

class Rectangle : public IGeometry 
{
	public:
		Rectangle ( );
		Rectangle ( const Point3&, const Vector3&, double, double );

		void 			rayhit ( const Ray&, HitResult& );
		bool			shadow_rayhit ( const Ray&, double& );

		void 			set_material ( IMaterial* );

	private:

		IMaterial*		m_material_ptr = nullptr;

		Point3 			m_center;
		Vector3 		m_normal;
		double 			m_width;
		double 			m_height;

		static const double 	m_EPSILON;
};
#endif
