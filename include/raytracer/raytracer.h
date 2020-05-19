#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <limits>

#include "maths/maths.h"

/*
 *	IRayTracer provides a common set of functions for implementing ray tracers
 * */
class IRayTracer 
{
	public:
		virtual ColourRGB trace_ray ( const Ray& ) 	    = 0;
		virtual ColourRGB trace_ray ( const Ray, int, int ) = 0;
};
#endif
