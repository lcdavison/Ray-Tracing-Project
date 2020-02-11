#include "scene/scene.h"

Scene::Scene ( )
{
	m_pwindow = new Window ( );
}

Scene::Scene ( unsigned short p_width, unsigned short p_height )
{
	m_pwindow = new Window ( p_width, p_height );
}

Scene::~Scene ( )
{
	//	Clear all geometry
	
	if ( m_pwindow )
	{
		delete m_pwindow;
	}
}

void Scene::build_scene ( )
{
	//	Create geometry, lights, materials, etc..
	Plane* plane = new Plane ( Point3 ( -10.0, 0.0, 0.0 ), Vector3 ( 1.0, 0.0, 0.0 ) );
	m_geometry.push_back ( plane );
}

void Scene::render ( )
{
	for ( int y = 0; y < m_pwindow->get_height ( ); ++y )
	{
		for ( int x = 0; x < m_pwindow->get_width ( ); ++x )
		{
			//	Create a ray
			Ray ray = m_pcamera->construct_ray ( x, y );

			//	Trace the ray
			ColourRGB pixel_colour = m_ptracer->trace_ray ( ray );

			//	Set colour
			m_pwindow->set_pixel ( x, y, pixel_colour );
		}
	}
}

void Scene::update_window ( )
{
	m_pwindow->update ( );
}

void Scene::set_tracer ( IRayTracer* p_tracer )
{
	m_ptracer = p_tracer;
}

void Scene::set_camera ( ICamera* p_camera )
{
	m_pcamera = p_camera;
}

const std::vector < IGeometry* >& Scene::get_geometry ( )
{
	return m_geometry;
}
