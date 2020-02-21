#include "raytracer/recursive_tracer.h"

RecursiveTracer::RecursiveTracer ( ) { }

RecursiveTracer::RecursiveTracer ( Scene* p_scene ) : m_pscene ( p_scene ) { }

ColourRGB RecursiveTracer::trace_ray ( const Ray& p_ray )
{ 
	return ColourRGB ( 0.0f, 0.0f, 0.0f ); 
}

ColourRGB RecursiveTracer::trace_ray ( const Ray p_ray, int p_depth, int p_max_depth )
{
	if ( p_depth > p_max_depth )
		return ColourRGB ( 0.0f, 0.0f, 0.0f );

	//	Find closest hit
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

		if ( closest_result.m_pmaterial->get_reflective ( ) )
		{
			//	Create reflection ray
			Vector3 direction = 2.0 * dot ( closest_result.m_normal, -1.0 * p_ray.get_direction ( ) ) * closest_result.m_normal - ( -1.0 * p_ray.get_direction ( ) );
			direction.normalize ( );

			Ray ray ( closest_result.m_hitpoint, direction );

			closest_result.m_reflection_radiance = trace_ray ( ray, p_depth + 1, p_max_depth );	//	Calculate total radiance of reflection
		}

		/*
		 *	Glossy Reflections
		 *
		 *	if ( closest_result.m_pmaterial->get_mask ( ) & RT_GLOSSY )
		 *	{
		 *		1. Construct Orthonormal basis at hitpoint
		 *		2. Monte Carlo integration:
		 *			1. Sample Hemisphere
		 *			2. Transform sample into orthonormal basis
		 *			3. Trace random direction and accumulate glossy reflection radiance
		 *		3. Divide by PDF and number of samples
		 *	}
		 *	
		 * */

		return closest_result.m_pmaterial->shade ( closest_result, p_ray );
	}

	return ColourRGB ( 0.4f, 0.4f, 0.4f );	//	Ray hit nothing
}
