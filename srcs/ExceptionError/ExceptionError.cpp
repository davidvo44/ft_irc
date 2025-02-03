#include "ExceptionError.hpp"

const char* ExceptionError::what() const throw()
{
	const char *c = _s.c_str();
	perror(c);
	return "";
}
