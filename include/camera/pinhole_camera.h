#ifndef PINHOLE_CAM_H
#define PINHOLE_CAM_H

#include "camera.h"

class PinholeCamera : public ICamera 
{
	public:
		PinholeCamera ( );
		PinholeCamera ( const Vector3&, double );

		void 		constuct_basis ( const Point3&, const Vector3& );	//	Compute orthonormal basis
		Ray 		construct_ray ( double, double );

		Point3		get_position ( );

	private:

		double		m_viewplane_dist = 100.0;	//	This will implicitly change the FOV of the camera
		Vector3 	m_basis [ 3 ];			//	Used to transform rays from camera space to world space
};
#endif
