#ifndef HITRESULT_H
#define HITRESULT_H

#include "maths/maths.h"

/*
 *	HitResult contains all information about the intersection of
 *	a ray and the geometry in a scene.
 * */
struct HitResult 
{
	bool 		m_hit = false;		//	Has ray hit something
	double 		m_distance = 0.0;	//	Distance of hit point
	Point3		m_hitpoint;		//	Hit point in world coordinates
	//	Ray
	//	Material
};
#endif
