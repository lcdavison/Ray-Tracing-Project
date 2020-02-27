#ifndef REFLECTIVE_H
#define REFLECTIVE_H

#include "brdf/brdf.h"

class IReflective 
{
	public:

		//void	set_reflection_coeff ( float p_coeff ) { m_reflection_brdf_ptr->set_coeff ( p_coeff ); }

		void 	set_reflection_brdf ( IBRDF* p_brdf ) { m_reflection_brdf = p_brdf; }
		IBRDF*	get_reflection_brdf ( ) { return m_reflection_brdf; }

	protected:

		IBRDF*	m_reflection_brdf = nullptr;

};
#endif
