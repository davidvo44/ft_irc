#include "Command.hpp"

void Command::JoinChannel(Client client, std::string ChName, Server &server)
{
	std::map<std::string, Channel>::iterator it = server.getChannel().find(ChName);

    if (server.getChannel().empty() == false &&  it != server.getChannel().end())
	{ 
       it->second.JoinChannel(client);
	   std::cout << client.GetName() << " join " << ChName << std::endl;
    }
	else
	{
		std::cout << "creating " << ChName << std::endl;
		server.getChannel()[ChName] = server.CreateChannel(client, ChName);
    }
	//:Nick!User@Host JOIN #general
	std::map<int, Client*>::iterator itclient = server.getClients().begin();
	while (itclient != server.getClients().end())
	{
		int fdcl = itclient->second->GetFd();
		write (fdcl, ":", 1);
		write (fdcl, client.GetNick().c_str(), strlen(client.GetNick().c_str()));
		write (fdcl, "!", 1);
		write (fdcl, client.GetName().c_str(), strlen(client.GetName().c_str()));
		write (fdcl, "@", 1);
		write (fdcl, client.GetIpAdd().c_str(), strlen(client.GetIpAdd().c_str()));
		write (fdcl, " JOIN ", 6);
		write (fdcl, ChName.c_str(), strlen(ChName.c_str()));
		write (fdcl, "\n", 1);
		itclient++;
	}
	
	write (1, ":", 1);
	write (1, client.GetNick().c_str(), strlen(client.GetNick().c_str()));
	write (1, "!", 1);
	write (1, client.GetName().c_str(), strlen(client.GetName().c_str()));
	write (1, "@", 1);
	write (1, client.GetIpAdd().c_str(), strlen(client.GetIpAdd().c_str()));
	write (1, " JOIN ", 6);
	write (1, ChName.c_str(), strlen(ChName.c_str()));
	write (1, "\n", 1);
}

void Command::PrivateMessage(Message message, Client Sender, Server server)
{
	std::map<std::string, Channel>::iterator it = server.getChannel().find(message.getTo());
	if (it == server.getChannel().end())
		return;
	std::map<int, Client>::iterator Clit = (it->second).GetClient().begin();
	for (;Clit != (it->second).GetClient().end(); Clit++)
	{
		int fdClient = (Clit->second).GetFd();
		std::cout << fdClient << std::endl;
		write(fdClient, Sender.GetName().c_str(), strlen(Sender.GetName().c_str()));
		write(fdClient, ": ", 2);
		write(fdClient, message.getContent().c_str(), strlen(message.getContent().c_str()));
		write(fdClient, "\n", 1);
	}
}

void Command::CheckCommande(std::string str, Server &server, int fd)
{
	Message str_message(str);
	std::map<int, Client*>::iterator it = server.getClients().find(fd);
	if (str_message.getCommand() == "JOIN")
		Command::JoinChannel(*it->second, str_message.getContent(), server);
	else if (str_message.getCommand() == "USER")
	{
		std::cout << "attribute :" << str_message.getContent() << std::endl;
		(it->second)->SetName(str_message.getContent());
	}
	else if (str_message.getCommand() == "NICK")
		(it->second)->SetNick(str_message.getContent());
	else if (str.compare(0, 7, "PRIVMSG") == 0)
		Command::PrivateMessage(str_message, *it->second, server);
}

void Command::GetLineCommand(char *buffer, int fd, Server &server)
{
	std::string str;
	char *tmp = buffer;
	while (*tmp)
	{
		char *newline = strchr(tmp, '\n');
		if (newline)
		{
			*newline = '\0';
			Command::CheckCommande(str.append(tmp), server, fd);
			tmp = newline + 1;
			str.clear();
		}
		else
		{
			Command::CheckCommande(str.append(tmp), server, fd);
			break;
		}
	}
}