#include "Message.hpp"

Message::Message(){}

Message::Message(std::string buffer)
{
	std::istringstream iss(buffer);
    std::string StrCut;

	while (iss >> StrCut)
		_words.push_back(StrCut);
	Message::parse();
}

void Message::parse()
{
	unsigned long i = 0;
	if (_words.size() > 0 && _words[0][0] == ':')
	{
		_prefix = _words[i];
		i++;
	}
	if (i == _words.size())
	{
		_command = "WRONG INPUT";
		return ;
	}
	_command = _words[i];
	i++;
	if (i == _words.size())
	{
		_command = "WRONG INPUT";
		return ;
	}
	if (_command == "PRIVMSG")
	{
		_to = _words[i];
		i++;
	}
		if (i == _words.size())
	{
		_command = "WRONG INPUT";
		return ;
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

}

std::string Message::getPrefix()
{
	return _prefix;
}

std::string Message::getCommand()
{
	return _command;
}

std::string Message::getTo()
{
	return _to;
}

std::string Message::getContent()
{
	return _content;
}
