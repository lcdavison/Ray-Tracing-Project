#include "event/event_manager.h"

extern bool _running;
extern bool _render;

std::queue < RT_EVENT > RTEventManager::m_events;

void RTEventManager::handle_events ( )
{
	//	Handle all events in queue
	while ( !m_events.empty ( ) )
	{
		RT_EVENT event = m_events.front ( );
		m_events.pop ( );

		//	Check event type
		switch ( event )
		{
			case RT_QUIT:
				::_running = false;
				return;
			case RT_RENDER:
				::_render = true;
				return;
		}
	}
}

void RTEventManager::push_event ( RT_EVENT p_event )
{
	m_events.push ( p_event );
}
