#include "raytracer/recursive_tracer.h"

RecursiveTracer::RecursiveTracer ( ) { }

RecursiveTracer::RecursiveTracer ( Scene* p_scene ) : m_scene_ptr ( p_scene ) { }

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

		ColourRGB reflection;
		ColourRGB refraction;

		if ( closest_result.m_material_ptr->get_flags ( ) & RT_REFLECTIVE )
		{
			Vector3 direction;
			ColourRGB brdf = dynamic_cast < IReflective* > ( closest_result.m_material_ptr )->get_reflection_brdf ( )->sample_function ( closest_result, direction, -1.0 * p_ray.get_direction ( ) );

			Ray ray ( closest_result.m_hitpoint, direction );
			reflection = trace_ray ( ray, p_depth + 1, p_max_depth ) * brdf;	//	Calculate total radiance of reflection
		}

		if ( closest_result.m_material_ptr->get_flags ( ) & RT_REFRACTIVE )
		{
			IRefractive* refract_material = dynamic_cast < IRefractive* > ( closest_result.m_material_ptr );

			Vector3 reflection_direction;
			ColourRGB brdf = dynamic_cast < IReflective* > ( closest_result.m_material_ptr )->get_reflection_brdf ( )->sample_function ( closest_result, reflection_direction, -1.0 * p_ray.get_direction ( ) );

			if ( refract_material->get_refraction_btdf ( )->total_internal_reflection ( closest_result, p_ray ) )
			{
				Ray ray ( closest_result.m_hitpoint, reflection_direction );
				reflection = trace_ray ( ray, p_depth + 1, p_max_depth );
			}
			else
			{
				//	Compute reflection
				Ray reflect_ray ( closest_result.m_hitpoint, reflection_direction );
				reflection = trace_ray ( reflect_ray, p_depth + 1, p_max_depth ) * brdf;

				//	Compute refraction
				Vector3 refraction_direction;
				ColourRGB btdf = refract_material->get_refraction_btdf ( )->sample_function ( closest_result, refraction_direction, -1.0 * p_ray.get_direction ( ) );

				Ray refract_ray ( closest_result.m_hitpoint, refraction_direction );
				refraction = trace_ray ( refract_ray, p_depth + 1, p_max_depth ) * btdf;
			}
		}

		closest_result.m_indirect_radiance = refraction + reflection;

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

		return closest_result.m_material_ptr->shade ( closest_result, p_ray );
	}

	return ColourRGB ( 0.4f, 0.4f, 0.4f );	//	Ray hit nothing
}
