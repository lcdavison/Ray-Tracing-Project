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

class Phong : public IMaterial, public IReflective, public IRefractive, public IGlossy
{
	public:

		Phong ( );
		Phong ( const ColourRGB&, float, float, float, float, unsigned char );

		~Phong ( );

		ColourRGB 		shade 		( const HitResult&, const Ray& );
		ColourRGB		shade_arealight ( const HitResult&, const Ray& );

		IBRDF*			get_diffuse_brdf  ( );
		IBRDF*			get_specular_brdf ( );

	protected:

		Lambertian* 		m_ambient_brdf 		= nullptr;
		Lambertian* 		m_diffuse_brdf 		= nullptr;

	private:

		PhongSpecular* 		m_specular_brdf 	= nullptr;
};
#endif
