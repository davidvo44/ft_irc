
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
            {
                HandleClientInput(i);
            }
        }
    }
}

void Poll::HandleClientInput(size_t clientIndex)
{
    std::string partial_data;
    char buffer[1024];

    while (true)
    {
        ssize_t bytes_read = recv(_fds[clientIndex].fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_read < 0)
        {
            perror("recv failed");
            break;
        }
        else if (bytes_read == 0)
        {
            DisconnectClient(clientIndex);
            break;
        }
        buffer[bytes_read] = '\0';

        partial_data.append(buffer);
        ProcessCompleteLines(partial_data, clientIndex);

        if (!IsClientConnected(clientIndex))
            break;
    }
}

void Poll::ProcessCompleteLines(std::string& partial_data, size_t clientIndex)
{
    size_t pos;
    while ((pos = partial_data.find('\n')) != std::string::npos)
    {
        std::string line = partial_data.substr(0, pos);
        partial_data.erase(0, pos + 1);

        std::cout << "RECEIVED: <" << line << ">\n";
        Command::GetLineCommand((char *)line.c_str(), _fds[clientIndex].fd, *_server);
    }
}

void Poll::DisconnectClient(size_t clientIndex)
{
    Command::QuitClientfromPoll(_fds[clientIndex].fd, *_server);
    DisconnectClientPoll(clientIndex);
}

bool Poll::IsClientConnected(size_t clientIndex)
{
    return write(_fds[clientIndex].fd, "", 0) != -1;
}


// void Poll::Start()
// {
// 	ssize_t bytes_read;
// 	while (1)
// 	{
// 		int activity = poll(_fds.data(), _fds.size(), -1);
// 		if (activity < 0)
// 			throw ExceptionError("Poll");
// 		if (_fds[0].revents & POLLIN)
// 			NewUser();
// 		for (size_t i = 1; i < _fds.size(); i++)
// 		{
// 			if (_fds[i].revents & POLLIN)
// 			{
// 				std::string partial_data;

// 				std::cout << "\n\n" << "    NEW COMMAND:\n";
// 				char buffer[1024]/*  = {0} */;
// 				while (true)
// 				{
// 					bytes_read = recv(_fds[i].fd, buffer, sizeof(buffer) - 1, 0);
// 					if (bytes_read < 0)
// 					{
// 						perror("recv failed");
// 						// continue;
// 						break;
// 					}
// 					else if (bytes_read == 0)
// 					{
// 						Command::QuitClientfromPoll(_fds[i].fd, *_server);
// 						DisconnectClientPoll(i);
// 						break;
// 						// continue;
// 					}
// 					buffer[bytes_read] = '\0';

// 					partial_data.append(buffer);
// 					size_t pos;
// 					std::string line;
// 					while ((pos = partial_data.find('\n')) != std::string::npos)
// 					{
// 						line = partial_data.substr(0, pos);
// 						partial_data.erase(0, pos + 1);
// 					}

// 					std::cout << "RECEIVED : < " << line;
// 					Command::GetLineCommand((char *)line.c_str(), _fds[i].fd, *_server);
// 					if (write(_fds[i].fd, "", 0) == -1)
// 						DisconnectClientPoll(i);
// 				}

//     		}
// 		}
// 	}
// }


void Poll::NewUser()
{
	sockaddr_in tmp = _server->getServerAddr();
	socklen_t addrlen = sizeof(_server->getServerAddr());
	pollfd newfd;
	int fdNewClient;

	fdNewClient = accept(_server->getFd(), (struct sockaddr *)&tmp, &addrlen);
	if (fdNewClient < 0)
	{
		// close(fdNewClient);
		// close(_server->getFd());
		throw ExceptionError("Accept Fail");
	}
	std::cout << "New client accepted : " << inet_ntoa(tmp.sin_addr) << std::endl;
	newfd.events = POLLIN;
	newfd.fd = fdNewClient;
	newfd.revents = 0;
	_server->CheckNewClient(newfd, inet_ntoa(tmp.sin_addr));
	_fds.push_back(newfd);
}

void Poll::DisconnectClientPoll(int i)
{
	std::cout << "Client disconnected." << std::endl;
	_fds.erase(_fds.begin() + i);
}
std::vector<pollfd> & Poll::getPollfd()
{
	return _fds;
}

Server & Poll::getServer()
{
	return *_server;
}
