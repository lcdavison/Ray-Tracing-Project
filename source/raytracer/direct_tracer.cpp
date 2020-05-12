#include "raytracer/direct_tracer.h"

DirectTracer::DirectTracer ( Scene* p_scene ) : m_scene_ptr ( p_scene )
{
}

ColourRGB DirectTracer::trace_ray ( const Ray& p_ray )
{
	HitResult closest_result;
	double min_distance = std::numeric_limits < double >::max ( );
	
	//	Calculate closest hit point
	for ( IGeometry* geometry : m_scene_ptr->get_geometry ( ) )
	{
		HitResult hit_data;
		geometry->rayhit ( p_ray, hit_data );

		if ( hit_data.m_hit && hit_data.m_distance < min_distance )
		{
			min_distance 	= hit_data.m_distance;
			closest_result 	= hit_data;
		}
	}

	//	Check if ray hit any geometry
	if ( closest_result.m_hit )
	{
		closest_result.m_hitpoint 		= p_ray.get_point ( closest_result.m_distance );
		closest_result.m_ambient_light_ptr 	= m_scene_ptr->get_ambient_light ( );
		closest_result.m_lights_ptr 		= &( m_scene_ptr->get_lights ( ) );
		closest_result.m_geometry_ptr		= &( m_scene_ptr->get_geometry ( ) );

		return closest_result.m_material_ptr->shade ( closest_result, p_ray );
	}

	return ColourRGB ( 0.4f, 0.4f, 0.4f );	//	Change this to return a background colour instead
}

ColourRGB DirectTracer::trace_ray ( const Ray p_ray, int p_depth, int p_max_depth )
{
	return DirectTracer::trace_ray ( p_ray );
}
