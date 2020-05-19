#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "light.h"

/*
 *	PointLight simulates an infinitely small light source positioned in the environment
 * */
class PointLight : public ILight 
{
	public:

		PointLight ( );
		PointLight ( const Point3&, const ColourRGB&, float );

		ColourRGB 	radiance 	( );

		bool		in_shadow 	( const Ray&, const HitResult& );

		Vector3 	get_direction 	( const Point3& );

	private:

		Point3		m_position;
		ColourRGB 	m_colour;
		float 		m_coeff;
};
#endif
