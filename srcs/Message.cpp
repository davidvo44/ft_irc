/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:53 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 20:31:27 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message(){}

Message::Message(std::string buffer)
{
	std::istringstream iss(buffer);
    std::string subStr;
	std::vector<std::string> _words;

	while (iss >> subStr)
		_words.push_back(subStr);
	_words.push_back("");
	parse(_words);
}

// void Message::parse(std::vector<std::string> _words)
// {
// 	for (unsigned long i = 0; _words[i] != "" && i ==_words.size(); ++i)
// 	{
// 		if (_words[i][0] == ':')
// 		{
// 			_prefix = _words[i++];
// 			continue;
// 		}
// 		_words[i];
// 	}
// }
void Message::parse(std::vector<std::string> _words)
{
	unsigned long i = 0;
	if (i == _words.size())
		return ;
	if (_words.size() >= 3 && _words[2] == ":!CHESS")
		_command = "CHESS";
	else
		_command = _words[i];
	i++;
	if (i == _words.size())
		return ;
	if (_command == "PRIVMSG" || _command == "PART" \
		|| _command == "TOPIC" || _command == "JOIN" \
		|| _command == "MODE" ||  _command == "KICK" \
		|| _command == "INVITE" || _command == "CHESS")
	{
		_target = _words[i];
		i++;
	}
	if (i == _words.size())
		return ;
	if (_command == "CHESS")
	{
		msgchess(_words, i);
		return;
	}
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
	if ((_command == "MODE" || _command == "KICK") && i != _words.size())
		_suffix = _words[i];
}

void Message::msgchess(std::vector<std::string> _words, unsigned long i)
{
	i++;
	if (i == _words.size())
		return ;
	_content = _words[i];
	i++;
	if (i == _words.size())
		return ;
	_suffix = _words[i];
}

const std::string & Message::getCommand() const
{
	return _command;
}

const std::string & Message::getTarget() const
{
	return _target;
}

std::string & Message::getContent()
{
	return _content;
}

const std::string &Message::getSuffix() const
{
	return _suffix;
}
