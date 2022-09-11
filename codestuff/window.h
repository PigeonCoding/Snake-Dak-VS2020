#pragma once

#include <raylib.h>
#include <iostream>



class Window 
{
public:
	

	int framesCounter = 0;

	void GameInit(int width, int height, const char* title);
	void CloseGame();
	void resetGame();
	void RunGame();
};
