#include "raytracer/direct_tracer.h"

DirectTracer::DirectTracer ( Scene* p_scene ) : m_pscene ( p_scene )
{
}

ColourRGB DirectTracer::trace_ray ( const Ray& p_ray )
{
	HitResult closest_result;
	double min_distance = std::numeric_limits < double >::max ( );
	
	for ( IGeometry* geometry : m_pscene->get_geometry ( ) )
	{
		HitResult hit_data;
		geometry->rayhit ( p_ray, hit_data );

		if ( hit_data.m_hit && hit_data.m_distance < min_distance )
		{
			min_distance = hit_data.m_distance;
			closest_result = hit_data;
		}
	}

	if ( closest_result.m_hit )
	{
		closest_result.m_hitpoint 	= p_ray.get_point ( closest_result.m_distance );
		closest_result.m_pambient_light = m_pscene->get_ambient_light ( );
		closest_result.m_plights 	= &( m_pscene->get_lights ( ) );
		closest_result.m_pgeometry	= &( m_pscene->get_geometry ( ) );

		return closest_result.m_pmaterial->shade ( closest_result, p_ray );
	}

	return ColourRGB ( 0.2f, 0.2f, 0.2f );	//	Change this to return a background colour instead
}

ColourRGB DirectTracer::trace_ray ( const Ray p_ray, int p_depth, int p_max_depth )
{
	return DirectTracer::trace_ray ( p_ray );
}
