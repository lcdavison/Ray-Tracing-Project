#ifndef CAMERA_H
#define CAMERA_H

#include "maths/maths.h"

class ICamera 
{
	public:

		virtual void	construct_basis ( const Point3&, const Vector3& ) 	= 0;	//	Construct orthonormal basis
		virtual Ray 	construct_ray ( double, double ) 			= 0;	//	Construct a ray to a pixel

		virtual unsigned int	get_vpwidth  ( ) 	const { return m_viewplane_width; }	//	Get viewplane width
		virtual unsigned int 	get_vpheight ( ) 	const { return m_viewplane_height; }	//	Get viewplane height
		virtual Point3		get_position ( )	const { return m_position; }		//	Get camera position

	protected:

		unsigned int 	m_viewplane_width;
		unsigned int	m_viewplane_height;
		Point3 		m_position;
};
#endif
