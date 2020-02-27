#ifndef CAMERA_H
#define CAMERA_H

#include "maths/maths.h"

class ICamera 
{
	public:

		virtual void	construct_basis ( const Point3&, const Vector3& ) 	= 0;	//	Construct orthonormal basis
		virtual Ray 	construct_ray 	( double, double ) 			= 0;	//	Construct a ray to a pixel

		void 		set_vpwidth  	( unsigned int p_width ) { m_viewplane_width = p_width; }
		void 		set_vpheight  	( unsigned int p_height ) { m_viewplane_height = p_height; }

		unsigned int	get_vpwidth  	( ) 	const { return m_viewplane_width; }	//	Get viewplane width
		unsigned int 	get_vpheight 	( ) 	const { return m_viewplane_height; }	//	Get viewplane height
		Point3		get_position 	( )	const { return m_position; }		//	Get camera position

	protected:

		unsigned int 	m_viewplane_width;
		unsigned int	m_viewplane_height;
		Point3 		m_position;
};
#endif
