/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:31 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/05 19:33:50 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
//:thierry!user@host QUIT :Bye !
void Command::QuitCommand(Server &server, Client &sender, Message &message)
{
	message.parseQUIT();

	std::string response = sender.getPrefix() + "QUIT :";
	if (message.getParameter().empty() == true)
		response += "bye\n";
	else
		response += message.getParameter();
	std::cout << "MESSAGE IS: " << response << std::endl;
	Command::SendBySharedChannels(response, sender, server);
}

void Command::QuitClient(int fd, Poll &poll, size_t i)
{
	std::cout << "Client disconnected." << std::endl;
	close(fd);
	poll.getPollfd().erase(poll.getPollfd().begin() + i);
}
