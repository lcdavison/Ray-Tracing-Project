#include <iostream>
#include <chrono>

#include "event/event_manager.h"

#include "scene/scene.h"

#include "camera/pinhole_camera.h"

#include "raytracer/direct_tracer.h"
#include "raytracer/recursive_tracer.h"

#include "geometry/sphere.h"
#include "geometry/plane.h"
#include "geometry/disk.h"
#include "geometry/cylinder.h"
#include "geometry/rectangle.h"

#include "material/matte.h"
#include "material/phong.h"
#include "material/blinn-phong.h"

#include "light/directional.h"
#include "light/point.h"

#include "sampling/sampler.h"
#include "sampling/regular_sampler.h"

bool _running 	= false;
bool _render 	= false;

int main ( int argc, char** argv )
{
	Scene scene ( 500, 500 );

	RegularSampler sampler ( 16, 1 );
	sampler.generate_samples ( );
	scene.set_sampler ( &sampler );
	
	PinholeCamera* cam = new PinholeCamera ( Point3 ( 0.0, 10.0, 100.0 ), 200.0 );
	cam->construct_basis ( Point3 ( 0.0, 0.0, 0.0 ), Vector3 ( 0.0, 1.0, 0.0 ) );
	cam->set_vpwidth ( 500 );
	cam->set_vpheight ( 500 );
	scene.set_camera ( cam );

	RecursiveTracer* tracey = new RecursiveTracer ( &scene );
	scene.set_tracer ( tracey );
	
	Phong* c_mat = new Phong ( ColourRGB ( 1.0f, 0.0f, 0.0f ), 0.0f, 0.0f, 0.0f, 10.0f, RT_REFLECTIVE );

	Cylinder* cylinder = new Cylinder ( Point3 ( -60.0, 0.0, -50.0 ), 50.0, 100.0 );
	cylinder->set_material ( c_mat );
	scene.add_geometry ( cylinder );

	BlinnPhong* s_mat = new BlinnPhong ( ColourRGB ( 0.8f, 0.8f, 0.3f ), 0.0f, 0.0f, 0.0f, 5.0f, RT_REFRACTIVE );

	//Sphere* sphere = new Sphere ( Point3 ( 80.0, 25.0, -100.0 ), 80.0 );
	Sphere* sphere = new Sphere ( Point3 ( 50.0, 25.0, -50.0 ), 50.0 );
	sphere->set_material ( s_mat );
	scene.add_geometry ( sphere );

	Phong* mat = new Phong ( ColourRGB ( 0.0f, 0.0f, 1.0f ), 0.2f, 0.8f, 0.2f, 1000.0f, 0 );
	Sphere* st = new Sphere ( Point3 ( 100.0, 25.0, 20.0 ), 25.0 );
	st->set_material ( mat );
	scene.add_geometry ( st );

	Matte* p_mat = new Matte ( ColourRGB ( 0.0f, 0.8f, 0.0f ), 0.1f, 1.0f );

	Plane* plane = new Plane ( Point3 ( 0.0, -50.0, 0.0 ), Vector3 ( 0.0, 1.0, 0.0 ) );
	plane->set_material ( p_mat );
	scene.add_geometry ( plane );

	DirectionalLight* dir_l = new DirectionalLight ( Vector3 ( -0.5, -0.5, 0.0 ), ColourRGB ( 1.0f, 1.0f, 1.0f ), 2.0f );
	dir_l->set_shadows ( true );
	scene.add_light ( dir_l );
	
	PointLight* point_l = new PointLight ( Point3 ( 80.0, 10.0, 40.0 ), ColourRGB ( 1.0f, 1.0f, 1.0f ), 2.0f );
	point_l->set_shadows ( true );
	scene.add_light ( point_l );

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
