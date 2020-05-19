#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include <string>
#include <vector>
#include <cstdio>

#include "maths/maths.h"

/*
 *	Provides a standard interface for writing images
 * */
class IImageWriter 
{
	public:

		virtual bool write_image ( const std::string&, std::vector < ColourRGB >& ) = 0;
};
#endif
