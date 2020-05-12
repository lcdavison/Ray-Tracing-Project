#ifndef REFLECTIVE_H
#define REFLECTIVE_H

#include "brdf/brdf.h"

/*
 *	IReflective provides a material with the capabilities for reflecting light
 * */
class IReflective 
{
	public:

		void 	set_reflection_brdf ( IBRDF* p_brdf ) { m_reflection_brdf = p_brdf; }
		IBRDF*	get_reflection_brdf ( ) { return m_reflection_brdf; }

	protected:

		IBRDF*	m_reflection_brdf = nullptr;

};
#endif
