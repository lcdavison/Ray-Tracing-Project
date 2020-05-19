#ifndef LIGHT_H
#define LIGHT_H

#include "maths/maths.h"

#include "geometry/hitresult.h"

//	Forward declaration
struct HitResult;

/*
 *	ILight provides a common set of functions for each type of light
 * */
class ILight 
{
	public:

		virtual ColourRGB 	radiance 	( ) = 0;

		virtual bool		in_shadow 	( const Ray&, const HitResult& ) = 0;

		virtual Vector3 	get_direction 	( const Point3& ) = 0;

		bool			casts_shadows 	( ) { return m_shadows; }
		void			set_shadows 	( bool p_value ) { m_shadows = p_value; }

		//	These are used for area lighting
		virtual double 		geometric_factor ( ) 		 { return 1.0; }
		virtual double		probability_density_function ( ) { return 1.0; }

		virtual void		set_num_samples ( unsigned int p_num_samples ) { m_num_samples = p_num_samples; }
		virtual unsigned int	get_num_samples ( ) { return m_num_samples; }

	protected:

		bool 			m_shadows     = false;
		unsigned int		m_num_samples = 1;	//	The number of samples used for area lighting
};
#endif
