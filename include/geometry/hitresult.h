#ifndef HITRESULT_H
#define HITRESULT_H

#include <limits>

#include "maths/maths.h"

/*
 *	HitResult contains all information about the intersection of
 *	a ray and the geometry in a scene.
 * */
struct HitResult 
{
	bool 		m_hit = false;		//	Has ray hit something
	double 		m_distance;		//	Distance of hit point
	Point3		m_hitpoint;		//	Hit point in world coordinates
	IMaterial*	m_pmaterial;		//	Material of object
};
#endif
