#ifndef GAME_INCLUDED
#define GAME_INCLUDED


#include "Board.h"
#include "Player.h"

class Game
{


public:
Game(const Board& b, Player* south, Player* north);
void display() const;
void status(bool& over, bool& hasWinner, Side& winner) const;
bool move();
void play();
int beans(Side s, int hole) const;

Board* BoardAccessor() { Board* temp = &m_Board; return temp; }

private:
	Board m_Board;
	Player* m_SouthPlayer;
	Player* m_NorthPlayer;
	Side m_TurnTrack;

};

#endif