/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivo <garivo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:40 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/26 00:12:23 by garivo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <sstream>

Client::Client() : _name("User") , _nick("NickUser"), _password("0"), _IpAdd("empty")
{
	std::cout << "Client connectedsss" << std::endl;
}

Client::Client(pollfd tmp, std::string IpAddr) : _pollfds(tmp) , _name("User"), _password("0"), _IpAdd(IpAddr), _log(true)
{
	std::string code;
	std::stringstream ss;
    ss << tmp.fd;
	_nick = "NickUser" + ss.str();
	std::cout << "Client connected" << std::endl;
}

int Client::GetFd()
{
	return _pollfds.fd;
}


std::string Client::GetName()
{
	return (_name);
}

std::string Client::GetNick()
{
	return (_nick);
}

std::string Client::GetPassword()
{
	return (_password);
}

std::string Client::GetIpAdd()
{
	return (_IpAdd);
}

void Client::SetName(std::string name)
{
	_name = name;
}

void Client::SetNick(std::string nick)
{
	_nick = nick;
}

void Client::SetPassword(std::string pass)
{
	_password = pass;
}

void Client::setIpAdd(std::string IpAdd)
{
	_IpAdd = IpAdd;
}

void Client::setLog(bool change)
{
	_log = change;
}
