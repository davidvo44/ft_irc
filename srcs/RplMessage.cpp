/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RplMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:58 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 23:14:01 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RplMessage.hpp"
#include "DefineList.hpp"
#include <cstring>
#include <unistd.h>
#include <sstream>

void RplMessage::GetRply(int code, int fd, int size, const char * value, ...)
{
	std::va_list args;
	std::string final_msg;
	std::vector <std::string> arg_list;
	std::ostringstream ss;
    ss << code;
	std::string scode = ss.str();

    va_start(args, value);
	arg_list.push_back(std::string(value));
	for (int i = 1; i < size; i++)
        arg_list.push_back(std::string(va_arg(args, const char*)));
	va_end(args);

	switch (code)
	{
		case RPL_WELCOME:
			final_msg = "::Welcome to the IRC network, " + arg_list[0] + "!" + arg_list[1] + "@" + arg_list[2];
			break;
		case RPL_YOURHOST:
			final_msg = ":Your host is irc.com, running version ft_irc";
			break;
		case RPL_CREATED:
			final_msg = ":This server was created today";
			break;
		case RPL_MYINFO:
			final_msg = ":irc.com ft_irc io tkl";
			break;
		case RPL_ENDOFWHO:
			final_msg = arg_list[1] + " :End of WHO list";
			break;
		case RPL_CHANNELMODEIS:
			final_msg =  arg_list[1] + " " + arg_list[2];
			break;
		case RPL_NOTOPIC:
			final_msg = arg_list[1] + " :No topic is set";
			break;
		case RPL_TOPIC:
			final_msg = arg_list[1] + " :" + arg_list[2];
			break;
		case RPL_INVITING:
			break;
		case RPL_WHOREPLY:
			final_msg = arg_list[1];
		case RPL_NAMREPLY:
			final_msg = "= " + arg_list[1] + " :" + arg_list[2];
			break;
		case RPL_ENDOFNAMES:
			final_msg = "= " + arg_list[1] + " ::End of /NAMES list";
			break;
	}
	std::string response = ":irc.com " + scode + " " + arg_list[0] + " " + final_msg + "\r\n";
    send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}
