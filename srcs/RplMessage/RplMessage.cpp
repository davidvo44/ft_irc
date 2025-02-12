#include "RplMessage.hpp"
#include <cstring>
#include <unistd.h>
#include <sstream>

void RplMessage::GetRply(int code, int fd, int size, const char * value, ...)
{
	std::va_list args;
	std::string final_msg;
	std::vector <std::string> arg_list;
	std::string scode;
	std::stringstream ss;
    ss << scode;
    va_start(args, value);
	for (int i = 0; i < size; i++)
	{
        const char* p = va_arg(args, const char*);
        arg_list.push_back(std::string(p));
	}
	switch (code)
	{
		case 331:
			final_msg = arg_list[1] + " :No topic is set";
			break;
		case 332:
			final_msg = arg_list[1] + " :" + arg_list[2];
			break;
		case 341:
			break;
	write (fd, scode.c_str(), strlen(scode.c_str()));
	write (fd, arg_list[0].c_str(), strlen(arg_list[0].c_str()));
	write (fd, final_msg.c_str(), strlen(final_msg.c_str()));
	write (fd, "\n", 1);
	}
}
