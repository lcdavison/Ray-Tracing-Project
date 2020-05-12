#include "brdf/fresnel_reflection.h"

FresnelReflection::FresnelReflection ( ) : m_exterior_index ( 1.0 ), m_interior_index ( 1.3 ) { }

FresnelReflection::FresnelReflection ( float p_exterior_index, float p_interior_index ) : m_exterior_index ( p_exterior_index ), m_interior_index ( p_interior_index ) { }

ColourRGB FresnelReflection::function ( const HitResult& p_hitdata, const Vector3& p_incoming, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

ColourRGB FresnelReflection::sample_function ( const HitResult& p_hitdata, Vector3& p_incoming, const Vector3& p_outgoing )
{
	//	Calculate reflection vector
	p_incoming = 2.0 * dot ( p_hitdata.m_normal, p_outgoing ) * p_hitdata.m_normal - p_outgoing;
	p_incoming.normalize ( );

	//	Calculate the fresnel coefficient (fc)
	double fresnel = fresnel_coefficient ( p_hitdata, p_outgoing );
	
	return fresnel * ColourRGB::WHITE;
}

ColourRGB FresnelReflection::reflectance ( const HitResult& p_hitdata, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

float FresnelReflection::fresnel_coefficient ( const HitResult& p_hitdata, const Vector3& p_outgoing )
{
	Vector3 normal 		= p_hitdata.m_normal;
	double incident_cosine  = dot ( p_outgoing, normal );
	double refraction_index = m_exterior_index / m_interior_index;

	//	Check if ray is inside the object
	if ( incident_cosine < 0.0 )
	{
		normal = -1.0 * normal;

		//	Flip indices of refraction
		refraction_index = m_interior_index / m_exterior_index;
	}

	//	Compute cosines of angles
	incident_cosine = dot ( p_outgoing, normal );
	double transmitted_cosine = std::sqrt ( 1.0 - ( refraction_index * refraction_index ) * ( 1.0 - ( incident_cosine * incident_cosine ) ) );

	//	Fresnel Equations
	double parallel 	= ( refraction_index * incident_cosine - transmitted_cosine ) / ( refraction_index * incident_cosine + transmitted_cosine );
	double perpendicular 	= ( incident_cosine - refraction_index * transmitted_cosine ) / ( incident_cosine + refraction_index * transmitted_cosine );

	return 0.5 * ( parallel * parallel + perpendicular * perpendicular );
}
