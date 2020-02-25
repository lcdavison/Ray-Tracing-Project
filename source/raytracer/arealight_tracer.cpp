#include "raytracer/arealight_tracer.h"

AreaLightTracer::AreaLightTracer ( Scene* p_scene ) : m_scene_ptr ( p_scene ) { }

ColourRGB AreaLightTracer::trace_ray ( const Ray& p_ray )
{
	return ColourRGB::BLACK;
}

ColourRGB AreaLightTracer::trace_ray ( const Ray p_ray, int p_depth, int p_max_depth )
{
	if ( p_depth > p_max_depth )
		return ColourRGB::BLACK;

	//	Find closest hit
	HitResult closest_result;
	double min_distance = std::numeric_limits < double >::max ( );
	
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

	if ( closest_result.m_hit )
	{
		closest_result.m_hitpoint 		= p_ray.get_point ( closest_result.m_distance );
		closest_result.m_ambient_light_ptr 	= m_scene_ptr->get_ambient_light ( );
		closest_result.m_lights_ptr 		= &( m_scene_ptr->get_lights ( ) );
		closest_result.m_geometry_ptr		= &( m_scene_ptr->get_geometry ( ) );

		if ( closest_result.m_material_ptr->get_flags ( ) & RT_REFLECTIVE )
		{
			Vector3 direction;
			ColourRGB brdf = closest_result.m_material_ptr->get_specular_brdf ( )->sample_function ( closest_result, direction, -1.0 * p_ray.get_direction ( ) );

			Ray ray ( closest_result.m_hitpoint, direction );
			closest_result.m_reflection_radiance = trace_ray ( ray, p_depth++, p_max_depth ) * brdf;
		}

		return closest_result.m_material_ptr->shade_arealight ( closest_result, p_ray );
	}

	return ColourRGB ( 0.4f, 0.4f, 0.4f );
}
