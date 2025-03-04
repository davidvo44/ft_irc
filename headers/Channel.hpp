/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:35 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 17:36:53 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"
#include "Bot.hpp"
#include <vector>

class Channel
{
public:
	Channel(std::string name, Client *client);
	Channel();
	~Channel();

	void AddClient(Client *client);
	void JoinChannel(Client *client);

	void PartChannel(Client client);
	void setTopic(const std::string topic);

	void addMode(char ope);
	void deleteMode(char ope);
	bool viewMode(char ope);
	bool IsOperator(int client);
	bool IsWlist(int client);
	void addToWhitelist(std::string client);

	std::string getName();
	const std::string getTopic();
	MutantMap<int, Client *> &GetClient();
	std::vector<int> &getOperator();
	std::string getPassword();
	void setPassword(std::string pass);
	Bot *getBot();

	Client *operator[](unsigned index);
	Client *operator!=(unsigned index);

private:
	std::string _name;
	MutantMap<int, Client *> _Clients;
	std::string _topic;
	int _mode;
	std::vector<int> _operator;
	std::vector<int> _wlist;
	std::vector<std::string> _whitelist;
	std::string _password;
	Bot *_bot;
};

#endif
