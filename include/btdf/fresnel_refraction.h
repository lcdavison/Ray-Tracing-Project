#ifndef FRESNEL_REFRACTION_H
#define FRESNEL_REFRACTION_H

#include "btdf.h"

/*
 *	Fresnel Refraction uses the Fresnel equations to compute the amount of
 *	light transmitted through an object
 * */
class FresnelRefraction : public IBTDF
{
	public:

		FresnelRefraction ( );
		FresnelRefraction ( float, float );

		ColourRGB 	function 		  ( const HitResult&, const Vector3&, const Vector3& );
		ColourRGB 	sample_function 	  ( const HitResult&, Vector3&, const Vector3& );
		ColourRGB 	transmittance 		  ( const HitResult&, const Vector3& );

		bool 		total_internal_reflection ( const HitResult&, const Ray& );

	private:

		float 		fresnel_coefficient ( const HitResult&, const Vector3& );

		float 		m_exterior_index;
		float 		m_interior_index;
};
#endif
