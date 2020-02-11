#include <iostream>
#include <chrono>

#include "scene/scene.h"
#include "event/event_manager.h"
#include "camera/pinhole_camera.h"
#include "raytracer/direct_tracer.h"

bool _running 	= false;
bool _render 	= false;

int main ( int argc, char** argv )
{
	Scene scene ( 500, 500 );
	
	PinholeCamera* cam = new PinholeCamera ( Point3 ( 50.0, 0.0, 100.0 ), 100.0 );
	cam->construct_basis ( Point3 ( 0.0, 0.0, 0.0 ), Vector3 ( 0.0, 1.0, 0.0 ) );
	cam->set_vpwidth ( 500 );
	cam->set_vpheight ( 500 );
	scene.set_camera ( cam );

	DirectTracer* tracey = new DirectTracer ( &scene );
	scene.set_tracer ( tracey );

	scene.build_scene ( );
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
