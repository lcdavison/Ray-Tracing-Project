#ifndef CAMERA_H
#define CAMERA_H

#include "maths/maths.h"

class ICamera 
{
	public:

		virtual Ray 	construct_ray ( double, double ) = 0;			//	Construct a ray to a pixel

	protected:

		Point3 		m_position;
};
#endif
