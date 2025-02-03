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

#endif