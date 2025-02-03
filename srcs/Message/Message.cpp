#include "Message.hpp"

Message::Message(){}

Message::Message(std::string buffer)
{
	std::istringstream iss(buffer);
    std::string StrCut;

    while (iss >> StrCut)
        _words.push_back(StrCut);
}

void Message::Check_CMD()
{
	
}