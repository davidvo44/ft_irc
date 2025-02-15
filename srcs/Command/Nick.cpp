#include "Command.hpp"

void Command::Nick(Message message, Client &Sender, Server server)
{
	int fdcl;

	std::cout << "NICK cmd :" << std::endl;
	std::map<std::string, Channel>::iterator it = server.getChannel().find(message.getTo());
	if (it == server.getChannel().end())
	{
		std::cout << ":" << Sender.GetNick() << "!" << Sender.GetName() << "@" << Sender.GetIpAdd() << " NICK " << message.getContent() << std::endl;
		fdcl = Sender.GetFd();
		Command::WritePrefix(fdcl, Sender);
		Sender.SetNick(message.getContent());
		std::string response = " NICK " + message.getContent() + "\n";
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	std::map<int, Client>::iterator itCl = (it->second).GetClient().begin();
	for (;itCl != (it->second).GetClient().end(); itCl++)
	{
		std::cout << ":" << Sender.GetNick() << "!" << Sender.GetName() << "@" << Sender.GetIpAdd() << " NICK " << message.getContent() << std::endl;
		fdcl = (itCl->second).GetFd();
		std::cout << fdcl << std::endl;
		Command::WritePrefix(fdcl, Sender);
		Sender.SetNick(message.getContent());
		std::string response = " NICK " + message.getContent() + "\n";
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		}
}