
#include "Channel.hpp"

Channel::Channel() {}

Channel::Channel(std::string name, Client *client) : _username(name), _mode(0)
{
	_Clients.insert(std::make_pair(client->getFd(), client));
	_operator.push_back(client->getFd());
	_bot = new Bot(_username, client->getPrefix());
}

Channel::~Channel()
{
	delete _bot;
}

void Channel::addClient(Client *client)
{
	_Clients[client->getFd()] = client;
}

void Channel::joinChannel(Client *client)
{
	_Clients.insert(std::make_pair(client->getFd(), client));
}

void Channel::removeClient(MutantMap<int, Client*>& clients, int clientKey, std::string clientNick)
{
	MutantMap<int, Client*>::iterator it = clients.find(clientKey);
	if (it != clients.end())
	{
		delete it->second;
		clients.erase(it);
		std::cout << clientNick << " removed successfully." << std::endl;
	}
	else
		std::cout << clientNick << " not found." << std::endl;
}

void Channel::partChannel(Client& client)
{
	std::cout << client.getNick() << " PART" << std::endl;
	_Clients.erase(client.getFd());
	std::vector<int>::iterator it = std::find(_operator.begin(), _operator.end(), client.getFd());
	if (it != _operator.end())
		_operator.erase(it);
	else
		return;
}

MutantMap<int, Client *> &Channel::getClient()
{
	return _Clients;
}

void Channel::setTopic(const std::string topic)
{
	_targetpic = topic;
}

const std::string Channel::getTopic()
{
	return _targetpic;
}

Bot *Channel::getBot()
{
	return _bot;
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
	std::cout << _mode << std::endl;
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

bool Channel::isOperator(int client)
{
	int i = 0;

	if (_operator.empty() == true)
		return false;
	while (_operator[i] != _operator.back())
	{
		if (_operator[i] == client)
			return true;
		i++;
	}
	if (_operator[i] == client)
		return true;
	return false;
}

bool Channel::isInWhitelist(int client)
{
	int i = 0;

	if (_wlist.empty() == true)
		return false;
	while (_wlist[i] != _wlist.back())
	{
		if (_wlist[i] == client)
			return true;
		i++;
	}
	if (_wlist[i] == client)
		return true;
	return false;
}

void Channel::addToWhitelist(int client)
{
	_wlist.push_back(client);
}

std::vector<int> &Channel::getOperator()
{
	return _operator;
}

std::string Channel::getName()
{
	return _username;
}

std::string Channel::getSuffixword()
{
	return (_suffixword);
}

void Channel::setPassword(std::string pass)
{
	_suffixword = pass;
}

Client *Channel::operator[](unsigned index)
{
	return _Clients.GetValueIndex(index);
}

Client *Channel::operator!=(unsigned index)
{
	return _Clients.GetValueIndex(index);
}
