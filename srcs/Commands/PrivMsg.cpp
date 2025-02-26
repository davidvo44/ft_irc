/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:28 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/27 00:44:51 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::PrivateMessage(Message &message, Client &sender, Server &server)
{
	std::string	response;
	Channel *chan = server.getChannel().findValue(message.getTo());
	if (chan == NULL)
		return;
	std::map<int, Client*>::iterator itCl = chan->GetClient().begin();
	for (;itCl != chan->GetClient().end(); itCl++)
	{
		std::cout << "Response : " << ":" << sender.GetNick() << "!" << sender.GetName() << "@" << sender.GetIpAdd() << " PRIVMSG " << message.getTo() << " " << message.getContent() << std::endl;
		Client client = *itCl->second;
		int fdcl = client.GetFd();
		if (fdcl == sender.GetFd())
			continue;
		std::cout << "Write to:" << fdcl << std::endl;
		response = sender.GetPrefix();
		response += "PRIVMSG " + message.getTo() + " " + message.getContent() + "\n";
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	}
}
