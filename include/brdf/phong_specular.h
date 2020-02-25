#ifndef PHONG_SPECULAR_H
#define PHONG_SPECULAR_H

#include "brdf.h"

class PhongSpecular : public IBRDF 
{
	public:

		PhongSpecular ( );
		PhongSpecular ( const ColourRGB&, float, float );

		ColourRGB 	function 	( const HitResult&, const Vector3&, const Vector3& );
		ColourRGB 	sample_function ( const HitResult&, Vector3&, const Vector3& );
		ColourRGB 	reflectance 	( const HitResult&, const Vector3& );

	private:

		ColourRGB 	m_colour;
		float 		m_coeff;
		float 		m_exponent;
};
#endif
