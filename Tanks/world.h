#ifndef _WORLD_H_
#define _WORLD_H_
#include "map.h"
#include "tank.h"
#include "bullet.h"
class World
{
private:
	Map map;
	vector<Enemy> enemy;
	vector<Bullet> bullet;
public:
	Hero hero;
	Map getMap()
	{
		return map;
	}
	Tank getHero()
	{
		return hero;
	}
	vector<Bullet> getBullet()
	{
		return bullet;
	}
	vector<Enemy> getEnemy()
	{
		return enemy ;
	}
	friend ifstream& operator>>(ifstream &i,World& w)
	{
		i>>w.map;
		return i;
	}
	World()
	{
		Coord c;
		c.x=6;
		c.y=6;
		Enemy e(c,1);
		enemy.push_back(e);
		c.x=6;
		c.y=4;
		Enemy e1(c,1);
		enemy.push_back(e1);
		c.x=3;
		c.y=6;
		Enemy e2(c,1);
		enemy.push_back(e2);
		c.x=9;
		c.y=6;
		Enemy e3(c,1);
		enemy.push_back(e3);
	
	}
	void addEnemy(Coord c)
	{
		Enemy e(c,1);
		enemy.push_back(e);
	}
	void killEnemy()
	{
		enemy.clear();
	}
	void killBullet()
	{
		bullet.clear();
	}

	void Start(Direction OY,Direction OX,Direction mous)
	{
		hero.move(OY,OX,mous,map,enemy,hero,bullet);
//		hero.rotatePush(x,y);
		for(int i=0;i<enemy.size();i++)
		{
			enemy[i].move(map,enemy,hero,bullet);
		}
		for(int i=0;i<bullet.size();i++)
		{
			if(!bullet[i].move(map,hero,enemy))
			{
				bullet.erase(bullet.begin()+i);
			}
		}

	}
};
#endif