#ifndef _BULLET_H_
#define _BULLET_H_
#include "my_func.h"
#include "tank.h"
#include "map.h"
class Hero;
class Enemy;
class Bullet
{
private:
	int time;
	Coord pos;
	Vector direction;
	int atack;
	double sped;
public:
	Bullet(Coord _pos,Vector _direction,int _atack,double _sped);
	Coord getPos();
	bool move(Map& m,Hero &hero,vector<Enemy> &enemy);
};
#endif