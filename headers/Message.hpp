/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:52 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 18:44:54 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <iostream>
#include <vector>
#include <sstream>

class Message
{
	public:

		Message();
		Message(std::string buffer);

		const std::string &getCommand()  const;
		const std::string &getTarget()  const;
		std::string &getContent();
		const std::string &getSuffix()  const;

	private:

		void parse(std::vector<std::string> _words);
		void msgchess(std::vector<std::string> _words, unsigned long i);
		std::string _prefix;    //  std::string prefix = ":" + clientNick + "!" + clientUser + "@" + clientHost;
		std::string _command;
		std::string _target;
		std::string _content;
		std::string _suffix;
};

#endif
