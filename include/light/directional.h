#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "light.h"

/*
 *	DirectionalLight simulates an infinitely far light source producing an even
 *	amount of light from a specific direction
 * */
class DirectionalLight : public ILight 
{
	public:

		DirectionalLight ( );
		DirectionalLight ( const Vector3&, const ColourRGB&, float );

		ColourRGB	radiance 	( );

		bool		in_shadow	( const Ray&, const HitResult& );

		Vector3		get_direction 	( const Point3& );

	private:

		Vector3 	m_direction;
		ColourRGB 	m_colour;
		float 		m_coeff;
};
#endif
