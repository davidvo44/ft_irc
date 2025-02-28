/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:31 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/28 07:58:10 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
//:thierry!user@host QUIT :Je me déconnecte, à bientôt !
void Command::QuitCommand(Server &server, Client &sender, Message &message)
{
	std::string response = sender.GetPrefix() + "QUIT :";
	if (message.getContent().empty() == true)
		response += "bye\n";
	else
		response += message.getContent();
	std::cout << "MESSAGE IS: " << response << std::endl;
	Command::SendBySharedChannels(response, sender, server);
}

void Command::QuitClient(int fd, Poll &poll, size_t i)
{
	std::cout << "Client disconnected." << std::endl;
	close(fd);
	poll.getPollfd().erase(poll.getPollfd().begin() + i);
}
