#ifndef BRDF_H
#define BRDF_H

#include "maths/maths.h"
#include "geometry/hitresult.h"

class IBRDF 
{
	public:

		virtual ColourRGB function 	( const HitResult&, const Vector3&, const Vector3& ) = 0;
		virtual ColourRGB reflectance 	( const HitResult&, const Vector3& ) = 0;
};
#endif
