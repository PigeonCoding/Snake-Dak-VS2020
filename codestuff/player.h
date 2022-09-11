#pragma once

#include<iostream>
#include<vector>
#include <raylib.h>


class Player {
public:
	void PlayerInit(Vector2 startingPos, int cell);
	void addPos(Vector2 pos);
	void MoveTimer(int delay);
	void DrawPlayer();
	void spawnFood();
	void DrawFood(Vector2 pos);

	bool dead = false;
	bool hasEaten = false;
	int foodPosX;
	int foodPosY;
	int size = 1;
	int cellSize = 0;
	int frameTimer = 0;
	bool canMove = true;
	std::vector <Vector2> PlayerLastPos;
	std::vector <Vector2> PlayerLastActivePos;
	Vector2 pos;
};