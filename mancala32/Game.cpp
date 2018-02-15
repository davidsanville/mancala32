//game needs to keep track of changes to boards members

#include "Game.h"
#include <iostream>
using namespace std;


Game::Game(const Board& b, Player* south, Player* north)
{

	m_Board = b;
	m_SouthPlayer = south;
	m_NorthPlayer = north;
	m_TurnTrack = SOUTH;
}


void Game::display() const
{

	cout << endl;
	cout << " ";
	for (int i = 1; i <= this->m_Board.holes(); i++){ cout << this->m_Board.beans(NORTH,i); }
	cout << endl;
	cout << m_Board.beans(NORTH, 0);  for (int i = 0; i < m_Board.holes(); i++) {
		cout << " ";
	} cout << m_Board.beans(SOUTH, 0) << endl << " ";
	for (int i = 1; i <= this->m_Board.holes(); i++){ cout << this->m_Board.beans(SOUTH, i); }
	cout << endl << endl;
	
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	
	//change over to false if there is a non-empty side
	over = true;
	bool empty = true;
		for (int i = 1; i <= m_Board.holes(); i++)
		{
			if (m_Board.beans(NORTH, i) > 0) { empty = false; }
		}
		if (empty) { over = true; }
		else if (!empty) { over = false; }

		if (!over)
		{
			empty = true;
			for (int i = 1; i <= m_Board.holes(); i++)
			{
				if (m_Board.beans(SOUTH, i) > 0) { empty = false; }
			}
			if (empty) { over = true; }
			else if (!empty) { over = false; }
		}


		//if over check for a winner
		hasWinner = false;
		if (over)
		{
			int North_Score = this->beans(NORTH, 0);
			int South_Score = this->beans(SOUTH, 0);
			if (North_Score > South_Score) { hasWinner = true; winner = NORTH; }
			if (North_Score < South_Score) { hasWinner = true; winner = SOUTH; }
		}
	
}


bool Game::move()
{
	bool f_over = false;
	bool f_hasWinner = false;
	Side f_winner = NORTH;
	Side f_endSide;
	int f_endHole;

	// if over return false
	this->status(f_over, f_hasWinner, f_winner);
	if (f_over) 
	{
		cout << "The game is over: " << endl;
		cout << "The winner is: " << f_winner << endl;
		return false; 
	}

	cout << "It is player " << m_TurnTrack << "'s turn: " << endl;

	//if (m_TurnTrack ==NORTH) { m_NorthPlayer->chooseMove(); }
	REPEAT_TURN:
	if (m_TurnTrack == NORTH) 
	{ 
		int NorthHoleToSow = m_NorthPlayer->chooseMove(this->m_Board, NORTH);
		if (NorthHoleToSow < 1) { cerr << "player chose hole out of bounds"; }
		m_Board.sow(NORTH,NorthHoleToSow, f_endSide, f_endHole);
		cout << "Player " << m_TurnTrack << " sowed hole #" << NorthHoleToSow << endl;

	}
	if (m_TurnTrack == SOUTH) 
	{
		int SouthHoleToSow = m_SouthPlayer->chooseMove(this->m_Board, SOUTH);
		if (SouthHoleToSow < 1) { cerr << "player chose hole out of bounds"; }
		m_Board.sow(SOUTH, SouthHoleToSow, f_endSide, f_endHole); 
		cout << "Player " << m_TurnTrack << " sowed hole #" << SouthHoleToSow << endl;
	}

	this->display();
	//if endHole is pot, repeat turn
	//cout << "endHole is: " << f_endHole << endl;
	if (f_endHole == 0) 
	{ 
		//check that game is not over before continuing
		this->status(f_over, f_hasWinner, f_winner);
		if (f_over)
		{
			cout << "The game is over: " << endl;
			cout << "The winner is: " << f_winner << endl;
			return false;
		}
		cout << "Dropped in pot! Go again: " << endl;
		//cout << "Press Enter to continue: " << endl;
		cin.ignore(10000, '\n');
		goto REPEAT_TURN; 
	}
	
	//identify capture, endhole was just empty, and on players side, and not a pot
	if (m_Board.beans(f_endSide, f_endHole) == 1 && f_endSide == m_TurnTrack && f_endHole !=0)
	{
		
		if (f_endSide == NORTH)
		{
			//if opposite hole is empty, break
			if (m_Board.beans(SOUTH, f_endHole) == 0) { goto END_CAPTURE_SEQUENCE; }
			//if not empty, capture it
			if (m_Board.moveToPot(SOUTH, f_endHole, NORTH)) { cout << "Captured! " << endl; }
			else cerr << "moveToPot called and return false..." << endl;
			this->display();
		}
		if (f_endSide == SOUTH) 
		{ 
			//if opposite hole is empty, break
			if (m_Board.beans(NORTH, f_endHole) == 0) { goto END_CAPTURE_SEQUENCE; }
			//if not empty, capture it
			if (m_Board.moveToPot(NORTH, f_endHole, SOUTH)) { cout << "Captured! " << endl; }
			else cerr << "moveToPot called and return false..." << endl;
			this->display();
		}
	}
	END_CAPTURE_SEQUENCE:

	if (m_TurnTrack == NORTH) { m_TurnTrack = SOUTH; return true; }
	if (m_TurnTrack == SOUTH) { m_TurnTrack = NORTH; return true; }

    return false; //had to add this line for compilation
}


void Game::play()
{
	cout << "May the odds be forever in your favor: " << endl;
	this->display();

PLAY_ON:
	
	if (this->move())
	{ 
		cout << "Press Enter to continue: " << endl;
		cin.ignore(10000, '\n');
		
		goto PLAY_ON; 
	}
	
	return;
}

int Game::beans(Side s, int hole) const
{
	return m_Board.beans(s, hole);
}
