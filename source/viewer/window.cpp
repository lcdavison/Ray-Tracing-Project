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
	SDL_DestroyWindow ( m_window_ptr );

	//	Exit SDL
	SDL_Quit ( );
}

void Window::update ( )
{
	handle_events ( );
}

void Window::present ( )
{
	SDL_UpdateWindowSurface ( m_window_ptr );
}

void Window::create_window ( )
{
	SDL_Init ( SDL_INIT_VIDEO );

	m_window_ptr = SDL_CreateWindow ( "Ray Tracer - Luke Davison", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0 );

	if ( !m_window_ptr )
	{
		std::cout << "Failed to create window" << std::endl;
	}

	m_surface_ptr = SDL_GetWindowSurface ( m_window_ptr );

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
			case SDL_WINDOWEVENT:
				switch ( event.window.event )
				{
					case SDL_WINDOWEVENT_FOCUS_GAINED:
						present ( );
						break;
				}
				break;
		}
	}
}

void Window::set_pixel ( unsigned short p_x, unsigned short p_y, ColourRGB& p_colour )
{
	//	Save colour in colourbuffer
	m_colourbuffer.at ( p_y * m_width + p_x ) = p_colour;

	unsigned int colour_int = p_colour.int_format ( );

	//	Set pixel colour in window
	SDL_LockSurface ( m_surface_ptr );

	unsigned int* pixel = ( unsigned int* ) ( ( unsigned char* ) ( m_surface_ptr->pixels ) + ( ( ( m_height - 1 ) - p_y ) * m_surface_ptr->pitch + p_x * m_surface_ptr->format->BytesPerPixel ) );
	*pixel = ( 255 << 24 ) | colour_int;	//	Alpha | Colour

	SDL_UnlockSurface ( m_surface_ptr );
}

unsigned short Window::get_width ( )
{
	return m_width;
}

unsigned short Window::get_height ( )
{
	return m_height;
}

std::vector < ColourRGB >& Window::get_colourbuffer ( )
{
	return m_colourbuffer;
}
