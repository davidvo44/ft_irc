/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:58:25 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/04 18:44:54 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <sys/socket.h>

Bot::Bot()
{
	StartGame();
}

Bot::Bot(std::string chan, std::string prefix) : _start(false), _whitefds(0), _blackfds(0), _prefix(prefix), _chan(chan)
{
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
		else if (i == 7)
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
	response = prefixmsg + "  A B C D E F G H\n";
	send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	response = prefixmsg + " +----------------\n";
	send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
    for (int i = 0; i < 8; i++)
	{
		std::ostringstream oss;
		oss << (1 + i);
		response = oss.str() + "|";
        for (int j = 0; j < 8; j++)
            response += board[i][j] + " ";
        response = prefixmsg + response + "| \n";
		send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
    }

    response = prefixmsg + " +----------------\n";
	send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
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
		WhiteMove(message);
	else
		BlackMove(message);
	response = prefixmsg + "Your turn\n";
	if (_turn % 2 == 0)
		send(_whitefds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	else
		send(_blackfds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

void Bot::WhiteMove(Message &message)
{
	std::string prefixmsg = _prefix + "PRIVMSG " + _chan + " ";
	std::string response;
	int x = message.getContent()[1] - '1';
	int y = message.getContent()[0] - 'A';
	int destx = message.getSuffix()[1] - '1';
	int desty = message.getSuffix()[0] - 'A';
	for (int i = 0; i < 8; i++)
	{
		if ((_whitePawn[i].x == destx && _whitePawn[i].y == desty) || \
		 (_whiteSpe[i].x == destx && _whiteSpe[i].y == desty))
		{
			response = prefixmsg + "Pawn at :" + message.getContent() + " can't move here\n";
			send(_whitefds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
			return;
		}
		if (_blackPawn[i].x == destx && _blackPawn[i].y == desty)
			_blackPawn[i].x = -1;
    	if (_blackSpe[i].x == destx && _blackSpe[i].y == desty)
			_blackPawn[i].x = -1;
	}
	for (int i = 0; i < 9; i++)
	{
		if (i == 8)
		{
			response = prefixmsg + "Pawn not found\n";
			send(_whitefds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
			return;
		}
		if (_whitePawn[i].x == x && _whitePawn[i].y == y)
		{
			_whitePawn[i].x = destx;
			_whitePawn[i].y = desty;
			break;
		}
		if (_whiteSpe[i].x == x && _whiteSpe[i].y == y)
		{
			_whiteSpe[i].x = destx;
			_whiteSpe[i].y = desty;
			break;
		}
	}
	_turn++;
	PrintChess(_whitefds);
	PrintChess(_blackfds);
}

void Bot::BlackMove(Message &message)
{
	std::string prefixmsg = _prefix + "PRIVMSG " + _chan + " ";
	std::string response;
	int x = message.getContent()[1] - '1';
	int y = message.getContent()[0] - 'A';
	int destx = message.getSuffix()[1] - '1';
	int desty = message.getSuffix()[0] - 'A';
	for (int i = 0; i < 8; i++)
	{
		if ((_blackPawn[i].x == destx && _blackPawn[i].y == desty) || \
		 (_blackSpe[i].x == destx && _blackSpe[i].y == desty))
		{
			response = prefixmsg + "Pawn at :" + message.getContent() + "can't move here\n";
			send(_blackfds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
			return;
		}
		if (_whitePawn[i].x == destx && _whitePawn[i].y == desty)
			_whitePawn[i].x = -1;
    	if (_whiteSpe[i].x == destx && _whiteSpe[i].y == desty)
			_whitePawn[i].x = -1;
	}
	for (int i = 0; i < 9; i++)
	{
		if (i == 8)
		{
			response = prefixmsg + "Pawn not found\n";
			send(_blackfds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
			return;
		}
		if (_blackPawn[i].x == x && _blackPawn[i].y == y)
		{
			_blackPawn[i].x = destx;
			_blackPawn[i].y = desty;
			break;
		}
		if (_blackSpe[i].x == x && _blackSpe[i].y == y)
		{
			_blackSpe[i].x = destx;
			_blackSpe[i].y = desty;
			break;
		}
	}
	_turn++;
	PrintChess(_whitefds);
	PrintChess(_blackfds);
}
