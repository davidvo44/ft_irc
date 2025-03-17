
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"
#include "Chess.hpp"
#include <algorithm>
#include "MutantMap.hpp"
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
	void setMaxclient(int nb);
	int getMaxclient();

	MutantMap<int, Client *> &getClient();
	void removeClient(MutantMap<int, Client*>& clients, int clientKey, std::string clientNick);

	std::vector<int> &getOperator();

	Chess *getChess();

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
	int _maxclient;

	Chess *_chess;
};

#endif
