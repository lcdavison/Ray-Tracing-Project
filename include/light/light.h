#ifndef LIGHT_H
#define LIGHT_H

#include "maths/maths.h"

#include "geometry/hitresult.h"

struct HitResult;

class ILight 
{
	public:

		virtual ColourRGB 	radiance 	( ) = 0;

		virtual bool		in_shadow 	( const Ray&, const HitResult& ) = 0;

		virtual Vector3 	get_direction 	( const Point3& ) = 0;

		virtual bool		casts_shadows 	( ) { return m_shadows; }
		virtual void		set_shadows 	( bool p_value ) { m_shadows = p_value; }

	protected:

		bool 			m_shadows = false;
};
#endif
