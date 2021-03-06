#include "sampling/multijittered_sampler.h"

MultiJitteredSampler::MultiJitteredSampler ( unsigned int p_num_samples, unsigned int p_num_sets )
{
	 m_num_samples	 = p_num_samples; 
	 m_num_sets	 = p_num_sets;
	 m_current_index = 0;

	 std::random_device rd;
	 m_generator 	 = std::default_random_engine ( rd ( ) );
	 m_random 	 = std::uniform_int_distribution < unsigned int > ( 0, m_num_sets - 1 );

	 setup_indices ( );
}

void MultiJitteredSampler::generate_samples ( )
{
	int samples_per_dimension = std::sqrt ( m_num_samples );

	double subcell_width = 1.0 / m_num_samples;
	std::uniform_real_distribution < double > rand ( 0.0, subcell_width );

	//	Generate starting pattern
	for ( int s = 0; s < m_num_sets; ++s )
	{
		for ( int y = 0; y < samples_per_dimension; ++y )
		{
			for ( int x = 0; x < samples_per_dimension; ++x )
			{
				m_samples.emplace_back ( ( ( double ) ( x ) / ( double ) ( samples_per_dimension ) ) + ( y * subcell_width ) + rand ( m_generator ), 
							 ( ( double ) ( y ) / ( double ) ( samples_per_dimension ) ) + ( x * subcell_width ) + rand ( m_generator ), 0.0 );
			}
		}
	}

	std::uniform_int_distribution < unsigned int > shuffle ( 0, samples_per_dimension - 1 );
	m_generator.seed ( std::time ( nullptr ) );

	//	Shuffle X coordinates
	for ( int s = 0; s < m_num_sets; ++s )
	{
		for ( int y = 0; y < samples_per_dimension; ++y )
		{
			for ( int x = 0; x < samples_per_dimension; ++x )
			{
				unsigned int index = x + ( shuffle ( m_generator ) % ( samples_per_dimension - x ) );

				double temp = m_samples.at ( s * m_num_samples + y * samples_per_dimension + x ).x;
				m_samples.at ( s * m_num_samples + y * samples_per_dimension + x ).x = m_samples.at ( s * m_num_samples + y * samples_per_dimension + index ).x;
				m_samples.at ( s * m_num_samples + y * samples_per_dimension + index ).x = temp;
			}
		}
	}

	shuffle.reset ( );
	m_generator.seed ( std::time ( nullptr ) );
	
	//	Shuffle Y coordinates
	for ( int s = 0; s < m_num_sets; ++s )
	{
		for ( int y = 0; y < samples_per_dimension; ++y )
		{
			for ( int x = 0; x < samples_per_dimension; ++x )
			{
				unsigned int index = y + ( shuffle ( m_generator ) % ( samples_per_dimension - y ) );

				double temp = m_samples.at ( s * m_num_samples + y * samples_per_dimension + x ).y;
				m_samples.at ( s * m_num_samples + y * samples_per_dimension + x ).y = m_samples.at ( s * m_num_samples + index * samples_per_dimension + x ).y;
				m_samples.at ( s * m_num_samples + index * samples_per_dimension + x ).y = temp;
			}
		}
	}
}
