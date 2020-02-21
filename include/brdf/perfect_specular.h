#ifndef PERFECT_SPECULAR_H
#define PERFECT_SPECULAR_H

#include "brdf.h"

class PerfectSpecular : public IBRDF
{
	public:
		
		PerfectSpecular ( );
		PerfectSpecular ( const ColourRGB&, float );

		ColourRGB 	function ( const HitResult&, const Vector3&, const Vector3& );
		ColourRGB 	reflectance ( const HitResult&, const Vector3& );

	private:

		ColourRGB 	m_colour;
		float 		m_coeff;
};
#endif
