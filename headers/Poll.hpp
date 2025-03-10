
#ifndef POLL_HPP
# define POLL_HPP

#include "Server.hpp"
#include "vector"

class Poll
{
	public:

		Poll(Server *server);
		void NewUser();
		void Start();
		std::vector<pollfd> & getPollfd();
		Server & getServer();
		void DisconnectClientPoll(int i);

	private:

		std::vector<pollfd> _fds;
		Server *_server;
};

#endif
