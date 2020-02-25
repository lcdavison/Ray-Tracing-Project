#ifndef PHONG_H
#define PHONG_H

#include "material.h"
#include "brdf/lambertian.h"
#include "brdf/phong_specular.h"
#include "brdf/perfect_specular.h"

class Phong : public IMaterial
{
	public:

		Phong ( );
		Phong ( const ColourRGB&, float, float, float, float );

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

class PhongReflective : public Phong 
{
	public:

		PhongReflective ( );
		PhongReflective ( const ColourRGB&, float, float, float, float, const ColourRGB&, float );

		~PhongReflective ( );

		ColourRGB 		shade 		( const HitResult&, const Ray& );
		ColourRGB		shade_arealight ( const HitResult&, const Ray& );

		IBRDF*			get_diffuse_brdf  ( );
		IBRDF*			get_specular_brdf ( );

	private:

		PerfectSpecular*	m_perfect_specular_brdf = nullptr;
};
#endif
