
#include "Server.hpp"
#include "ExceptionError.hpp"
#include <signal.h>
#include "DefineList.hpp"

Server::Server()
{
	_Port = 6698;
	ServerInit();
}

Server::Server(const char *argPort, const char *argPass) : _bot(NULL)
{
	std::string port = argPort;
	std::stringstream stream(port);
	int portIntFormat;

	stream >> portIntFormat;
	if (stream.fail())
		throw ExceptionError("Port overflow: You've managed to make it overflow with");
	if (portIntFormat > 65365 || portIntFormat < 2048)
		throw ExceptionError("Port chosen is greater than 65365 or lower than 2048: If you choose another port you will achieve");
	_Port = portIntFormat;
	_password = argPass;
	memset(&_ServerAddr, 0, sizeof(_ServerAddr));
	_ServerAddr.sin_family = AF_INET;
	_ServerAddr.sin_addr.s_addr = INADDR_ANY;
	_ServerAddr.sin_port = htons(_Port);
	ServerInit();
}

Server::~Server()
{
	for (MutantMap<int, Client *>::iterator itCl = _Clients.begin();itCl != _Clients.end(); itCl++)
		delete itCl->second;
	for (MutantMap<std::string, Channel *>::iterator itCh = _Channel.begin(); itCh != _Channel.end(); itCh++)
		delete itCh->second;
	close (_SerSocketFd);
}

Server* Server::getInstance(const char *argPort, const  char *argPass)
{
	if (!_instanceServ)
		_instanceServ = new Server(argPort, argPass);
	return _instanceServ;
}
Server* Server::getInstance()
{
	if (!_instanceServ)
		_instanceServ = new Server();
	return _instanceServ;
}


static void signalHandler(int signum)
{
	if (signum == SIGINT)
	{
		std::cout << "\nServer closed" << std::endl;
		delete Poll::getInstance();
		throw ExceptionError("SIGINT");
	}
}

void Server::ServerInit()
{
	_SerSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	int opt = 1;
	if (setsockopt(_SerSocketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		close(_SerSocketFd);
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

Bot *Server::getBot()
{
	return _bot;
}

void Server::setBot(Bot *bot)
{
	_bot = bot;
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

void Server::CheckNewBot(int sock[2])
{
	Bot *bot = new Bot(sock[0], sock[1]);

	_Clients[sock[0]] = bot;
	_bot = bot;
	bot->initBot();
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
