
#include "main.hpp"

void debug(const char *color)
{
	std::cout << color << "DEBUG: " << RESET
			  << "function: " << __FUNCTION__ << ", line: " << __LINE__
			  << std::endl;
}