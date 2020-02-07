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

		void trace_ray ( const Ray&, HitResult& );

	private:

		Scene*		m_pscene = nullptr;
};
#endif
