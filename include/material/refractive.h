#ifndef REFRACTIVE_H
#define REFRACTIVE_H

#include "btdf/btdf.h"

/*
 *	IRefractive provides a material with the capabilities for transmitting light
 * */
class IRefractive 
{
	public:

		void 	set_refraction_btdf ( IBTDF* p_btdf ) { m_refraction_btdf = p_btdf; }
		IBTDF*	get_refraction_btdf ( ) { return m_refraction_btdf; }

	protected:

		IBTDF* m_refraction_btdf;
};
#endif
