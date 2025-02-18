#include "Command.hpp"

void Command::PrivateMessage(Message message, Client sender, Server server)
{
	std::map<std::string, Channel>::iterator it = server.getChannel().find(message.getTo());
	if (it == server.getChannel().end())
		return;
	std::map<int, Client>::iterator itCl = (it->second).GetClient().begin();
	for (;itCl != (it->second).GetClient().end(); itCl++)
	{
		std::cout << "Response : " << ":" << sender.GetNick() << "!" << sender.GetName() << "@" << sender.GetIpAdd() << " PRIVMSG " << message.getTo() << " " << message.getContent() << std::endl;
		Client client = itCl->second;
		int fdcl = client.GetFd();
		if (fdcl == sender.GetFd())
		continue;
		std::cout << "Write to:" << fdcl << std::endl;
		std::string response = "PRIVMSG " + message.getTo() + " " + message.getContent() + "\n";
		WritePrefix(fdcl, sender);
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	}
}
