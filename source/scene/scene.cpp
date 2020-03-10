#include "scene/scene.h"

#include <algorithm>

Scene::Scene ( )
{
	m_window_ptr 	    = new Window ( );
	m_imagewriter_ptr   = new PNGWriter ( );
	m_ambient_light_ptr = new AmbientLight ( );
}

Scene::Scene ( unsigned short p_width, unsigned short p_height )
{
	m_window_ptr 	    = new Window ( p_width, p_height );
	m_imagewriter_ptr   = new PNGWriter ( p_width, p_height );
	m_ambient_light_ptr = new AmbientLight ( );
}

Scene::~Scene ( )
{
	//	Clear all geometry
	for ( IGeometry* geometry : m_geometry )
	{
		delete geometry;
	}
	
	if ( m_window_ptr )
	{
		delete m_window_ptr;
		m_window_ptr = nullptr;
	}
}

void Scene::render ( )
{
	auto ray_start = std::chrono::high_resolution_clock::now ( );

	for ( int y = 0; y < m_window_ptr->get_height ( ); ++y )
	{
		for ( int x = 0; x < m_window_ptr->get_width ( ); ++x )
		{
			ColourRGB pixel_colour = ColourRGB ( 0.0f, 0.0f, 0.0f );

			for ( int i = 0; i < m_anti_aliasing_samples; ++i )
			{
				//	Get sample point
				Point3 sample_point = m_sampler_ptr->sample_square ( );

				//	Create a ray
				Ray ray = m_camera_ptr->construct_ray ( x + sample_point.x, y + sample_point.y );

				//	Trace the ray
				pixel_colour = pixel_colour + m_tracer_ptr->trace_ray ( ray, 0, 3 );
			}

			pixel_colour = pixel_colour * ( 1.0f / ( float ) ( m_anti_aliasing_samples ) ) ;

			//	Set colour
			m_window_ptr->set_pixel ( x, y, pixel_colour );
		}

		m_window_ptr->present ( );

	//	std::cout << "Finished Row : " << y << std::endl;
	}

	auto ray_end = std::chrono::high_resolution_clock::now ( );
	std::chrono::duration < double, std::milli > ms = ray_end - ray_start;

	std::cout << "Render Time : " << ms.count ( ) / 1000 << " secs" << std::endl;

	//	Create filename
	std::time_t date = std::time ( nullptr );
	std::string date_str = "./renders/" + std::string ( std::ctime ( &date ) ) + ".png";
	date_str.erase ( std::remove_if ( date_str.begin ( ), date_str.end ( ), [] (char c) { return c == ' ' || c == ':' || c == '\n'; } ), date_str.end ( ) );

	if ( m_imagewriter_ptr->write_image ( date_str, m_window_ptr->get_colourbuffer ( ) ) )
		std::cout << "Success" << std::endl;
}

void Scene::update_window ( )
{
	m_window_ptr->update ( );
}

void Scene::add_geometry ( IGeometry* p_geometry )
{
	m_geometry.push_back ( p_geometry );
}

void Scene::add_light ( ILight* p_light )
{
	m_lights.push_back ( p_light );
}

void Scene::set_tracer ( IRayTracer* p_tracer )
{
	m_tracer_ptr = p_tracer;
}

void Scene::set_camera ( ICamera* p_camera )
{
	m_camera_ptr = p_camera;
}

void Scene::set_sampler ( ISampler* p_sampler )
{
	m_anti_aliasing_samples = p_sampler->get_num_samples ( );
	m_sampler_ptr = p_sampler;
}

AmbientLight* Scene::get_ambient_light ( )
{
	return m_ambient_light_ptr;
}

std::vector < ILight* >& Scene::get_lights ( )
{
	return m_lights;
}

std::vector < IGeometry* >& Scene::get_geometry ( )
{
	return m_geometry;
}
