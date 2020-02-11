#ifndef DIRECT_TRACER_H
#define DIRECT_TRACER_H

#include "raytracer.h"
#include "scene/scene.h"

/*
 *	DirectTracer will trace rays for direct illumination only
 * */
class DirectTracer : public IRayTracer 
{
	public:

		DirectTracer ( ) = default;
		DirectTracer ( Scene* );

		ColourRGB trace_ray ( const Ray& );

	private:

		Scene*		m_pscene = nullptr;
};
#endif
