#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "light.h"

class DirectionalLight : public ILight 
{
	public:

		DirectionalLight ( );
		DirectionalLight ( const Vector3&, const ColourRGB&, float );

		Vector3		get_direction ( const Point3& );
		ColourRGB	radiance ( );

	private:

		Vector3 	m_direction;
		ColourRGB 	m_colour;
		float 		m_coeff;
};
#endif
