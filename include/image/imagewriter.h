#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include <string>
#include <vector>
#include <cstdio>

#include "maths/maths.h"

class IImageWriter 
{
	public:

		virtual bool write_image ( const std::string&, const std::vector < ColourRGB >& ) = 0;
};
#endif