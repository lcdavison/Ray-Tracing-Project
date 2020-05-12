#ifndef PHONG_SPECULAR_H
#define PHONG_SPECULAR_H

#include "brdf.h"

/*
 * 	Implements the Phong reflection model
 * */
class PhongSpecular : public IBRDF 
{
	public:

		PhongSpecular ( );
		PhongSpecular ( const ColourRGB&, float, float );

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
