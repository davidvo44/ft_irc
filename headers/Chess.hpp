
#ifndef CHESS_HPP
#define CHESS_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <sys/socket.h>
#include <cstdlib>
#include <unistd.h>
#include "Message.hpp"

struct PiecePosition
{
	int x;
	int y;
};

class Chess
{
public:
	Chess();
	Chess(std::string chan, std::string prefx);

	int getWhiteFd() const;
	int getBlackFd() const;
	void StartGame();
	void PrintChess(int fd);
	void JoinChess(int fd);
	void Ongame(int fd, Message &message);
	void MovePiece(std::map<int, PiecePosition> &Pawn, std::map<int, PiecePosition> &Spe, Message &message);
	void send_error(int fd);
	bool isChess(int x, int y);

	bool WhitePawnCondition(int x, int y, int destx, int desty);
	bool BlackPawnCondition(int x, int y, int destx, int desty);
	bool TowerCondition(int x, int y, int destx, int desty);
	bool CollisionCondition(int x, int y);
	bool KnightCondition(int x, int y, int destx, int desty);
	bool BishopCondition(int x, int y, int destx, int desty);
	bool QueenCondition(int x, int y, int destx, int desty);
	bool KingCondition(int x, int y, int destx, int desty);
	bool Check_Kill_n_Chess(PiecePosition &piece, int fd, int x, int y, int destx, int desty);
	bool checkSpecialPieceMove(Message &message, int i);
	bool checkPawnPieceMove(int fd, Message &message);
private:
	std::string _name;
	int _turn;
	bool _start;
	int _whitefds;
	int _blackfds;
	std::string board[8][8];
	std::map<int, PiecePosition> _whitePawn;
	std::map<int, PiecePosition> _whiteSpe;
	std::map<int, PiecePosition> _blackPawn;
	std::map<int, PiecePosition> _blackSpe;
	std::string _prefix;
	std::string _chan;
	bool _ischess;
};

#endif
