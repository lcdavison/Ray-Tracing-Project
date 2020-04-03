#include "sampling/sampler.h"

void ISampler::map_to_hemisphere ( double exp )
{
	for ( Point3 sample : m_samples )
	{
		//	Uses a Phong Distribution
		double cosine_theta 	= std::pow  ( 1.0 - sample.x, 1.0 / ( exp + 1 ) );
		double sine_theta 	= std::sqrt ( 1.0 - ( cosine_theta * cosine_theta ) );
		double phi 		= 2.0 * M_PI * sample.y;

		//	Convert from Spherical coordinates to Cartesian coordinates
		Point3 hemisphere_sample;
		hemisphere_sample.x = std::cos ( phi ) * sine_theta;
		hemisphere_sample.y = std::sin ( phi ) * sine_theta;
		hemisphere_sample.z = cosine_theta;

		m_hemisphere_samples.push_back ( hemisphere_sample );
	}
}

Point3 ISampler::sample_square ( )
{
	if ( m_current_index % m_num_samples == 0 )	//	Reached the end of a set
		m_start_marker = ( m_random ( m_generator ) ) * m_num_samples;	//	Update start marker

	return m_samples.at ( m_start_marker + m_shuffled_indices [ m_start_marker + m_current_index++ % m_num_samples ] );
}

Point3 ISampler::sample_hemisphere ( )
{
	if ( m_current_index % m_num_samples == 0 )	//	Reached the end of a set
		m_start_marker = ( m_random ( m_generator ) ) * m_num_samples;	//	Update start marker

	return m_hemisphere_samples.at ( m_start_marker + m_shuffled_indices [ m_start_marker + m_current_index++ % m_num_samples ] );
}

unsigned int ISampler::get_num_samples ( )
{
	return m_num_samples;
}

void ISampler::setup_indices ( )
{
	std::vector < unsigned int > indices;

	for ( int i = 0; i < m_num_samples; ++i )
		indices.push_back ( i );

	for ( int s = 0; s < m_num_sets; ++s )
	{
		std::random_shuffle ( indices.begin ( ), indices.end ( ) );

		for ( int i = 0; i < m_num_samples; ++i )
		{
			m_shuffled_indices.push_back ( indices.at ( i ) );
		}
	}
}
