#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "light.h"

//	Forward declaration
struct HitResult;

/*
 *	Crudely approximates ambient light present in the environment
 * */
class AmbientLight : public ILight 
{
	public:
		
		AmbientLight ( );

		ColourRGB 	radiance 	( );

		bool		in_shadow 	( const Ray&, const HitResult& );

		Vector3 	get_direction 	( const Point3& );

	private:

		float 		m_coeff;
		ColourRGB 	m_colour;
};
#endif
