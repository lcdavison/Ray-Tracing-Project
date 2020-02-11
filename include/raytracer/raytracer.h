#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <limits>

#include "maths/maths.h"
#include "geometry/hitresult.h"

class IRayTracer 
{
	public:
		virtual ColourRGB trace_ray ( const Ray& ) = 0;
};
#endif
