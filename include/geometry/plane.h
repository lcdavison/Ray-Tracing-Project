#ifndef PLANE_H
#define PLANE_H

#include "geometry.h"
#include "material/material.h"

class Plane : public IGeometry
{
	public:
		Plane ( );
		Plane ( const Point3&, const Vector3& );

		void			rayhit ( const Ray&, HitResult& );
		bool			shadow_rayhit ( const Ray&, double& );

		void			set_material ( IMaterial* p_material );

	private:

		IMaterial* 		m_pmaterial = nullptr;
		Point3 			m_point;
		Vector3 		m_normal;

		static const double 	m_EPSILON;
};
#endif
