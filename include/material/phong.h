#ifndef PHONG_H
#define PHONG_H

#include "material.h"
#include "reflective.h"
#include "refractive.h"
#include "glossy.h"

#include "brdf/lambertian.h"
#include "brdf/phong_specular.h"
#include "brdf/perfect_reflection.h"
#include "brdf/glossy_reflection.h"

#include "btdf/perfect_refraction.h"

/*
 *	Phong is a plastic type material which uses the Phong reflection model
 * */
class Phong : public IMaterial, public IReflective, public IRefractive, public IGlossy
{
	public:

		Phong ( );
		Phong ( const ColourRGB&, float, float, float, float, unsigned char );

		~Phong ( );

		ColourRGB 		shade 		( const HitResult&, const Ray& );
		ColourRGB		shade_arealight ( const HitResult&, const Ray& );

	private:

		Lambertian* 		m_ambient_brdf 	= nullptr;
		Lambertian* 		m_diffuse_brdf 	= nullptr;
		PhongSpecular* 		m_specular_brdf	= nullptr;
};
#endif
