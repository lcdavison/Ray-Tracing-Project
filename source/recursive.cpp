#include <iostream>
#include <chrono>

#include "event/event_manager.h"

#include "scene/scene.h"

#include "camera/pinhole_camera.h"

#include "raytracer/recursive_tracer.h"

#include "geometry/sphere.h"
#include "geometry/plane.h"
#include "geometry/cylinder.h"
#include "geometry/rectangle.h"

#include "material/matte.h"
#include "material/phong.h"
#include "material/blinn-phong.h"
#include "material/emissive.h"

#include "light/directional.h"
#include "light/point.h"

#include "sampling/sampler.h"
#include "sampling/regular_sampler.h"
#include "sampling/multijittered_sampler.h"

bool _running 	= false;
bool _render 	= false;

int main ( int argc, char** argv )
{
	Scene scene ( 1280, 720 );

	//	Create sampler for anti-aliasing
	MultiJitteredSampler sampler ( 64, 2 );
	sampler.generate_samples ( );
	scene.set_sampler ( &sampler );

	//	Create camera
	PinholeCamera* cam = new PinholeCamera ( Point3 ( 0.0, 10.0, 100.0 ), 200.0 );
	cam->construct_basis ( Point3 ( 0.0, -5.0, 0.0 ), Vector3 ( 0.0, 1.0, 0.0 ) );
	cam->set_vpwidth ( 1280 );
	cam->set_vpheight ( 720 );
	scene.set_camera ( cam );

	//	Create recursive ray tracer
	RecursiveTracer* atracer = new RecursiveTracer ( &scene );
	scene.set_tracer ( atracer );

	//	Create Reflective Sphere
	BlinnPhong* reflective_mat = new BlinnPhong ( ColourRGB ( 0.8f, 0.8f, 0.3f ), 0.0f, 0.0f, 0.0f, 25.0f, RT_REFLECTIVE );

	Sphere* reflect_one = new Sphere ( Point3 ( 0.0, 25.0, -100.0 ), 80.0 );
	reflect_one->set_material ( reflective_mat );
	scene.add_geometry ( reflect_one );

	//	Create second reflective sphere
	Phong* normal_mat = new Phong ( ColourRGB ( 0.8f, 0.0f, 0.0f ), 0.1, 0.3f, 0.0f, 5.0f, RT_REFLECTIVE );

	Sphere* reflect_two = new Sphere ( Point3 ( -140.0, 25.0, -20.0 ), 60.0 );
	reflect_two->set_material ( normal_mat );
	scene.add_geometry ( reflect_two );

	//	Create refractive sphere
	BlinnPhong* refractive_mat = new BlinnPhong ( ColourRGB ( 0.0f, 0.0f, 0.8f ), 0.1f, 0.3f, 0.0f, 5.0f, RT_REFRACTIVE );

	Sphere* refractive_sphere = new Sphere ( Point3 ( 140.0, 25.0, -20.0 ), 60.0 );
	refractive_sphere->set_material ( refractive_mat );
	scene.add_geometry ( refractive_sphere );

	//	PLANE
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
