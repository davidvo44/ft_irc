#include "Bot.hpp"
#include <sys/socket.h>
#include <cstdlib>

Bot::Bot()
{
	StartGame();
}

Bot::Bot(std::string chan, std::string prefix) : _start(false), _whitefds(0), _blackfds(0), _chan(chan)
{
	(void)prefix;
	_prefix = ":Chess!Chess@127.0.0.1 ";
	StartGame();
}

void Bot::StartGame()
{
	for (int i = 0; i < 8; i++)
	{
    	_whitePawn[i].x = 1;
    	_whitePawn[i].y = i;
    	_blackPawn[i].x = 6;
    	_blackPawn[i].y = i;
	}
	for (int i = 0; i < 8; i++)
	{
		_whiteSpe[i].x = 0;
		_blackSpe[i].x = 7;
	}

	_whiteSpe[0].y = _blackSpe[0].y = 0;
	_whiteSpe[1].y = _blackSpe[1].y = 7;
	_whiteSpe[2].y = _blackSpe[2].y = 1;
	_whiteSpe[3].y = _blackSpe[3].y = 6;
	_whiteSpe[4].y = _blackSpe[4].y = 2;
	_whiteSpe[5].y = _blackSpe[5].y = 5;
	_whiteSpe[6].y = _blackSpe[6].y = 3;
	_whiteSpe[7].y = _blackSpe[7].y = 4;
}

void Bot::PrintChess(int fd)
{
	std::string prefixmsg = _prefix + "PRIVMSG " + _chan + " ";
	for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board[i][j] = " ";

	for (int i = 0; i < 8; i++)
	{
		if (_whitePawn[i].x != -1)
			board[_whitePawn[i].x][_whitePawn[i].y] = "♙";
		if (_blackPawn[i].x != -1)
			board[_blackPawn[i].x][_blackPawn[i].y] = "♟";
		if (i < 2)
		{
			if (_whiteSpe[i].x != -1)
				board[_whiteSpe[i].x][_whiteSpe[i].y] = "♖";
			if (_blackSpe[i].x != -1)
				board[_blackSpe[i].x][_blackSpe[i].y] = "♜";
		}
		else if (i < 4)
		{
			if (_whiteSpe[i].x != -1)
				board[_whiteSpe[i].x][_whiteSpe[i].y] = "♘";
			if (_blackSpe[i].x != -1)
				board[_blackSpe[i].x][_blackSpe[i].y] = "♞";
		}
		else if (i < 6)
		{
			if (_whiteSpe[i].x != -1)
				board[_whiteSpe[i].x][_whiteSpe[i].y] = "♗";
			if (_blackSpe[i].x != -1)
				board[_blackSpe[i].x][_blackSpe[i].y] = "♝";
		}
		else if (i == 6)
		{
			if (_whiteSpe[i].x != -1)
				board[_whiteSpe[i].x][_whiteSpe[i].y] = "♕";
			if (_blackSpe[i].x != -1)
				board[_blackSpe[i].x][_blackSpe[i].y] = "♛";
		}
		else
		{
			if (_whiteSpe[i].x != -1)
				board[_whiteSpe[i].x][_whiteSpe[i].y] = "♔";
			if (_blackSpe[i].x != -1)
				board[_blackSpe[i].x][_blackSpe[i].y] = "♚";
		}
	}
	std::string response = prefixmsg + "\n";
	send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	response = prefixmsg + "   A | B | C | D | E | F | G | H\n";
	send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	response = prefixmsg + " +-------------------------------+\n";
	send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
    for (int i = 0; i < 8; i++)
	{
		std::ostringstream oss;
		oss << (1 + i);
		response = oss.str() + "| ";
        for (int j = 0; j < 8; j++)
            response += board[i][j] + " | ";
        response = prefixmsg + response + "\n";
		send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		response = prefixmsg + " +-------------------------------+\n";
		send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
    }
}

void Bot::JoinChess(int fds)
{
	std::string prefixmsg = _prefix + "PRIVMSG " + _chan + " ";
	std::string response;
	if (_start == true)
	{
		response = prefixmsg + "Can't join, game already started\n";
		send(fds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	if (_whitefds == 0)
	{
		_whitefds = fds;
		response = prefixmsg + "Joining White piece, looking for player...\n";
		send(fds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	response = prefixmsg + "Joining Black piece\n";
	send(fds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	_blackfds = fds;
	response = prefixmsg + "Game Start!!!\n";
	send(_whitefds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	PrintChess(_whitefds);
	send(_blackfds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	PrintChess(_blackfds);
	_start = true;
	_turn = 0;
	response = prefixmsg + "Your turn\n";
	send(_whitefds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

void Bot::Ongame(int fd, Message &message)
{
	std::string prefixmsg = _prefix + "PRIVMSG " + _chan + " ";
	std::string response;
	if (_turn % 2 == 0 && fd != _whitefds)
	{
		response = prefixmsg + "Not your turn!!!\n";
		send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	if (_turn % 2 == 1 && fd != _blackfds)
	{
		response = prefixmsg + "Not your turn!!!\n";
		send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	if (message.getContent().empty() == true || message.getSuffix().empty() == true)
	{
		response = prefixmsg + "Need more parameter!!!\n";
		send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	if (_turn % 2 == 0)
		MovePiece(_whitePawn, _whiteSpe, message);
	else
		MovePiece(_blackPawn, _blackSpe, message);
	response = prefixmsg + "Your turn\n";
	if (_turn % 2 == 0)
		send(_whitefds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	else
		send(_blackfds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	response = prefixmsg + "CHESS!!\n";
	if (isChess(_whiteSpe[7].x, _whiteSpe[7].y) == 1)	
		send(_whitefds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	if (isChess(_blackSpe[7].x, _blackSpe[7].y) == 1)
		send(_blackfds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

bool Bot::CollisionCondition(int x, int y)
{
	for (int i = 0; i < 8; i++)
	{
		if ((_whitePawn[i].x == x && _whitePawn[i].y == y) || \
		 (_whiteSpe[i].x == x && _whiteSpe[i].y == y) || \
		 (_blackPawn[i].x == x && _blackPawn[i].y == y) || \
		 ((_blackSpe[i].x == x && _blackSpe[i].y == y)))
			return 1;
	}
	return 0;
}

bool Bot::isChess(int x, int y)
{
	if (_blackSpe[7].x == x && _blackSpe[7].y == y)
	{
		for (int i = 0; i < 8; i++)
			if (WhitePawnCondition(_whitePawn[i].x, _whitePawn[i].y, x, y) == 1)
				return 1;
		if (TowerCondition(_whiteSpe[0].x, _whiteSpe[0].y, x, y) == 1 ||\
		TowerCondition(_whiteSpe[1].x, _whiteSpe[1].y, x, y) == 1 ||\
		KnightCondition(_whiteSpe[2].x, _whiteSpe[2].y, x, y) == 1 ||\
		KnightCondition(_whiteSpe[3].x, _whiteSpe[3].y, x, y) == 1 ||\
		BishopCondition(_whiteSpe[4].x, _whiteSpe[4].y, x, y) == 1 ||\
		BishopCondition(_whiteSpe[5].x, _whiteSpe[5].y, x, y) == 1 ||\
		QueenCondition(_whiteSpe[6].x, _whiteSpe[6].y, x, y) == 1 ||\
		KingCondition(_whiteSpe[7].x, _whiteSpe[7].y, x, y) == 1 )
			return 1;
		return 0;
	}
	for (int i = 0; i < 8; i++)
		if (BlackPawnCondition(_blackPawn[i].x, _blackPawn[i].y, x, y) == 1)
			return 1;
	if (TowerCondition(_blackSpe[0].x, _blackSpe[0].y, x, y) == 1 ||\
		TowerCondition(_blackSpe[1].x, _blackSpe[1].y, x, y) == 1 ||\
		KnightCondition(_blackSpe[2].x, _blackSpe[2].y, x, y) == 1 ||\
		KnightCondition(_blackSpe[3].x, _blackSpe[3].y, x, y) == 1 ||\
		BishopCondition(_blackSpe[4].x, _blackSpe[4].y, x, y) == 1 ||\
		BishopCondition(_blackSpe[5].x, _blackSpe[5].y, x, y) == 1 ||\
		QueenCondition(_blackSpe[6].x, _blackSpe[6].y, x, y) == 1 ||\
		KingCondition(_blackSpe[7].x, _blackSpe[7].y, x, y) == 1 )
			return 1;
	return 0;
}

void Bot::send_error(int fd)
{
	std::string prefixmsg = _prefix + "PRIVMSG " + _chan + " ";
	std::string response;
	response = prefixmsg + "Invalid Move\n";
			send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}
