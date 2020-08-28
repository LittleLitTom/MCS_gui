#pragma once
#include <stdlib.h>

union MyUnion
{
	float float_;
	unsigned int uint_;
};

class utilities
{
public:
	static unsigned int floatToByte(float float_);
	static float byteToFloat(unsigned int uint_);
};
