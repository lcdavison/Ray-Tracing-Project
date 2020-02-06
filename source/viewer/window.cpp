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
	SDL_DestroyRenderer ( m_prenderer );
}

void Window::update ( )
{
	handle_events ( );
	SDL_RenderPresent ( m_prenderer );
}

void Window::create_window ( )
{
	m_pwindow = SDL_CreateWindow ( "Ray Tracer - Luke Davison", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0 );

	if ( !m_pwindow )
	{
		std::cout << "Failed to create window" << std::endl;
		//	Do something
	}

	m_prenderer = SDL_CreateRenderer ( m_pwindow, -1, SDL_RENDERER_ACCELERATED );

	if ( !m_prenderer )
	{
		std::cout << "Failed to create SDL renderer" << std::endl;
		//	Do something
	}
}

void Window::handle_events ( ) 
{
	SDL_Event event;

	while ( SDL_PollEvent ( &event ) )
	{
		switch ( event.type )
		{
			case SDL_QUIT:
				//	TODO: Post a quit event to an event queue 
				return;
		}
	}
}

void Window::set_pixel ( unsigned short p_x, unsigned short p_y, const ColourRGB& p_colour )
{
	m_colourbuffer.at ( p_y * m_width + p_x ) = p_colour;
}

unsigned short Window::get_width ( )
{
	return m_width;
}

unsigned short Window::get_height ( )
{
	return m_height;
}
