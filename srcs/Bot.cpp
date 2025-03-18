
#include "Bot.hpp"
#include "Poll.hpp"

Bot::Bot(int fdOut, int fdIn) : Client(fdOut, "localhost")
{
	_sock[0] = fdOut;
	_sock[1] = fdIn;
}

Bot::~Bot()
{
	close(_sock[0]);
	close (_sock[1]);
}

void Bot::createChess(Channel &chan)
{
	(void)chan;
}

void Bot::initBot()
{
    _fds.fd = _sock[0];
    _fds.events = POLLIN;
	_fds.revents = 0;
	Poll::getInstance()->getPollfd().push_back(_fds);
	std::string log = "PASS " + Server::getInstance()->getPassword() + "\n";
	log += "NICK ChessBot\nUSER ChessBot\n";
	send(_sock[1], log.c_str(), log.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

void Bot::joinChan()
{
	std::string log;
	Server *server = Server::getInstance();
	for (std::map<std::string, Channel*>::iterator it = server->getChannel().begin();it != server->getChannel().end(); it++)
	{
		if (it->second->isInWhitelist(_sock[0]) == true)
		{
			if(!it->second->getClient().findValue(_sock[0]))
			{
				log+= "JOIN " + it->second->getName() + "\n";
				send(_sock[1], log.c_str(), log.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
			}

		}
	}
}