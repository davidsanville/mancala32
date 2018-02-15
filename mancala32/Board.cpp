#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
{
	m_Holes = nHoles;
	m_InitialBeansPerHole = nInitialBeansPerHole;
	m_totalBeans = nHoles * nInitialBeansPerHole;

	NS.resize(2);
	//NS.resize(2);
	for (int i = 0; i < 2; i++)
	{
		NS[i].resize(nHoles+1);
	}
	

	NS[0][0].m_Side = NORTH;
	NS[0][0].m_BeansInHole = 0;
	NS[0][0].m_HoleIndex = 0;
	NS[1][0].m_Side = SOUTH;
	NS[1][0].m_BeansInHole = 0;
	NS[1][0].m_HoleIndex = 0;
	
	for (int i = 1; i <= nHoles; i++)
	{
		NS[0][i].m_Side = NORTH;
		NS[0][i].m_BeansInHole = nInitialBeansPerHole;
		NS[0][i].m_HoleIndex = i;

		NS[1][i].m_Side = SOUTH;
		NS[1][i].m_BeansInHole = nInitialBeansPerHole;
		NS[1][i].m_HoleIndex = i;
	}
	

}


Board::Board(const Board& toCpy)
{
	
	m_Holes = toCpy.m_Holes;
	m_InitialBeansPerHole = toCpy.m_InitialBeansPerHole;
	m_totalBeans = toCpy.m_totalBeans;

	
	NS.resize(2);
	for (int i = 0; i < 2; i++)
	{
		NS[i].resize(toCpy.holes()+1);
	}


	NS[0][0].m_Side = toCpy.NS[0][0].m_Side;
	NS[0][0].m_BeansInHole = toCpy.NS[0][0].m_BeansInHole;
	NS[0][0].m_HoleIndex = toCpy.NS[0][0].m_HoleIndex;
	NS[1][0].m_Side = toCpy.NS[1][0].m_Side;
	NS[1][0].m_BeansInHole = toCpy.NS[1][0].m_BeansInHole;
	NS[1][0].m_HoleIndex = toCpy.NS[1][0].m_HoleIndex;


	for (int i = 1; i <= toCpy.holes(); i++)
	{
		NS[0][i].m_Side = toCpy.NS[0][i].m_Side;
		NS[0][i].m_BeansInHole = toCpy.NS[0][i].m_BeansInHole;
		NS[0][i].m_HoleIndex = toCpy.NS[0][i].m_HoleIndex;

		NS[1][i].m_Side = toCpy.NS[1][i].m_Side;
		NS[1][i].m_BeansInHole = toCpy.NS[1][i].m_BeansInHole;
		NS[1][i].m_HoleIndex = toCpy.NS[1][i].m_HoleIndex;
	}
}


int Board::beansInPlay(Side s) const
{
	int count = 0;
	for (int i = 1; i <= this->m_Holes; i++)
	{
		count += NS[s][i].m_BeansInHole;
	}
	return count;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	if (s != NORTH && s != SOUTH) { return false; }
	if (hole <= 0 || hole > m_Holes) { return false; }
	if (NS[s][hole].m_BeansInHole == 0) { return false; }


	int left = NS[s][hole].m_BeansInHole;
	NS[s][hole].m_BeansInHole = 0;

	endSide = s;
	Side turnSide = s;
	int i = 0;
	if (turnSide == NORTH) { i = hole - 1; }
	else if (turnSide == SOUTH) { i = hole +1; }
	
	while (left > 0)
	{
		//if in NORTH pot
		if (i == 0 && endSide == NORTH)
		{
			if (turnSide == NORTH)
			{
				NS[0][0].m_BeansInHole++;
				endHole = 0;
				left--;
			}

			i++;
			if (left > 0) { endSide = SOUTH; }
		}

		//if in SOUTH pot
		if (i == m_Holes +1 && endSide == SOUTH)
		{
			if (turnSide == SOUTH)
			{
				NS[1][0].m_BeansInHole++;
				endHole = 0;
				left--;
			}

			if (left > 0) { endSide = NORTH; i--; }

		}
		
		//if not in a pot
		if (left > 0) {
			NS[endSide][i].m_BeansInHole++;
			endHole = i;
			left--;
		}

		//update hole
		if (endSide == NORTH) { i--; }
		else if (endSide == SOUTH) { i++; }
	}
	
	
	return true;
}



bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	//initial arguement checks
	if (hole <= 0 || hole > this->m_Holes) { return false; }
	if (s != NORTH && s != SOUTH) { return false; }
	if (potOwner != NORTH && potOwner != SOUTH) { return false; }

	//pot gains beans and hole, then set that hole to 0
	this->NS[potOwner][0].m_BeansInHole += this->NS[s][hole].m_BeansInHole;
	this->NS[s][hole].m_BeansInHole = 0;

	return true;
}
bool Board::setBeans(Side s, int hole, int beans)
{
	//initial arguement checks
	if (hole < 0 || hole > this->m_Holes) { return false; }
	if (s != NORTH && s != SOUTH) { return false; }

	//set (s,hole) to third parameter
	this->NS[s][hole].m_BeansInHole = beans;
	return true;
}