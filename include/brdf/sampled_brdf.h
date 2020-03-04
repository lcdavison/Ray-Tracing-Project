#ifndef SAMPLED_BRDF_H
#define SAMPLED_BRDF_H

#include "sampling/sampler.h"

/*
 *	ISampledBRDF provides a BRDF with necessary capabilities for sampling
 * */
class ISampledBRDF 
{
	public:

		void 		set_sampler ( ISampler* p_sampler ) { m_sampler_ptr = p_sampler; }
		float 		get_probability_density_function ( ) { return m_probability_density_function; }

	protected:

		float 		m_probability_density_function;
		ISampler* 	m_sampler_ptr = nullptr;
};
#endif
