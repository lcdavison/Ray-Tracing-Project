#include <iostream>
#include <chrono>

#include "event/event_manager.h"

#include "scene/scene.h"

#include "camera/pinhole_camera.h"

#include "raytracer/direct_tracer.h"

#include "geometry/sphere.h"
#include "geometry/plane.h"
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
	//	Create Scene
	Scene scene ( 1280, 720 );

	//	Setup sampler for Anti-Aliasing
	RegularSampler sampler ( 16, 1 );
	sampler.generate_samples ( );
	scene.set_sampler ( &sampler );
	
	//	Construct Camera
	PinholeCamera* cam = new PinholeCamera ( Point3 ( 0.0, 10.0, 100.0 ), 200.0 );
	cam->construct_basis ( Point3 ( 0.0, 0.0, 0.0 ), Vector3 ( 0.0, 1.0, 0.0 ) );
	cam->set_vpwidth ( 1280 );
	cam->set_vpheight ( 720 );
	scene.set_camera ( cam );

	//	Setup Ray Tracer
	DirectTracer* tracey = new DirectTracer ( &scene );
	scene.set_tracer ( tracey );
	
	//	Create cylinder
	Phong* c_mat = new Phong ( ColourRGB ( 1.0f, 0.0f, 0.0f ), 0.1f, 0.5f, 0.5f, 10.0f, 0 );

	Cylinder* cylinder = new Cylinder ( Point3 ( -60.0, 0.0, -50.0 ), 50.0, 100.0 );
	cylinder->set_material ( c_mat );
	scene.add_geometry ( cylinder );

	//	Create Sphere
	BlinnPhong* s_mat = new BlinnPhong ( ColourRGB ( 0.8f, 0.8f, 0.3f ), 0.1f, 0.5f, 0.5f, 5.0f, 0 );

	Sphere* sphere = new Sphere ( Point3 ( 50.0, 25.0, -50.0 ), 50.0 );
	sphere->set_material ( s_mat );
	scene.add_geometry ( sphere );

	//	Create Plane
	Matte* p_mat = new Matte ( ColourRGB ( 0.0f, 0.8f, 0.0f ), 0.1f, 1.0f );

	Plane* plane = new Plane ( Point3 ( 0.0, -50.0, 0.0 ), Vector3 ( 0.0, 1.0, 0.0 ) );
	plane->set_material ( p_mat );
	scene.add_geometry ( plane );

	//	Create directional light
	DirectionalLight* dir_l = new DirectionalLight ( Vector3 ( -0.5, -0.5, 0.0 ), ColourRGB ( 1.0f, 1.0f, 1.0f ), 2.0f );
	dir_l->set_shadows ( true );
	scene.add_light ( dir_l );
	
	//	Create point light
	PointLight* point_l = new PointLight ( Point3 ( 80.0, 10.0, 40.0 ), ColourRGB ( 1.0f, 1.0f, 1.0f ), 2.0f );
	point_l->set_shadows ( true );
	scene.add_light ( point_l );

	//	Render scene
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
