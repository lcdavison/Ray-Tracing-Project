#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "maths/maths.h"

#include "geometry/geometry.h"

#include "viewer/window.h"

#include "camera/camera.h"

#include "raytracer/raytracer.h"

#include "light/light.h"
#include "light/ambient.h"

class Scene 
{
	public:
		
		Scene ( );
		Scene ( unsigned short, unsigned short );

		//	Prevent Scene data from being copied or moved
		Scene ( const Scene& ) 	= delete;
		Scene ( Scene&& ) 	= delete;

		~Scene ( );

		void 					build_scene ( );
		void 					render ( );
		void					update_window ( );

		void 					add_geometry 	( IGeometry* );
		void					add_light	( ILight* );

		void 					set_tracer ( IRayTracer* );
		void					set_camera ( ICamera* );

		AmbientLight*				get_ambient_light 	( );
		std::vector < IGeometry* >&		get_geometry		( );
		std::vector < ILight* >&		get_lights		( );

	private:

		std::vector < IGeometry* > 		m_geometry;

		std::vector < ILight* >			m_lights;
		AmbientLight*				m_pambient_light = nullptr;

		Window* 				m_pwindow = nullptr;
		
		IRayTracer*				m_ptracer = nullptr;	//	Determines how the rays will be traced
		ICamera*				m_pcamera = nullptr;


};
#endif
