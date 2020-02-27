#ifndef MULTI_JITTERED_SAMPLER_H
#define MULTI_JITTERED_SAMPLER_H

#include "sampler.h"

class MultiJitteredSampler : public ISampler
{
	public:

		MultiJitteredSampler ( unsigned int, unsigned int );

		void generate_samples ( );
};
#endif
