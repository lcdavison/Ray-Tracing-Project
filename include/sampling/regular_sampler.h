#ifndef REGULAR_SAMPLER_H
#define REGULAR_SAMPLER_H

#include "sampler.h"

class RegularSampler : public ISampler 
{
	public:

		RegularSampler ( );
		RegularSampler ( unsigned int, unsigned int );

		void 	generate_samples ( );
};
#endif
