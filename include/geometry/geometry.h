#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "maths/maths.h"
#include "hitresult.h"

class IGeometry 
{
	public:

		virtual bool 	rayhit ( const Ray&, HitResult& ) = 0;
};
#endif
