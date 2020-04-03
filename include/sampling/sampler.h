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

		void 			map_to_hemisphere ( double );	//	Used to map samples to a hemisphere 

		Point3			sample_square ( );
		Point3			sample_hemisphere ( );

		unsigned int 		get_num_samples ( );

	protected:

		void 			setup_indices ( );

		unsigned int			m_num_samples;		//	Number of samples per set
		unsigned int 			m_num_sets;		//	Number of sets of samples
		unsigned int			m_start_marker;		//	Indicates beginning of a randomly chosen set
		unsigned int			m_current_index;	//	Current position in array

		std::vector < Point3 > 		m_samples;		//	Samples mapped on a square
		std::vector < Point3 >		m_hemisphere_samples;	//	Samples mapped to a hemisphere
		std::vector < unsigned int > 	m_shuffled_indices;	//	Used to sample non-sequentially

		std::default_random_engine 			m_generator;
		std::uniform_int_distribution < unsigned int >	m_random;
};
#endif
