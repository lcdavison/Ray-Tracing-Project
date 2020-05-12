#ifndef GLOSSY_H
#define GLOSSY_H

#include "brdf/brdf.h"
#include "brdf/sampled_brdf.h"

/*
 *	IGlossy provides a material with the capabilities for glossy reflections
 * */
class IGlossy 
{
	public:

		void 	set_glossy_brdf ( IBRDF* p_brdf ) { m_glossy_brdf = p_brdf; }
		IBRDF* 	get_glossy_brdf ( ) { return m_glossy_brdf; }

	protected:

		IBRDF*	m_glossy_brdf = nullptr;
};
#endif
