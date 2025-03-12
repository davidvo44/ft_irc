/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:55 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/28 15:24:29 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLL_HPP
# define POLL_HPP

#include "Server.hpp"
#include "vector"

class Poll
{
	public:

		Poll(Server *server);
		void NewUser();
		void Start();
		std::vector<pollfd> & getPollfd();
		std::map<int, std::string> & getReadBuffer();
		Server & getServer();

	private:

		void receiveMessage(int fd, int i);
		std::vector<pollfd> _fds;
		std::map<int, std::string> _read_buffer;
		Server *_server;
};

#endif
