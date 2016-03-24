#ifndef _MAP_H_
#define _MAP_H_
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "my_func.h"
using namespace std;
class Zon
{
public:
	int svoy;//свойства
	string znak;
	Zon(const Zon& z)
	{
		svoy=z.svoy;
		znak=z.znak;
	}
	Zon()
	{
		svoy=0;
		znak="proh";
	}
};
class Map
{
private:
	string name;
	vector<vector<Zon>> zon;
	Coord size;
public:
	Map()
	{
	}
	~Map()
	{
		zon.clear();
	}
	Map(string _name,Coord _size)
	{
		name=_name;
		size=_size;
		Zon z1;
		Zon z2;
		z2.svoy=2;
		z2.znak="sten";
		for(int i=0;i<size.y;i++)
		{
			vector<Zon> z;
			for(int j=0;j<size.x;j++)
			{
				if(i!=0&&j!=0&&i!=size.y-1&&j!=size.x-1)
					z.push_back(z1);
				else
				{
					z.push_back(z2);
				}

			}
			zon.push_back(z);
		}
	}
	bool vid(Coord m1,Coord m2)
	{
		Vector v(m1,m2);
		if(m1.x==m2.x)
		{
			int _i=1;
			if(m1.y<m2.y)
				int _i=-1;
			for(int i=m1.y;i<m2.y;i=i+_i)
			{
				if(getZon(m1.x,i).svoy==2)
				{
					return 0;
				}
			}
		}
		else
		if(m1.y==m2.y)
		{
			int _i=1;
			if(m1.x<m2.x)
				int _i=-1;
			for(int i=m1.x;i<m2.x;i=i+_i)
			{
				if(getZon(i,m1.y).svoy==2)
				{
					return 0;
				}
			}
		}
		else
		{
			int _i=0,_j=0;
			if(m2.y<=m1.y)
				_i=1;
			else
				_i=-1;
			if(m2.x<=m1.x)
				_j=1;
			else
				_j=-1;
			for(int i=m2.y;i!=m1.y;i=i+_i)
			{
				for(int j=m2.x;j!=m1.x;j=j+_j)
				{
					if(mod((j-m1.x)/(m1.x-m2.x))==mod((i-m1.y)/(m1.y-m2.y))&&getZon(j,i).svoy==2)
					{
						return 0;
					}
				}
			}
		}
		return 1;
	}
	Map(const Map& m)
	{
		name=m.name;
		size.x=m.size.x;
		size.y=m.size.y;
		for(int i=0;i<size.y;i++)
		{
			vector<Zon> z2;
			for(int j=0;j<size.x;j++)
			{
				z2.push_back(m.zon[i][j]);
			}
			zon.push_back(z2);
		}
	}
	friend ofstream& operator<<(ofstream& o,Map& m)
	{
		o<<m.name<<endl;
		o<<m.size.x<<' '<<m.size.y<<endl;
		for(int i=0;i<m.size.y;i++)
		{
			for(int j=0;j<m.size.x;j++)
			{
				o<<m.getZon(j,i).svoy<<' '<<m.getZon(j,i).znak<<' ';
			}
			o<<endl;
		}
		return o;
	}
	friend ifstream& operator>>(ifstream& i,Map& m)
	{
		int size_dv=0;
		i>>m.name;
		i>>m.size.x;
		i>>m.size.y;
		for(int g=0;g<m.size.y;g++)
		{
			vector<Zon> _z;
			for(int j=0;j<m.size.x;j++)
			{
				Zon z;
				i>>z.svoy;
				i>>z.znak;
				_z.push_back(z);
			}
			m.zon.push_back(_z);
			i.get();
		}
		return i;
	}
	Zon getZon(int x,int y)
	{
		return zon[y][x];
	}
	Coord getSize()
	{
		return size;
	}
};
#endif