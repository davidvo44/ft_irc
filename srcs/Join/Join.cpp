#include "Join.hpp"

void Command::JoinChannel(std::string ChannelName)
{
	ChannelName.erase(0, 5);
	std::cout << "Client has join " << ChannelName << std::endl;
	
}

void Command::PrivateMessage(Message message, Client Sender)
{
	// std::map<int, Client*>::iterator it = _server->getClients().find(_fds[i].fd);
	// std::map<std::string, Channel> _Channel;
}