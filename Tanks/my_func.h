
#ifndef _MY_FUNC_
#define _MY_FUNC_
#include <math.h>
class Coord
{
public:
	double x;
	double y;
	Coord();
	Coord(double _x,double _y);
};

enum Direction
{
  NUL,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  XA
};
int mod(int m);
class Vector
{
	Coord coord;
public:
	Vector()
	{
		coord.x=0;
		coord.y=0;
	}
	void operator=(Vector v)
	{
		coord.x=v.getCoord().x;
		coord.y=v.getCoord().y;
		
	}
	Vector(Coord p1,Coord p2)
	{
		coord.x=p2.x-p1.x;
		coord.y=p2.y-p1.y;
	}
	void rotate(double angle)
	{
		angle=angle*acos(double(-1))/180;
        Vector rotated_point;
		rotated_point.coord.x = coord.x * cos(angle) - coord.y * sin(angle);
        rotated_point.coord.y = coord.x * sin(angle) + coord.y * cos(angle);
        *this=rotated_point;
	}
	Vector(double _x,double _y)
	{
		coord.x=_x;
		coord.y=_y;
	}
	Coord getCoord()
	{
		return coord;
	}
	void setCoord(Coord _coord)
	{
		coord.x=_coord.x;
		coord.y=_coord.y;
	}
	double dlina()
	{
		return sqrt((coord.x*coord.x)+(coord.y*coord.y));
	}
	Vector operator+(Vector& v)
	{
		Vector res;
		res.coord.x=coord.x+v.coord.x;
		res.coord.y=coord.y+v.coord.y;
		return res;
	}
	Vector operator*(double d)
	{
		Vector res;
		res.coord.x=coord.x*d;
		res.coord.y=coord.y*d;
		return res;
	}
	Vector operator/(double d)
	{
		Vector res;
		res.coord.x=coord.x/d;
		res.coord.y=coord.y/d;
		return res;
	}
	bool operator==(Vector& v)
	{
		if(v.coord.x==coord.x&&v.coord.y==coord.y)
			return 1;
		else
			return 0;
	}
	double operator,(Vector& v)
	{
		return coord.x*v.coord.x+coord.y*v.coord.y;
	}
	double operator^(Vector& v)
	{

		return (*this,v)/(dlina()*v.dlina());
	}
	double angl()
	{

		Vector v(0,-1);
		if(this->getCoord().x>v.getCoord().x)
			return 360-(acos(*this^v)/acos(double(-1))*180);
		else
			return acos(*this^v)/acos(double(-1))*180;
	}
};
#endif