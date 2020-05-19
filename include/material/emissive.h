#ifndef EMISSIVE_H
#define EMISSIVE_H

#include "material.h"

/*
 *	Emissive material is used for AreaLight sources which emit a constant colour
 *	across their surface
 * */
class Emissive : public IMaterial 
{
	public:

		Emissive ( );
		Emissive ( const ColourRGB&, float );

		ColourRGB 	shade 		( const HitResult&, const Ray& );
		ColourRGB 	shade_arealight ( const HitResult&, const Ray& );

		ColourRGB 	get_radiance ( );

	private:

		ColourRGB 	m_colour;
		float		m_coeff;
};
#endif
