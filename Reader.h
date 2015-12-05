#ifndef READER_H
#define READER_H

#include "Board.h"

class Reader
{
public:
	static Board read_file(const char* filename);
};

#endif
