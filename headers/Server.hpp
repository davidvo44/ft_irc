
#ifndef SERVER_HPP
# define SERVER_HPP

#include "ft_irc.hpp"
#include "MutantMap.hpp"

class Client;
class Channel;

class Server
{
public:
	Server();
	Server(const char *argPort, const  char *argPass);
	int getFd();
	Client getIdxClients(int idx);
	std::string getPassword();
	MutantMap<int, Client *> &getClients();
	MutantMap<std::string, Channel *> &getChannel();
	sockaddr_in getServerAddr();
	void ServerInit();
	void CheckNewClient(pollfd &tmp, std::string IpAdd);
	void AcceptNewClient(int fd);
	void CloseFds();
	void ClearClients(int fd);
	Channel *CreateChannel(Client *client, std::string ChName);
	Client * operator[](unsigned index);
	void freeCloseAll();

private:
	int _Port;
	int _SerSocketFd;
	std::string _password;
	MutantMap<int, Client *> _Clients;
	MutantMap<std::string, Channel *> _Channel;
	struct sockaddr_in _ServerAddr;
};

#include "Client.hpp"
#include "Channel.hpp"

#endif
