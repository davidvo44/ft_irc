/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:57:17 by saperrie          #+#    #+#             */
/*   Updated: 2025/03/03 13:57:20 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <unistd.h>
#include "Message.hpp"

struct PiecePosition
{
	int x;
	int y;
};

class Bot
{
public:
	Bot();
	Bot(std::string chan, std::string prefx);
	void StartGame();
	void PrintChess(int fd);
	void JoinChess(int fd);
	void Ongame(int fd, Message &message);
	void WhiteMove(Message &message);
	void BlackMove(Message &message);

private:
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
};

#endif

// stockfish
