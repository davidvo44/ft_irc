
#include "Poll.hpp"
#include "ExceptionError.hpp"
#include "Command.hpp"
#include "Message.hpp"

#include <cstdlib>
#include <unistd.h>

Poll::Poll(Server *server) : _server(server)
{
	pollfd tmp;
	tmp.events = POLLIN;
	tmp.fd = server->getFd();
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
				std::cout << "\n\n" << "NEW COMMAND:\n";
				char buffer[1024] = {0};
				int valread = recv(_fds[i].fd, buffer, sizeof(buffer), MSG_DONTWAIT | MSG_NOSIGNAL);
				if (valread <= 0)
				{
					Command::QuitClient(_fds[i].fd, *this, i);
					continue;
				}
				buffer[valread] = '\0';
				std::cout << "RECEIVED : < " << buffer;
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

	fdNewClient = accept(_server->getFd(), (struct sockaddr *)&tmp, &addrlen);
	if (fdNewClient < 0)
		throw ExceptionError("Accept Fail");
	std::cout << "New client accepted : " << inet_ntoa(tmp.sin_addr) << std::endl;
	newfd.events = POLLIN;
	newfd.fd = fdNewClient;
	newfd.revents = 0;
	_server->CheckNewClient(newfd, inet_ntoa(tmp.sin_addr));
	_fds.push_back(newfd);
}

std::vector<pollfd> & Poll::getPollfd()
{
	return _fds;
}

Server & Poll::getServer()
{
	return *_server;
}
