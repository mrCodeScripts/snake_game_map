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

    /**
     * FOR MORE SYMBOLS GO TO : https://www.alt-codes.net/square-symbols
     */
    chooseMap(map);
    int mapWidth = map[0].size();
    int mapHeight = map.size();
    std::vector<std::pair<int, int>> snake;
    std::vector<std::pair<int, int>> snakeSeg = {
        {int(mapWidth / 2), int(mapHeight / 2)},
        {int(mapWidth / 2), int(mapHeight / 2) - 1},
        {int(mapWidth / 2), int(mapHeight / 2) - 2},
    };
    std::pair<int, int> snakeDir = {1, 0};

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

        snakeControls(snakeDir, animate);
        updateSnake(snakeSeg, snakeDir);
        detectCollision(snakeSeg[0], map, gameOver);
        if (gameOver) animate = false;
        renderGame(map, snakeSeg, snakeBod, block, gameOver, frame);
        gameInformations(snakeDir, snakeSeg);

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

        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

    return 0;
}