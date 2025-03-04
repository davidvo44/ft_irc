/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:40 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 18:44:17 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "ft_irc.hpp"
#include "Server.hpp"

class Client
{
public:
	Client();
	Client(pollfd &tmp, std::string IpAddr);

	int getFd();
	std::string getName();
	std::string getNick();
	std::string getIpAddr();
	void setName(const std::string name);
	void setNick(const std::string nick);
	void setPassword(const std::string pass);
	void setIpAddr(const std::string ipadd);
	std::string getPrefix();

private:
	pollfd _pollfds;
	std::string _username;
	std::string _nick;
	std::string _suffixword;
	std::string _IpAddr;
};

#endif
