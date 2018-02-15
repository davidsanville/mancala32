#include "Player.h"



int BadPlayer::chooseMove(const Board& b, Side s) const
{
	if (s != NORTH && s != SOUTH) { return -1; }
	Board tempBoard = b;
	for (int i = 1; i <= tempBoard.holes(); i++)
	{
		//cout << "tempBoard.holes() is: " << tempBoard.holes();
		//cout << "beans in side" << s <<" hole " << i << " is " << tempBoard.beans(s, i) << endl;
		if (tempBoard.beans(s, i) > 0) { return i; }
	}
	return -1;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	if (s != NORTH && s != SOUTH) { return -1; }
	int racecar;
	REPROMPT:
	cout << "Enter the hole you wish to sow: " << endl;
	cin >> racecar; 
	if (b.beans(s, racecar) == 0 || racecar <= 0 || racecar > b.holes()) { cout << "Invalid hole! Try again: " << endl; goto REPROMPT; }
	return racecar;

}



int SmartPlayer::evaluate(const TreeNode& tn, Side s) const
{
	//for (int i = 0; i < tn.m_numLegalMoves; i++)

	//cout << tn.TreeBoard.beans(s, 0);
	int val = tn.TreeBoard.beans(s, 0) - tn.TreeBoard.beans(opponent(s), 0);
	return val;
}



Board SmartPlayer::simulateMove(const Board& b, Side s, int h) const
{
	Board simulationBoard(b);
	Side simEndSide;
	int simEndHole;
	simulationBoard.sow(s, h, simEndSide, simEndHole);
	//check for capture and ending in a pot
	if (simEndHole == 0 && simEndSide == s)
	{
		chooseMove(simulationBoard, s);
	}
	if (simulationBoard.beans(s,simEndHole) == 1 && simulationBoard.beans(opponent(s), simEndHole) > 0)
	{
		//cerr << "spotted capture" << endl;
		simulationBoard.moveToPot(opponent(s), simEndHole, s);
		//cerr << simulationBoard.beans(s, 0);  
	}
	return simulationBoard;
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	//move recursively thru tree while creating nodes

	//create tree head from current board
	TreeNode Head(b, s);
	Board currBoard = b;
	//int headVal = evaluate(Head, s);
	int bestDiff = evaluate(Head, s);
	int bestIndex = 0;

	//if passed a board where game is over exit recursion
	if (currBoard.beansInPlay(s) == 0 && currBoard.beansInPlay(opponent(s)) == 0)
	{
		bestIndex = -1;
	}

	//construct temp Boards for first level of progeny
	for (int i = 0; i < Head.m_numLegalMoves; i++)
	{
		
		//push a Treenode with one simulated legal moved completed onto Children member vector
		//Progeny member side is opponents
		Head.Children.push_back(TreeNode(simulateMove(currBoard, s, Head.IndexOfLegals[i]), opponent(s)));
		//cout << Head.Children.back().TreeBoard.beans(s, 0);
		int hand = evaluate(Head.Children.back(),s);
		//cout << "hand is: " << hand << endl;
		if (hand > bestDiff) { bestDiff = hand; bestIndex = i; }
	
	}
	
	//Evaluate children vector


	if (Head.IndexOfLegals[bestIndex] < 1 || Head.IndexOfLegals[bestIndex] > currBoard.holes())
	{
		return Head.IndexOfLegals[0];
	}
	return Head.IndexOfLegals[bestIndex];
}











/*
int SmartPlayer::countLegalMoves(vector<int> &legs, const Board& b, Side s) const
{
	int j = 0;
	bool over = true;
	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) > 0){ legs.push_back(i); over = false; }
	}
	if (over) { return -1; }
	else return legs.size();
}
//implement a determine value function, apply to treeBoards
int SmartPlayer::value(const Board& b, Side playerSide) const
{
	int value = 0;
	if (playerSide == NORTH)
	{
		value = b.beans(NORTH, 0) - b.beans(SOUTH, 0);
	}
	if (playerSide == SOUTH)
	{
		value = b.beans(SOUTH, 0) - b.beans(NORTH, 0);
	}
	return value;
}


void SmartPlayer::chooseMove(const Board& b, Side playerSide, int& bestHole, int value)
{
	//find all legal moves
	vector<int> legals;
	legals.reserve(b.holes());
	int numLegalsMove = countLegalMoves(legals, b, playerSide);
	if (numLegalsMove == -1) { cerr << "No legal moves found: " << endl; bestHole = -1; }

	//create game tree
	//vector <vector<Game>> tree;
	//reserve how many turns ahead we will look
	tree.resize(3);
	//reserve all legal moves for first level

	tree[0].resize(numLegalsMove);
}


int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	

	//evaluate current position
	int currValue = value(b, s);
	int chosenHole = -2;

	
	
	
	//Side playerSide = s;
	Side dummy = NORTH;
	int frank = -2;
	for (int i = 0; i < numLegalsMove; i++)
	{
		Board tempTreeBoard = b;
		//"makes" possible moves
		tempTreeBoard.sow(s, legals[i], dummy, frank);
		//hold possible moves
		tree[0][i] = tempTreeBoard;
		//determine value of possible moves
		int hand = value(tree[0][i], s);
		//cout << "hand holding value is: " << hand << endl;
		//compare to current highest value
		if (hand > currValue) { currValue = hand; chosenHole = legals[i]; }
	}

	//if no better move if found, do first legal move
	if (chosenHole == -2){ return legals[0]; }

	if (chosenHole > 0 && chosenHole <= b.holes()) { return chosenHole; }
	else cerr << "Did not find valid hole! " << endl;
	return -1;

	/*
	for every hole h the player can choose
		"make" the move h
		chooseMove(opponent, h2, v2)
		"unmake" the move
	if v2 is better for the player than best seen so far,
		bestHole = h
		value = v2
		*/


	//return -999;
//}

