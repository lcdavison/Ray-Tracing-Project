#ifndef GLOSSY_REFLECTION_H
#define GLOSSY_REFLECTION_H

#include "brdf.h"
#include "sampled_brdf.h"
#include "sampling/multijittered_sampler.h"

/*
 *	Glossy Reflection computes light that is reflected and scatters in a cone of
 *	directions, producing a blurred reflection
 * */
class GlossyReflection : public IBRDF, public ISampledBRDF
{
	public:

		GlossyReflection ( );
		GlossyReflection ( const ColourRGB&, float, float );

		ColourRGB 	function 	( const HitResult&, const Vector3&, const Vector3& );
		ColourRGB 	sample_function ( const HitResult&, Vector3&, const Vector3& );
		ColourRGB 	reflectance 	( const HitResult&, const Vector3& );

		void 		set_colour 	( const ColourRGB& );
		void 		set_coeff 	( float );
		void 		set_exponent 	( float );

	private:

		ColourRGB 	m_colour;
		float 		m_coeff;
		float 		m_exponent;
};
#endif
