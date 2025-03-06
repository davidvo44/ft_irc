/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:53 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/06 18:58:15 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"


Message::Message() : _prefix(""), _command(""), _target(""), _parameter(""), _suffix("") {}

Message::Message(std::string buffer)
{
	std::istringstream iss(buffer);
    std::string subStr;
	while (iss >> subStr)
		_words.push_back(subStr);
	std::vector<std::string>::iterator it = _words.begin();
	if (_words[0][0] != ':')
		_words.insert(it, "");
	else
		_prefix = (_words.size() > 0 && !_words[0].empty()) ? _words[0] : "";
	if (_words.size() >= 4 && _words[3] == ":!CHESS")
		_command = "CHESS";
	else
    _command = (_words.size() > 1 && !_words[1].empty()) ? _words[1] : "";
}

void	Message::handleMultipleWordArgs(std::string& argName, unsigned int vectorIndex)
{
	if (_words.size() > vectorIndex && _words[vectorIndex][0] == ':')
	{
		_words[vectorIndex].erase(0, 1);
		for (unsigned int i = vectorIndex; i < _words.size(); ++i)
			argName += _words[i] + " ";
	}
	else
		argName = (_words.size() > vectorIndex && !_words[vectorIndex].empty()) ? _words[vectorIndex] : "";
}

void	Message::parseNICK_USER_PASS(void)
{
    _parameter = (_words.size() > 2 && !_words[2].empty()) ? _words[2] : "";
}

void	Message::parseWHO(void)
{
    _target = (_words.size() > 2 && !_words[2].empty()) ? _words[2] : "";
}

void	Message::parsePRIVMSG_PART_TOPIC(void)
{
	_target = (_words.size() > 2 && !_words[2].empty()) ? _words[2] : "";
	handleMultipleWordArgs(_parameter, 3);
}


/*
JOIN #1,#2,#3 password1,,password3		#1 and #3 have passwords
JOIN #1,#2,#3 password1,password2,		#1 and #2 have passwords
JOIN #1,#2,#3 ,password2,				#2 has a password

for N channels joined, if any requires a password, N-1 commas are needed for passwords
*/
void	Message::parseJOIN(void) // TO BE CONTINUED
{
	_target = (_words.size() > 2 && !_words[2].empty()) ? _words[2] : "";
	_parameter = (_words.size() > 3 && !_words[3].empty()) ? _words[3] : "";
	_suffix = (_words.size() > 4 && !_words[4].empty()) ? _words[4] : "";
}

void	Message::parseKICK(void) // TO BE CONTINUED
{
	_target = (_words.size() > 2 && !_words[2].empty()) ? _words[2] : "";
	_parameter = (_words.size() > 3 && !_words[3].empty()) ? _words[3] : "";
	handleMultipleWordArgs(_suffix, 4);
}

void	Message::parseQUIT(void)
{
	handleMultipleWordArgs(_parameter, 2);
}

void Message::parseCHESS(void)
{
	_target = (_words.size() > 2 && !_words[2].empty()) ? _words[2] : "";
	_parameter = (_words.size() > 4 && !_words[4].empty()) ? _words[4] : "";
	_suffix = (_words.size() > 5 && !_words[5].empty()) ? _words[5] : "";
}

/* 	std::cout << "suffix : " << _suffix << std::endl;
	std::cout << "CMD : " << _command << std::endl;
	std::cout << "target : " << _target << std::endl;
	std::cout << "param : " << _parameter<< std::endl;
 */

// void Message::parse(std::vector<std::string>& _words)
// {
// 	std::vector<std::string>::iterator it = _words.begin();
// 	if (_words[0][0] != ':')
// 		_words.insert(it, "");
// 	else
// 		_prefix = (_words.size() > PREFIX && !_words[PREFIX].empty()) ? _words[PREFIX] : "";
//     _command = (_words.size() > COMMAND && !_words[COMMAND].empty()) ? _words[COMMAND] : "";
//     // _target = (_words.size() > TARGET && !_words[TARGET].empty()) ? _words[TARGET] : "";
//     // _parameter = (_words.size() > PARAMETER && !_words[PARAMETER].empty()) ? _words[PARAMETER] : "";
//     // _suffix = (_words.size() > SUFFIX && !_words[SUFFIX].empty()) ? _words[SUFFIX] : "";
// }

// void Message::parse(std::vector<std::string> _words)
// {
// 	unsigned long i = 0;
// 	if (i == _words.size())
// 		return ;
// 	if (_words.size() >= 3 && _words[2] == ":!CHESS")
// 		_command = "CHESS";
// 	else
// 		_command = _words[i];
// 	i++;
// 	if (i == _words.size())
// 		return ;
// 	if (_command == "PRIVMSG" || _command == "PART" \
// 		|| _command == "TOPIC" || _command == "JOIN" \
// 		|| _command == "MODE" ||  _command == "KICK" \
// 		|| _command == "INVITE" || _command == "CHESS")
// 	{
// 		_target = _words[i];
// 		i++;
// 	}
// 	if (i == _words.size())
// 		return ;
// 	if (_command == "CHESS")
// 	{
// 		msgchess(_words, i);
// 		return;
// 	}
// 	_parameter = _words[i];
// 	if (_words[i][0] == ':')
// 	{
// 		_parameter.erase(0,1);
// 		i++;
// 		for (; i != _words.size(); i++)
// 		{
// 			_parameter = _parameter + " " + _words[i];
// 		}
// 	}
// 	i++;
// 	if ((_command == "MODE" || _command == "KICK") && i != _words.size())
// 		_suffix = _words[i];
// }

void Message::msgchess(std::vector<std::string> _words, unsigned long i)
{
	i++;
	if (i == _words.size())
		return ;
	_parameter = _words[i];
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

std::string & Message::getParameter()
{
	return _parameter;
}

const std::string &Message::getSuffix() const
{
	return _suffix;
}
