#ifndef EMISSIVE_H
#define EMISSIVE_H

#include "material.h"

class Emissive : public IMaterial 
{
	public:

		Emissive ( );
		Emissive ( const ColourRGB&, float );

		ColourRGB 	shade 		( const HitResult&, const Ray& );
		ColourRGB 	shade_arealight ( const HitResult&, const Ray& );

		IBRDF*		get_diffuse_brdf  ( );
		IBRDF*		get_specular_brdf ( );

		ColourRGB 	get_radiance ( );

	private:

		ColourRGB 	m_colour;
		float		m_coeff;
};
#endif
