#include "Command.hpp"


void Command::CheckCommande(std::string str, Server &server, int fd)
{
	Message str_message(str);
	std::map<int, Client*>::iterator it = server.getClients().find(fd);
	try
	{
	if (str_message.getCommand() == "JOIN")
		Command::JoinChannel(*it->second, str_message.getContent(), server);
	else if (str_message.getCommand() == "USER")
	{
		std::cout << "attribute :" << str_message.getContent() << std::endl;
		(it->second)->SetName(str_message.getContent());
	}
	else if (str_message.getCommand() == "NICK")
		(it->second)->SetNick(str_message.getContent());
	else if (str_message.getCommand() == "PASS")
		(it->second)->SetPassword(str_message.getContent());
	else if (str_message.getCommand() == "PRIVMSG")
		Command::PrivateMessage(str_message, *it->second, server);
	else if (str_message.getCommand() == "WHO")
		Command::PrivateMessage(str_message, *it->second, server);
	else
		throw ProtocolError(421, str, (it->second)->GetNick());
	}
	catch(const std::exception& e)
	{
			Command::WritePrefix((it->second)->GetFd(), *(it->second));
			write ((it->second)->GetFd(), e.what(), strlen(e.what()));
			write ((it->second)->GetFd(), "\n", 1);

			Command::WritePrefix(1, *(it->second));
			write (1, e.what(), strlen(e.what()));
			write (1, "\n", 1);
	}
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

void Command::WhoCommand(int FdCl, Client client, Message message)
{
	Client clientChan;
	write (FdCl, "352 ", 4);
	write (FdCl, client.GetName().c_str(), strlen(client.GetName().c_str()));
	write (FdCl, message.getContent().c_str(), strlen(message.getContent().c_str()));
	write (FdCl, clientChan.GetNick().c_str(), strlen(clientChan.GetNick().c_str()));
	write (FdCl, clientChan.GetIpAdd().c_str(), strlen(clientChan.GetIpAdd().c_str()));
	write (FdCl, clientChan.GetName().c_str(), strlen(clientChan.GetName().c_str()));

// ERR_NOSUCHSERVER
//352 TonPseudo #general UserA host1 irc.net NickA H :0 RealNameA
}