
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"
#include "Bot.hpp"
#include <algorithm>
#include <vector>

class Channel
{
public:
	Channel(std::string name, Client *client);
	Channel();
	~Channel();

	void addClient(Client *client);
	void joinChannel(Client *client);

	void partChannel(Client& client);
	void setTopic(const std::string topic);

	void addMode(char ope);
	void deleteMode(char ope);
	bool viewMode(char ope);
	bool isOperator(int client);
	bool isInWhitelist(int client);
	void addToWhitelist(int client);

	std::string getName();
	const std::string getTopic();
	std::string getSuffixword();
	void setPassword(std::string pass);

	MutantMap<int, Client *> &getClient();
	void removeClient(MutantMap<int, Client*>& clients, int clientKey, std::string clientNick);

	std::vector<int> &getOperator();

	Bot *getBot();

	Client *operator[](unsigned index);
	Client *operator!=(unsigned index);

private:
	std::string _username;
	std::string _targetpic;
	std::string _suffixword;

	MutantMap<int, Client *> _Clients;

	std::vector<int> _operator;
	std::vector<int> _wlist;

	int _mode;

	Bot *_bot;
};

#endif
