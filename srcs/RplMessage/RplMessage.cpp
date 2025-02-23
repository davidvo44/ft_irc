#include "RplMessage.hpp"
#include <cstring>
#include <unistd.h>
#include <sstream>

void RplMessage::GetRply(int code, int fd, int size, const char * value, ...)
{
	std::va_list args;
	std::string final_msg;
	std::vector <std::string> arg_list;
	std::ostringstream ss;
    ss << code;
	std::string scode = ss.str();
    va_start(args, value);
	arg_list.push_back(std::string(value));
	for (int i = 1; i < size; i++)
        arg_list.push_back(std::string(va_arg(args, const char*)));
	va_end(args);

	switch (code)
	{
		case 324:
			final_msg =  arg_list[1] + " " + arg_list[2];
		case 331:
			final_msg = arg_list[1] + " :No topic is set";
			break;
		case 332:
			final_msg = arg_list[1] + " :" + arg_list[2];
			break;
		case 341:
			break;
	}
	std::string response = ":irc.com " + scode + " " + arg_list[0] + " " + final_msg + "\n";
    send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}
