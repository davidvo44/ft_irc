/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:11 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/28 07:51:57 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "MutantMap.hpp"

void Command::CheckCommand(std::string str, Server &server, int fd)
{
	std::string array[] = {"JOIN", "USER", "NICK", "PASS", "PRIVMSG", "WHO", "PART", "TOPIC", "KICK", "INVITE", "MODE", "CAP", "QUIT"};
	int index = 0;
	Message message(str);
	while (index < 13)
	{
		if (message.getCommand().compare(array[index]) == 0)
		break;
		index++;
	}
	Client *client = server.getClients().findValue(fd);
	try
	{
		switch (index)
		{
			case 0:
				Command::JoinChannel(*client, message, server);
				break;
			case 1:
				std::cout << "attribute :" << message.getContent() << std::endl;
				client->SetName(message.getContent());
				break;
			case 2:
				Command::Nick(message, *client, server);
				break;
			case 3:
				client->SetPassword(message.getContent());
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
				break;
			case 10:
				Command::checkMode(message, *client, server);
				break;
			case 11:
				break;
			case 12:
			QuitCommand(server, *client, message);
				break;
			default:
				throw ProtocolError(ERR_UNKNOWNCOMMAND, str, client->GetNick());
		}
	}
	catch(const std::exception& e)
	{
		Command::CatchErrors(client, e);
	}
}

void Command::CatchErrors(Client *client, const std::exception& e)
{
	int fdcl = client->GetFd();
	std::string	response;

	response = client->GetPrefix() + " " + e.what() + "\n";
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
}

static void SendClientFromChannel(const std::string to_send, Channel &chan, std::vector<int> &sentclient);

void	Command::SendBySharedChannels(std::string to_send, Client &sender, Server &server)
{
	std::vector<int> sentclient;

	sentclient.push_back(sender.GetFd());
	std::map<std::string, Channel*>::iterator it = server.getChannel().begin();
	for (;it != server.getChannel().end(); it++)
	{
		if (it->second->GetClient().findValue(sender.GetFd()))
			SendClientFromChannel(to_send, *it->second, sentclient);
	}
}

static void SendClientFromChannel(const std::string to_send, Channel &chan, std::vector<int> &sentclient)
{
	int idx = 0;
	while (chan[idx])
	{
		if (std::find(sentclient.begin(), sentclient.end(), chan[idx]->GetFd()) == sentclient.end())
		{
			sentclient.push_back(chan[idx]->GetFd());
			std::cout << "We sent by shared channel to " << chan[idx]->GetNick() << std::endl;
			send(chan[idx]->GetFd(), to_send.c_str(), to_send.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		}
		idx++;
	}
}
