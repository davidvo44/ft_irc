
#include "Client.hpp"
#include <sstream>

Client::Client() : _username("User"), _nick("NickUser"), _suffixword("0"), _IpAddr("empty")
{
	std::cout << "Athentification...." << std::endl;
}

Client::Client(pollfd &tmp, std::string IpAddr) : _pollfds(tmp), _username("User"), _suffixword("0"), _IpAddr(IpAddr), _logStep(0)
{
	std::string code;
	std::stringstream ss;
	ss << tmp.fd;
	_nick = "NickUser" + ss.str();
	std::cout << "Athentification...." << std::endl;
	std::string response = "Authentification....\n";
	send(_pollfds.fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
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

unsigned int Client::getLogStep()
{
	return _logStep;
}

void Client::setLogStep(unsigned int nbr)
{
	_logStep = nbr;
}

std::string Client::getPrefix()
{
	std::string prefix = ":" + _nick + "!" + _username + "@" + _IpAddr + " ";
	return (prefix);
}
