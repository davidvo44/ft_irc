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
		case 442:
			_finalMessage = code + " :You're not on that channel";
			return;
		case 461:
			_finalMessage = code + " :Not enough parameters";
			return;
	}
	_finalMessage = "Unknown Code";
}

int ProtocolError::getCode()
{
	return _code;
}