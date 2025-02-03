#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>

class Message
{
	private:
		std::string _prefix;
		std::string _command;
		std::string _to;
		std::string _content;

	public:
		Message();
		Message(std::string buffer);
};

#endif