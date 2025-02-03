#include "Channel.hpp"

Channel::Channel()
{
	
}

Channel::Channel(std::string name, Client client) : _name(name)
{
	_Clients.insert(std::make_pair(client.GetFd(), client));
}

Channel::~Channel()
{

}

void Channel::AddClient(Client client)
{
	_Clients[client.GetFd()] = client;
}

void Channel::JoinChannel(Client client)
{
	_Clients.insert(std::make_pair(client.GetFd(), client));
}

std::map<int, Client> Channel::GetClient()
{
	return _Clients;
}
