
#include "Command.hpp"
#include "MutantMap.hpp"

void Command::CheckCommand(std::string str, Server &server, int fd)
{
	std::string array[] = {"JOIN", "USER", "NICK", "PASS", "PRIVMSG", "WHO", "PART", "TOPIC", "KICK", "INVITE", "MODE", "CAP", "QUIT", "getBot"};
	int index = 0;
	Message message(str);
	if (message.getCommand().empty() == true)
		return;
	while (index < 14)
	{
		if (message.getCommand().compare(array[index]) == 0)
			break;
		index++;
	}
	Client *client = server.getClients().findValue(fd);
	if (client == NULL)
		return;
	try
	{
		switch (index)
		{
		case 0:
			Command::joinChannel(*client, message, server);
			break;
		case 1:
			Command::UserCommand(*client, message, server);
			break;
		case 2:
			Command::Nick(message, *client, server);
			break;
		case 3:
			Command::PassCommand(server, *client, message);
			break;
		case 4:
			Command::PrivateMessage(message, *client, server);
			break;
		case 5:
			Command::WhoCommand(fd, *client, message, server);
			break;
		case 6:
			Command::Part(message, *client, server);
			break;
		case 7:
			Command::Topic(message, *client, server);
			break;
		case 8:
			Command::Kick(message, *client, server);
			break;
		case 9:
			Command::Invite(message, *client, server);
			break;
		case 10:
			Command::checkMode(message, *client, server);
			break;
		case 11:
			break;
		case 12:
			Command::QuitCommand(server, *client, message);
			break;
		case 13:
			Command::JoinBot(server, *client);
			break;
		default:
			throw ProtocolError(ERR_UNKNOWNCOMMAND, str, client->getNick());
		}
	}
	catch (const std::exception &e)
	{
		Command::CatchErrors(client, e);
	}
}

void Command::CatchErrors(Client *client, const std::exception &e)
{
	int fdcl = client->getFd();
	std::string response;

	response = client->getPrefix() + " " + e.what() + "\r\n";
	send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
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
			Command::CheckCommand(str.append(tmp), server, fd);
			tmp = newline + 1;
			str.clear();
		}
		else
		{
			Command::CheckCommand(str.append(tmp), server, fd);
			break;
		}
	}
	if (server.getBot())
		server.getBot()->joinChan();
}

void Command::ft_send(int fdSender, int fdDest, std::string response)
{
	std::string errormsg = "Cannot send message\r\n";
	if (send(fdDest, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL) == -1)
	{
		if (fdSender != fdDest)
			if (send(fdDest, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL) != -1)
				return;
		delete Poll::getInstance();
		exit(1);
	}
}
