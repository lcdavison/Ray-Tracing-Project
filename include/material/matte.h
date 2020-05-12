#ifndef MATTE_H
#define MATTE_H

#include "material.h"
#include "brdf/lambertian.h"

/*
 *	Matte is a material which simulates perfect diffuse lighting
 * */
class Matte : public IMaterial 
{
	public:

		Matte ( );
		Matte ( const ColourRGB&, float, float );

		~Matte ( );

		ColourRGB	shade 		( const HitResult&, const Ray& );
		ColourRGB	shade_arealight ( const HitResult&, const Ray& );

		void 		set_ambient_coeff ( float );
		void 		set_diffuse_coeff ( float );

		void 		set_colour ( const ColourRGB& );

	private:

		Lambertian* 	m_ambient_brdf = nullptr;		//	Crude approximation of globally reflected light
		Lambertian* 	m_diffuse_brdf = nullptr;		//	Direct illumination from light sources
};
#endif
