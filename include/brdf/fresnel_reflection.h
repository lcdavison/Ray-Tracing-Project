#ifndef FRESNEL_REFLECTION_H
#define FRESNEL_REFLECTION_H

#include "brdf.h"

/*
 *	Fresnel Reflection reflects light based on the Fresnel equations
 * */
class FresnelReflection : public IBRDF
{
	public:

		FresnelReflection ( );
		FresnelReflection ( float, float );

		ColourRGB 	function 	( const HitResult&, const Vector3&, const Vector3& );
		ColourRGB 	sample_function ( const HitResult&, Vector3&, const Vector3& );
		ColourRGB 	reflectance 	( const HitResult&, const Vector3& );

	private:

		float 		fresnel_coefficient ( const HitResult&, const Vector3& );

		float 		m_exterior_index;	//	Outside medium index of refraction
		float 		m_interior_index; 	//	Inside medium index of refraction
};
#endif
