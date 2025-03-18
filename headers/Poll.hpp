
#ifndef POLL_HPP
# define POLL_HPP

#include "Server.hpp"
#include "vector"

class Poll
{
	public:

		Poll();
		Poll(Server *server);
		~Poll();
		static Poll* getInstance(Server *server);
		static Poll* getInstance();
		void NewUser();
		void Start();
		std::vector<pollfd> & getPollfd();
		std::map<int, std::string> & getReadBuffer();
		Server & getServer();
		void HandleClientInput(size_t clientIndex);
		void ProcessCompleteLines(size_t clientIndex);
		void DisconnectClient(size_t clientIndex);
		bool IsClientConnected(size_t clientIndex);
		void DeleteClientPoll(int fd);

	private:

		void receiveMessage(int fd);
		std::vector<pollfd> _fds;
		std::map<int, std::string> _read_buffer;
		Server *_server;
		static Poll* _instancePoll;
};

#endif
