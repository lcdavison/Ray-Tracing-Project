#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

#include <iostream>
#include <chrono>
#include <vector>

#include "maths/maths.h"
#include "event/event_manager.h"

typedef std::chrono::time_point < std::chrono::high_resolution_clock > TimePoint;

class Window 
{
	public:
		Window ( );
		Window ( unsigned short, unsigned short );

		~Window ( );

		void 			update ( );

		void 			set_pixel ( unsigned short, unsigned short, const ColourRGB& );

		unsigned short 		get_width ( );
		unsigned short 		get_height ( );

	private:

		void create_window ( );

		void handle_events ( );

		SDL_Window* 			m_pwindow = nullptr;
		SDL_Renderer*			m_prenderer = nullptr;

		std::vector < ColourRGB > 	m_colourbuffer;		//	Stores colours to later be written to an image file

		//	Window dimensions : default 500w x 500h
		unsigned short 			m_width = 500;
		unsigned short 			m_height = 500;

		TimePoint 			m_update_timer = std::chrono::high_resolution_clock::now ( );
};
#endif
