#ifndef MATERIAL_H
#define MATERIAL_H

#include "maths/maths.h"
#include "brdf/brdf.h"
#include "geometry/hitresult.h"

struct HitResult;
class IBRDF;

enum RT_MATERIAL_TYPE { RT_REFLECTIVE = 0x1, RT_REFRACTIVE = 0x2, RT_GLOSSY = 0x4 };

/*
 *	IMaterial provides a common set of functions for each material
 * */
class IMaterial 
{
	public:

		virtual ColourRGB 	shade 		( const HitResult&, const Ray& ) 	= 0;
		virtual ColourRGB	shade_arealight ( const HitResult&, const Ray& ) 	= 0;	//	Different shade function due to Monte Carlo Approximation for lighting

		void 			set_flags ( unsigned char p_flags ) { m_flags |= p_flags; }
		unsigned char		get_flags ( ) { return m_flags; }

	protected:

		unsigned char m_flags = 0;
};
#endif
