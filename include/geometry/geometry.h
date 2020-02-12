#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "maths/maths.h"
#include "hitresult.h"
#include "material/material.h"

class IGeometry 
{
	public:

		virtual bool 		rayhit ( const Ray&, HitResult& ) = 0;

	protected:

		IMaterial*	m_pmaterial;
};
#endif
