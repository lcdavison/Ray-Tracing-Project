#include <iostream>
#include <chrono>

#include "scene/scene.h"
#include "event/event_manager.h"

bool _running 	= false;
bool _render 	= false;

int main ( int argc, char** argv )
{
	Scene scene ( 500, 500 );

	_running = true;

	while ( _running )
	{
		//	Handle ray tracer events
		RTEventManager::handle_events ( );
		
		scene.update_window ( );
	}

	return 0;
}
