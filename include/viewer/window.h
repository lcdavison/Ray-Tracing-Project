#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <iostream>

class Window 
{
	public:
		Window ( );
		Window ( unsigned short, unsigned short );

		~Window ( );

		unsigned short get_width ( );
		unsigned short get_height ( );

	private:

		void create_window ( );

		SDL_Window* m_pwindow;

		//	Window dimensions : default 500w x 500h
		unsigned short m_width = 500;
		unsigned short m_height = 500;
};
#endif
