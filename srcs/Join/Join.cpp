#include "Join.hpp"

void Join::JoinChannel(std::string ChannelName)
{
	ChannelName.erase(0, 5);
	std::cout << "Client has join " << ChannelName << std::endl;
	
}