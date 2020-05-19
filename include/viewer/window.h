#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

#include <iostream>
#include <chrono>
#include <vector>

#include "maths/maths.h"
#include "event/event_manager.h"

/*
 *	Window is used to handle the viewing of the rendering process
 * */
class Window 
{
	public:
		Window ( );
		Window ( unsigned short, unsigned short );

		~Window ( );

		void 					update ( );
		void					present ( );

		void 					set_pixel ( unsigned short, unsigned short, ColourRGB& );

		unsigned short 				get_width ( );
		unsigned short 				get_height ( );
		std::vector < ColourRGB >&		get_colourbuffer ( );

	private:

		void create_window ( );

		void handle_events ( );

		SDL_Window* 			m_window_ptr 	= nullptr;
		SDL_Surface*			m_surface_ptr 	= nullptr;

		std::vector < ColourRGB > 	m_colourbuffer;		//	Stores colours to later be written to an image file

		//	Window dimensions : default 500w x 500h
		unsigned short 			m_width  = 500;
		unsigned short 			m_height = 500;
};
#endif
