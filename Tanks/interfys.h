#ifndef _INTERFYS_H_
#define _INTERFYS_H_
#include "world.h"
#include "map.h"
#include "Input.h"
#include"CEntity.h"
#include "CSurface.h"
#include <iostream>
#include <fstream>
#pragma comment(lib,"SDL.lib")
#include <SDL.h>
#include <Windows.h>
#include <map>
#include <string>
using namespace std;

class Game;
const int size_zon=40;
class Interfys
{
	Input *i;
	World w;
	std::map<string,SDL_Surface*> image;
	SDL_Window *win;
	SDL_Renderer *ren;
public:
	Interfys()
	{
		SDL_Init(SDL_INIT_VIDEO);
		win = SDL_CreateWindow("MY TANKS", 100, 100,640, 480, SDL_WINDOW_SHOWN);
		ren=SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		//image["disply"]==SDL_GetWindowSurface(win);
		//CSurface::Transparent(image["disply"],255,0,255);
		image["tanks"]=SDL_LoadBMP("tanks.bmp");
		CSurface::Transparent(image["tanks"],255,0,255);
		image["proh"]=SDL_LoadBMP("proh.bmp");
		CSurface::Transparent(image["proh"],255,0,255);
		image["sten"]=SDL_LoadBMP("sten.bmp");
		CSurface::Transparent(image["sten"],255,0,255);
		image["bullet"]=SDL_LoadBMP("bullet.bmp");
		CSurface::Transparent(image["bullet"],255,0,255);
		//image["fon"]=SDL_GetWindowSurface(win);
		image["fon"]=SDL_LoadBMP("t.bmp");
		CSurface::Transparent(image["fon"],0,0,0);
		image["push"]=SDL_LoadBMP("push.bmp");
		CSurface::Transparent(image["push"],255,0,255);

		ifstream f("card.txt");
		f>>w;
		f.close();
		
		//win = SDL_CreateWindow("Hello World",640, 480, SDL_WINDOW_SHOWN);
		i=new Input();
		SDL_Rect Area;
		for(int i=0;i<w.getMap().getSize().y;i++)
		{
			Area.y=i*size_zon;
			for(int j=0;j<w.getMap().getSize().x;j++)
			{
				Area.x=j*size_zon;
				
					SDL_BlitSurface(image[w.getMap().getZon(j,i).znak], NULL, image["fon"], &Area);
			}
		}
	}
	void start()
	{
		i->Update();
		int x=0,y=0;
		while(!i->IsExit())
		{
			printMap();
			Direction OX=NUL;
			Direction OY=NUL;
			Direction mous=NUL;
			printMap();

			i->Update();
			int _x=i->GetButtonDownCoords().x;
			if(_x<640 && _x!=x)
			{
				if(x<_x)
				{
					mous=RIGHT;
					}
				if(x>_x)
				{
					mous=LEFT;
				}
				x=_x;
			}
				i->Update();
			if(i->IsMouseButtonDown(1))
			{
				mous=XA;
			}
			//1073741906 up,1073741905 down,1073741904 left,1073741903 right
				
			if(i->IsKeyDown(1073741906))
				OY=UP;
			if(i->IsKeyDown(1073741905))
				OY=DOWN;
			i->Update();
			if(i->IsKeyDown(1073741904))
				OX=LEFT;
			if(i->IsKeyDown(1073741903))
				OX=RIGHT;
			w.Start(OY,OX,mous);
		}
	}

	void printMap()
	{
		SDL_Texture *tex=NULL;
		SDL_Rect Area;
		SDL_Rect SrcArea;
		SDL_Surface* display=SDL_GetWindowSurface(win);
		Area.x=0;
		Area.y=0;
		SrcArea.x = 0;//w.getHero().getPos().x*40-320;
		SrcArea.y = 0;//w.getHero().getPos().y*40-240;
		SrcArea.w = 640;
		SrcArea.h = 480;
		SDL_BlitSurface(image["fon"],&SrcArea, display, &Area);
		int angl=w.getHero().getDiretion().angl();
			SrcArea.x = (360-angl)*40;
			SrcArea.y = 0;
			SrcArea.w = size_zon;
			SrcArea.h = size_zon;
		Area.x=w.getHero().getPos().x*size_zon;
		Area.y=w.getHero().getPos().y*size_zon;
		SDL_BlitSurface(image[w.getHero().getZnak()], &SrcArea, display, &Area);
		angl=w.getHero().getDiretionPush().angl();
		if(angl>=0&&angl<=180)
		{
			SrcArea.x = (180-angl-1)*25;
			SrcArea.y = 20;
			SrcArea.w = 30;
			SrcArea.h = 20;
		}
		else
		{
			SrcArea.x = ((360-angl))*25;
			SrcArea.y = 0;
			SrcArea.w = 30;
			SrcArea.h = 20;
		}
		Area.x=Area.x+10;
		Area.y=Area.y+10;
		SDL_BlitSurface(image["push"], &SrcArea, display, &Area);


	for(int g=0;g<w.getEnemy().size();g++)
	{		
		angl=w.getEnemy()[g].getDiretion().angl();
		SrcArea.x = (360-angl)*40;
			SrcArea.y = 0;
			SrcArea.w = size_zon;
			SrcArea.h = size_zon;
		Area.x=w.getEnemy()[g].getPos().x*size_zon;
		Area.y=w.getEnemy()[g].getPos().y*size_zon;
		SDL_BlitSurface(image[w.getEnemy()[g].getZnak()], &SrcArea, display, &Area);
		angl=w.getEnemy()[g].getDiretionPush().angl();
		if(angl>=0&&angl<=180)
		{
			SrcArea.x = (180-angl-1)*25;
			SrcArea.y = 20;
			SrcArea.w = 30;
			SrcArea.h = 20;
		}
		else
		{
			SrcArea.x = ((360-angl))*25;
			SrcArea.y = 0;
			SrcArea.w = 30;
			SrcArea.h = 20;
		}
		Area.x=Area.x+10;
		Area.y=Area.y+10;
		SDL_BlitSurface(image["push"], &SrcArea, display, &Area);
	}
	for(int g=0;g<w.getBullet().size();g++)	{
		Area.x=w.getBullet()[g].getPos().x*size_zon;
		Area.y=w.getBullet()[g].getPos().y*size_zon;
		SDL_BlitSurface(image["bullet"], NULL, display, &Area);
	}
		tex=SDL_CreateTextureFromSurface(ren, display);
		SDL_RenderCopy(ren, tex, NULL, NULL);
		SDL_RenderPresent(ren);
		SDL_DestroyTexture(tex);
		SDL_RenderClear(ren);
		SDL_FreeSurface(display);
	}
};

#endif