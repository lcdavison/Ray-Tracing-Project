#ifndef PHONG_H
#define PHONG_H

#include "material.h"
#include "reflective.h"
#include "refractive.h"

#include "brdf/lambertian.h"
#include "brdf/phong_specular.h"
#include "brdf/perfect_specular.h"

class Phong : public IMaterial, public IReflective, public IRefractive
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
