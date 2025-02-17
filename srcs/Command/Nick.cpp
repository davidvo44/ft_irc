#include "Command.hpp"

void Command::Nick(Message message, Client &sender, Server server)
{
	int fdcl;

	std::cout << "NICK cmd :" << std::endl;
	std::map<std::string, Channel>::iterator it = server.getChannel().begin();
	
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

	for (;it != server.getChannel().end(); it++)
	{
		std::vector<std::string> sentclient;
		std::map<int, Client>::iterator itcl = (it->second).GetClient().begin();
		for (;itcl != (it->second).GetClient().end(); itcl++)
		{
			if (itcl->second.GetName() == sender.GetName())
			{
				std::map<int, Client>::iterator itcl2 = (it->second).GetClient().begin();
				for (;itcl2 != (it->second).GetClient().end(); itcl2++)
				{
					std::vector<std::string>::iterator vit = std::find(sentclient.begin(), sentclient.end(), itcl2->second.GetName());
					if (vit == sentclient.end())
					{
						sentclient.push_back(itcl2->second.GetName());
						//printf("Le nick la hein|%p|\n", &(itcl2->second));
						std::cout << "We sent nick to " << itcl2->second.GetName() << std::endl;
						std::cout << ":" << sender.GetNick() << "!" << sender.GetName() << "@" << sender.GetIpAdd() << " NICK " << message.getContent() << std::endl;
						fdcl = (itcl2->second).GetFd();
						std::cout << fdcl << std::endl;
						Command::WritePrefix(fdcl, sender);
						sender.SetNick(message.getContent());
						std::string response = " NICK " + message.getContent() + "\n";
						send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
					}
				}
				break;
			}
		}
	}
}