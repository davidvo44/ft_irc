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