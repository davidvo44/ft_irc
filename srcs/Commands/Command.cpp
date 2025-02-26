/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:11 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/27 00:54:20 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "MutantMap.hpp"

void Command::CheckCommand(std::string str, Server &server, int fd)
{
	std::string array[] = {"JOIN", "USER", "NICK", "PASS", "PRIVMSG", "WHO", "PART", "TOPIC", "KICK", "INVITE", "MODE", "CAP"};
	int index = 0;
	Message str_message(str);
	while (index < 12)
	{
		if (str_message.getCommand().compare(array[index]) == 0)
		break;
		index++;
	}
	Client *client = server.getClients().findValue(fd);
	// std::map<int, Client*>::iterator it = server.getClients().find(fd); 
	try
	{
		switch (index)
		{
			case 0:
				Command::JoinChannel(*client, str_message, server);
				break;
			case 1:
				std::cout << "attribute :" << str_message.getContent() << std::endl;
				client->SetName(str_message.getContent());
				break;
			case 2:
				Command::Nick(str_message, *client, server);
				break;
			case 3:
				client->SetPassword(str_message.getContent());
				break;
			case 4:
				Command::PrivateMessage(str_message, *client, server);
				break;
			case 5:
				Command::WhoCommand(fd, *client, str_message, server);
				break;
			case 6:
				Command::Part(str_message, *client, server);
				break;
			case 7:
				Command::Topic(str_message, *client, server);
				break;
			case 8:
				Command::Kick(str_message, *client, server);
				break;
			case 9:
				break;
			case 10:
				Command::checkMode(str_message, *client, server);
				break;
			case 11:
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

void	Command::SendBySharedChannels(std::string to_send, Client sender, Server &server)
{
	int fdcl;
	std::map<std::string, Channel*>::iterator it = server.getChannel().begin();

	for (;it != server.getChannel().end(); it++)
	{
		std::vector<std::string> sentclient;
		std::map<int, Client*>::iterator itcl = (*it->second).GetClient().begin();
		sentclient.push_back(sender.GetNick());
		for (;itcl != (*it->second).GetClient().end(); itcl++)
		{
			if ((*itcl->second).GetNick() == sender.GetNick())
			{
				std::map<int, Client*>::iterator itcl2 = (*it->second).GetClient().begin();
				for (;itcl2 != (*it->second).GetClient().end(); itcl2++)
				{
					std::vector<std::string>::iterator vit = std::find(sentclient.begin(), sentclient.end(), (*itcl2->second).GetNick());
					if (vit == sentclient.end())
					{
						sentclient.push_back((*itcl2->second).GetNick());
						std::cout << "We sent by shared channel to " << (*itcl2->second).GetNick() << std::endl;
						fdcl = (*itcl2->second).GetFd();
						std::cout << fdcl << std::endl;
						send(fdcl, to_send.c_str(), to_send.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
					}
				}
				break;
			}
		}
	}
}
