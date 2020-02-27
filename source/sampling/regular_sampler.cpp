#include "sampling/regular_sampler.h"

RegularSampler::RegularSampler ( ) { }

RegularSampler::RegularSampler ( unsigned int p_num_samples, unsigned int p_num_sets )
{
	m_num_samples 	= p_num_samples;
	m_num_sets 	= p_num_sets;
	m_current_index = 0;
	m_random 	= std::uniform_int_distribution < unsigned int > ( 0, m_num_sets - 1 );
}

void RegularSampler::generate_samples ( )
{
	unsigned int samples_per_dimension = std::sqrt ( m_num_samples );

	for ( int s = 0; s < m_num_sets; ++s )
	{
		for ( int y = 0; y < samples_per_dimension; ++y )
		{
			for ( int x = 0; x < samples_per_dimension; ++x )
			{
				m_samples.emplace_back ( ( x + 0.5 ) / ( double ) ( samples_per_dimension ), 
							 ( y + 0.5 ) / ( double ) ( samples_per_dimension ), 
							 0.0 );
			}	
		}
	}
}
