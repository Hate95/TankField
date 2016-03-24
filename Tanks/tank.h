#ifndef _TANK_H_
#define _TANK_H_
#include "my_func.h"
#include "bullet.h"
#include "map.h"
#include <vector>
using namespace std;
class Bullet;
class Enemy;
class Hero;
class Tank
{
protected:
	string znak;
	int HP;
	Coord pos;
	Vector direction;
	Vector direction_push;
	int rotateSped;
	int atack;
	double sped;
	double a;
public:
	Tank();
	Tank(Coord _pos,int _atack,int _sped,int _a);
	string getZnak();
	void Atack(vector<Bullet>& bul);
	void rotate(Direction d);
	void rotatePush(Direction d);
	void moveUp(Map& m,vector<Enemy>& enemy,Hero& hero);
	void A(int start);
	Coord getPos();
	Vector getDiretion();
	Vector getDiretionPush();
	bool povr(int Atack);//повреждение
	virtual void move();
};
class Hero:public Tank
{
public:
	void move(Direction OY,Direction OX,Direction mous,Map& map,vector<Enemy>& enemy,Hero& hero,vector<Bullet> &bul);
};
class Enemy:public Tank
{
private:
	vector<Coord> memory;
	int zonVid;//область видемости
	int zonAtack;
public:
	void Robot(Map& map);
	Enemy(Coord _pos,int _atack);
	void randMove(Map& map,vector<Enemy>& enemy,Hero& hero);
	int vid(Map& map,vector<Enemy>& enemy,Hero& hero);//0-невидет,1-видет но есть преграда,2-видет хорошо 
	void move(Map& map,vector<Enemy>& enemy,Hero& hero,vector<Bullet>& bul);
	void Robot2(int* zon,Coord myPos,Coord size);
};
#endif