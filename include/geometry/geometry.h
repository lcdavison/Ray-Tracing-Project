#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "maths/maths.h"
#include "hitresult.h"

class Geometry 
{
	public:
		Geometry ( ) = default;

		virtual bool rayhit ( const Ray&, HitResult& );
};
#endif
