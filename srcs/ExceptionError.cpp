
#include "ExceptionError.hpp"
#include "DefineList.hpp"
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
		case ERR_NOSUCHNICK:
			_finalMessage = code + " :No such nick/channel";
			return;
		case ERR_NOSUCHCHANNEL:
			_finalMessage = code + " :No such channel";
			return;
		case ERR_CANNOTSENDTOCHAN:
			_finalMessage = code + " :Cannot send to channel";
			return;
		case ERR_NORECIPIENT:
			_finalMessage = " :No recipient given";
			return;
		case ERR_NOTEXTTOSEND:
			_finalMessage = code + " :No text to send";
			return;
		case ERR_UNKNOWNCOMMAND:
			_finalMessage = code + " :Unknown command";
			return;
		case ERR_NONICKNAMEGIVEN:
			_finalMessage = ss.str() + " " + _user + " :No nickname given";
			return;
		case ERR_ERRONEUSNICKNAME:
			_finalMessage = ss.str() + " " + _user + " :Erroneus nickname";
			return;
		case ERR_NICKNAMEINUSE:
			_finalMessage = code + " :Nickname is already in use";
			return;
		case ERR_USERNOTINCHANNEL:
			_finalMessage = code + " :They aren't on that channel";
			return;
		case ERR_NOTONCHANNEL:
			_finalMessage = code + " :You're not on that channel";
			return;
		case ERR_USERONCHANNEL:
			_finalMessage = code + " :is already on channel";
			return;
		case ERR_NOTREGISTERED:
			_finalMessage = code + "  :You have not registered";
			return;
		case ERR_NEEDMOREPARAMS:
			_finalMessage = code + " :Not enough parameters";
			return;
		case ERR_ALREADYREGISTERED:
			_finalMessage = code + " :You may not reregister";
			return;
		case ERR_PASSWDMISMATCH:
			_finalMessage = code + " :Password incorrect";
			return;
		case ERR_CHANNELISFULL:
			_finalMessage = code + " :Cannot join channel (+l)";
			return;
		case ERR_UNKNOWNMODE:
			_finalMessage = code + " :is unknown mode char to me";
			return;
		case ERR_INVITEONLYCHAN:
			_finalMessage = code + " :Cannot join channel (+i)";
			return;
		case ERR_BADCHANNELKEY:
			_finalMessage = code + " :Cannot join channel (+k)";
			return;
		case ERR_BADCHANMASK:
			_finalMessage = code + " :Bad Channel Mask";
			return;
		case ERR_CHANOPRIVSNEEDED:
			_finalMessage = code + " :You're not channel operator";
			return;
		case ERR_INVALIDMODEPARAM:
			_finalMessage = code + " :Wrong parameter";
	}
	_finalMessage = "Unknown Code";
}

int ProtocolError::getCode()
{
	return _code;
}
