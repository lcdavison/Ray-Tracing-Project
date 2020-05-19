#include "brdf/glossy_reflection.h"

GlossyReflection::GlossyReflection ( ) : m_colour ( ColourRGB ( 0.0f, 1.0f, 0.0f ) ), m_coeff ( 1.0f ), m_exponent ( 2.0f ) 
{
	//	Setup sampler
	MultiJitteredSampler* brdf_sampler = new MultiJitteredSampler ( 25, 4 );
	brdf_sampler->generate_samples ( );
	brdf_sampler->map_to_hemisphere ( m_exponent );

	m_sampler_ptr = brdf_sampler;
}

GlossyReflection::GlossyReflection ( const ColourRGB& p_colour, float p_coeff, float p_exponent ) : m_colour ( p_colour ), m_coeff ( p_coeff ), m_exponent ( p_exponent )
{	
	//	Setup sampler
	MultiJitteredSampler* brdf_sampler = new MultiJitteredSampler ( 25, 4 );
	brdf_sampler->generate_samples ( );
	brdf_sampler->map_to_hemisphere ( m_exponent );

	m_sampler_ptr = brdf_sampler;
}

ColourRGB GlossyReflection::function ( const HitResult& p_hitresult, const Vector3& p_incoming, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;	
}

ColourRGB GlossyReflection::sample_function ( const HitResult& p_hitresult, Vector3& p_incoming, const Vector3& p_outgoing )
{
	//	Compute reflection vector
	Vector3 reflection_dir = 2.0 * dot ( p_hitresult.m_normal, p_outgoing )	* p_hitresult.m_normal - p_outgoing;

	//	Construct an orthonormal basis around reflection direction
	const Vector3& z = reflection_dir;
	Vector3 x = cross ( Vector3 ( 0.00424, 1.0, 0.00764 ), z );
	Vector3 y = cross ( z, x );

	//	Transform direction into tangent space
	Point3 sample 	= m_sampler_ptr->sample_hemisphere ( );
	p_incoming 	= sample.x * x + sample.y * y + sample.z * z;

	//	Test if glossy ray is below the surface of the object
	if ( dot ( p_hitresult.m_normal, p_incoming ) < 0.0 )
		p_incoming = -1.0 * sample.x * x - sample.y * y + sample.z * z;

	float cosine_theta = dot ( p_incoming, reflection_dir );

	float specular = std::pow ( cosine_theta, m_exponent );
	m_probability_density_function = specular;

	return m_coeff * m_colour * specular;
}

ColourRGB GlossyReflection::reflectance ( const HitResult& p_hitresult, const Vector3& p_outgoing )
{
	return ColourRGB::BLACK;
}

void GlossyReflection::set_colour ( const ColourRGB& p_colour )
{
	m_colour = p_colour;
}

void GlossyReflection::set_coeff ( float p_coeff )
{
	m_coeff = p_coeff;
}

void GlossyReflection::set_exponent ( float p_exponent )
{
	m_exponent = p_exponent;
}
