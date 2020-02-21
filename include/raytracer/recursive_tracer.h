#ifndef RECURSIVE_TRACER_H
#define RECURSIVE_TRACER_H

#include "raytracer.h"
#include "geometry/hitresult.h"
#include "scene/scene.h"

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

		Scene* 		m_pscene = nullptr;
};
#endif
