/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendClientSharedChannels.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:58:05 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 18:36:13 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

static void SendClientFromChannel(const std::string to_send, Channel &chan, std::vector<int> &sentclient);

void	Command::SendBySharedChannels(std::string to_send, Client &sender, Server &server)
{
	std::vector<int> sentclient;

	sentclient.push_back(sender.getFd());
	std::map<std::string, Channel*>::iterator it = server.getChannel().begin();
	for (;it != server.getChannel().end(); it++)
	{
		if (it->second->getClient().findValue(sender.getFd()))
			SendClientFromChannel(to_send, *it->second, sentclient);
	}
}

static void SendClientFromChannel(const std::string to_send, Channel &chan, std::vector<int> &sentclient)
{
	int idx = 0;
	while (chan[idx])
	{
		if (std::find(sentclient.begin(), sentclient.end(), chan[idx]->getFd()) == sentclient.end())
		{
			sentclient.push_back(chan[idx]->getFd());
			std::cout << "We sent by shared channel to " << chan[idx]->getNick() << std::endl;
			send(chan[idx]->getFd(), to_send.c_str(), to_send.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		}
		idx++;
	}
}
