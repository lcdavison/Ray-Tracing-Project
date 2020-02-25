#ifndef HITRESULT_H
#define HITRESULT_H

#include <vector>

#include "maths/maths.h"

#include "geometry/geometry.h"

#include "material/material.h"

#include "light/light.h"

class IMaterial;	//	Forward declarations
class IGeometry;
class ILight;
class IBRDF;

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
	ColourRGB			m_reflection_radiance = ColourRGB ( 0.0f, 0.0f, 0.0f );	//	Radiance of reflections
	Ray*				m_pray;			//	Ray which was traced
	IMaterial*			m_material_ptr;		//	Material of object
	ILight*				m_ambient_light_ptr;	//	Scene ambient light
	std::vector < ILight* >*	m_lights_ptr;		//	Lights in scene
	std::vector < IGeometry* >*	m_geometry_ptr;		//	Geometry in scene - used for shadows
};
#endif
