#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "maths/maths.h"
#include "hitresult.h"

struct HitResult;

class IGeometry 
{
	public:

		virtual void	rayhit 		( const Ray&, HitResult& ) = 0;		//	Tests for primary ray intersection
		virtual bool	shadow_rayhit 	( const Ray&, double& ) = 0;		//	Tests for shadow ray intersection
};
#endif
