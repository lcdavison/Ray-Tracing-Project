#ifndef AREALIGHT_H
#define AREALIGHT_H

#include "light.h"
#include "geometry/light_geometry.h"
#include "material/emissive.h"

/*
 *	AreaLight is used for producing realistic lighting, and softer shadows
 * */
class AreaLight : public ILight 
{
	public:

		AreaLight ( );

		ColourRGB 	radiance ( );	//	Emissive colour of the material
		bool		in_shadow ( const Ray&, const HitResult& );

		Vector3		get_direction ( const Point3& );

		void 		set_geometry ( ILightGeometry* );
		void 		set_material ( Emissive* );

		double		geometric_factor ( ) override;
		double		probability_density_function ( ) override;

	private:

		ILightGeometry*		m_geometry_ptr = nullptr;	//	The physical representation of the light
		Emissive*		m_material_ptr = nullptr;	//	Emissive material generating light radiance

		Point3			m_sample_point;
		Vector3			m_sample_normal;
		Vector3			m_geometric_vector;		//	Used in computing the geometric factor
		Vector3			m_direction;
};
#endif
