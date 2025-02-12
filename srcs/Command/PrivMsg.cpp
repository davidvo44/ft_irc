#include "Command.hpp"

void Command::PrivateMessage(Message message, Client Sender, Server server)
{
	(void) Sender;
	std::map<std::string, Channel>::iterator it = server.getChannel().find(message.getTo());
	if (it == server.getChannel().end())
		return;
	std::map<int, Client>::iterator itCl = (it->second).GetClient().begin();
	for (;itCl != (it->second).GetClient().end(); itCl++)
	{
		Client client = itCl->second;
		if (client.GetName() == Sender.GetName())
			continue;
		int fdcl = client.GetFd();
		std::cout << "Write to:" << fdcl << std::endl;
		WritePrefix(fdcl, Sender);
		write(fdcl, "PRIVMSG ", 8);
		write(fdcl, message.getTo().c_str(), strlen(message.getTo().c_str()));
		write(fdcl, " ", 1);
		write(fdcl, message.getContent().c_str(), strlen(message.getContent().c_str()));
		write(fdcl, "\n", 1);
	}
}
