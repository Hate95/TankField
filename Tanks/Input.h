#ifndef _INPUT_H_
#define _INPUT_H_
#pragma comment(lib,"SDL.lib")
#include <SDL.h>
#include <Windows.h>

class Input
{
private:
    SDL_Event evt;
	
public:
	void Update()
	{
		while(SDL_PollEvent(&evt));
	}
	bool IsMouseButtonDown(byte key)
	{
		if(evt.type == SDL_MOUSEBUTTONDOWN)
			if(evt.button.button == key)
				return true;
		return false;
	}
	bool IsMouseButtonUp(byte key)
	{
		if(evt.type == SDL_MOUSEBUTTONUP)
			if(evt.button.button == key)
				return true;
		return false;
	}
    POINT GetButtonDownCoords()
	{
		POINT point;
		point.x = evt.button.x;
		point.y = evt.button.y;

	    return point;
	}
	//byte-SDL_Keycode//1073741906 up,1073741905 down,1073741904 left,1073741903right
	bool IsKeyDown(SDL_Keycode key)
	{
		return (evt.type == SDL_KEYDOWN &&evt.key.keysym.sym == key);
	}
	bool IsKeyUp(byte key)
	{
		return (evt.type == SDL_KEYUP && evt.key.keysym.sym == key);
	}
	byte GetPressedKey()
	{
		return evt.key.keysym.sym;
	}
	bool Input::IsExit()
	{
		return (evt.type == SDL_QUIT);
	}
};
#endif