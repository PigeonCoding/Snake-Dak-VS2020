#include <raylib.h>
#include <iostream>
#include "player.h"

using namespace std;

typedef enum GameScreen { LOGO = 0, TITLE, DEAD, GAMEPLAY } GameScreen;
GameScreen currentScreen;

int framesCounter = 0;

Player snake;

const int SCREENWIDTH = 600;
const int SCREENHEIGHT = 600;

const int cellSize = 20;

int dir = 0;

int foodPos;

void init() {
    currentScreen = LOGO;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Snake Dak");
    SetTargetFPS(60);
    
    snake.PlayerInit({ 10, 10 }, cellSize);
    snake.size = 2;   
}

void close() {
    CloseWindow();
}

void draw() {
    ClearBackground(BLACK);

    switch (currentScreen)
    {
        case LOGO:
            DrawText("made by pigeon", SCREENWIDTH / 2 - 30, SCREENHEIGHT / 2, 30, WHITE);
            framesCounter++;
            break;
        case TITLE:
            DrawText("press Space to start the game", SCREENWIDTH / 2 - 30, SCREENHEIGHT / 2, 30, WHITE);
            ClearBackground(BLACK);
            if (IsKeyDown(KEY_SPACE)) { currentScreen = GAMEPLAY; }
            break;
        case GAMEPLAY:
            snake.DrawPlayer();

            if (!snake.hasEaten) {
                snake.spawnFood();
            }

            DrawRectangle(snake.foodPosX, snake.foodPosY, cellSize, cellSize, GREEN);
    }
    
}

void InputManager() {
    if (IsKeyPressed(KEY_S)){
        dir = -1;
    }
    if (IsKeyPressed(KEY_W)){
        dir = 1;

    }
    if (IsKeyPressed(KEY_D)){
        dir = -2;

    }
    if (IsKeyPressed(KEY_A)){
        dir = 2;
    }
}

void mouvement() {
    Vector2 direction = {0, 0};

    if (snake.canMove) {
        if (dir == 1) {
            direction.y -= cellSize;
        }
        if (dir == -1) {
            direction.y += cellSize;
        }
        if (dir == -2) {
            direction.x += cellSize;
        }
        if (dir == 2) {
            direction.x -= cellSize;
        }

        snake.addPos(direction);
    }

    if (snake.pos.x == snake.foodPosX && snake.pos.y == snake.foodPosY) {
        snake.size++;
        snake.foodPosX = -100;
        snake.foodPosY = -100;
        snake.hasEaten = false;
    }

    if (snake.pos.x > 0 && snake.pos.x < SCREENWIDTH - cellSize && snake.pos.y > 0 && snake.pos.y < SCREENHEIGHT){}
    else {
        dir = 0;
        snake.dead = true;
    }

    snake.MoveTimer(10);
}

void run()
{
    while (!WindowShouldClose() && !snake.dead)
    {
        if (framesCounter == 50) { currentScreen = TITLE; framesCounter++;}

        InputManager();
        mouvement();

        BeginDrawing();
        
        draw();
        
        EndDrawing();
    }
}

