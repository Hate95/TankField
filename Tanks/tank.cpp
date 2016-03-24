#include "tank.h"
	Tank::Tank()
	{
		HP=100;
		pos.x=4;
		pos.y=6;
		Coord d;
		d.x=0;
		d.y=-1;
		direction.setCoord(d);
		direction_push.setCoord(d);
		rotateSped=5;
		atack=1;
		sped=0;
		a=0;
		znak="tanks";
	}
	Tank::Tank(Coord _pos,int _atack,int _sped,int _a)
	{
		HP=100;
		pos.x=_pos.x;
		pos.y=_pos.y;
		_pos.x=0;
		_pos.y=-1;
		direction.setCoord(_pos);
		direction_push.setCoord(_pos);
		atack=_atack;
		sped=_sped;
		a=_a;
		znak="tanks";
	}
	string Tank::getZnak()
	{
		return znak;
	}
	void Tank::Atack(vector<Bullet>& bul)
	{
		Coord c=pos;
		c.x=pos.x+0.5;
		c.y=pos.y+0.5;
		Bullet b(c,direction_push,atack,0.1);
		bul.push_back(b);
	}
	void Tank::rotate(Direction d)
	{
		if(d==LEFT)
		{
			direction.rotate(-1*rotateSped);
		}
		if(d==RIGHT)
		{
			direction.rotate(1*rotateSped);
		}
	}
	void Tank::rotatePush(Direction d)
	{
		if(d==LEFT)
		{
			direction_push.rotate(-1);
		}
		if(d==RIGHT)
		{
			direction_push.rotate(1);
		}
	}
	void Tank::moveUp(Map& m,vector<Enemy>& enemy,Hero& hero)
	{
		int e=1;
		//столкновение с героем TD
		if(int(pos.x+(direction.getCoord().x*sped/40))==int(hero.getPos().x)	 && int(pos.y+(direction.getCoord().y*sped/40))==int(hero.getPos().y) &&
		   int(pos.x+(direction.getCoord().x*sped/40) + 1)==int(hero.getPos().x) && int(pos.y+(direction.getCoord().y*sped/40) + 1)==int(hero.getPos().y) &&
		   int(pos.x+(direction.getCoord().x*sped/40) + 1)==int(hero.getPos().x) && int(pos.y+(direction.getCoord().y*sped/40))==int(hero.getPos().y) &&
		   int(pos.x+(direction.getCoord().x*sped/40))==int(hero.getPos().x)	 && int(pos.y+(direction.getCoord().y*sped/40) + 1)==int(hero.getPos().y))
		{
			//проверка не тот же ли танк
			if(int(pos.x+(direction.getCoord().x*sped/40))==int(pos.x)&&int(pos.y+(direction.getCoord().y*sped/40))==int(pos.y))
			{
			}
			else
			{
				e=0;
			}
		}
		if(e)
		{
			for(int i=0;i<enemy.size();i++)
			{
				//столкновение с врагом
				if((int(pos.x+(direction.getCoord().x)*sped/40)==int(enemy[i].getPos().x)	    && int(pos.y+(direction.getCoord().y)*sped/40)==int(enemy[i].getPos().y)) &&
				   (int(pos.x+((direction.getCoord().x)*sped/40) + 1)==int(enemy[i].getPos().x) && int(pos.y+((direction.getCoord().y)*sped/40) + 1)==int(enemy[i].getPos().y)) &&
				   (int(pos.x+((direction.getCoord().x)*sped/40)+1)==int(enemy[i].getPos().x)   && int(pos.y+(direction.getCoord().y)*sped/40)==int(enemy[i].getPos().y))		&&
				   (int(pos.x+(direction.getCoord().x)*sped/40)==int(enemy[i].getPos().x)	    && int(pos.y+((direction.getCoord().y)*sped/40)+1)==int(enemy[i].getPos().y)))
				{
					//проверка не тот же ли танк
					if(int(pos.y+(direction.getCoord().y)*sped/40)==int(pos.y)&&int(pos.x+(direction.getCoord().x)*sped/40)==int(pos.x))
					{
					}
					else
					{
						e=0;
					}
				}
			}
		}
			if(e)
			{
				//столкновение со стеной
				if(int(pos.x+(direction.getCoord().x)*sped/40) < m.getSize().x &&
				   int(pos.y+(direction.getCoord().y)*sped/40) < m.getSize().y &&
				   int(pos.x+(direction.getCoord().x)*sped/40) > 0 &&
				   int(pos.y+(direction.getCoord().y)*sped/40) > 0 &&
				   
				   m.getZon(pos.x+(direction.getCoord().x)*sped/40, pos.y+(direction.getCoord().y)*sped/40).svoy<1 &&
				   m.getZon((pos.x+(direction.getCoord().x)*sped/40)+1, (pos.y+(direction.getCoord().y)*sped/40)+1).svoy<1 &&
				   m.getZon((pos.x+(direction.getCoord().x)*sped/40)+1, (pos.y+(direction.getCoord().y)*sped/40)).svoy<1 &&
				   m.getZon((pos.x+(direction.getCoord().x)*sped/40),   (pos.y+(direction.getCoord().y)*sped/40)+1).svoy<1)
				{
					pos.x=pos.x+(direction.getCoord().x*sped/40);
					pos.y=pos.y+(direction.getCoord().y*sped/40);
				}
				else
				{
					sped = 0;
				}
				
			}
	}
	void Tank::A(int start)
	{
		if(start==1)
		{
			if(sped<4)
				a=0.1;
			else
				a=0;
		}
		if(start==-1)
		{
			if(sped>-4)
				a=-0.1;
			else
				a=0;
		}
		if(start==0)
		{
			if(sped>0)
				a=-0.1;
			else
				if(sped<0)
					a=0.1;
				else
					if(sped=0)
						a=0;
		}
			sped=sped+a;
	}
	Coord Tank::getPos()
	{
		return pos;
	}
	Vector Tank::getDiretion()
	{
		return direction;
	}
	Vector Tank::getDiretionPush()
	{
		return direction_push;
	}
	bool Tank::povr(int Atack)//повреждение
	{
		if((HP=HP-Atack)<=0)
		{
			return 0;
		}
		return 1;
	}
	void Tank::move()
	{
	}
	void Hero::move(Direction OY,Direction OX,Direction mous,Map& map,vector<Enemy>& enemy,Hero& hero,vector<Bullet> &bul)
	{
		rotatePush(mous);
		if(mous==XA)
		{
			Atack(bul);
		}
		switch(OY)
		{
		case(UP):
			{
				A(1);
				break;
			}
		case(DOWN):
			{
				A(-1);
				break;
			}
		case(NUL):
			{
				A(0);
				break;
			}
		}
		rotate(OX);
		moveUp(map,enemy,hero);
	}
	Enemy::Enemy(Coord _pos,int _atack)
	{
		znak="tanks";
		rotateSped=1;
		zonVid=5;
		zonAtack=2;
		HP=100;
		pos.x=_pos.x;
		pos.y=_pos.y;
		_pos.x=0;
		_pos.y=-1;
		direction.setCoord(_pos);
		direction_push.setCoord(_pos);
		atack=_atack;
		sped=0;
		a=0;

	}
	void Enemy::randMove(Map& map,vector<Enemy>& enemy,Hero& hero)
	{
		int i=rand()%3;
		switch(i)
		{
		case(0):
			{
				A(1);
				//moveUp(map,enemy,hero);
				break;
			}
		case(1):
			{
				//moveUp(map,enemy,hero);
				A(-1);
				break;
			}
		case(2):
			{
				A(0);
				rotate(LEFT);
				break;
			}
		case(3):
			{
				A(0);
				rotate(RIGHT);
				break;
			}
		}
	}
	int Enemy::vid(Map& map,vector<Enemy>& enemy,Hero& hero)//0-невидет,1-видет но есть преграда,2-видет хорошо 
	{
		int iex=2;
		Vector v(hero.getPos(),getPos());
		if(v.dlina()<=zonVid)//растояние
		{
			if((getDiretion()^v)<0)//поле зрения 180
			{

				if(int(getPos().x)==int(hero.getPos().x))
				{
					int _i=1;
					if(getPos().y>hero.getPos().y)
					{
						_i=-1;
					}
					for(int i=getPos().y;i!=int(hero.getPos().y);i=i+_i)
					{
						if(map.getZon(int(getPos().x),i).svoy==2)
						{
							return 0;
						}
						else
						if(map.getZon(int(getPos().x),i).svoy==1)
						{
							iex=1;
						}
					}
				}
				else
				if(int(getPos().y)==int(hero.getPos().y))
				{
					int _i=1;
					if(getPos().x>hero.getPos().x)
					{
						_i=-1;
					}
					for(int i=getPos().x;i!=int(hero.getPos().x);i=i+_i)
					{
						if(map.getZon(i,int(getPos().y)).svoy==2)
						{
							return 0;
						}
						else
						if(map.getZon(i,int(getPos().y)).svoy==1)
						{
							iex=1;
						}
					}
				}
				else
				{
					int _i=0,_j=0;
					if(hero.getPos().y<=getPos().y)
						_i=1;
					else
						_i=-1;
					if(hero.getPos().x<=getPos().x)
						_j=1;
					else
						_j=-1;
					for(int i=hero.getPos().y;i!=int(getPos().y);i=i+_i)
					{
						for(int j=hero.getPos().x;j!=int(getPos().x);j=j+_j)
						{
							if(mod((j-getPos().x)/(getPos().x-hero.getPos().x))==mod((getPos().y)/(getPos().y-hero.getPos().y))&&map.getZon(j,i).svoy<2)
							{
								return 0;
							}
							else
								if(mod((j-getPos().x)/(getPos().x-hero.getPos().x))==mod((getPos().y)/(getPos().y-hero.getPos().y))&&map.getZon(j,i).svoy<2)
								{
									iex=1;
								}
						}
					}
				}
				if(memory.size()>0)
				{
					memory[0]=hero.getPos();
				}
				else
					memory.push_back(hero.getPos());
				return iex;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	void Enemy::move(Map& map,vector<Enemy>& enemy,Hero& hero,vector<Bullet>& bul)
	{
		switch(vid(map,enemy,hero))
		{
		case(0):
			{
				/*if(memory.size()>0)
				{
					Vector v(getPos(),memory[0]);
					double f=v.dlina();
					int vang=v.angl();
					int ang=getDiretion().angl();
					//vang-ang;
	
					v=v/f;
					if(vang-ang==0)
					{
						if(int(f)==0)
						{
							memory.erase(memory.begin());
						}
						else
							A(1);
					}
					else
					{
						A(0);
						if(vang-ang>0)
							rotate(LEFT);
						else
							rotate(RIGHT);
					}
				}
				else*/
					randMove(map,enemy,hero);
				break;
			}
		case(1):
			{
				randMove(map,enemy,hero);
				//Robot(map);

				break;
			}
		case(2):
			{
				Vector v(getPos(),hero.getPos());
				double f=v.dlina();
				int vang=v.angl();
				int ang=getDiretion().angl();

				v=v/f;
 				if(vang-ang==0)
				{
					//A(1);
					if((f)<=zonAtack)
					{
						A(0);
						Atack(bul);
					}
					else
						A(1);
				}
				else
				{
					A(0);
					if(vang-ang>0)
						rotate(LEFT);
					else
						rotate(RIGHT);
				}
				break;
			}
		}
		moveUp(map,enemy,hero);
		direction_push=direction;
	}
	void Enemy::Robot(Map& map)
	{
		Coord c1;
		Coord myPos;
		myPos.x=zonVid;
		myPos.y=zonVid;
		c1.x=pos.x-zonVid;
		c1.y=pos.y-zonVid;
		if(c1.x<0)
		{
			c1.x=0;
			myPos.x=pos.x;
		}
		
		if(c1.y<0)
		{
			c1.y=0;
			myPos.y=pos.y;
		}
		Coord c2;
		c2.x=pos.x+zonVid;
		c2.y=pos.y+zonVid;
		Coord sizeZon(c2.x-c1.x,c2.y-c1.y);
		int* zon;
		zon=new int[sizeZon.x*sizeZon.y];
		for(int i=0;i<int(sizeZon.y);i++)
		{
			for(int j=0;j<int(sizeZon.x);j++)
			{
				if(map.getZon(c1.x+j,c1.y+i).svoy>0||i<1||j<1||i>int(sizeZon.y-1)||j>int(sizeZon.x-1))
				{
					zon[int(i*sizeZon.x+j)]=-1;
				}
				else
				{
					zon[int(i*sizeZon.x+j)]=999;
				}
			}
		}
		zon[int(myPos.y*sizeZon.x+myPos.x)]=0;
		Robot2(zon,myPos,sizeZon);
	}
	void Enemy::Robot2(int* zon,Coord myPos,Coord size)
	{
		if(zon[int((myPos.y-1)*size.x+(myPos.x))]!=-1&&zon[int((myPos.y-1)*size.x+(myPos.x))]>zon[int((myPos.y)*size.x+(myPos.x))]+1)
		{
			zon[int((myPos.y-1)*size.x+(myPos.x))]=zon[int((myPos.y)*size.x+(myPos.x))]+1;
			Coord c(myPos.x,myPos.y-1);
			Robot2(zon,c,size);
		}
		if(zon[int((myPos.y+1)*size.x+(myPos.x))]!=-1&&zon[int((myPos.y+1)*size.x+(myPos.x))]>zon[int((myPos.y)*size.x+(myPos.x))]+1)
		{
			zon[int((myPos.y+1)*size.x+(myPos.x))]=zon[int((myPos.y)*size.x+(myPos.x))]+1;
			Coord c(myPos.x,myPos.y+1);
			Robot2(zon,c,size);
		}
		if(zon[int((myPos.y)*size.x+(myPos.x-1))]!=-1&&zon[int((myPos.y)*size.x+(myPos.x-1))]>zon[int((myPos.y)*size.x+(myPos.x))]+1)
		{
			zon[int((myPos.y)*size.x+(myPos.x-1))]=zon[int((myPos.y)*size.x+(myPos.x))]+1;
			Coord c(myPos.x-1,myPos.y);
			Robot2(zon,c,size);
		}
		if(zon[int((myPos.y)*size.x+(myPos.x+1))]!=-1&&zon[int((myPos.y)*size.x+(myPos.x+1))]>zon[int((myPos.y)*size.x+(myPos.x))]+1)
		{
			zon[int((myPos.y)*size.x+(myPos.x+1))]=zon[int((myPos.y)*size.x+(myPos.x))]+1;
			Coord c(myPos.x+1,myPos.y);
			Robot2(zon,c,size);
		}
	}
