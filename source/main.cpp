#include <iostream>
#include <chrono>

#include "scene/scene.h"
#include "event/event_manager.h"
#include "camera/pinhole_camera.h"
#include "raytracer/direct_tracer.h"

#include "geometry/sphere.h"
#include "geometry/plane.h"

#include "material/matte.h"

bool _running 	= false;
bool _render 	= false;

int main ( int argc, char** argv )
{
	Scene scene ( 500, 500 );
	
	PinholeCamera* cam = new PinholeCamera ( Point3 ( 0.0, 0.0, 100.0 ), 100.0 );
	cam->construct_basis ( Point3 ( 0.0, 0.0, 0.0 ), Vector3 ( 0.0, 1.0, 0.0 ) );
	cam->set_vpwidth ( 500 );
	cam->set_vpheight ( 500 );
	scene.set_camera ( cam );

	DirectTracer* tracey = new DirectTracer ( &scene );
	scene.set_tracer ( tracey );

	Matte* s_mat = new Matte ( ColourRGB ( 0.0f, 0.0f, 0.5f ), 0.8f, 0.7f );

	Sphere* sphere = new Sphere ( Point3 ( 0.0, 10.0, -40.0 ), 80.0 );
	sphere->set_material ( s_mat );
	scene.add_geometry ( sphere );

	Matte* p_mat = new Matte ( ColourRGB ( 0.0f, 0.8f, 0.0f ), 0.8f, 0.7f );

	Plane* plane = new Plane ( Point3 ( 0.0, 10.0, -100.0 ), Vector3 ( 0.0, 0.5, 0.5 ) );
	plane->set_material ( p_mat );
	scene.add_geometry ( plane );

	scene.build_scene ( );	//	Change this function
	scene.render ( );

	_running = true;

	while ( _running )
	{
		//	Handle ray tracer events
		RTEventManager::handle_events ( );
		
		scene.update_window ( );
	}

	return 0;
}
