#include "Client.hpp"

Client::Client()
{
	std::cout << "Client connected" << std::endl;
}

Client::Client(pollfd tmp, std::string IpAddr) : _pollfds(tmp), _name("User") , _nick("NickUser"), _password("0"), _IpAdd(IpAddr), _log(true)
{
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