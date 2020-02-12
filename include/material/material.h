#ifndef MATERIAL_H
#define MATERIAL_H

#include "maths/maths.h"
#include "geometry/hitresult.h"

struct HitResult;

class IMaterial 
{
	public:

		virtual ColourRGB shade ( const HitResult& ) = 0;
};
#endif
