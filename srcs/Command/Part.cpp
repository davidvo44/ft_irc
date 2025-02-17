#include "Command.hpp"

void Command::Part(Message message, Client &sender, Server &server)
{
	int 	fdcl;

	std::cout << "PART cmd :" << std::endl;
	std::map<std::string, Channel>::iterator it = server.getChannel().find(message.getContent());
	std::map<int, Client>::iterator itcl = (it->second).GetClient().begin();
	if (it == server.getChannel().end())
	{
		std::cout << "Channel didn't exist" << std::endl;
		return;
	}
	for (;itcl != (it->second).GetClient().end(); itcl++)
	{
		std::cout << ":" << sender.GetNick() << "!" << sender.GetName() << "@" << sender.GetIpAdd() << " PART " << message.getTo() << " " << message.getContent() << std::endl;
		fdcl = (itcl->second).GetFd();
		std::cout << fdcl << std::endl;
		Command::WritePrefix(fdcl, sender);
		std::string response = " PART " + message.getTo() + " " + message.getContent() + "\n";
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	}
	it->second.PartChannel(sender);
}