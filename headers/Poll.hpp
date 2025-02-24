/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:55 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/24 12:13:57 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLL_HPP
#define POLL_HPP

#include "Server.hpp"
#include "vector"

class Poll
{
private:
	std::vector<pollfd> _fds;
	Server *_server;
public:
	Poll(Server *server);
	void NewUser();
	void Start();
	std::vector<pollfd> & getPollfd();
	Server & getServer();
};

#endif
