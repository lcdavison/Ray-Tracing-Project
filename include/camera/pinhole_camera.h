#ifndef PINHOLE_CAM_H
#define PINHOLE_CAM_H

#include "camera.h"

/*
 *	The pinhole camera is a standard 3D camera which supports arbitrary orientations
 *	using an orthonormal basis
 * */
class PinholeCamera : public ICamera 
{
	public:
		PinholeCamera ( );
		PinholeCamera ( const Point3&, double );

		void 		construct_basis ( const Point3&, const Vector3& );
		Ray 		construct_ray ( double, double );

	private:

		double		m_viewplane_dist = 100.0;	//	This will implicitly change the FOV of the camera
		Vector3 	m_basis [ 3 ];			//	Used to transform rays from camera space to world space
};
#endif
