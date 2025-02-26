/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:25 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/27 00:45:20 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::Part(Message message, Client &sender, Server &server)
{
	int 		fdcl;
	std::string	response;
	std::cout << "PART cmd :" << std::endl;
	Channel *channel = server.getChannel().findValue(message.getTo());
	if (channel == NULL)
	{
		std::cout << "Channel didn't exist" << std::endl;
		return;
	}
	std::map<int, Client*>::iterator itcl = channel->GetClient().begin();
	for (;itcl != channel->GetClient().end(); itcl++)
	{
		std::cout << ":" << sender.GetNick() << "!" << sender.GetName() << "@" << sender.GetIpAdd() << " PART " << message.getTo() << " " << message.getContent() << std::endl;
		fdcl = (*itcl->second).GetFd();
		std::cout << fdcl << std::endl;
		response = sender.GetPrefix();
		response += " PART " + message.getTo() + " " + message.getContent() + "\n";
		send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	}
	channel->PartChannel(sender);
}
