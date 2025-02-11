#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include "../Channel/Channel.hpp"
#include "../Poll/Poll.hpp"
#include "../Message/Message.hpp"
#include "./../ExceptionError/ExceptionError.hpp"

class Command
{
	public:
		static void CheckCommande(std::string str, Server &server, int fd);
		static void GetLineCommand(char *buffer, int fd, Server &server);
		static void WritePrefix(int FdCl, Client client);

		static void JoinChannel(Client client, std::string ChName, Server &server);
		static void PrivateMessage(Message message, Client Sender, Server server);
		static void QuitClient(int fd, Poll &server, size_t i);
		static void WhoCommand(int FdCl, Client client, Message message);
};

#endif