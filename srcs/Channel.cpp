/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:38 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/03 17:18:38 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() {}

Channel::Channel(std::string name, Client *client) : _name(name), _mode(0)
{
	_Clients.insert(std::make_pair(client->GetFd(), client));
	_operator.push_back(client->GetFd());
	_bot = new Bot(_name, client->GetPrefix());
}

Channel::~Channel() {}

void Channel::AddClient(Client *client)
{
	_Clients[client->GetFd()] = client;
}

void Channel::JoinChannel(Client *client)
{
	_Clients.insert(std::make_pair(client->GetFd(), client));
}

void Channel::PartChannel(Client client)
{
	std::cout << client.GetNick() << " LEFT" << std::endl;
	_Clients.erase(client.GetFd());
}

MutantMap<int, Client *> &Channel::GetClient()
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

bool Channel::IsOperator(int client)
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

bool Channel::IsWlist(int client)
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

void Channel::addToWhitelist(std::string client)
{
	_whitelist.push_back(client);
}

std::vector<int> &Channel::getOperator()
{
	return _operator;
}

std::string Channel::getName()
{
	return _name;
}

std::string Channel::getPassword()
{
	return (_password);
}

void Channel::setPassword(std::string pass)
{
	_password = pass;
}

Client *Channel::operator[](unsigned index)
{
	return _Clients.GetValueIndex(index);
}

Client *Channel::operator!=(unsigned index)
{
	return _Clients.GetValueIndex(index);
}
