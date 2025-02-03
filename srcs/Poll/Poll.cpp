#include "Poll.hpp"
#include "../ExceptionError/ExceptionError.hpp"
#include "../Join/Join.hpp"
#include <cstdlib> 
#include <unistd.h>
#include "../Message/Message.hpp"

Poll::Poll(Server *server) : _server(server)
{
	pollfd tmp;
	tmp.events = POLLIN;
	tmp.fd = server->getFD();
	tmp.revents = 0;
	_fds.push_back(tmp);
}

void Poll::Start()
{
	while (1)
	{
		int activity = poll(_fds.data(), _fds.size(), -1);
		if (activity < 0)
			throw ExceptionError("Poll Error");
		if (_fds[0].revents & POLLIN)
			NewUser();
		for (size_t i = 1; i < _fds.size(); i++)
		{
			if (_fds[i].revents & POLLIN)
			{
				char buffer[1024] = {0};
				int valread = read(_fds[i].fd, buffer, sizeof(buffer));
				if (valread <= 0)
				{
					std::cout << "Client disconnected." << std::endl;
					close(_fds[i].fd);
					_fds.erase(_fds.begin() + i);
					continue;
				}
				buffer[valread - 1] = 0;
				std::string str(buffer);
				Message str_message(str);
				std::map<int, Client*>::iterator it = _server->getClients().find(_fds[i].fd);
				if (str_message.getCommand() == "JOIN")
					_server->JoinChannel(*it->second, str);
				else if (str_message.getCommand() == "USER")
					(it->second)->SetName(str.erase(0, 5));
				else //if (str.compare(0, 7, "PRIVMSG") == 0)
				{
            		write(_fds[i].fd, it->second->GetName().c_str(), strlen(it->second->GetName().c_str()));
					write(_fds[i].fd, ": ", 2);
            		write(_fds[i].fd, buffer, valread - 1);
            		write(_fds[i].fd, "\n", 1);
				}
			}
		}
	}
}

void Poll::NewUser()
{
	sockaddr_in tmp = _server->getServerAddr();
	socklen_t addrlen = sizeof(_server->getServerAddr());
	pollfd newfd;
	int fdNewClient;

	fdNewClient = accept(_server->getFD(), (struct sockaddr *)&tmp, &addrlen);
	if (fdNewClient < 0)
		throw ExceptionError("Accept Fail");
	std::cout << "New client accepted : " << inet_ntoa(tmp.sin_addr) << std::endl;
	newfd.events = POLLIN;
	newfd.fd = fdNewClient;
	newfd.revents = 0;
	_server->AcceptNewClient(newfd);
	_fds.push_back(newfd);
}
