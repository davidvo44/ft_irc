#ifndef RPLMESSAGE_HPP
#define RPLMESSAGE_HPP

#include <iostream> 
#include <vector>
#include <cstdarg>

class RplMessage
{
public:
	static void GetRply(int code, int fd, int size, const char * value, ...);
};

#endif