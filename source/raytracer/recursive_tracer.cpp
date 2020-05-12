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
	
	//	Test for intersections
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
		//	Set hit data
		closest_result.m_hitpoint 		= p_ray.get_point ( closest_result.m_distance );
		closest_result.m_ambient_light_ptr 	= m_scene_ptr->get_ambient_light ( );
		closest_result.m_lights_ptr 		= &( m_scene_ptr->get_lights ( ) );
		closest_result.m_geometry_ptr		= &( m_scene_ptr->get_geometry ( ) );

		ColourRGB reflection;
		ColourRGB refraction;

		//	Check if material is reflective
		if ( closest_result.m_material_ptr->get_flags ( ) & RT_REFLECTIVE )
		{
			Vector3 direction;
			ColourRGB brdf = dynamic_cast < IReflective* > ( closest_result.m_material_ptr )->get_reflection_brdf ( )->sample_function ( closest_result, direction, -1.0 * p_ray.get_direction ( ) );

			Ray ray ( closest_result.m_hitpoint, direction );
			reflection = trace_ray ( ray, p_depth + 1, p_max_depth ) * brdf;	//	Calculate total radiance of reflection
		}

		//	Check if material is glossy
		if ( closest_result.m_material_ptr->get_flags ( ) & RT_GLOSSY )
		{
			IGlossy* material  	   = dynamic_cast < IGlossy* > ( closest_result.m_material_ptr );
			ISampledBRDF* brdf_sampler = dynamic_cast < ISampledBRDF* > ( material->get_glossy_brdf ( ) );

			//	Monte Carlo integration
			for ( int i = 0; i < 20; ++i )
			{
				Vector3 direction;
				ColourRGB brdf = material->get_glossy_brdf ( )->sample_function ( closest_result, direction, -1.0 * p_ray.get_direction ( ) );

				Ray ray ( closest_result.m_hitpoint, direction );
				reflection = reflection + ( trace_ray ( ray, p_depth + 1, p_max_depth ) * brdf * ( 1.0f / brdf_sampler->get_probability_density_function ( ) ) );
			}

			reflection = reflection * ( 1.0 / 20.0 );
		}

		//	Check if material is transmissive
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

		return closest_result.m_material_ptr->shade ( closest_result, p_ray );
	}

	return ColourRGB ( 0.4f, 0.4f, 0.4f );	//	Ray hit nothing
}
