/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:40 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/28 05:43:03 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <sstream>

Client::Client() : _name("User"), _nick("NickUser"), _password("0"), _IpAdd("empty")
{
	std::cout << "Client connectedsss" << std::endl;
}

Client::Client(pollfd &tmp, std::string IpAddr) : _pollfds(tmp), _name("User"), _password("0"), _IpAdd(IpAddr)
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

std::string Client::GetPrefix()
{
	std::string prefix = ":" + _nick + "!" + _name + "@" + _IpAdd + " ";
	return (prefix);
}