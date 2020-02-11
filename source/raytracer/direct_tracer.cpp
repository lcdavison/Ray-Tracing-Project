#include "raytracer/direct_tracer.h"

#include <iostream>

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
		return ColourRGB ( 0.0f, 1.0f, 0.0f );
	}

	return ColourRGB ( 0.0f, 0.0f, 0.0f );
}
