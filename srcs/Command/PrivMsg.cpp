#include "Command.hpp"

void Command::PrivateMessage(Message message, Client Sender, Server server)
{
	std::map<std::string, Channel>::iterator it = server.getChannel().find(message.getTo());
	if (it == server.getChannel().end())
		return;
	std::map<int, Client>::iterator itCl = (it->second).GetClient().begin();
	for (;itCl != (it->second).GetClient().end(); itCl++)
	{
		std::cout << "Response : " << ":" << Sender.GetNick() << "!" << Sender.GetName() << "@" << Sender.GetIpAdd() << " PRIVMSG " << message.getTo() << " " << message.getContent() << std::endl;
		Client client = itCl->second;
		if (client.GetName() == Sender.GetName())
			continue;
		int fdcl = client.GetFd();
		std::cout << "Write to:" << fdcl << std::endl;
		std::string response = "PRIVMSG " + message.getTo() + " " + message.getContent() + "\n";
		WritePrefix(fdcl, Sender);
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	}
}
