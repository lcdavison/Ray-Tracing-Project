#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <limits>

#include "maths/maths.h"

class IRayTracer 
{
	public:
		virtual ColourRGB trace_ray ( const Ray& ) = 0;
		virtual ColourRGB trace_ray ( const Ray, int, int ) = 0;
};
#endif
