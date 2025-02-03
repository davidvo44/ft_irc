#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "./../../header/ft_irc.hpp"
#include "../Server/Server.hpp"

class Client
{
private:
	pollfd _pollfds;
	std::string _name;
	std::string _password;
public:
	Client();
	Client(pollfd tmp);
	int GetFd();
	std::string GetName();
	std::string GetPassword();
	void SetName(std::string name);
	void SetPassword(std::string pass);
	void setIpAdd(std::string ipadd);
};

#endif