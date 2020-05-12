#ifndef REGULAR_SAMPLER_H
#define REGULAR_SAMPLER_H

#include "sampler.h"

/*
 *	RegularSampler produces sample points regularly distributed in a grid of square cells
 * */
class RegularSampler : public ISampler 
{
	public:

		RegularSampler ( );
		RegularSampler ( unsigned int, unsigned int );

		void 	generate_samples ( );
};
#endif
