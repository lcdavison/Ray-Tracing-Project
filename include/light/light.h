#ifndef LIGHT_H
#define LIGHT_H

#include "maths/maths.h"

class ILight 
{
	public:

		virtual ColourRGB 	radiance 	( ) = 0;
		virtual Vector3 	get_direction 	( ) = 0;

	private:

		bool 			m_shadows = false;
};
#endif
