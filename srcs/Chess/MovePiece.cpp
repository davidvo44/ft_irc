
#include "Bot.hpp"

void Bot::MovePiece(std::map<int, PiecePosition> &Pawn, std::map<int, PiecePosition> &Spe, Message &message)
{
	int fd;
	if (Pawn[0].x == _whitePawn[0].x && Pawn[0].y == _whitePawn[0].y)
		fd = _whitefds;
	else
		fd = _blackfds;
	int x = message.getParameter()[1] - '1';
	int y = message.getParameter()[0] - 'A';
	int destx = message.getSuffix()[1] - '1';
	int desty = message.getSuffix()[0] - 'A';
	for (int i = 0; i < 8; i++)
	{
		if ((Pawn[i].x == destx && Pawn[i].y == desty) ||
			(Spe[i].x == destx && Spe[i].y == desty))
			return (send_error(fd));
	}
	for (int i = 0; i < 9; i++)
	{
		if (Pawn[i].x == x && Pawn[i].y == y)
		{
			if (checkPawnPieceMove(fd, message) == false)
				return (send_error(fd));
			Pawn[i].x = destx;
			Pawn[i].y = desty;
			if (Check_Kill_n_Chess(Pawn[i], fd, x, y, destx, desty) == 0)
				return (send_error(fd));
			break;
		}
		if (Spe[i].x == x && Spe[i].y == y)
		{
			if (checkSpecialPieceMove(message, i) == false)
				return (send_error(fd));
			Spe[i].x = destx;
			Spe[i].y = desty;
			if (Check_Kill_n_Chess(Spe[i], fd, x, y, destx, desty) == 0)
				return (send_error(fd));
			break;
		}
		if (i == 8)
			return (send_error(fd));
	}
	for (int i = 0; i < 8; i++)
	{
		if (_whitePawn[i].x == destx && _whitePawn[i].y == desty && fd == _blackfds)
			_whitePawn[i].x = -1;
		if (_blackPawn[i].x == destx && _blackPawn[i].y == desty && fd == _whitefds)
			_blackPawn[i].x = -1;
		if (_whiteSpe[i].x == destx && _whiteSpe[i].y == desty && fd == _blackfds)
			_whiteSpe[i].x = -1;
		if (_blackSpe[i].x == destx && _blackSpe[i].y == desty && fd == _whitefds)
			_blackSpe[i].x = -1;
	}
	PrintChess(_whitefds);
	PrintChess(_blackfds);
	_turn++;
}

bool Bot::Check_Kill_n_Chess(PiecePosition &piece, int fd, int x, int y, int destx, int desty)
{
	if (fd == _blackfds)
	{
		for (int i = 0; i < 8; i++)
		{
			if (_whitePawn[i].x == destx && _whitePawn[i].y == desty)
				_whitePawn[i].x = -2;
			if (_whiteSpe[i].x == destx && _whiteSpe[i].y == desty)
				_whiteSpe[i].x = -2;
		}
		if (isChess(_blackSpe[7].x, _blackSpe[7].y) == 1)
		{
			piece.x = x;
			piece.y = y;
			for (int i = 0; i < 8; i++)
			{
				if (_whitePawn[i].x == -2)
					_whitePawn[i].x = destx;
				if (_whiteSpe[i].x == -2)
					_whiteSpe[i].x = destx;
			}
			return 0;
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			if (_blackPawn[i].x == destx && _blackPawn[i].y == desty)
				_blackPawn[i].x = -2;
			if (_blackSpe[i].x == destx && _blackSpe[i].y == desty)
				_blackSpe[i].x = -2;
		}
		if (isChess(_whiteSpe[7].x, _whiteSpe[7].y) == 1)
		{
			piece.x = x;
			piece.y = y;
			for (int i = 0; i < 8; i++)
			{
				if (_blackPawn[i].x == -2)
					_blackPawn[i].x = destx;
				if (_blackSpe[i].x == -2)
					_blackSpe[i].x = destx;
			}
			return 0;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (_whitePawn[i].x == -2)
			_whitePawn[i].x = -1;
		if (_whiteSpe[i].x == -2)
			_whiteSpe[i].x = -1;
		if (_blackPawn[i].x == -2)
			_blackPawn[i].x = -1;
		if (_blackSpe[i].x == -2)
			_blackSpe[i].x = -1;
	}
	return 1;
}

bool Bot::checkSpecialPieceMove(Message &message, int i)
{
	int x = message.getParameter()[1] - '1';
	int y = message.getParameter()[0] - 'A';
	int destx = message.getSuffix()[1] - '1';
	int desty = message.getSuffix()[0] - 'A';
	if (i < 2)
	{
		std::cout << "tower\n";
		if (TowerCondition(x, y, destx, desty) == 0)
			return false;
	}
	else if (i < 4)
	{
		std::cout << "knight\n";
		if (KnightCondition(x, y, destx, desty) == 0)
			return false;
	}
	else if (i < 6)
	{
		std::cout << "bishop\n";
		if (BishopCondition(x, y, destx, desty) == 0)
			return false;
	}
	else if (i == 6)
	{
		std::cout << "queen\n";
		if (BishopCondition(x, y, destx, desty) == 0)
			return false;
	}
	else
	{
		if (KingCondition(x, y, destx, desty) == 0)
			return false;
	}
	return true;
}

bool Bot::checkPawnPieceMove(int fd, Message &message)
{
	int x = message.getParameter()[1] - '1';
	int y = message.getParameter()[0] - 'A';
	int destx = message.getSuffix()[1] - '1';
	int desty = message.getSuffix()[0] - 'A';
	std::cout << "Pawn deteccted\n";
	if (fd == _whitefds)
	{
		if (WhitePawnCondition(x, y, destx, desty) == 0)
			return false;
	}
	else
	{
		if (BlackPawnCondition(x, y, destx, desty) == 0)
			return false;
	}
	return true;
}
