
#ifndef SIDE_INCLUDED
#define SIDE_INCLUDED

enum Side { NORTH, SOUTH };

inline
Side opponent(Side s)
{
	return Side(1 - s);
}


#endif // SIDE_INCLUDED