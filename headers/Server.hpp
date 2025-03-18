
#ifndef SERVER_HPP
# define SERVER_HPP

#include "ft_irc.hpp"
#include "Bot.hpp"
#include "MutantMap.hpp"

class Channel;
class Client;

class Server
{
public:
	Server();
	static Server* getInstance(const char *argPort, const  char *argPass);
	static Server* getInstance();
	Server(const char *argPort, const  char *argPass);
	~Server();
	int getFd();
	Client getIdxClients(int idx);
	std::string getPassword();
	Bot *getBot();
	void setBot(Bot *bot);
	MutantMap<int, Client *> &getClients();
	MutantMap<std::string, Channel *> &getChannel();
	sockaddr_in getServerAddr();
	void ServerInit();
	void CheckNewClient(int fd, std::string IpAdd);
	void CheckNewBot(int sock[2]);
	void AcceptNewClient(int fd);
	void CloseFds();
	void ClearClients(int fd);
	Channel *CreateChannel(Client *client, std::string ChName);
	Client * operator[](unsigned index);

private:
	int _Port;
	int _SerSocketFd;
	std::string _password;
	MutantMap<int, Client *> _Clients;
	MutantMap<std::string, Channel *> _Channel;
	struct sockaddr_in _ServerAddr;
	static Server* _instanceServ;
	Bot *_bot;
};

#include "Channel.hpp"
#include "Poll.hpp"

#endif
