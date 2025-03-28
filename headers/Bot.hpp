
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
	void createChess(Channel &chan);
	void joinChan();
	void initBot();
	int getFdIn();
private:
	std::string _name;
	int _sock[2];
	pollfd _fds;
};

#endif
