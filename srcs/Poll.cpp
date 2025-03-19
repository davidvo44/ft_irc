
#include "Poll.hpp"
#include "ExceptionError.hpp"
#include "Command.hpp"
#include "Message.hpp"

#include <cstdlib>
#include <unistd.h>

#define RED     "\033[31m"
#define RESET   "\033[0m"

Poll::Poll() : _server(NULL)
{
}

Poll::Poll(Server *server) : _server(server)
{
	pollfd tmp;
	tmp.events = POLLIN;
	tmp.fd = server->getFd();
	tmp.revents = 0;
	_fds.push_back(tmp);
}

Poll::~Poll()
{
	delete _server;
}

void	Poll::receiveMessage(int fd)
{
	std::string message;
	char buffer[1024] = {0};
	int valread = recv(fd, buffer, sizeof(buffer), MSG_DONTWAIT);
	if (valread <= 0)
	{
		std::cout << "client quit\n";
		Command::QuitClientfromPoll(fd, *_server);
		return;
	}
	_read_buffer[fd] += buffer;
	while (_read_buffer[fd].find("\n") != std::string::npos)
	{
		message = _read_buffer[fd].substr(0, _read_buffer[fd].find("\n"));
		_read_buffer[fd] = _read_buffer[fd].substr(_read_buffer[fd].find("\n") + 1);
		if (message.length() > 512)
		{
			_read_buffer[fd].clear();
			return;
		}
		std::cout << RED << message << RESET << std::endl;
		Command::GetLineCommand((char *)message.c_str(), fd, *_server);
	}
}

void Poll::DeleteClientPoll(int fd)
{
	std::cout << "Client disconnected." << std::endl;
	for (size_t i = 1; i < _fds.size(); i++)
	{
		if (_fds[i].fd == fd)
		{
			std::map<int, std::string>::iterator buffer_it = _read_buffer.find(fd);
			if (buffer_it != _read_buffer.end())
				_read_buffer.erase(buffer_it);
			_fds.erase(_fds.begin() + i);
			break;
		}
	}
}

void Poll::Start()
{
	while (true)
	{
		int activity = poll(_fds.data(), _fds.size(), -1);
		if (activity < 0)
			throw ExceptionError("Poll");

		if (_fds[0].revents & POLLIN)
			NewUser();

		for (size_t i = 1; i < _fds.size(); i++)
		{
			if (_fds[i].revents & POLLIN)
				receiveMessage(_fds[i].fd);
		}
	}
}


void Poll::NewUser()
{
	sockaddr_in servAddr = _server->getServerAddr();
	socklen_t servAddrLen = sizeof(_server->getServerAddr());
	pollfd newfd;
	int fdNewClient;

	fdNewClient = accept(_server->getFd(), (struct sockaddr *)&servAddr, &servAddrLen);
	if (fdNewClient < 0)
		throw ExceptionError("Accept Fail");
	std::cout << "New client accepted : " << inet_ntoa(servAddr.sin_addr) << std::endl;
	newfd.events = POLLIN;
	newfd.fd = fdNewClient;
	newfd.revents = 0;
	_server->CheckNewClient(fdNewClient, inet_ntoa(servAddr.sin_addr));
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

Poll* Poll::getInstance(Server *server)
{
	if (!_instancePoll)
		_instancePoll = new Poll(server);
	return _instancePoll;
}
Poll* Poll::getInstance()
{
	if (!_instancePoll)
		_instancePoll = new Poll();
	return _instancePoll;
}
