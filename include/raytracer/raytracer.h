#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "maths/maths.h"
#include "geometry/hitresult.h"

class IRayTracer 
{
	public:
		virtual void trace_ray ( const Ray&, HitResult& ) = 0;
};
#endif
