#ifndef PHONG_H
#define PHONG_H

#include "material.h"
#include "brdf/lambertian.h"
#include "brdf/phong_specular.h"

class Phong : public IMaterial
{
	public:

		Phong ( );
		Phong ( const ColourRGB&, float, float, float, float );

		~Phong ( );

		ColourRGB 		shade ( const HitResult&, const Ray& );

	private:

		Lambertian* 		m_ambient_brdf 	= nullptr;
		Lambertian* 		m_diffuse_brdf 	= nullptr;
		PhongSpecular* 		m_specular_brdf = nullptr;
};
#endif
