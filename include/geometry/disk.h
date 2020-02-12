#ifndef DISK_H
#define DISK_H

#include "maths/maths.h"

class Disk : public IGeometry 
{
	public:
	
		Disk ( );

		bool rayhit ( const Ray&, HitResult& );

	private:

		Vector3 	m_normal;
		Point3		m_center;
		double		m_radius;
};
#endif
