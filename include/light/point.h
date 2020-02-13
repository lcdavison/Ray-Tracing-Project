#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "light.h"

class PointLight : public ILight 
{
	public:

		PointLight ( );
		PointLight ( const Point3&, const ColourRGB&, float );

		Vector3 	get_direction ( const Point3& );
		ColourRGB 	radiance ( );

	private:

		Point3		m_position;
		ColourRGB 	m_colour;
		float 		m_coeff;
};
#endif
