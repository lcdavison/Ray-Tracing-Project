#include "camera/pinhole_camera.h"

PinholeCamera::PinholeCamera ( ) : m_viewplane_dist ( 100.0 ) 
{
	m_position = Point3 ( 0.0, 0.0, 100.0 );
}

PinholeCamera::PinholeCamera ( const Point3& p_position, double p_vpdist ) : m_viewplane_dist ( p_vpdist )
{
	m_position = p_position;
}

void PinholeCamera::construct_basis ( const Point3& p_target, const Vector3& p_world_up )
{
	//	Direction from target to camera
	Vector3 target_to_cam = m_position - p_target;
	target_to_cam.normalize ( );

	m_basis [ 0 ] = cross ( p_world_up, target_to_cam );		//	x-axis
	m_basis [ 1 ] = cross ( target_to_cam, m_basis [ 0 ] );		//	y-axis
	m_basis [ 2 ] = target_to_cam;					//	z-axis
}

Ray PinholeCamera::construct_ray ( double p_pixelx, double p_pixely )
{
	//	Remap coordinates so (0,0) is the center of the screen
	double x = p_pixelx - ( ( m_viewplane_width - 1 ) * 0.5 );	
	double y = p_pixely - ( ( m_viewplane_height - 1 ) * 0.5 );

	//	Compute ray direction
	Vector3 ray_dir ( x, y, -m_viewplane_dist );									//	Camera is origin of view space
	ray_dir = ( ray_dir.x * m_basis [ 0 ] ) + ( ray_dir.y * m_basis [ 1 ] ) + ( ray_dir.z * m_basis [ 2 ] );	//	Transform ray into world space	- applies rotation
	ray_dir.normalize ( );

	return Ray ( m_position, ray_dir );
}
