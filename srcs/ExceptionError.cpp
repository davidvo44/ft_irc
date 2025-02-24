/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExceptionError.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:14:42 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/24 12:14:44 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ExceptionError.hpp"
#include <sstream>

const char* ExceptionError::what() const throw()
{
	const char *c = _s.c_str();
	perror(c);
	return "";
}

const char* ProtocolError::what() const throw()
{
	return _finalMessage.c_str();
}

void ProtocolError::GetError()
{
	std::string code;
	std::stringstream ss;
    ss << _code;
	code = ss.str() + " " + _user + " " + _s;
	switch (_code)
	{
		case 401:
			return;
		case 402:
			return;
		case 403:
			_finalMessage = code + " :No such channel";
			return;
		case 421:
			_finalMessage = code + " :Unknown command";
			return;
		case 431:
			_finalMessage = ss.str() + " " + _user + ":No nickname given";
			return;
		case 433:
			_finalMessage = code + " :Nickname is already in use";
			return;
		case 442:
			_finalMessage = code + " :You're not on that channel";
			return;
		case 461:
			_finalMessage = code + " :Not enough parameters";
			return;
		case 472:
			_finalMessage = code + " :is unknown mode char to me";
			return;
		case 482:
			_finalMessage = code + " :You're not channel operator";
			return;
	}
	_finalMessage = "Unknown Code";
}

int ProtocolError::getCode()
{
	return _code;
}
