
#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <map>

class Message
{
public:

	Message();
	Message(std::string buffer);

	const std::string &getCommand() const;
	const std::string &getTarget() const;
	std::string &getParameter();
	const std::string &getSuffix() const;

	void setTarget(const std::string target);
	void setParameter(const std::string parameter);

	void handleMultipleWordArgs(std::string &argName, unsigned int vectorIndex);

	void parseNICK_USER_PASS(void);
	void parseWHO(void);
	void parsePRIVMSG_PART_TOPIC(void);
	void parseQUIT(void);
	void parseMode(void);

	std::map<std::string, std::string>* parseJOIN(void);
	void parseKICK(void);

	void	parseINVITE(void);

	void parseCHESS(void);

	unsigned int countCommas(std::string channels);


private:

	void msgchess(std::vector<std::string> _words, unsigned long i);
	std::map<std::string, std::string> _channelsAndPasswords;
	std::vector<std::string> _words;
	std::string _prefix;
	std::string _command;
	std::string _target;
	std::string _parameter;
	std::string _suffix;
};

#endif
