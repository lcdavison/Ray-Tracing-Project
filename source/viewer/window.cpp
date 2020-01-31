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

void Window::create_window ( )
{
	m_pwindow = SDL_CreateWindow ( "Ray Tracer - Luke Davison", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0 );

	if ( !m_pwindow )
	{
		std::cout << "Failed to create window" << std::endl;
		//	Do something
	}
}

unsigned short Window::get_width ( )
{
	return m_width;
}

unsigned short Window::get_height ( )
{
	return m_height;
}
