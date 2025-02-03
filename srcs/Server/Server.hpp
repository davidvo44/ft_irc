#ifndef SERVER_HPP
#define SERVER_HPP

#include "./../../header/ft_irc.hpp"

class Client;
class Channel;

class Server //-> class for server
{
private:
	int _Port;
	int _SerSocketFd;
	std::map<int, Client> _Clients;
	std::map<std::string, Channel> _Channel;
	struct sockaddr_in _ServerAddr;
public:
	Server();
	int getFD();
	Client getIdxClients(int idx);
	std::map<int, Client> &getClients();
	sockaddr_in getServerAddr();
	void ServerInit();
	void AcceptNewClient(pollfd tmp);
	void CloseFds();
	void ClearClients(int fd);
	void JoinChannel(Client client, std::string ChName);
	Channel CreateChannel(Client client, std::string ChName);
	void SendMessage(std::string ChName, Client clientSender);
};

#include "./../Client/Client.hpp"
#include "./../Channel/Channel.hpp"

#endif