#include "Server.hpp"
#include "./../ExceptionError/ExceptionError.hpp"

Server::Server()
{
	_Port = 6697;
	ServerInit();
}

void Server::ServerInit()
{
	_SerSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_SerSocketFd < 0) {
        throw ExceptionError("socket");
    }
	memset(&_ServerAddr, 0, sizeof(_ServerAddr));
    _ServerAddr.sin_family = AF_INET;
    _ServerAddr.sin_addr.s_addr = INADDR_ANY; 
    _ServerAddr.sin_port = htons(_Port);

	if (bind(_SerSocketFd, (struct sockaddr *)&_ServerAddr, sizeof(_ServerAddr)) < 0) {
        close(_SerSocketFd);
        throw ExceptionError("bind");
    }
	if (listen(_SerSocketFd, 5) < 0) {
		close(_SerSocketFd);
		throw ExceptionError("listen");
    }
	std::cout << "Server listening on port " << _Port << std::endl;
}

Client Server::getIdxClients(int idx)
{
	return (_Clients[idx]);
}

std::map<int, Client> & Server::getClients()
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

void Server::AcceptNewClient(pollfd tmp)
{
	Client Newclient(tmp);
	_Clients[tmp.fd] = Newclient;
}

void Server::CloseFds()
{

}
void Server::ClearClients(int fd)
{
	(void)fd;
}

void Server::JoinChannel(Client client, std::string ChName)
{
	ChName.erase(0, 5);
	std::map<std::string, Channel>::iterator it = _Channel.find(ChName);

    if (_Channel.empty() == false &&  it != _Channel.end())
	{ 
       it->second.JoinChannel(client);
    }
	else
	{
		std::cout << "creating " << ChName << std::endl;
		_Channel[ChName] = CreateChannel(client, ChName);
    }
}

Channel Server::CreateChannel(Client client, std::string ChName)
{
	Channel NewChannel(ChName, client);
	return (NewChannel);
}

void Server::SendMessage(std::string ChName, Client clientSender)
{
	std::map<std::string, Channel>::iterator ItChannel = _Channel.find(ChName);
	int fds = 0;

    if (_Channel.empty() == false &&  ItChannel != _Channel.end())
       return;
	std::map<int, Client>::iterator ItClient = ItChannel->second.GetClient().begin();
	while (ItClient != ItChannel->second.GetClient().end())
	{
		fds = ItClient->second.GetFd();
		write(fds, clientSender.GetName().c_str(), strlen(clientSender.GetName().c_str()));
		write(fds, ": ", 2);
		write(fds, buffer, valread);
		write(fds, "\n", 1);
		ItClient++;
	}
}