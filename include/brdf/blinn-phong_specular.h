#ifndef BLINN_PHONG_SPECULAR_H
#define BLINN_PHONG_SPECULAR_H

#include "brdf.h"

/*
 * 	Implements the Blinn-Phong reflection model
 * */
class BlinnPhongSpecular : public IBRDF
{
	public:

		BlinnPhongSpecular ( );
		BlinnPhongSpecular ( const ColourRGB&, float, float );

		ColourRGB 	function 	( const HitResult&, const Vector3&, const Vector3& );
		ColourRGB 	sample_function ( const HitResult&, Vector3&, const Vector3& );
		ColourRGB 	reflectance 	( const HitResult&, const Vector3& );

		void 		set_colour 	( const ColourRGB& );
		void 		set_coeff 	( float );
		void 		set_exponent 	( float );

	private:

		ColourRGB 	m_colour;
		float 		m_coeff;
		float 		m_exponent;
};
#endif
