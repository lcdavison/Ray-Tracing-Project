#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "maths/maths.h"
#include "hitresult.h"

struct HitResult;

/*
 *	IGeometry provides a common set of functions for creating geometry for rendering
 * */
class IGeometry 
{
	public:

		virtual void	rayhit 		( const Ray&, HitResult& ) = 0;		//	Tests for primary ray intersection
		virtual bool	shadow_rayhit 	( const Ray&, double& ) = 0;		//	Tests for shadow ray intersection

		void 		set_casts_shadows ( bool p_value ) { m_casts_shadows = p_value; }
		bool		casts_shadows 	  ( ) 		   { return m_casts_shadows; }

	protected:

		bool 		m_casts_shadows = true;
};
#endif
