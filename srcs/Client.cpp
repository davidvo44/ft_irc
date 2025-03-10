/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:40 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 18:44:17 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <sstream>

Client::Client() : _username("User"), _nick("NickUser"), _suffixword("0"), _IpAddr("empty")
{
	std::cout << "Client connectedsss" << std::endl;
}

Client::Client(pollfd &tmp, std::string IpAddr) : _pollfds(tmp), _username("User"), _suffixword("0"), _IpAddr(IpAddr)
{
	std::string code;
	std::stringstream ss;
	ss << tmp.fd;
	_nick = "NickUser" + ss.str();
	std::cout << "Client connected" << std::endl;
}

int Client::getFd()
{
	return _pollfds.fd;
}

std::string Client::getName()
{
	return (_username);
}

std::string Client::getNick()
{
	return (_nick);
}

std::string Client::getIpAddr()
{
	return (_IpAddr);
}

void Client::setName(std::string name)
{
	_username = name;
}

void Client::setNick(std::string nick)
{
	_nick = nick;
}

void Client::setPassword(std::string pass)
{
	_suffixword = pass;
}

void Client::setIpAddr(std::string IpAdd)
{
	_IpAddr = IpAdd;
}

std::string Client::getPrefix()
{
	std::string prefix = ":" + _nick + "!" + _username + "@" + _IpAddr + " ";
	return (prefix);
}
