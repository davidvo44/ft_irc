
#include "Chess.hpp"

Chess::Chess()
{
	StartGame();
}

Chess::Chess(std::string chan, std::string prefix) :_name("Chessbot"), _start(false), _whitefds(0), _blackfds(0), _chan(chan)
{
	(void)prefix;
	_prefix = ":Chess!Chess@127.0.0.1 ";
	StartGame();
}

int Chess::getWhiteFd() const
{
	return (_whitefds);
}

int Chess::getBlackFd() const
{
	return (_blackfds);
}

void Chess::StartGame()
{
	_start = false;
	_whitefds = 0;
	_blackfds = 0;
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

void Chess::PrintChess(int fd)
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
	std::string response = prefixmsg + "\r\n";
	send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	response = prefixmsg + "   A ┃ B ┃ C ┃ D ┃ E ┃ F ┃ G ┃ H\n";
	send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	response = prefixmsg + " ┏━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┓\n";
	send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
    for (int i = 0; i < 8; i++)
	{
		std::ostringstream oss;
		oss << (1 + i);
		response = oss.str() + "┃ ";
        for (int j = 0; j < 8; j++)
            response += board[i][j] + " ┃ ";
        response = prefixmsg + response + "\r\n";
		send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		response = prefixmsg + "━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫\n";
		send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
    }
}

void Chess::JoinChess(int fds)
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
		response = prefixmsg + "Joining White piece, looking for player...\r\n";
		send(fds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	response = prefixmsg + "Joining Black piece\r\n";
	send(fds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	_blackfds = fds;
	response = prefixmsg + "Game Start!!!\r\n";
	send(_whitefds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	PrintChess(_whitefds);
	send(_blackfds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	PrintChess(_blackfds);
	_start = true;
	_turn = 0;
	response = prefixmsg + "Your turn\n";
	send(_whitefds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}