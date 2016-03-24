#include "my_func.h"
	Coord::Coord()
	{
		x=0;
		y=0;
	}
	Coord::Coord(double _x,double _y)
	{
		x=_x;
		y=_y;
	}
	int mod(int m)
	{
		if(m<0)
			return -m;
		return m;
	}