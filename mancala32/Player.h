#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "Board.h"

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Player 
{
public:
	Player(string name) :m_name(name){}
	string name() const { return m_name; }
	virtual bool isInteractive() const { return false; }
	virtual int chooseMove(const Board& b, Side s) const = 0;
	virtual ~Player() {}
private:
	string m_name;
	
};

class HumanPlayer : public Player
{	
public:
	HumanPlayer(string nm) : Player(nm)  {}
	bool isInteractive() const { return true; }
	int chooseMove(const Board& b, Side s) const;
	//~HumanPlayer() {};
private:
	string m_name;
	
	
};

class BadPlayer : public Player
{
public:
	BadPlayer(string nm) : Player(nm)  {}
	bool isInteractive() const { return false; }
	int chooseMove(const Board& b, Side s) const;
private:
	string m_name;
		
};
////////////////////////////////SMARTPLAYER///////////////////////


struct TreeNode
{

	TreeNode(const Board& b, Side s) 
		:TreeBoard(b), TreeSide(s)
	{
		m_numLegalMoves = 0;
		//count and index legal moves
		for (int i = 1; i <= TreeBoard.holes(); i++)
		{
			//if non-empty hole, increment numLegalMoves and save index
			if (TreeBoard.beans(s, i) > 0) { m_numLegalMoves++; IndexOfLegals.push_back(i); }
		}
		//allocate space for Children
	}

	Board TreeBoard;
	Side TreeSide;
	vector<TreeNode> Children;
	vector<int> IndexOfLegals;
	int m_numLegalMoves;
};


class SmartPlayer : public Player
{
public:
	SmartPlayer(string nm) : Player(nm)  {}
	 bool isInteractive() const { return false; }
	 int chooseMove(const Board& b, Side s) const;
	 Board simulateMove(const Board& b, Side s, int h) const;
	 int evaluate(const TreeNode& tn, Side s) const;

private:
	string m_name;

};





#endif //PLAYER_INCLUDED