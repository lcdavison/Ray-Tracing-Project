#ifndef HITRESULT_H
#define HITRESULT_H

#include <vector>

#include "maths/maths.h"
#include "material/material.h"
#include "light/light.h"
#include "light/ambient.h"

class IMaterial;	//	Forward declarations

/*
 *	HitResult contains all information about the intersection of
 *	a ray and the geometry in a scene.
 * */
struct HitResult 
{
	bool 				m_hit = false;		//	Has ray hit something
	double 				m_distance;		//	Distance of hit point
	Point3				m_hitpoint;		//	Hit point in world coordinates
	Vector3				m_normal;		//	Normal at hit point
	IMaterial*			m_pmaterial;		//	Material of object
	AmbientLight*			m_pambient_light;	
	std::vector < ILight* >*	m_plights;
};
#endif
