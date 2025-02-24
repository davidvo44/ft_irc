/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExceptionError.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:47 by saperrie          #+#    #+#             */
/*   Updated: 2025/02/24 18:05:59 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONERROR_HPP
#define EXCEPTIONERROR_HPP

#include <iostream>
#include <cstdio>

class ExceptionError : public std::exception
{
public:
	ExceptionError(const std::string &s) throw() : _s(s) {};
	virtual const char *what() const throw();
	~ExceptionError() throw() {};
private:
	const std::string _s;
};

class ProtocolError : public std::exception
{
public:
	ProtocolError(int code, const std::string &s, const std::string &user) throw() :  _s(s), _user(user), _code(code) {GetError();};
	virtual const char *what() const throw();
	~ProtocolError() throw() {};
	void GetError();
	int getCode();

private:
	const std::string _s;
	const std::string _user;
	int _code;
	std::string _finalMessage;
};

#endif
