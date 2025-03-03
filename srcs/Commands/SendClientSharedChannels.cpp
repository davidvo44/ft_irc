/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendClientSharedChannels.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:58:05 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/03 13:58:08 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

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
