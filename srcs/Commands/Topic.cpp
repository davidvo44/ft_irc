/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:33 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 18:43:48 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::Topic(Message message, Client &sender, Server &server)
{
	Channel *chan = server.getChannel().findValue(message.getTarget());
	if (message.getTarget() == "ft_irc")
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getCommand(), sender.getNick());
    if (!chan)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTarget(), sender.getNick());
	if (!chan->getClient().findValue(sender.getFd()))
		throw ProtocolError(ERR_NOTONCHANNEL, message.getTarget(), sender.getNick());
	if (message.getContent().empty() == true)
		getTopic(message , sender, *chan);
	else
		chan->setTopic(message.getContent());
}

void Command::getTopic(Message message, Client &sender, Channel &chan)
{
	std::string response;

	if (chan.getTopic().empty() == true)
		//RplMessage::GetRply(RPL_NOTOPIC, sender.getFd(), 2, sender.getNick().c_str(), message.getTarget().c_str());
		response = RPL_NOTOPIC(sender.getNick(), message.getTarget());
	else
		response = RPL_TOPIC(sender.getNick(), message.getTarget(), chan.getTopic());
		//RplMessage::GetRply(RPL_TOPIC, sender.getFd(), 3, sender.getNick().c_str()
		//, message.getTarget().c_str(), chan.getTopic().c_str());
	send(sender.getFd(), response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}
