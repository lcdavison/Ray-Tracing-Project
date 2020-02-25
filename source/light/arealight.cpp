#include "light/arealight.h"

AreaLight::AreaLight ( ) { }

ColourRGB AreaLight::radiance ( )
{
	if ( dot ( m_direction, -1.0 * m_sample_normal ) > 0.0 )
		return m_material_ptr->get_radiance ( );

	return ColourRGB::BLACK;
}

bool AreaLight::in_shadow ( const Ray& p_ray, const HitResult& p_hitdata )
{
	Vector3 hitpoint_to_light = m_sample_point - p_hitdata.m_hitpoint;

	for ( IGeometry* geometry : *p_hitdata.m_geometry_ptr )
	{
		if ( geometry->casts_shadows ( ) )
		{
			double distance;

			if ( geometry->shadow_rayhit ( p_ray, distance ) && distance < dot ( hitpoint_to_light, p_ray.get_direction ( ) ) )
				return true;
		}
	}

	return false;
}

Vector3	AreaLight::get_direction ( const Point3& p_hitpoint )
{
	m_sample_point = m_geometry_ptr->sample ( );
	m_sample_normal = m_geometry_ptr->sample_normal ( m_sample_point );

	m_geometric_vector = m_sample_point - p_hitpoint;

	m_direction = m_geometric_vector;
	m_direction.normalize ( );

	return m_direction;
}

double AreaLight::geometric_factor ( )
{
	return dot ( -1.0 * m_sample_normal, m_direction ) / dot ( m_geometric_vector, m_geometric_vector );
}

double AreaLight::probability_density_function ( )
{
	return m_geometry_ptr->probability_density_function ( );
}

void AreaLight::set_geometry ( ILightGeometry* p_geometry )
{
	m_geometry_ptr = p_geometry;
}

void AreaLight::set_material ( Emissive* p_material )
{
	m_material_ptr = p_material;
}
