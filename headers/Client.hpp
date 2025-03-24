
#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "ft_irc.hpp"

class Client
{
public:
	Client();
	Client(int fd, std::string IpAddr);
	virtual ~Client();
	int getFd();
	std::string getName();
	std::string getNick();
	std::string getIpAddr();
	unsigned int getLogStep();
	void setName(const std::string name);
	void setNick(const std::string nick);
	void setPassword(const std::string pass);
	void setIpAddr(const std::string ipadd);
	void setLogStep(unsigned int nbr);
	std::string getPrefix();

protected:
	int _fd;
	std::string _username;
	std::string _nick;
	std::string _suffixword;
	std::string _IpAddr;
	unsigned int _logStep;
};

#endif
