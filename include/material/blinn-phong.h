#ifndef BLINN_PHONG_H
#define BLINN_PHONG_H

#include "material.h"
#include "brdf/lambertian.h"
#include "brdf/blinn-phong_specular.h"
#include "brdf/perfect_specular.h"

class BlinnPhong : public IMaterial
{
	public:

		BlinnPhong ( );
		BlinnPhong ( const ColourRGB&, float, float, float, float );

		~BlinnPhong ( );

		ColourRGB 			shade ( const HitResult&, const Ray& );
		ColourRGB			shade_arealight ( const HitResult&, const Ray& );

		IBRDF*				get_diffuse_brdf  ( );
		IBRDF*				get_specular_brdf ( );

	protected:

		Lambertian* 			m_ambient_brdf 	= nullptr;
		Lambertian* 			m_diffuse_brdf 	= nullptr;

	private:

		BlinnPhongSpecular* 		m_specular_brdf = nullptr;
};

class BlinnPhongReflective : public BlinnPhong 
{
	public:

		BlinnPhongReflective ( );
		BlinnPhongReflective ( const ColourRGB&, float, float, float, float, const ColourRGB&, float );

		~BlinnPhongReflective ( );

		ColourRGB 		shade ( const HitResult&, const Ray& );
		ColourRGB		shade_arealight ( const HitResult&, const Ray& );

		IBRDF*			get_diffuse_brdf  ( );
		IBRDF*			get_specular_brdf ( );

	private:

		PerfectSpecular*	m_perfect_specular_brdf = nullptr;
};
#endif
