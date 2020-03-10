#ifndef PNG_WRITER_H
#define PNG_WRITER_H

#include <png.h>

#include "imagewriter.h"

class PNGWriter : public IImageWriter 
{
	public:

		PNGWriter ( );
		PNGWriter ( unsigned int, unsigned int );

		~PNGWriter ( );

		bool 		write_image ( const std::string&, std::vector < ColourRGB >& );

	private:

		unsigned int 	m_width    = 500;
		unsigned int 	m_height   = 500;
		FILE*		m_file_ptr = nullptr;
};
#endif
