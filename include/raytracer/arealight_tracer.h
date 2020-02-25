#ifndef AREALIGHT_TRACER_H
#define AREALIGHT_TRACER_H

#include "raytracer.h"
#include "scene/scene.h"

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
