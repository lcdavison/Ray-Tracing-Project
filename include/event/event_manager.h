#ifndef RT_EVENT_MANAGER_H
#define RT_EVENT_MANAGER_H

#include <queue>

#include "rtevent.h"

/*
 *	RTEventManager handles events which are created throughout the ray tracer
 * */
class RTEventManager
{
	public:

		static void 			handle_events ( );
		static void 			push_event ( RT_EVENT );

	private:

		static std::queue < RT_EVENT > 	m_events;
};
#endif
