/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:12:44 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 18:27:20 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	Poll::receiveMessage(int fd, int i)
{
	std::string message;
	char buffer[1024] = {0};
	int valread = recv(fd, buffer, sizeof(buffer), MSG_DONTWAIT);

	if (valread <= 0)
	{
		Command::QuitClient(fd, *this, i);
		return;
	}
	_read_buffer[fd] += buffer;
	while (_read_buffer[fd].find("\n") != std::string::npos)
	{
		message = _read_buffer[fd].substr(0, _read_buffer[fd].find("\n"));
		_read_buffer[fd] = _read_buffer[fd].substr(_read_buffer[fd].find("\n") + 1);
		if (message.length() > 512)
			return;
		std::cout << "RECEIVED : < " << message << " > from FD: " << fd << std::endl;
		Command::GetLineCommand((char *)message.c_str(), fd, *_server);
	}
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
				receiveMessage(_fds[i].fd, i);
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
	_server->AcceptNewClient(newfd, inet_ntoa(tmp.sin_addr));
	_fds.push_back(newfd);
	_read_buffer.insert(std::make_pair(newfd.fd, ""));
}

std::vector<pollfd> & Poll::getPollfd()
{
	return _fds;
}

std::map<int, std::string> & Poll::getReadBuffer()
{
	return _read_buffer;
}

Server & Poll::getServer()
{
	return *_server;
}
