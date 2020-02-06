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
}

void Scene::render ( )
{
	for ( int y = 0; y < m_pwindow->get_height ( ); ++y )
	{
		for ( int x = 0; x < m_pwindow->get_width ( ); ++x )
		{
			
		}
	}
}

void Scene::update_window ( )
{
	m_pwindow->update ( );
}

HitResult Scene::hit_objects ( const Ray& p_ray )
{
	
}
