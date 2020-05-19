#ifndef DISK_H
#define DISK_H

#include "geometry.h"
#include "material/material.h"

/*
 *	Used for rendering a flat disk
 * */
class Disk : public IGeometry 
{
	public:
	
		Disk ( );
		Disk ( const Point3&, const Vector3&, double );

		void			rayhit ( const Ray&, HitResult& );
		bool			shadow_rayhit ( const Ray&, double& );

		void 			set_material ( IMaterial* );

	private:

		IMaterial*		m_material_ptr = nullptr;

		Vector3 		m_normal;
		Point3			m_center;
		double			m_radius;

		static const double 	m_EPSILON;
};
#endif
