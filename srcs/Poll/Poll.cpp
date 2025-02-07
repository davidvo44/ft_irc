#include "Poll.hpp"
#include "../ExceptionError/ExceptionError.hpp"
#include "../Command/Command.hpp"
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
				buffer[valread] = '\0';
				Command::GetLineCommand(buffer, _fds[i].fd, *_server);
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
	_server->AcceptNewClient(newfd, inet_ntoa(tmp.sin_addr));
	_fds.push_back(newfd);
}
