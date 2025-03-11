
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
		void HandleClientInput(size_t clientIndex);
		void ProcessCompleteLines(std::string& partial_data, size_t clientIndex);
		void DisconnectClient(size_t clientIndex);
		bool IsClientConnected(size_t clientIndex);

	private:

		std::vector<pollfd> _fds;
		Server *_server;
};

#endif
