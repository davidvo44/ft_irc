/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:53 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/27 00:40:06 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message(){}

Message::Message(std::string buffer)
{
	std::istringstream iss(buffer);
    std::string StrCut;
	std::vector<std::string> _words;

	while (iss >> StrCut)
		_words.push_back(StrCut);
	Message::parse(_words);
}

void Message::parse(std::vector<std::string> _words)
{
	unsigned long i = 0;
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
	i++;
	if (_command == "MODE" && i != _words.size())
		_pass = _words[i];
}

const std::string & Message::getCommand() const
{
	return _command;
}

const std::string & Message::getTo() const
{
	return _to;
}

std::string & Message::getContent()
{
	return _content;
}

const std::string &Message::getPass() const
{
	return _pass;
}