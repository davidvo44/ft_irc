#include "Command.hpp"

void Command::Nick(Message message, Client &sender, Server server)
{
	int fdcl;

	std::cout << "NICK cmd :" << std::endl;
	std::map<std::string, Channel>::iterator it = server.getChannel().find(message.getContent());
	if (it == server.getChannel().end())
	{
		std::cout << ":" << sender.GetNick() << "!" << sender.GetName() << "@" << sender.GetIpAdd() << " NICK " << message.getContent() << std::endl;
		fdcl = sender.GetFd();
		Command::WritePrefix(fdcl, sender);
		sender.SetNick(message.getContent());
		std::string response = " NICK " + message.getContent() + "\n";
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	std::map<int, Client>::iterator itcl = (it->second).GetClient().begin();
	for (;itcl != (it->second).GetClient().end(); itcl++)
	{
		printf("Le nick la hein|%p|\n", &(itcl->second));
		std::cout << ":" << sender.GetNick() << "!" << sender.GetName() << "@" << sender.GetIpAdd() << " NICK " << message.getContent() << std::endl;
		fdcl = (itcl->second).GetFd();
		std::cout << fdcl << std::endl;
		Command::WritePrefix(fdcl, sender);
		sender.SetNick(message.getContent());
		std::string response = " NICK " + message.getContent() + "\n";
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	}
}