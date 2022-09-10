#include "player.h"
#include <stdlib.h>

void Player::PlayerInit(Vector2 startingPos, int cell) {
	Player::pos = startingPos;
	Player::PlayerLastPos.push_back(startingPos);
	Player::cellSize = cell;

}

void Player::addPos(Vector2 poss) {
	
	Player::PlayerLastPos.push_back(Player::pos);
	Player::pos.x += poss.x;
	Player::pos.y += poss.y;
}

void Player::MoveTimer(int delay) {
	if (Player::frameTimer > delay)
	{
		//std::cout << "delay off\n";
		Player::frameTimer = 0;
		Player::canMove = true;
	}
	else {
		Player::frameTimer++;
		Player::canMove = false;
	}
}

void Player::DrawPlayer() {
	//std::cout << Player::PlayerLastPos.size() << std::endl;
	PlayerLastActivePos.clear();
	for (int v = 1; v < Player::size; v++) {
		if (v <= Player::PlayerLastPos.size()) {
			PlayerLastActivePos.push_back(PlayerLastPos[Player::PlayerLastPos.size() - v]);
			DrawRectangle(Player::PlayerLastPos[Player::PlayerLastPos.size() - v].x, Player::PlayerLastPos[Player::PlayerLastPos.size() - v].y, cellSize, cellSize, WHITE);
		}
	}

	for (int f = 1; f < PlayerLastActivePos.size(); f++) {
		if (pos.x == PlayerLastActivePos[f].x && pos.y == PlayerLastActivePos[f].y) {
			Player::dead = true;
		}
	}
}


void Player::spawnFood() {
	int gudX = 0;
	int gudY = 0;

	bool isGood = false;

	gudX = (GetRandomValue(cellSize, GetScreenWidth() / cellSize)) * 10;
	gudY = (GetRandomValue(cellSize, GetScreenHeight() / cellSize)) * 10;


	if (gudX % cellSize == 0 && gudY % cellSize == 0) {

		for (int f = 0; f < PlayerLastActivePos.size(); f++) {
			if (gudX + cellSize / 2 != PlayerLastActivePos[f].x && gudY + cellSize / 2 != PlayerLastActivePos[f].y) {
				isGood = true;
			}
			else 
			{
				isGood = false;
			}
		}
	}
	else if (gudX % cellSize != 0 && gudY % cellSize != 0) {
		gudX = (GetRandomValue(cellSize, GetScreenWidth() / cellSize)) * 10;
		gudY = (GetRandomValue(cellSize, GetScreenHeight() / cellSize)) * 10;
	}

	if (isGood)
	{
		foodPosX = gudX + cellSize / 2;
		foodPosY = gudY + cellSize / 2;

		hasEaten = true;
	}
}


