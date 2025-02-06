#ifndef JOIN_HPP
#define JOIN_HPP

#include <iostream>
#include "../Channel/Channel.hpp"
#include "../Server/Server.hpp"
#include "../Message/Message.hpp"

class Command
{
	public:
		static void JoinChannel(std::string ChannelName);
		static void PrivateMessage(Message message, Client Sender);
};

#endif