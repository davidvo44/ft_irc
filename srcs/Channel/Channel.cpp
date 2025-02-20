#include "Channel.hpp"

Channel::Channel(){}

Channel::Channel(std::string name, Client &client) : _name(name), _mode(0)
{
	_Clients.insert(std::make_pair(client.GetFd(), client));
	_operator.push_back(client.GetFd());
}

Channel::~Channel(){}

void Channel::AddClient(Client client)
{
	_Clients[client.GetFd()] = client;
}

void Channel::JoinChannel(Client client)
{
	_Clients.insert(std::make_pair(client.GetFd(), client));
}

void Channel::PartChannel(Client client)
{
	std::cout << client.GetNick() << " PARTING" << std::endl;
	_Clients.erase(client.GetFd());
}

std::map<int, Client> & Channel::GetClient()
{
	return _Clients;
}

void Channel::setTopic(const std::string topic)
{
	_topic = topic;
}

const std::string Channel::getTopic()
{
	return _topic;
}

void Channel::addMode(char ope)
{
	char array[] = {'i', 't', 'k', 'l'};
	int bit_position = 0;
	while (bit_position < 10)
	{
		if (ope == array[bit_position])
			break;
		bit_position++;
	}
	int mask = (1 << bit_position);
	_mode = _mode | mask;
}

void Channel::deleteMode(char ope)
{
	char array[] = {'i', 't', 'k', 'l'};
	int bit_position = 0;
	while (bit_position < 10)
	{
		if (ope == array[bit_position])
			break;
		bit_position++;
	}
	int mask = ~(1 << bit_position);
	_mode = _mode & mask;
}

bool Channel::viewMode(char ope)
{
	char array[] = {'i', 't', 'k', 'l'};
	int bit_position = 0;
	while (bit_position < 10)
	{
		if (ope == array[bit_position])
			break;
		bit_position++;
	}
	return (_mode & (1 << bit_position));
}
