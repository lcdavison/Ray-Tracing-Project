#ifndef BRDF_H
#define BRDF_H

#include "maths/maths.h"
#include "geometry/hitresult.h"

//	Forward declaration
struct HitResult;

/*
 *	The IBRDF interface provides a common set of functions for all Bi-Directional Reflection Distribution Functions
 *	implemented.
 * */
class IBRDF 
{
	public:

		virtual ColourRGB 	function 	( const HitResult&, const Vector3&, const Vector3& ) = 0;	//	Main BRDF function
		virtual ColourRGB 	sample_function ( const HitResult&, Vector3&, const Vector3& ) = 0;		//	Some BRDF's only reflect light in a refined set of directions
		virtual ColourRGB 	reflectance 	( const HitResult&, const Vector3& ) = 0;			//	Describes the effectiveness of reflection
};
#endif
