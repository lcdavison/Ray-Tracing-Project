#include "brdf/blinn-phong_specular.h"

BlinnPhongSpecular::BlinnPhongSpecular ( ) { }

BlinnPhongSpecular::BlinnPhongSpecular ( const ColourRGB& p_colour, float p_coeff, float p_exponent ) : m_colour ( p_colour ), m_coeff ( p_coeff ), m_exponent ( p_exponent ) { }

ColourRGB BlinnPhongSpecular::function ( const HitResult& p_hitdata, const Vector3& p_incoming, const Vector3& p_outgoing )
{
	//	Compute halfway vector
	Vector3 halfway = p_incoming + p_outgoing;
	halfway.normalize ( );

	//	Calculate cosine of angle between halfway and ray direction
	double half_dot_out = dot ( halfway, p_outgoing );

	//	Only reflect light when cosine is positive
	if ( half_dot_out > 0.0 )
		return m_colour * m_coeff * std::pow ( half_dot_out, m_exponent );

	return ColourRGB::BLACK;
}

ColourRGB BlinnPhongSpecular::sample_function ( const HitResult& p_hitdata, Vector3& p_incoming, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;	
}

ColourRGB BlinnPhongSpecular::reflectance ( const HitResult& p_hitdata, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

void BlinnPhongSpecular::set_colour ( const ColourRGB& p_colour )
{
	m_colour = p_colour;
}

void BlinnPhongSpecular::set_coeff ( float p_coeff )
{
	m_coeff = p_coeff;
}

void BlinnPhongSpecular::set_exponent ( float p_exponent )
{
	m_exponent = p_exponent;
}
