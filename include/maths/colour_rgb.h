#ifndef COLOUR_RGB_H
#define COLOUR_RGB_H
class ColourRGB 
{
	public:

		ColourRGB ( );
		ColourRGB ( float, float, float );
		ColourRGB ( const ColourRGB& ) = default;

		float 		get_red	( ) 	const;
		float 		get_green ( ) 	const;
		float 		get_blue ( ) 	const;

		unsigned int 	int_format ( ) 	const;

	private:

		float 		m_red;
		float 		m_green;
		float 		m_blue;
};

//	Define operators for colour
ColourRGB operator + ( const ColourRGB&, const ColourRGB& );
ColourRGB operator * ( const ColourRGB&, const ColourRGB& );
#endif
