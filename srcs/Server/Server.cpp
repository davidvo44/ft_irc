#include "Server.hpp"
#include "./../ExceptionError/ExceptionError.hpp"

Server::Server()
{
	_Port = 6698;
	ServerInit();
}

void Server::ServerInit()
{
	_SerSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_SerSocketFd < 0)
		throw ExceptionError("socket");
	memset(&_ServerAddr, 0, sizeof(_ServerAddr));
    _ServerAddr.sin_family = AF_INET;
    _ServerAddr.sin_addr.s_addr = INADDR_ANY; 
    _ServerAddr.sin_port = htons(_Port);

	if (bind(_SerSocketFd, (struct sockaddr *)&_ServerAddr, sizeof(_ServerAddr)) < 0)
	{
        close(_SerSocketFd);
        throw ExceptionError("bind");
    }
	if (listen(_SerSocketFd, 5) < 0)
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

std::map<std::string, Channel> & Server::getChannel()
{
	return (_Channel);
}

std::map<int, Client*> & Server::getClients()
{
	return (_Clients);
}

sockaddr_in Server::getServerAddr()
{
	return (_ServerAddr);
}
int Server::getFD()
{
	return _SerSocketFd;
}

void Server::AcceptNewClient(pollfd &tmp, std::string IpAdd)
{
	_Clients[tmp.fd] = new Client(tmp, IpAdd);

}

void Server::CloseFds()
{

}
void Server::ClearClients(int fd)
{
	(void)fd;
}

Channel Server::CreateChannel(Client client, std::string ChName)
{
	Channel NewChannel(ChName, client);
	return (NewChannel);
}
