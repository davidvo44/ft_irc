/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:22 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/24 18:02:00 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::Nick(Message message, Client &sender, Server &server)
{
	int			fdcl;
	std::string	response;

	std::cout << "NICK cmd :" << std::endl;
	std::cout << ":" << sender.GetNick() << "!" << sender.GetName() << "@" << sender.GetIpAdd() << " NICK " << message.getContent() << std::endl;


	fdcl = sender.GetFd();
	response = GetPrefix(sender);
	response += "NICK " + message.getContent() + "\n";

	SendBySharedChannels(response, sender, server);

	send(fdcl, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	sender.SetNick(message.getContent());
}
