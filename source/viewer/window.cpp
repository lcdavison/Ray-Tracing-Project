#include "viewer/window.h"

Window::Window ( ) 
{
	this->create_window ( );
}

Window::Window ( unsigned short p_width, unsigned short p_height ) : m_width ( p_width ), m_height ( p_height )
{
	this->create_window ( );
}

Window::~Window ( ) 
{
	SDL_DestroyWindow ( m_pwindow );
}

void Window::update ( )
{
	handle_events ( );

	/*TimePoint now = std::chrono::high_resolution_clock::now ( );
	auto elapsed = std::chrono::duration_cast < std::chrono::milliseconds > ( now - m_update_timer );

	if ( elapsed.count ( ) >= 1000 )
	{
		m_update_timer = std::chrono::high_resolution_clock::now ( );
		SDL_RenderPresent ( m_prenderer );
	}*/
}

void Window::present ( )
{
	SDL_UpdateWindowSurface ( m_pwindow );
}

void Window::create_window ( )
{
	m_pwindow = SDL_CreateWindow ( "Ray Tracer - Luke Davison", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0 );

	if ( !m_pwindow )
	{
		std::cout << "Failed to create window" << std::endl;
		//	Do something
	}

	m_surface_ptr = SDL_GetWindowSurface ( m_pwindow );

	m_colourbuffer.resize ( m_width * m_height, ColourRGB ( 0.0f, 0.0f, 0.0f ) );
}

void Window::handle_events ( ) 
{
	SDL_Event event;

	while ( SDL_PollEvent ( &event ) )
	{
		switch ( event.type )
		{
			case SDL_QUIT:
				RTEventManager::push_event ( RT_QUIT );
				return;
		}
	}
}

void Window::set_pixel ( unsigned short p_x, unsigned short p_y, const ColourRGB& p_colour )
{
	m_colourbuffer.at ( p_y * m_width + p_x ) = p_colour;

	unsigned int colour_int = p_colour.int_format ( );

	unsigned int* pixel = ( unsigned int * ) ( ( unsigned char* ) ( m_surface_ptr->pixels ) + ( ( ( m_height ) - p_y ) * m_surface_ptr->pitch + p_x * m_surface_ptr->format->BytesPerPixel ) );
	*pixel = ( 255 << 24 ) | colour_int;
}

unsigned short Window::get_width ( )
{
	return m_width;
}

unsigned short Window::get_height ( )
{
	return m_height;
}

const std::vector < ColourRGB >& Window::get_colourbuffer ( )
{
	return m_colourbuffer;
}
