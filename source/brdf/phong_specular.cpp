#include "brdf/phong_specular.h"

PhongSpecular::PhongSpecular ( ) : m_colour ( ColourRGB ( 0.0f, 1.0f, 0.0f ) ), m_coeff ( 0.5f ), m_exponent ( 2.0f ) { }

PhongSpecular::PhongSpecular ( const ColourRGB& p_colour, float p_coeff, float p_exponent ) : m_colour ( p_colour ), m_coeff ( p_coeff ), m_exponent ( p_exponent ) { }

ColourRGB PhongSpecular::function ( const HitResult& p_hitdata, const Vector3& p_incoming, const Vector3& p_outgoing )
{
	//	Reflect light about the normal
	Vector3 reflection = 2.0 * dot ( p_incoming, p_hitdata.m_normal ) * p_hitdata.m_normal - p_incoming;
	reflection.normalize ( );

	//	Compute cosine of angle between reflection and ray direction
	double reflect_dot_ray = dot ( p_outgoing, reflection );

	//	Only reflect light if cosine is positive
	if ( reflect_dot_ray > 0.0 )
		return m_coeff * m_colour * std::pow ( reflect_dot_ray, m_exponent );

	return ColourRGB::BLACK;
}

ColourRGB PhongSpecular::sample_function ( const HitResult& p_hitdata, Vector3& p_incoming, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

ColourRGB PhongSpecular::reflectance ( const HitResult& p_hitdata, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

void PhongSpecular::set_colour ( const ColourRGB& p_colour )
{
	m_colour = p_colour;
}

void PhongSpecular::set_coeff ( float p_coeff )
{
	m_coeff = p_coeff;
}

void PhongSpecular::set_exponent ( float p_exponent )
{
	m_exponent = p_exponent;
}
