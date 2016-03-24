#include "bullet.h"
	Bullet::Bullet(Coord _pos,Vector _direction,int _atack,double _sped)
	{
		time=30;
		sped=0.1;
		pos.x=_pos.x;+_direction.getCoord().x*sped;
		pos.y=_pos.y;+_direction.getCoord().y*sped;
		direction=_direction;
		atack=_atack;
		//sped=_sped;
	}
	Coord Bullet::getPos()
	{
		return pos;
	}

	bool Bullet::move(Map& m,Hero &hero,vector<Enemy> &enemy)
	{
		if(time<0)
		{
			return 0;
		}
		time--;
		//столкновение с героем
		if(int(hero.getPos().x)==int(pos.x+direction.getCoord().x*sped)&&int(hero.getPos().y)==int(pos.y+direction.getCoord().y*sped))
		{
			hero.povr(atack);//ataka hero
			return 0;
		}
		//столкновение с врагом
		for(int j=0;j<enemy.size();j++)
		{
			if(int(enemy[j].getPos().x)==int(pos.x+direction.getCoord().x*sped)&&int(enemy[j].getPos().y)==int(pos.y+direction.getCoord().y*sped))
			{
				if(enemy[j].povr(atack)<=0)//ataka enemy
				{
					enemy.erase(enemy.begin()+j);
				}
				return 0;
			}
		}
		//столкновение со стеной
		if(m.getZon(pos.x+direction.getCoord().x*sped,pos.y+direction.getCoord().y*sped).svoy<1)
		{
			pos.x=pos.x+direction.getCoord().x*sped;
			pos.y=pos.y+direction.getCoord().y*sped;
			return 1;
		}
		return 0;
	}