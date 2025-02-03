#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <vector>
#include <sstream>

class Message
{
	private:
		std::string _prefix;    //  std::string prefix = ":" + clientNick + "!" + clientUser + "@" + clientHost;
		std::string _command;
		std::string _to;
		std::string _content;
		std::vector<std::string> _words;

	public:
		Message();
		Message(std::string buffer);
		void parse();
		std::string getPrefix();
		std::string getCommand();
		std::string getTo();
		std::string getContent();
};

#endif