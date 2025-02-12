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
	std::map<int, Client>::iterator itCl = (it->second).GetClient().begin();
	for (;itCl != (it->second).GetClient().end(); itCl++)
	{
		Client client = itCl->second;
		if (client.GetName() == Sender.GetName())
			continue;
		int fdcl = client.GetFd();
		std::cout << fdcl << std::endl;
		write(fdcl, ":", 1);
		write(fdcl, Sender.GetNick().c_str(), strlen(Sender.GetNick().c_str()));
		write(fdcl, "!", 1);
		write(fdcl, Sender.GetName().c_str(), strlen(Sender.GetName().c_str()));
		write(fdcl, "@", 1);
		write(fdcl, Sender.GetIpAdd().c_str(), strlen(Sender.GetIpAdd().c_str()));
		write(fdcl, " PRIVMSG ", 9);
		write(fdcl, message.getTo().c_str(), strlen(message.getTo().c_str()));
		write(fdcl, " ", 1);
		write(fdcl, message.getContent().c_str(), strlen(message.getContent().c_str()));
		write(fdcl, "\n", 1);
	}
}

void Command::Nick(Message message, Client &Sender, Server server)
{
	int fdcl;

	std::cout << "NICK cmd :" << std::endl;
	std::map<std::string, Channel>::iterator it = server.getChannel().find(message.getTo());
	if (it == server.getChannel().end())
	{
		std::cout << ":" << Sender.GetNick() << "!" << Sender.GetName() << "@" << Sender.GetIpAdd() << " NICK " << message.getContent() << std::endl;
		fdcl = Sender.GetFd();
		write(fdcl, ":", 1);
		write(fdcl, Sender.GetNick().c_str(), strlen(Sender.GetNick().c_str()));
		write(fdcl, "!", 1);
		write(fdcl, Sender.GetName().c_str(), strlen(Sender.GetName().c_str()));
		write(fdcl, "@", 1);
		write(fdcl, Sender.GetIpAdd().c_str(), strlen(Sender.GetIpAdd().c_str()));
		Sender.SetNick(message.getContent());
		write(fdcl, " NICK ", 6);
		write(fdcl, message.getContent().c_str(), strlen(message.getContent().c_str()));
		write(fdcl, "\n", 1);
		return;
	}
	std::map<int, Client>::iterator itCl = (it->second).GetClient().begin();
	for (;itCl != (it->second).GetClient().end(); itCl++)
	{
		std::cout << ":" << Sender.GetNick() << "!" << Sender.GetName() << "@" << Sender.GetIpAdd() << " NICK " << message.getContent() << std::endl;
		fdcl = (itCl->second).GetFd();
		std::cout << fdcl << std::endl;
		write(fdcl, ":", 1);
		write(fdcl, Sender.GetNick().c_str(), strlen(Sender.GetNick().c_str()));
		write(fdcl, "!", 1);
		write(fdcl, Sender.GetName().c_str(), strlen(Sender.GetName().c_str()));
		write(fdcl, "@", 1);
		write(fdcl, Sender.GetIpAdd().c_str(), strlen(Sender.GetIpAdd().c_str()));
		Sender.SetNick(message.getContent());
		write(fdcl, " NICK ", 6);
		write(fdcl, message.getContent().c_str(), strlen(message.getContent().c_str()));
		write(fdcl, "\n", 1);
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
		Command::Nick(str_message, *it->second, server);
	else if (str_message.getCommand() == "PASS")
		(it->second)->SetPassword(str_message.getContent());
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

void Command::QuitClient(int fd, Poll &poll, size_t i)
{
	std::cout << "Client disconnected." << std::endl;
	close(fd);
	poll.getPollfd().erase(poll.getPollfd().begin() + i);
	std::map<int, Client*>::iterator it = poll.getServer().getClients().find(fd);
	it->second->setLog(false);
}