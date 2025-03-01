/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:17 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/28 09:03:11 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include "Channel.hpp"
#include "Poll.hpp"
#include "Message.hpp"
#include "ExceptionError.hpp"
#include "RplMessage.hpp"
#include "DefineList.hpp"

#include <vector>
#include <algorithm>

class Command
{
	public:
			//Init Command
		static void			CheckCommand(std::string str, Server &server, int fd);
		static void			GetLineCommand(char *buffer, int fd, Server &server);
		static void			SendBySharedChannels(std::string to_send, Client &sender, Server &server);
		static void CatchErrors(Client *client, const std::exception& e);

			//Command List
		static void JoinChannel(Client &client, Message message, Server &server);
		static void Nick(Message message, Client &sender, Server &server);
		static void Part(Message message, Client &sender, Server &server);
		static void PrivateMessage(Message &message, Client &sender, Server &server);
		static void QuitClient(int fd, Poll &poll, size_t i);
		static void WhoCommand(int FdCl, Client &client, Message &message, Server &server);
		static void Topic(Message message, Client &sender, Server &server);
		static void getTopic(Message message, Client &sender, Channel &chan);
		static void Kick(Message message, Client &client, Server &server);
		static void checkMode(Message message, Client &sender, Server &server);
		static void QuitCommand(Server &server, Client &sender, Message &message);
};

#endif
