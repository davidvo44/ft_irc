#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include "../Channel/Channel.hpp"
#include "../Poll/Poll.hpp"
#include "../Message/Message.hpp"

class Command
{
	public:
		static void JoinChannel(Client client, std::string ChName, Server &server);
		static void PrivateMessage(Message message, Client Sender, Server server);
		static void Nick(Message message, Client &Sender, Server server);
		static void CheckCommande(std::string str, Server &server, int fd);
		static void GetLineCommand(char *buffer, int fd, Server &server);
		static void QuitClient(int fd, Poll &server, size_t i);

};

#endif