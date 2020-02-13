#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "light.h"

class AmbientLight : public ILight 
{
	public:
		
		AmbientLight ( );

		ColourRGB 	radiance ( );
		Vector3 	get_direction ( const Point3& );

	private:

		float 		m_coeff;
		ColourRGB 	m_colour;
};
#endif
