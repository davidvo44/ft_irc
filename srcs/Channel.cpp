/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:38 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/25 18:17:04 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() {}

Channel::Channel(std::string name, Client *client) : _name(name)
{
	_Clients.insert(std::make_pair(client->GetFd(), client));
	_operator.push_back(client->GetFd());
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

std::map<int, Client *> &Channel::GetClient()
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
	std::cout << "ADDDDD\n";
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
	std::cout << "DELETEEEEE\n";
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

std::vector<int> &Channel::getOperator()
{
	return _operator;
}

std::string Channel::getName()
{
	return _name;
}
