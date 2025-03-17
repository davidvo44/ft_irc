
#include "Bot.hpp"
#include "Poll.hpp"

Bot::Bot(int fdOut, int fdIn) : Client(fdOut, "localhost")
{
	_sock[0] = fdOut;
	_sock[1] = fdIn;
	Bot::initBot();
}

Bot::~Bot()
{
	close(_sock[0]);
	close (_sock[1]);
}

void Bot::sendServ()
{
	
}

void Bot::createChess(Channel &chan)
{
	(void)chan;
}

void Bot::initBot()
{
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, _sock) == -1)
	{
        throw("socket");
    }
    _fds.fd = _sock[0];
    _fds.events = POLLIN;
	_fds.revents = 0;
	Poll::getInstance()->getPollfd().push_back(_fds);
	std::string log = "PASS " + Server::getInstance()->getPassword() + "\n";
	log += "NICK ChessBot\nUSER ChessBot\n";
	if (fork() == 0)
	{
        close(_sock[0]);
        sleep(1);
		send(_sock[1], log.c_str(), log.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
        close(_sock[1]);
        exit(0);
    }
}
