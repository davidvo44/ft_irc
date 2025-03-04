/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:05 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 18:36:13 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "ft_irc.hpp"
#include "MutantMap.hpp"

class Client;
class Channel;

class Server
{
public:
	Server();
	int getFd();
	Client getIdxClients(int idx);
	MutantMap<int, Client *> &getClients();
	MutantMap<std::string, Channel *> &getChannel();
	sockaddr_in getServerAddr();
	void ServerInit();
	void AcceptNewClient(pollfd &tmp, std::string IpAdd);
	void CloseFds();
	void ClearClients(int fd);
	Channel *CreateChannel(Client *client, std::string ChName);
	Client * operator[](unsigned index);

private:
	int _Port;
	int _SerSocketFd;
	MutantMap<int, Client *> _Clients;
	MutantMap<std::string, Channel *> _Channel;
	struct sockaddr_in _ServerAddr;
};

#include "Client.hpp"
#include "Channel.hpp"

#endif
