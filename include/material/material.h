#ifndef MATERIAL_H
#define MATERIAL_H

#include "maths/maths.h"
#include "brdf/brdf.h"
#include "geometry/hitresult.h"

struct HitResult;
class IBRDF;

enum RT_MATERIAL_TYPE { RT_REFLECTIVE = 0x1, RT_REFRACTIVE = 0x2, RT_GLOSSY = 0x4 };

class IMaterial 
{
	public:

		virtual ColourRGB 	shade 		( const HitResult&, const Ray& ) 	= 0;
		virtual ColourRGB	shade_arealight ( const HitResult&, const Ray& ) 	= 0;	//	Different shade function due to Monte Carlo Approximation for lighting

		virtual IBRDF* 		get_diffuse_brdf 	( ) = 0;	//	This is used for path tracing
		virtual IBRDF*		get_specular_brdf 	( ) = 0;	//	Used for reflections

		void 			set_flags ( unsigned char p_flags ) { m_flags |= p_flags; }
		unsigned char		get_flags ( ) { return m_flags; }

	protected:

		unsigned char m_flags = 0;
};
#endif
