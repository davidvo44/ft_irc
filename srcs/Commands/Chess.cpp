/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chess.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:57:09 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/06 18:58:21 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::ChessCommand(Server &server, Client &sender, Message &message)
{
	message.parseCHESS();
	Channel *chan = server.getChannel().findValue(message.getTarget());
	if (chan == NULL)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getParameter(), sender.getNick());
	if (message.getParameter().empty() == true)
	{
		chan->getBot()->PrintChess(sender.getFd());
		return ;
	}
	if (message.getParameter() == "join")
	{
		chan->getBot()->JoinChess(sender.getFd());
		return;
	}
	chan->getBot()->Ongame(sender.getFd(), message);
}
