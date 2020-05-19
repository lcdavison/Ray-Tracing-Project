#ifndef RECURSIVE_TRACER_H
#define RECURSIVE_TRACER_H

#include "raytracer.h"
#include "geometry/hitresult.h"
#include "scene/scene.h"
#include "material/reflective.h"
#include "material/refractive.h"
#include "material/glossy.h"

/*
 *	The recursive tracer is used to recursively compute reflections
 *	and refractions.
 * */
class RecursiveTracer : public IRayTracer 
{
	public:

		RecursiveTracer ( );
		RecursiveTracer ( Scene* );

		ColourRGB 	trace_ray ( const Ray& );
		ColourRGB 	trace_ray ( const Ray, int, int );

	private:

		Scene* 		m_scene_ptr = nullptr;
};
#endif
