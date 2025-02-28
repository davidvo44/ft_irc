/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:52 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/28 15:24:19 by saperrie         ###   ########.fr       */
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
		const std::string &getTo()  const;
		std::string &getContent();
		const std::string &getPass()  const;

	private:

		void parse(std::vector<std::string> _words);
		std::string _prefix;    //  std::string prefix = ":" + clientNick + "!" + clientUser + "@" + clientHost;
		std::string _command;
		std::string _to;
		std::string _content;
		std::string _pass;
};

#endif
