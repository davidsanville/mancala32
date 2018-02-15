#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED  

#include "Side.h"
#include <vector>
#include <iostream>

using namespace std;

class Board {

public:
	Board() : m_Holes(0) {}
	Board(int nHoles, int nInitialBeansPerHole);
	Board(const Board& toCpy);
			
	int holes() const { return m_Holes; }
	int beans(Side s, int hole) const { return NS[s][hole].m_BeansInHole; }
	int beansInPlay(Side s) const;
	int totalBeans() const { return m_totalBeans; }
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	bool moveToPot(Side s, int hole, Side potOwner);
	bool setBeans(Side s, int hole, int beans);
	
	
	
private:
	int m_Holes;
	int m_InitialBeansPerHole;
	int m_totalBeans;
	

	struct Hole
	{
		
		Hole() :m_BeansInHole(0){}
		Side m_Side;
		int m_HoleIndex;
		int m_BeansInHole;

	};
	

	//vector<Hole> NS[2];
	vector < vector<Hole> > NS;

};




#endif 