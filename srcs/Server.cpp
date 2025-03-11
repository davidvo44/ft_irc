/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:11:46 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 20:35:15 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ExceptionError.hpp"
#include <signal.h>
#include "DefineList.hpp"

Server::Server()
{
	_Port = 6698;
	ServerInit();
}

static int serverSocket = -1;

static void signalHandler(int signum)
{
	if (signum == SIGINT)
	{

		std::cout << "\nServer closed" << std::endl;
		if (serverSocket != -1)
			close(serverSocket);
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

void Server::AcceptNewClient(pollfd &tmp, std::string IpAdd)
{
	std::string response;
	std::string nick;

	_Clients[tmp.fd] = new Client(tmp, IpAdd);
	nick = _Clients[tmp.fd]->getNick();
	response = RPL_WELCOME(nick) + RPL_YOURHOST(nick) + RPL_CREATED(nick) + RPL_MYINFO(nick);
	send(tmp.fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	//RplMessage::GetRply(RPL_WELCOME, tmp.fd, 3, _Clients[tmp.fd]->getNick().c_str(), _Clients[tmp.fd]->getName().c_str(),
	//_Clients[tmp.fd]->getIpAddr().c_str());
	// RplMessage::GetRply(RPL_YOURHOST, tmp.fd, 0, "");
	// RplMessage::GetRply(RPL_CREATED, tmp.fd, 0, "");
	// RplMessage::GetRply(RPL_MYINFO, tmp.fd, 0, "");
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
