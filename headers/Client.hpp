/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:40 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/25 12:50:42 by saperrie         ###   ########.fr       */
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
		Client(pollfd tmp, std::string IpAddr);
		int GetFd();
		std::string GetName();
		std::string GetNick();
		std::string GetPassword();
		std::string GetIpAdd();
		void SetName(std::string name);
		void SetNick(std::string nick);
		void SetPassword(std::string pass);
		void setIpAdd(std::string ipadd);
		void setLog(bool change);

	private:

		pollfd _pollfds;
		std::string _name;
		std::string _nick;
		std::string _password;
		std::string _IpAdd;
		bool _log;
};

#endif
