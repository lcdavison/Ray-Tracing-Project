#include "btdf/perfect_refraction.h"

PerfectRefraction::PerfectRefraction ( ) { }

PerfectRefraction::PerfectRefraction ( float p_index, float p_coeff ) : m_index_of_refraction ( p_index ), m_coeff ( p_coeff ) { }
 
ColourRGB PerfectRefraction::function ( const HitResult& p_hitdata, const Vector3& p_transmitted, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

ColourRGB PerfectRefraction::sample_function ( const HitResult& p_hitdata, Vector3& p_transmitted, const Vector3& p_outgoing )
{
	Vector3 surface_normal = p_hitdata.m_normal;
	double incident_cosine = dot ( surface_normal, p_outgoing );
	double refraction_index = 1.0 / m_index_of_refraction;	//	Index of air / index of object

	//	Check if inside the object
	if ( incident_cosine < 0.0 )
	{
		incident_cosine *= -1.0;

		//	Flip hit point normal
		surface_normal = surface_normal * -1.0;

		refraction_index = m_index_of_refraction / 1.0;
	}

	//	Compute the transmitted vector
	double incident_sine_sqrd = std::max ( 0.0, 1.0 - ( incident_cosine * incident_cosine ) );

	double transmitted_cosine = std::sqrt ( 1.0 - ( incident_sine_sqrd * ( refraction_index * refraction_index ) ) );

	p_transmitted = ( -1.0 * p_outgoing ) * refraction_index + ( incident_cosine * refraction_index - transmitted_cosine ) * surface_normal;
	return m_coeff * ( refraction_index * refraction_index ) * ColourRGB::WHITE;
}

ColourRGB PerfectRefraction::reflectance ( const HitResult& p_hitdata, const Vector3& p_transmitted, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

bool PerfectRefraction::total_internal_reflection ( const HitResult& p_hitdata, const Ray& p_ray )
{
	double incident_cosine = dot ( p_hitdata.m_normal, -1.0 * p_ray.get_direction ( ) );

	double refraction_index = 1.0 / m_index_of_refraction;

	//	Checks whether the ray is inside an object
	//	the relative index of refraction should be reversed in this case
	if ( incident_cosine < 0.0 )
		refraction_index = m_index_of_refraction;

	return ( 1 - ( 1 - ( incident_cosine * incident_cosine ) ) * ( refraction_index * refraction_index ) ) < 0.0;
}
