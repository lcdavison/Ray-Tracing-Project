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

	MultiJitteredSampler sampler ( 64, 2 );
	sampler.generate_samples ( );
	scene.set_sampler ( &sampler );

	PinholeCamera* cam = new PinholeCamera ( Point3 ( 0.0, 10.0, 100.0 ), 200.0 );
	cam->construct_basis ( Point3 ( 0.0, -5.0, 0.0 ), Vector3 ( 0.0, 1.0, 0.0 ) );
	cam->set_vpwidth ( 1280 );
	cam->set_vpheight ( 720 );
	scene.set_camera ( cam );

	RecursiveTracer* atracer = new RecursiveTracer ( &scene );
	scene.set_tracer ( atracer );

	//	Create Glossy Sphere
	BlinnPhong* glossy_mat = new BlinnPhong ( ColourRGB ( 0.8f, 0.8f, 0.3f ), 0.0f, 0.0f, 0.0f, 25.0f, RT_REFLECTIVE );

	Sphere* sphere = new Sphere ( Point3 ( 0.0, 25.0, -100.0 ), 80.0 );
	sphere->set_material ( glossy_mat );
	scene.add_geometry ( sphere );

	//	Create normal sphere
	Phong* normal_mat = new Phong ( ColourRGB ( 0.8f, 0.0f, 0.0f ), 0.1, 0.3f, 0.0f, 5.0f, RT_REFLECTIVE );

	Sphere* normal_sphere = new Sphere ( Point3 ( -140.0, 25.0, -20.0 ), 60.0 );
	normal_sphere->set_material ( normal_mat );
	scene.add_geometry ( normal_sphere );

	//	Create out of view sphere
	BlinnPhong* outview_mat = new BlinnPhong ( ColourRGB ( 0.0f, 0.0f, 0.8f ), 0.1f, 0.3f, 0.0f, 5.0f, RT_REFRACTIVE );

	Sphere* outview_sphere = new Sphere ( Point3 ( 140.0, 25.0, -20.0 ), 60.0 );
	outview_sphere->set_material ( outview_mat );
	scene.add_geometry ( outview_sphere );

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
