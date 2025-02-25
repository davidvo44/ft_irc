/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:05 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/25 12:49:42 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"

class Client;
class Channel;

class Server
{
	public:

		Server();
		int getFD();
		Client getIdxClients(int idx);
		std::map<int, Client*> &getClients();
		std::map<std::string, Channel> &getChannel();
		sockaddr_in getServerAddr();
		void ServerInit();
		void AcceptNewClient(pollfd &tmp, std::string IpAdd);
		void CloseFds();
		void ClearClients(int fd);
		Channel CreateChannel(Client* client, std::string ChName);

	private:

		int _Port;
		int _SerSocketFd;
		std::map<int, Client*> _Clients;
		std::map<std::string, Channel> _Channel;
		struct sockaddr_in _ServerAddr;
};

#include "Client.hpp"
#include "Channel.hpp"

#endif
