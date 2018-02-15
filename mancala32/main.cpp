//fix smart player legals vector

#include "Board.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{

	

	Board Kalah(4, 1);
	Kalah.setBeans(SOUTH, 4, 0);
	Kalah.setBeans(NORTH, 4, 5);
	HumanPlayer hp("David");
	HumanPlayer hp1("Nick");
	BadPlayer bp("Stephen");
	BadPlayer bp2("Jack");
	SmartPlayer sp("Ash");
	
	
	//Game g(Kalah, &bp2, &bp);
	//Game g(Kalah, &hp, &bp);
	//Kalah.setBeans(NORTH, 1, 9);
	Game g(Kalah, &sp, &hp);

	g.play();
	


	//g.display();
	//Side dum = NORTH;
	//int dumer = 0;
	//g.BoardAccessor()->sow(NORTH, 3,dum,dumer);  
	//g.display();
	//cout << "The ending hole is: " << dum  << " " << dumer << endl;
	//g.BoardAccessor()->sow(NORTH, 6, dum, dumer);
//	g.display();
	//g.BoardAccessor()->sow(SOUTH, 4, dum, dumer);
	//g.display();
	//Board temp = g.BoardAccessor();
	//temp.sow(NORTH, 4, dum, dumer);
	//Game G(temp, &hp1, &hp2);
	//G.display();

	




	/*
	Board Kalah(6, 4);
	assert(Kalah.holes() == 6);
	cout << "Passed Board construction test: " << endl;
	assert(Kalah.beans(NORTH, 2) == 4);
	cout << "Passed beans in a particular hole test: " << endl;
	assert(Kalah.beansInPlay(NORTH) == 24);
	cout << "Passed beansInPlay(side) test: " << endl;

	Side endSide = NORTH;
	int endHole = -1;
	assert(Kalah.sow(NORTH, 4, endSide, endHole));
	assert(Kalah.beans(NORTH, 4) == 0 && Kalah.beans(NORTH, 3) == 5 && Kalah.beans(NORTH, 2) == 5 && Kalah.beans(NORTH, 1) == 5 && Kalah.beans(NORTH, 0) == 1);
	assert(endHole == 0);
	assert(endSide == NORTH);
	cout << "Passed sow tests: " << endl;

	*/
	system("pause");
	return 0;
}