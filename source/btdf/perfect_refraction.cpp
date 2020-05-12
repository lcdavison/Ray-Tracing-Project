#include "btdf/perfect_refraction.h"

PerfectRefraction::PerfectRefraction ( ) : m_index_of_refraction ( 1.52f ), m_coeff ( 1.0f ) { }

PerfectRefraction::PerfectRefraction ( float p_index, float p_coeff ) : m_index_of_refraction ( p_index ), m_coeff ( p_coeff ) { }
 
ColourRGB PerfectRefraction::function ( const HitResult& p_hitdata, const Vector3& p_transmitted, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

ColourRGB PerfectRefraction::sample_function ( const HitResult& p_hitdata, Vector3& p_transmitted, const Vector3& p_outgoing )
{
	Vector3 surface_normal  = p_hitdata.m_normal;
	double incident_cosine  = dot ( surface_normal, p_outgoing );	//	Cosine of angle between ray and normal
	double refraction_index = 1.0 / m_index_of_refraction;		//	Index of air / index of object

	//	Check if inside the object
	if ( incident_cosine < 0.0 )
	{
		//	Reverse cosine
		incident_cosine *= -1.0;

		//	Flip hit point normal
		surface_normal = surface_normal * -1.0;

		//	Reverse relative index of refraction
		refraction_index = m_index_of_refraction;
	}


	//	Compute sine of incident angle squared
	double incident_sine_sqrd = std::max ( 0.0, 1.0 - ( incident_cosine * incident_cosine ) );

	//	Compute cosine of transmission angle
	double transmitted_cosine = std::sqrt ( 1.0 - ( incident_sine_sqrd * ( refraction_index * refraction_index ) ) );

	//	Compute the transmitted vector
	p_transmitted = ( -1.0 * p_outgoing ) * refraction_index + ( incident_cosine * refraction_index - transmitted_cosine ) * surface_normal;

	return m_coeff * ( refraction_index * refraction_index ) * ColourRGB::WHITE;
}

ColourRGB PerfectRefraction::transmittance ( const HitResult& p_hitdata, const Vector3& p_transmitted )
{
	return ColourRGB::BLACK;
}

bool PerfectRefraction::total_internal_reflection ( const HitResult& p_hitdata, const Ray& p_ray )
{
	//	Compute angle between ray and hit normal
	double incident_cosine = dot ( p_hitdata.m_normal, -1.0 * p_ray.get_direction ( ) );

	double refraction_index = 1.0 / m_index_of_refraction;	//	Relative index of refraction

	//	Checks whether the ray is inside an object
	//	the relative index of refraction should be reversed in this case
	if ( incident_cosine < 0.0 )
		refraction_index = m_index_of_refraction;

	double incident_sine_sqrd = 1.0 - ( incident_cosine * incident_cosine );

	return ( 1.0 - incident_sine_sqrd * ( refraction_index * refraction_index ) ) < 0.0;
}
