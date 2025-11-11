#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <utility>
#include <windows.h>
#include <conio.h>
#include <format>
#include "headers/gameControls.h"
#include "headers/maps.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    bool animate = true;
    bool gameOver = false;
    bool clearedScreen = false;
    std::vector<std::vector<int>> map;
    std::string block = u8"██";
    std::string snakeBod = u8"██";
    std::string snakeFood = u8"██";

    /**
     * FOR MORE SYMBOLS GO TO : https://www.alt-codes.net/square-symbols
     */
    chooseMap(map);
    int mapWidth = map[0].size();
    int mapHeight = map.size();
    int minFoods = 10;
    int maxFoods = 20;
    std::vector<std::pair<int, int>> snake;
    std::vector<std::pair<int, int>> snakeSeg = {
        {int(mapWidth / 2), int(mapHeight / 2)},
        {int(mapWidth / 2), int(mapHeight / 2) - 1},
        {int(mapWidth / 2), int(mapHeight / 2) - 2},
    };
    std::pair<int, int> snakeDir = {1, 0};
    std::vector<std::pair<int, int>> foods;
    int score = 0;
    auto lastFrame = std::chrono::high_resolution_clock::now();
    float speed = 0.5f;
    float speedInc = 0.3f;
    float accumilator = 0.0f;
    float dt;

    while (animate)
    {
        std::string frame;
        hideCursor();
        if (!clearedScreen)
        {
            fullClearScreen();
            clearedScreen = true;
        }
        else
        {
            goToTop();
        }

        if (foods.empty())
        {
            generateFoods(foods, map, minFoods, maxFoods);
        }

        snakeControls(snakeDir, animate);
        deltaTime(lastFrame, speed, accumilator, dt);
        while (accumilator >= 1.0f)
        {
            updateSnake(snakeSeg, snakeDir);
            accumilator -= 1.0f; // this will stop the while loop when the accumilator reaches higher or equal to 1.0f
        }
        detectCollisionWall(snakeSeg[0], map, gameOver);
        detectCollisionFood(foods, snakeSeg[0], snakeSeg, speed, speedInc, score);
        if (gameOver)
            animate = false;

        renderGame(map, snakeSeg, snakeBod, block, gameOver, foods, snakeFood, frame);
        gameInformations(snakeDir, snakeSeg, speed, speedInc);

        if (gameOver)
        {
            fullClearScreen();
            gameOverScreen();
        }

        if (!gameOver && !animate)
        {
            fullClearScreen();
            gameDone();
        }

        // std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

    return 0;
}