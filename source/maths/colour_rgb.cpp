#include "maths/colour_rgb.h"

ColourRGB ColourRGB::BLACK = ColourRGB ( 0.0f, 0.0f, 0.0f );
ColourRGB ColourRGB::WHITE = ColourRGB ( 1.0f, 1.0f, 1.0f );

ColourRGB::ColourRGB ( ) : m_red ( 0.0f ), m_green ( 0.0f ), m_blue ( 0.0f )
{
}

ColourRGB::ColourRGB ( float p_red, float p_green, float p_blue ) : m_red ( p_red ), m_green ( p_green ), m_blue ( p_blue )
{
}

float ColourRGB::get_red ( ) const
{
	return m_red;
}

float ColourRGB::get_green ( ) const
{
	return m_green;
}

float ColourRGB::get_blue ( ) const
{
	return m_blue;
}

unsigned int ColourRGB::int_format ( ) 
{
	//	Perform Tone Mapping
	float max_value = std::max ( m_red, std::max ( m_green, m_blue ) );

	if ( max_value > 1.0 )
	{
		m_red 	/= max_value;
		m_green /= max_value;
		m_blue  /= max_value;
	}

	unsigned int final_colour = 0;

	final_colour |= ( ( unsigned int ) ( m_red * 255 ) ) << 16;
	final_colour |= ( ( unsigned int ) ( m_green * 255 ) ) << 8;
	final_colour |= ( ( unsigned int ) ( m_blue * 255 ) );

	return final_colour; 
}

ColourRGB operator + ( const ColourRGB& l, const ColourRGB& r )
{
	return ColourRGB ( l.get_red ( ) + r.get_red ( ), l.get_green ( ) + r.get_green ( ), l.get_blue ( ) + r.get_blue ( ) );
}

ColourRGB operator * ( const ColourRGB& l, const ColourRGB& r )
{
	return ColourRGB ( l.get_red ( ) * r.get_red ( ), l.get_green ( ) * r.get_green ( ), l.get_blue ( ) * r.get_blue ( ) );
}

ColourRGB operator * ( const ColourRGB& c, float s )
{
	return ColourRGB ( c.get_red ( ) * s, c.get_green ( ) * s, c.get_blue ( ) * s );
}

ColourRGB operator * ( float s, const ColourRGB& c )
{
	return ColourRGB ( c.get_red ( ) * s, c.get_green ( ) * s, c.get_blue ( ) * s );
}
