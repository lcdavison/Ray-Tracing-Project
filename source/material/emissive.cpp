#include "material/emissive.h"

Emissive::Emissive ( ) { }

Emissive::Emissive ( const ColourRGB& p_colour, float p_coeff ) : m_colour ( p_colour ), m_coeff ( p_coeff ) { }

ColourRGB Emissive::shade ( const HitResult& p_hitresult, const Ray& p_ray )
{
	if ( dot ( p_hitresult.m_normal, -1.0 * p_ray.get_direction ( ) ) > 0.0 )
		return m_colour * m_coeff;

	return ColourRGB::BLACK;
}

ColourRGB Emissive::shade_arealight ( const HitResult& p_hitresult, const Ray& p_ray )
{
	if ( dot ( p_hitresult.m_normal, -1.0 * p_ray.get_direction ( ) ) > 0.0 )
		return m_colour * m_coeff;

	return ColourRGB::BLACK;
}

IBRDF* Emissive::get_diffuse_brdf ( )
{
	return nullptr;
}

IBRDF* Emissive::get_specular_brdf ( )
{
	return nullptr;
}

ColourRGB Emissive::get_radiance ( )
{
	return m_colour * m_coeff;
}
