#ifndef LIGHT_GEOMETRY_H
#define LIGHT_GEOMETRY_H

#include "sampling/sampler.h"

/*
 *	Provides geometric object with functions for use when representing an area light
 * */
class ILightGeometry 
{
	public:

		virtual Point3 		sample ( ) = 0;
		virtual Vector3 	sample_normal ( const Point3& ) = 0;

		double 			probability_density_function ( ) { return m_inverse_area; }
		
		void 			set_sampler ( ISampler* p_sampler ) { m_sampler_ptr = p_sampler; }
		ISampler*		get_sampler ( ) { return m_sampler_ptr; }

	protected:

		ISampler* 	m_sampler_ptr;
		double 		m_inverse_area;
};
#endif
