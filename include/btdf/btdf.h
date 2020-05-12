#ifndef BTDF_H
#define BTDF_H

#include "maths/maths.h"
#include "geometry/hitresult.h"

/*
 *	The Bi-Directional Transmission Distribution Function describes how light 
 *	is transmitted through the surface of a material.
 * */
class IBTDF 
{
	public:

		virtual ColourRGB 	function 		  ( const HitResult&, const Vector3&, const Vector3& ) 	= 0;
		virtual ColourRGB 	sample_function 	  ( const HitResult&, Vector3&, const Vector3& ) 	= 0;
		virtual ColourRGB 	transmittance 		  ( const HitResult&, const Vector3& ) 			= 0;
		virtual bool 		total_internal_reflection ( const HitResult&, const Ray& ) = 0;				//	Determines whether a ray is transmitted or fully reflected
};
#endif
