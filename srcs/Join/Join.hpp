#ifndef JOIN_HPP
#define JOIN_HPP

#include <iostream>
#include "../Channel/Channel.hpp"
#include "../Server/Server.hpp"

class Join
{
	public:
		static void JoinChannel(std::string ChannelName);
};

#endif