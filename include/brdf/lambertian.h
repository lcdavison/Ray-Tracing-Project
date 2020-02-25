#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "brdf.h"

class Lambertian : public IBRDF 
{
	public:

		Lambertian ( );
		Lambertian ( const ColourRGB&, float );

		ColourRGB 	function 	( const HitResult&, const Vector3&, const Vector3& );
		ColourRGB 	sample_function ( const HitResult&, Vector3&, const Vector3& );
		ColourRGB 	reflectance 	( const HitResult&, const Vector3& );

		void 		set_coeff 	( float );
		void 		set_colour 	( const ColourRGB& );

	private:

		float 		m_coeff;
		ColourRGB	m_colour;
};
#endif
