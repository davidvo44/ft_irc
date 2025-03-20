
#include "Chess.hpp"

void Chess::Ongame(int fd, Message &message)
{
	std::string prefixmsg = _prefix + "PRIVMSG " + _chan + " ";
	std::string response;
	if (_turn % 2 == 0 && fd != _whitefds)
	{
		response = prefixmsg + "Not your turn!!!\r\n";
		send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	if (_turn % 2 == 1 && fd != _blackfds)
	{
		response = prefixmsg + "Not your turn!!!\r\n";
		send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	if (message.getParameter().empty() == true || message.getSuffix().empty() == true)
	{
		response = prefixmsg + "Need more parameter!!!\r\n";
		send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
		return;
	}
	if (_turn % 2 == 0)
		MovePiece(_whitePawn, _whiteSpe, message);
	else
		MovePiece(_blackPawn, _blackSpe, message);
	response = prefixmsg + "Your turn\r\n";
	if (_turn % 2 == 0)
		send(_whitefds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	else
		send(_blackfds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	response = prefixmsg + "CHESS!!\r\n";
	if (isChess(_whiteSpe[7].x, _whiteSpe[7].y) == 1)
		send(_whitefds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
	if (isChess(_blackSpe[7].x, _blackSpe[7].y) == 1)
		send(_blackfds, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

bool Chess::CollisionCondition(int x, int y)
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

bool Chess::isChess(int x, int y)
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

void Chess::send_error(int fd)
{
	std::string prefixmsg = _prefix + "PRIVMSG " + _chan + " ";
	std::string response;
	response = prefixmsg + "Invalid Move\r\n";
			send(fd, response.c_str(), response.length(), MSG_DONTWAIT | MSG_NOSIGNAL);
}
