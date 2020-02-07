#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "maths/maths.h"
#include "geometry/geometry.h"
#include "geometry/hitresult.h"
#include "viewer/window.h"
#include "camera/camera.h"

#include "raytracer/raytracer.h"

class Scene 
{
	public:
		
		Scene ( );
		Scene ( unsigned short, unsigned short );

		//	Prevent Scene data from being copied or moved
		Scene ( const Scene& ) 	= delete;
		Scene ( Scene&& ) 	= delete;

		~Scene ( );

		void 				build_scene ( );
		void 				render ( );
		void				update_window ( );

		HitResult 			hit_objects ( const Ray& );

		void 				set_tracer ( IRayTracer* );

	private:

		std::vector < IGeometry* > 	m_geometry;
		Window* 			m_pwindow = nullptr;
		
		IRayTracer*			m_ptracer = nullptr;	//	Determines how the rays will be traced
		ICamera*			m_pcamera = nullptr;

		//	Lights etc..

};
#endif
