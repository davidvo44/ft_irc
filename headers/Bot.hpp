
#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include "Client.hpp"

class Channel;

class Bot : public Client
{
public:
	Bot(int out, int in);
	~Bot();
	void sendServ();
	void createChess(Channel &chan);
private:
	void initBot();
	std::string _name;
	int _sock[2];
	pollfd _fds;
};

#endif
