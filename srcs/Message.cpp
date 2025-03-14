
#include "Message.hpp"

Message::Message() : _prefix(""), _command(""), _target(""), _parameter(""), _suffix("") {}

Message::Message(std::string buffer)
{
	std::istringstream iss(buffer);
	std::string subStr;
	while (iss >> subStr)
	_words.push_back(subStr);
	std::vector<std::string>::iterator it = _words.begin();
	if (_words.empty() == true)
		return;
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

unsigned int Message::countCommas(std::string channels)
{
	unsigned int channelCount = 0;
	for(std::string::size_type index = 0; index != std::string::npos;)
	{
		if (channelCount != 0)
			index++;
		index = channels.find(",", index);
		channelCount++;
	}
	 std::cout << "COUNT : " << channelCount << std::endl;
	return channelCount;
}

std::map<std::string, std::string>*	Message::parseJOIN(void)
{
	std::string channel;
	std::string password;
	if (_words.size() < 2)
		return NULL;
	if (_words.size() > 3 && !_words[3].empty())
	{
		if (countCommas(_words[2]) != countCommas(_words[3]))
			return NULL;
		std::istringstream issChannels(_words[2]);
		std::istringstream issPasswords(_words[3]);
		while (issChannels)
		{
			std::getline(issChannels, channel, ',');
			std::getline(issPasswords, password, ',');
			_channelsAndPasswords[channel] = password;
		}
	}
	else
	{
		std::istringstream issChannels(_words[2]);
		while (issChannels)
		{
			std::getline(issChannels, channel, ',');
			_channelsAndPasswords[channel] = "";
		}
	}
	return &_channelsAndPasswords;
}

void Message::parseMode(void)
{
	_target = (_words.size() > 2 && !_words[2].empty()) ? _words[2] : "";
	_parameter = (_words.size() > 3 && !_words[3].empty()) ? _words[3] : "";
	_suffix = (_words.size() > 4 && !_words[4].empty()) ? _words[4] : "";
}

void	Message::parseKICK(void)
{
	_target = (_words.size() > 2 && !_words[2].empty()) ? _words[2] : "";
	_parameter = (_words.size() > 3 && !_words[3].empty()) ? _words[3] : "";
	handleMultipleWordArgs(_suffix, 4);
}

void	Message::parseINVITE(void)
{
	_target = (_words.size() > 3 && !_words[3].empty()) ? _words[3] : "";
	_parameter = (_words.size() > 2 && !_words[2].empty()) ? _words[2] : "";
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

void Message::setParameter(const std::string parameter)
{
	_parameter = parameter;
}

void Message::setTarget(const std::string target)
{
	_target = target;
}
