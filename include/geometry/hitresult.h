#ifndef HITRESULT_H
#define HITRESULT_H

#include <vector>

#include "maths/maths.h"

#include "geometry/geometry.h"

#include "material/material.h"

#include "light/light.h"

//	Forward declarations
class IMaterial;	
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
	IMaterial*			m_material_ptr;		//	Material of hit object
	ColourRGB			m_indirect_radiance;	//	Radiance recieved from other objects
	ILight*				m_ambient_light_ptr;	//	Ambient light in scene
	std::vector < ILight* >*	m_lights_ptr;		//	Lights in scene - used for shading
	std::vector < IGeometry* >*	m_geometry_ptr;		//	Geometry in scene - used for shadows
};
#endif
