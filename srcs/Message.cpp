/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:53 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/25 17:22:43 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message(){}

Message::Message(std::string buffer)
{
	std::istringstream iss(buffer);
    std::string StrCut;

	while (iss >> StrCut)
		_words.push_back(StrCut);
	Message::parse();
}

void Message::parse()
{
	unsigned long i = 0;

	if (_words.size() > 0 && _words[0][0] == ':')
	{
		_prefix = _words[i];
		i++;
	}
	if (i == _words.size())
		return ;
	_command = _words[i];
	i++;
	if (i == _words.size())
		return ;
	if (_command == "PRIVMSG" || _command == "PART" || _command == "TOPIC" || _command == "JOIN" || _command == "MODE" ||  _command == "KICK")
	{
		_to = _words[i];
		i++;
	}
	if (i == _words.size())
		return ;
	_content = _words[i];
	if (_words[i][0] == ':')
	{
		_content.erase(0,1);
		i++;
		for (; i != _words.size(); i++)
		{
			_content = _content + " " + _words[i];
		}
	}

}

std::string & Message::getPrefix()
{
	return _prefix;
}

std::string & Message::getCommand()
{
	return _command;
}

std::string & Message::getTo()
{
	return _to;
}

std::string & Message::getContent()
{
	return _content;
}
