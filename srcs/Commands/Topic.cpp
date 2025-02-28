/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:33 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/27 19:32:45 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::Topic(Message message, Client &sender, Server &server)
{
	Channel *chan = server.getChannel().findValue(message.getTo());
	if (message.getTo() == "ft_irc")
		throw ProtocolError(ERR_NEEDMOREPARAMS, message.getCommand(), sender.GetNick());
    if (!chan)
		throw ProtocolError(ERR_NOSUCHCHANNEL, message.getTo(), sender.GetNick());
	if (!chan->GetClient().findValue(sender.GetFd()))
		throw ProtocolError(ERR_NOTONCHANNEL, message.getTo(), sender.GetNick());
	if (message.getContent().empty() == true)
		getTopic(message , sender, *chan);
	else
		chan->setTopic(message.getContent());
}

void Command::getTopic(Message message, Client &sender, Channel &chan)
{
	if (chan.getTopic().empty() == true)
		RplMessage::GetRply(RPL_NOTOPIC, sender.GetFd(), 2, sender.GetNick().c_str(), message.getTo().c_str());
	else
		RplMessage::GetRply(RPL_TOPIC, sender.GetFd(), 3, sender.GetNick().c_str()\
		, message.getTo().c_str(), chan.getTopic().c_str());
}
