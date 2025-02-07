#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "./../../header/ft_irc.hpp"
#include "../Server/Server.hpp"

class Client
{
private:
	pollfd _pollfds;
	std::string _name;
	std::string _nick;
	std::string _password;
	std::string _IpAdd;
public:
	Client();
	Client(pollfd tmp, std::string IpAddr);
	int GetFd();
	std::string GetName();
	std::string GetNick();
	std::string GetPassword();
	std::string GetIpAdd();
	void SetName(std::string name);
	void SetNick(std::string nick);
	void SetPassword(std::string pass);
	void setIpAdd(std::string ipadd);
};

#endif