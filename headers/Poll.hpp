
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
		std::map<int, std::string> & getReadBuffer();
		Server & getServer();
		void HandleClientInput(size_t clientIndex);
		void ProcessCompleteLines(size_t clientIndex);
		void DisconnectClient(size_t clientIndex);
		bool IsClientConnected(size_t clientIndex);

	private:

		void receiveMessage(int fd);
		std::vector<pollfd> _fds;
		std::map<int, std::string> _read_buffer;
		Server *_server;
};

#endif
