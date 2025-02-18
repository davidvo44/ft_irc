#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include "../Channel/Channel.hpp"
#include "../Poll/Poll.hpp"
#include "../Message/Message.hpp"
#include "./../ExceptionError/ExceptionError.hpp"
#include "./../RplMessage/RplMessage.hpp"

class Command
{
	public:
			//Init Command
		static void CheckCommande(std::string str, Server &server, int fd);
		static void GetLineCommand(char *buffer, int fd, Server &server);
		static void WritePrefix(int FdCl, Client client);
		static void CatchErrors(Client *client, const std::exception& e);
			//Command List
		static void JoinChannel(Client client, Message message, Server &server);
		static void Nick(Message message, Client &sender, Server server);
		static void Part(Message message, Client &sender, Server &server);
		static void PrivateMessage(Message message, Client sender, Server server);
		static void QuitClient(int fd, Poll &server, size_t i);
		static void WhoCommand(int FdCl, Client client, Message message, Server server);
		static void Topic(Message message, Client &sender, Server &server);
		static void getTopic(Message message, Client &sender, Server &server);
		static void Kick();
};

#endif