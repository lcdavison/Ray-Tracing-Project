#ifndef BLINN_PHONG_H
#define BLINN_PHONG_H

#include "material.h"
#include "reflective.h"
#include "refractive.h"
#include "glossy.h"

#include "brdf/lambertian.h"
#include "brdf/blinn-phong_specular.h"
#include "brdf/perfect_reflection.h"
#include "brdf/fresnel_reflection.h"
#include "brdf/glossy_reflection.h"

#include "btdf/perfect_refraction.h"
#include "btdf/fresnel_refraction.h"

/*
 *	BlinnPhong is a plastic type material using the Blinn-Phong reflection model
 * */
class BlinnPhong : public IMaterial, public IReflective, public IRefractive, public IGlossy
{
	public:

		BlinnPhong ( );
		BlinnPhong ( const ColourRGB&, float, float, float, float, unsigned char );

		~BlinnPhong ( );

		ColourRGB 			shade ( const HitResult&, const Ray& );
		ColourRGB			shade_arealight ( const HitResult&, const Ray& );

	private:

		Lambertian* 			m_ambient_brdf 	= nullptr;
		Lambertian* 			m_diffuse_brdf 	= nullptr;
		BlinnPhongSpecular* 		m_specular_brdf = nullptr;
};
#endif
