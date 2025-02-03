#include "Client.hpp"

Client::Client()
{
	std::cout << "Client connected" << std::endl;
}

Client::Client(pollfd tmp) : _pollfds(tmp), _name("User"), _password("0")
{
	std::cout << "Client connected" << std::endl;
}

int Client::GetFd()
{
	return _pollfds.fd;
}

void Client::setIpAdd(std::string IpAdd)
{
	(void)IpAdd;
}

std::string Client::GetName()
{
	return (_name);
}

std::string Client::GetPassword()
{
	return (_password);
}

void Client::SetName(std::string name)
{
	_name = name;
}

void Client::SetPassword(std::string pass)
{
	_password = pass;
}
