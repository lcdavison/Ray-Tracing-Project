#ifndef PERFECT_REFRACTION_H
#define PERFECT_REFRACTION_H

#include "btdf.h"

/*
 *	Perfect Refraction inaccuratley computes the refraction of light from air to 
 *	another medium, without use of the Fresnel equations
 * */
class PerfectRefraction : public IBTDF 
{
	public:

		PerfectRefraction ( );
		PerfectRefraction ( float, float );

		ColourRGB 	function 		  ( const HitResult&, const Vector3&, const Vector3& );
		ColourRGB 	sample_function 	  ( const HitResult&, Vector3&, const Vector3& );
		ColourRGB 	transmittance 		  ( const HitResult&, const Vector3& );

		bool 		total_internal_reflection ( const HitResult&, const Ray& );
	
	private:

		float 		m_coeff;
		double 		m_index_of_refraction;
};
#endif
