#ifndef AREALIGHT_TRACER_H
#define AREALIGHT_TRACER_H

#include "raytracer.h"
#include "scene/scene.h"
#include "material/reflective.h"
#include "material/refractive.h"
#include "material/glossy.h"

/*
 *	AreaLightTracer is a ray tracer primarily designed for use with AreaLights
 * */
class AreaLightTracer : public IRayTracer 
{
	public:

		AreaLightTracer ( Scene* );

		ColourRGB 	trace_ray ( const Ray& );
		ColourRGB 	trace_ray ( const Ray, int, int );

	private:

		Scene* 		m_scene_ptr;
};
#endif
