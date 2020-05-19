#include "btdf/fresnel_refraction.h"

FresnelRefraction::FresnelRefraction ( ) : m_exterior_index ( 1.0f ), m_interior_index ( 1.52f ) { }

FresnelRefraction::FresnelRefraction ( float p_exterior_index, float p_interior_index ) : m_exterior_index ( p_exterior_index ), m_interior_index ( p_interior_index ) { }

ColourRGB FresnelRefraction::function ( const HitResult& p_hitdata, const Vector3& p_incoming, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

ColourRGB FresnelRefraction::sample_function ( const HitResult& p_hitdata, Vector3& p_transmitted, const Vector3& p_outgoing )
{
	//	Setup refraction data
	Vector3 surface_normal  = p_hitdata.m_normal;
	double incident_cosine  = dot ( surface_normal, p_outgoing );	//	Cosine of the incident angle
	double refraction_index = m_exterior_index / m_interior_index;	//	Relative index of refraction = exit index / entry index

	//	Check if inside object
	if ( incident_cosine < 0.0 )
	{
		//	Reverse normal and relative index of refraction
		surface_normal   = -1.0 * surface_normal;
		incident_cosine *= -1.0;
		refraction_index = m_interior_index / m_exterior_index;
	}

	
	double incident_sine_sqrd = std::max ( 0.0, 1.0 - ( incident_cosine * incident_cosine ) );			//	Sine squared of incident angle
	double transmitted_cosine = std::sqrt ( 1.0 - ( refraction_index * refraction_index ) * incident_sine_sqrd );	//	Cosine of the transmitted angle

	//	Compute Transmitted vector
	p_transmitted = ( -1.0 * p_outgoing ) * refraction_index + ( incident_cosine * refraction_index - transmitted_cosine ) * surface_normal;

	//	Compute Fresnel coefficient
	double fresnel = fresnel_coefficient ( p_hitdata, p_outgoing );

	return fresnel * ( refraction_index * refraction_index ) * ColourRGB::WHITE;
}

ColourRGB FresnelRefraction::transmittance ( const HitResult& p_hitdata, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

bool FresnelRefraction::total_internal_reflection ( const HitResult& p_hitdata, const Ray& p_ray )
{
	double incident_cosine 	= dot ( p_hitdata.m_normal, -1.0 * p_ray.get_direction ( ) );	//	Cosine of the incident angle
	double refractive_index = m_exterior_index / m_interior_index;				//	Relative index of refraction

	//	Check if inside object
	if ( incident_cosine < 0.0 )
		refractive_index = m_interior_index / m_exterior_index;		

	//	Determine whether ray is past the critical angle
	double incident_sine_sqrd = 1.0 - ( incident_cosine * incident_cosine );
	return ( 1.0 - ( refractive_index * refractive_index ) * incident_sine_sqrd ) < 0.0;
}

float FresnelRefraction::fresnel_coefficient ( const HitResult& p_hitdata, const Vector3& p_outgoing )
{
	Vector3 normal 		= p_hitdata.m_normal;
	double incident_cosine  = dot ( p_outgoing, normal );		//	Cosine of the incident angle
	double refraction_index = m_exterior_index / m_interior_index;	//	Relative index of refraction

	//	Check if inside object
	if ( incident_cosine < 0.0 )
	{
		//	Flip data
		normal 		 = -1.0 * normal;
		refraction_index = m_interior_index / m_exterior_index;
	}

	//	Compute cosines of angles
	incident_cosine 	  = dot ( p_outgoing, normal );
	double transmitted_cosine = std::sqrt ( 1.0 - ( refraction_index * refraction_index ) * ( 1.0 - ( incident_cosine * incident_cosine ) ) );

	//	Fresnel Equations
	double parallel      = ( refraction_index * incident_cosine - transmitted_cosine ) / ( refraction_index * incident_cosine + transmitted_cosine );
	double perpendicular = ( incident_cosine - refraction_index * transmitted_cosine ) / ( incident_cosine + refraction_index * transmitted_cosine );

	//	Transmission coefficient
	return 1.0 - ( 0.5 * ( parallel * parallel + perpendicular * perpendicular ) );
}
