#ifndef MATERIAL_H
#define MATERIAL_H

#include "maths/maths.h"
#include "geometry/hitresult.h"

struct HitResult;

enum RT_MATERIAL_TYPE { RT_REFLECTIVE, RT_GLOSSY };

class IMaterial 
{
	public:

		virtual ColourRGB shade ( const HitResult&, const Ray& ) = 0;

		virtual bool 	get_reflective ( ) { return m_reflective; }
		unsigned char 	get_flags ( ) { return m_flags; }

	protected:

		unsigned char m_flags = 0;

		bool m_reflective = false;
};
#endif
