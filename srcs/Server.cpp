
#include "Server.hpp"
#include "ExceptionError.hpp"
#include <signal.h>
#include "DefineList.hpp"

Server::Server()
{
	_Port = 6698;
	ServerInit();
}

Server::Server(const char *argPort, const char *argPass)
{
	if (atoi(argPort) > 65365)
	{
		std::cout << "Port chosen is greater than 65365!" << std::endl;
		return;
	}
	_Port = atoi(argPort);
	_password = argPass;
	memset(&_ServerAddr, 0, sizeof(_ServerAddr));
	_ServerAddr.sin_family = AF_INET;
	_ServerAddr.sin_addr.s_addr = INADDR_ANY;
	_ServerAddr.sin_port = htons(_Port);
	ServerInit();
}

Server* Server::getInstance(const char *argPort, const  char *argPass)
{
	if (!_instance)
		_instance = new Server(argPort, argPass);
	return _instance;
}
Server* Server::getInstance()
{
	if (!_instance)
		_instance = new Server();
	return _instance;
}

static int serverSocket = -1;

static void signalHandler(int signum)
{
	if (signum == SIGINT)
	{
		std::cout << "\nServer closed" << std::endl;
		if (serverSocket != -1)
			close(serverSocket);
		Server::getInstance()->freeCloseAll();
		delete Server::getInstance();
		throw ExceptionError("SIGINT");
	}
}

void Server::ServerInit()
{
	_SerSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	serverSocket = _SerSocketFd;
	int opt = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		close(serverSocket);
		throw ExceptionError("setsockopt");
	}
	if (_SerSocketFd < 0)
		throw ExceptionError("socket");
	signal(SIGINT, signalHandler);
	if (bind(_SerSocketFd, (struct sockaddr *)&_ServerAddr, sizeof(_ServerAddr)) < 0)
	{
		close(_SerSocketFd);
		throw ExceptionError("bind");
	}

	if (listen(_SerSocketFd, 128) < 0)
	{
		close(_SerSocketFd);
		throw ExceptionError("listen");
	}
	std::cout << "Server listening on port " << _Port << std::endl;
}

Client Server::getIdxClients(int idx)
{
	return (*_Clients[idx]);
}

MutantMap<std::string, Channel *> &Server::getChannel()
{
	return (_Channel);
}

MutantMap<int, Client *> &Server::getClients()
{
	return (_Clients);
}

sockaddr_in Server::getServerAddr()
{
	return (_ServerAddr);
}
int Server::getFd()
{
	return _SerSocketFd;
}
void Server::CheckNewClient(int fd, std::string IpAdd)
{
	_Clients[fd] = new Client(fd, IpAdd);
}

void Server::AcceptNewClient(int fd)
{
	std::string response;
	std::string nick;

	nick = _Clients[fd]->getNick();
	response = RPL_WELCOME(nick) + RPL_YOURHOST(nick) + RPL_CREATED(nick) + RPL_MYINFO(nick);
	send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

void Server::CloseFds()
{
}

void Server::ClearClients(int fd)
{
	(void)fd;
}

Channel *Server::CreateChannel(Client *client, std::string ChName)
{
	Channel *NewChannel = new Channel(ChName, client);
	return (NewChannel);
}

Client *Server::operator[](unsigned index)
{
	return _Clients.GetValueIndex(index);
}

std::string Server::getPassword()
{
	return _password;
}

void Server::freeCloseAll()
{
	MutantMap<int, Client *>::iterator itCl = _Clients.begin();
	while (itCl != _Clients.end())
	{
		close (itCl->second->getFd());
		delete itCl->second;
		itCl++;
	}
	MutantMap<std::string, Channel *>::iterator itCh = _Channel.begin();
	while (itCh != _Channel.end())
	{
		if (itCh->second)
			delete itCh->second;
		itCh++;
	}
}

bool Server::getLogBot()
{
	return _logBot;
}

void Server::setLogBot(bool value)
{
	_logBot = value;
}
