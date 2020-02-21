#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

#include <iostream>
#include <chrono>
#include <vector>

#include "maths/maths.h"
#include "event/event_manager.h"

typedef std::chrono::time_point < std::chrono::high_resolution_clock > TimePoint;

//	TODO: Use an SDL_Surface instead and manually blit the surface to the screen

class Window 
{
	public:
		Window ( );
		Window ( unsigned short, unsigned short );

		~Window ( );

		void 					update ( );
		void					present ( );

		void 					set_pixel ( unsigned short, unsigned short, const ColourRGB& );

		unsigned short 				get_width ( );
		unsigned short 				get_height ( );
		const std::vector < ColourRGB >&	get_colourbuffer ( );

	private:

		void create_window ( );

		void handle_events ( );

		SDL_Window* 			m_pwindow = nullptr;
		SDL_Surface*			m_surface_ptr = nullptr;

		std::vector < ColourRGB > 	m_colourbuffer;		//	Stores colours to later be written to an image file

		//	Window dimensions : default 500w x 500h
		unsigned short 			m_width = 500;
		unsigned short 			m_height = 500;

		TimePoint 			m_update_timer = std::chrono::high_resolution_clock::now ( );
};
#endif
