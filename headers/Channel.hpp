/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:35 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/25 12:50:58 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"
#include <vector>

class Channel
{
	public:

		Channel(std::string name, Client* client);
		Channel();
		~Channel();
		void AddClient(Client* client);
		void JoinChannel(Client* client);
		void PartChannel(Client client);
		void setTopic(const std::string topic);
		void addMode(char ope);
		void deleteMode(char ope);
		bool viewMode(char ope);
		bool IsOperator(int client);
		std::string getName();
		const std::string getTopic();
		std::map<int, Client*> &GetClient();
		std::vector<int> & getOperator();

	private:

		std::string _name;
		std::map<int, Client*> _Clients;
		std::string _topic;
		int _mode; // binary format 1 1 1 1: -i, -t, -k, -l
		std::vector<int> _operator;
};

#endif
