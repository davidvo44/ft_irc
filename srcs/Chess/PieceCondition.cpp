
#include "Bot.hpp"

bool Bot::WhitePawnCondition(int x, int y, int destx, int desty)
{
	if (x == 1 && destx == 3)
	{
		if (desty == y)
			if (CollisionCondition(2, y) == 0 || CollisionCondition(3, y) == 0)
				return 1;
		return 0;
	}
	if (x + 1 != destx)
		return 0;
	if (std::abs(y - desty) > 1)
		return 0;
	if (std::abs(y - desty) == 1)
		if (CollisionCondition(destx, desty) == 1)
			return 1;
	if (desty == y)
		if (CollisionCondition(destx, desty) == 0)
			return 1;
	return 0;
}

bool Bot::BlackPawnCondition(int x, int y, int destx, int desty)
{
	if (x == 6 && destx == 4)
	{
		if (desty == y)
			if (CollisionCondition(5, y) == 0 || CollisionCondition(4, y) == 0)
				return 1;
		return 0;
	}
	std::cout << "Pawn distance is: " << std::abs(y - desty) << std::endl;
	if (x - 1 != destx)
		return 0;
	if (std::abs(y - desty) > 1)
		return 0;
	if (std::abs(y - desty) == 1)
		if (CollisionCondition(destx, desty) == 1)
			return 1;
	if (desty == y)
		if (CollisionCondition(destx, desty) == 0)
			return 1;
	return 0;
}

bool Bot::TowerCondition(int x, int y, int destx, int desty)
{
	if (x != destx && y != desty)
		return 0;
	if (destx - x > 0)
	{
		for (int i = x + 1; i != destx; i++)
		{
			if (CollisionCondition(i, y) == 1)
				return 0;
		}
	}
	else if (destx - x < 0)
	{
		for (int i = x - 1; i != destx; i--)
		{
			if (CollisionCondition(i, y) == 1)
				return 0;
		}
	}
	else if (desty - y > 0)
	{
		for (int i = y + 1; i != desty; i++)
		{
			if (CollisionCondition(x, i) == 1)
				return 0;
		}
	}
	else if (desty - y < 0)
	{
		for (int i = y - 1; i != desty; i--)
		{
			if (CollisionCondition(x, i) == 1)
				return 0;
		}
	}
	return 1;
}

bool Bot::KnightCondition(int x, int y, int destx, int desty)
{
	if (std::abs(x - destx) == 1 && std::abs(y - desty) == 2)
		return 1;
	if (std::abs(x - destx) == 2 && std::abs(y - desty) == 1)
		return 1;
	else
		return 0;
}

bool Bot::BishopCondition(int x, int y, int destx, int desty)
{
	int input = y - x;
	if (destx + input == desty)
	{
		if (destx - x > 0)
		{
			for (int i = x + 1; i != destx; i++)
				if (CollisionCondition(i, i + input) == 1)
					return 0;
		}
		if (destx - x < 0)
		{
			for (int i = x - 1; i != destx; i--)
			{
				if (CollisionCondition(i, i + input) == 1)
					return 0;
			}
		}
		return 1;
	}
	input = y + x;
	if (input - destx == desty)
	{
		if (destx - x > 0)
		{
			for (int i = x + 1; i != destx; i++)
			{
				if (CollisionCondition(i, input - i) == 1)
					return 0;
			}
		}
		if (destx - x < 0)
		{
			for (int i = x - 1; i != destx; i--)
			{
				if (CollisionCondition(i, input - i) == 1)
					return 0;
			}
		}
		return 1;
	}
	return 0;
}

bool Bot::QueenCondition(int x, int y, int destx, int desty)
{
	if (BishopCondition(x, y, destx, desty) == 1)
		return 1;
	if (TowerCondition(x, y, destx, desty) == 1)
		return 1;
	return 0;
}

bool Bot::KingCondition(int x, int y, int destx, int desty)
{
	if (std::abs(y - desty) > 1 || std::abs(x - destx) > 1)
		return 0;
	std::cout << "King diag\n";
	_whiteSpe[7].x = destx;
	_whiteSpe[7].y = desty;
	return 1;
}
