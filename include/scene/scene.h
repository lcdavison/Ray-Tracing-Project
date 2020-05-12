#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <chrono>

#include "maths/maths.h"

#include "geometry/geometry.h"

#include "viewer/window.h"

#include "camera/camera.h"

#include "raytracer/raytracer.h"

#include "light/light.h"
#include "light/ambient.h"

#include "image/imagewriter.h"
#include "image/pngwriter.h"

#include "sampling/sampler.h"

/*
 *	Scene stores all data required to render the geometry
 * */
class Scene 
{
	public:
		
		Scene ( );
		Scene ( unsigned short, unsigned short );

		//	Prevent Scene data from being copied or moved
		Scene ( const Scene& ) 	= delete;
		Scene ( Scene&& ) 	= delete;

		~Scene ( );

		void 					render ( );
		void					update_window ( );

		void 					add_geometry 	( IGeometry* );
		void					add_light	( ILight* );

		void 					set_tracer  ( IRayTracer* );
		void					set_camera  ( ICamera* );
		void					set_sampler ( ISampler* );

		AmbientLight*				get_ambient_light 	( );
		std::vector < IGeometry* >&		get_geometry		( );
		std::vector < ILight* >&		get_lights		( );

	private:

		unsigned int 				m_anti_aliasing_samples;

		std::vector < IGeometry* > 		m_geometry;
		std::vector < ILight* >			m_lights;

		AmbientLight*				m_ambient_light_ptr 	= nullptr;

		Window* 				m_window_ptr 		= nullptr;
		
		IRayTracer*				m_tracer_ptr 		= nullptr;	//	Determines how the rays will be traced
		ICamera*				m_camera_ptr 		= nullptr;	//	Determines the viewing parameters
		IImageWriter*				m_imagewriter_ptr 	= nullptr;	//	Determines the output format of an image
		ISampler*				m_sampler_ptr		= nullptr;	//	Generate sample points for anti-aliasing
};
#endif
