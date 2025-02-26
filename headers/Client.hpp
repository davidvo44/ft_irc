/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:40 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/27 00:44:12 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ft_irc.hpp"
#include "Server.hpp"

class Client
{
public:
	Client();
	Client(pollfd &tmp, std::string IpAddr);
	int GetFd();
	std::string GetName();
	std::string GetNick();
	std::string GetPassword();
	std::string GetIpAdd();
	void SetName(const std::string name);
	void SetNick(const std::string nick);
	void SetPassword(const std::string pass);
	void setIpAdd(const std::string ipadd);
	void setLog(const bool change);
	std::string GetPrefix();

private:
	pollfd _pollfds;
	std::string _name;
	std::string _nick;
	std::string _password;
	std::string _IpAdd;
	bool _log;
};

#endif
