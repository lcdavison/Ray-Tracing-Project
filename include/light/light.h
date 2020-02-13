#ifndef LIGHT_H
#define LIGHT_H

#include "maths/maths.h"

class ILight 
{
	public:

		virtual ColourRGB 	radiance 	( ) = 0;
		virtual Vector3 	get_direction 	( const Point3& ) = 0;

	protected:

		bool 			m_shadows = false;
};
#endif
