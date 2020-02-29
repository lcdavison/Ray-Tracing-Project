#ifndef SAMPLER_H
#define SAMPLER_H

#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

#include <iostream>

#include "maths/maths.h"

/*
 *	A sampler is used to generate and store sample points for use during rendering
 * */
class ISampler 
{
	public:

		virtual void 		generate_samples ( ) = 0;

		void 			map_to_disk ( );	//	Used for sampling circles

		void 			map_to_hemisphere ( )	//	Used to map samples to a hemisphere 
		{
			for ( Point3 sample : m_samples )
			{
				double sine_theta = std::sqrt ( sample.x );
				double cosine_theta = std::sqrt ( 1.0 - sample.x );
				double phi = 2.0 * M_PI * sample.y;

				Point3 hemisphere_sample;
				hemisphere_sample.x = std::cos ( phi ) * sine_theta;
				hemisphere_sample.y = std::sin ( phi ) * sine_theta;
				hemisphere_sample.z = std::sqrt ( 1.0 - sample.x );

				m_hemisphere_samples.push_back ( hemisphere_sample );
			}
		}	

		Point3			sample_square ( )
		{
			if ( m_current_index % m_num_samples == 0 )	//	Reached the end of a set
				m_start_marker = ( m_random ( m_generator ) ) * m_num_samples;	//	Update start marker

			return m_samples.at ( m_start_marker + m_shuffled_indices [ m_start_marker + m_current_index++ % m_num_samples ] );
		}

		Point3			sample_hemisphere ( )
		{
			if ( m_current_index % m_num_samples == 0 )	//	Reached the end of a set
				m_start_marker = ( m_random ( m_generator ) ) * m_num_samples;	//	Update start marker

			return m_hemisphere_samples.at ( m_start_marker + m_shuffled_indices [ m_start_marker + m_current_index++ % m_num_samples ] );
		}

		unsigned int 		get_num_samples ( ) { return m_num_samples; }

	protected:

		void 			setup_indices ( )
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

		unsigned int			m_num_samples;		//	Number of samples per set
		unsigned int 			m_num_sets;		//	Number of sets of samples
		unsigned int			m_start_marker;		//	Indicates beginning of a randomly chosen set
		unsigned int			m_current_index;	//	Current position in array

		std::vector < Point3 > 		m_samples;
		std::vector < Point3 >		m_hemisphere_samples;
		std::vector < unsigned int > 	m_shuffled_indices;	//	Used to sample non-sequentially

		std::default_random_engine 			m_generator;
		std::uniform_int_distribution < unsigned int >	m_random;
};
#endif
