#include <iostream>
#include <chrono>

#include "event/event_manager.h"

#include "scene/scene.h"

#include "camera/pinhole_camera.h"

#include "raytracer/arealight_tracer.h"

#include "geometry/sphere.h"
#include "geometry/plane.h"
#include "geometry/cylinder.h"
#include "geometry/rectangle.h"

#include "material/matte.h"
#include "material/blinn-phong.h"
#include "material/emissive.h"

#include "light/arealight.h"

#include "sampling/sampler.h"
#include "sampling/multijittered_sampler.h"

bool _running 	= false;
bool _render 	= false;

int main ( int argc, char** argv )
{
	//	Setup scene
	Scene scene ( 1024, 576 );

	//	Setup multijittered sampler for Anti-Aliasing
	MultiJitteredSampler sampler ( 16, 2 );
	sampler.generate_samples ( );
	scene.set_sampler ( &sampler );

	//	Setup camera
	PinholeCamera* cam = new PinholeCamera ( Point3 ( 0.0, 80.0, 400.0 ), 150.0 );
	cam->construct_basis ( Point3 ( 0.0, -5.0, 0.0 ), Vector3 ( 0.0, 1.0, 0.0 ) );
	cam->set_vpwidth ( 1024 );
	cam->set_vpheight ( 576 );
	scene.set_camera ( cam );

	//	Setup arealight tracer
	AreaLightTracer* atracer = new AreaLightTracer ( &scene );
	scene.set_tracer ( atracer );

	//	Setup cylinders
	BlinnPhong* c_mat = new BlinnPhong ( ColourRGB ( 1.0f, 0.0f, 0.0f ), 0.1f, 0.6f, 0.4f, 10.0f, 0 );

	Cylinder* cylinder = new Cylinder ( Point3 ( -100.0, 0.0, -80.0 ), 50.0, 100.0 );
	cylinder->set_material ( c_mat );
	scene.add_geometry ( cylinder );

	Cylinder* cylinder_t = new Cylinder ( Point3 ( -100.0, 0.0, 100.0 ), 50.0, 100.0 );
	cylinder_t->set_material ( c_mat );
	scene.add_geometry ( cylinder_t );

	//	Setup sphere	
	BlinnPhong* s_mat = new BlinnPhong ( ColourRGB ( 0.8f, 0.8f, 0.2f ), 0.0f, 0.0f, 0.0f, 5.0f, RT_REFLECTIVE );

	Sphere* sphere = new Sphere ( Point3 ( 40.0, 25.0, 10.0 ), 60.0 );
	sphere->set_material ( s_mat );
	scene.add_geometry ( sphere );

	//	Setup plane	
	Matte* p_mat = new Matte ( ColourRGB ( 0.0f, 0.8f, 0.0f ), 0.3f, 1.0f );

	Plane* plane = new Plane ( Point3 ( 0.0, -50.0, 0.0 ), Vector3 ( 0.0, 1.0, 0.0 ) );
	plane->set_material ( p_mat );
	scene.add_geometry ( plane );

	//	Setup arealight
	Emissive* light_mat = new Emissive ( ColourRGB ( 1.0f, 1.0f, 1.0f ), 80.0f );

	//	Setup light material
	MultiJitteredSampler* samp = new MultiJitteredSampler ( 25, 4 );
	samp->generate_samples ( );

	//	Setup light geometry
	Rectangle* rect = new Rectangle ( Point3 ( 300.0, 160.0, -30.0 ), Vector3 ( 0.0, 0.0, 80.0 ), Vector3 ( 0.0, 80.0, 0.0 ) );
	rect->set_material ( light_mat );
	rect->set_sampler ( samp );
	rect->set_casts_shadows ( false );
	scene.add_geometry ( rect );
	
	AreaLight* light = new AreaLight ( );
	light->set_geometry ( rect );
	light->set_material ( light_mat );
	light->set_num_samples ( 25 );
	light->set_shadows ( true );
	scene.add_light ( light );

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
