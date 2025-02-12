#include "Command.hpp"
#include "vector"

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
	std::string array[] = {"JOIN", "USER", "NICK", "PASS", "PRIVMSG", "WHO"};
	int index = 0;
	Message str_message(str);
	while (index < 6)
	{
		if (str_message.getCommand().compare(array[index]) == 0)
			break;
		index++;
	}
	std::map<int, Client*>::iterator it = server.getClients().find(fd);
	try
	{
		switch (index)
		{
			case 0:
				Command::JoinChannel(*it->second, str_message.getContent(), server);
				break;
			case 1:
				std::cout << "attribute :" << str_message.getContent() << std::endl;
				(it->second)->SetName(str_message.getContent());
				break;
			case 2:
				Command::Nick(str_message, *it->second, server);
				break;
			case 3:
				(it->second)->SetPassword(str_message.getContent());
				break;
			case 4:
				Command::PrivateMessage(str_message, *it->second, server);
				break;
			case 5:
				Command::PrivateMessage(str_message, *it->second, server);
				break;
			default:
				throw ProtocolError(421, str, (it->second)->GetNick());
		}
	}
	catch(const std::exception& e)
	{
		Command::CatchErrors((it->second), e);
	}
}

void Command::CatchErrors(Client *client, const std::exception& e)
{
	Command::WritePrefix(client->GetFd(), *client);
	write (client->GetFd(), e.what(), strlen(e.what()));
	write (client->GetFd(), "\n", 1);

	Command::WritePrefix(1, *client);
	write (1, e.what(), strlen(e.what()));
	write (1, "\n", 1);
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

void Command::WritePrefix(int FdCl, Client client)
{
	write (FdCl, ":", 1);
	write (FdCl, client.GetNick().c_str(), strlen(client.GetNick().c_str()));
	write (FdCl, "!", 1);
	write (FdCl, client.GetName().c_str(), strlen(client.GetName().c_str()));
	write (FdCl, "@", 1);
	write (FdCl, client.GetIpAdd().c_str(), strlen(client.GetIpAdd().c_str()));
	write (FdCl, " ", 1);
}
