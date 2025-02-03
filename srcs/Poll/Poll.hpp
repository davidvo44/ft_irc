#ifndef POLL_HPP
#define POLL_HPP

#include "../Server/Server.hpp"
#include "vector"

class Poll
{
private:
	std::vector<pollfd> _fds;
	Server *_server;
public:
	Poll(Server *server);
	void NewUser();
	void Start();
};

#endif