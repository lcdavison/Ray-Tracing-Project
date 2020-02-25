#include "image/pngwriter.h"

PNGWriter::PNGWriter ( unsigned int p_width, unsigned int p_height ) : m_width ( p_width ), m_height ( p_height ) 
{ }

PNGWriter::~PNGWriter ( ) { }

bool PNGWriter::write_image ( const std::string& p_filepath, std::vector < ColourRGB >& p_colourbuffer )
{
	png_structp png_ptr 	= nullptr;
	png_infop   info_ptr 	= nullptr;
	png_byte**  row_ptrs	= nullptr;
	
	m_file_ptr = std::fopen ( p_filepath.c_str ( ), "wb" );

	if ( !m_file_ptr )
	{
		return false;
	}

	png_ptr = png_create_write_struct ( PNG_LIBPNG_VER_STRING, NULL, NULL, NULL );

	if ( !png_ptr )
	{
		return false;
	}

	info_ptr = png_create_info_struct ( png_ptr );

	if ( !info_ptr )
	{
		return false;
	}

	//	Setup Header
	png_set_IHDR ( png_ptr, info_ptr, m_width, m_height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT );

	//	Initialize image rows
	row_ptrs = ( png_byte** ) png_malloc ( png_ptr, sizeof ( png_byte* ) * m_height );

	for ( int y = 0; y < m_height; ++y )
	{
		png_byte* row = ( png_byte* ) png_malloc ( png_ptr, sizeof ( png_byte ) * 3 * m_width );
		row_ptrs [ ( m_height - 1 ) - y ] = row;

		//	Set row data
		for ( int x = 0; x < m_width; ++x )
		{
			unsigned int pixel_colour = p_colourbuffer.at ( y * m_width + x ).int_format ( );
			
			//	Red
			*row = ( pixel_colour & 0xFF0000 ) >> 16;
			row++;

			//	Green
			*row = ( pixel_colour & 0x00FF00 ) >> 8;
			row++;

			//	Blue
			*row = ( pixel_colour & 0x0000FF );
			row++;
		}
	}

	png_init_io ( png_ptr, m_file_ptr );
	png_set_rows ( png_ptr, info_ptr, row_ptrs );
	png_write_png ( png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL );

	//	Clear up memory
	for ( int y = 0; y < m_height; ++y )
	{
		png_free ( png_ptr, row_ptrs [ y ] );
	}

	png_free ( png_ptr, row_ptrs );

	std::fclose ( m_file_ptr );

	return true;
}
