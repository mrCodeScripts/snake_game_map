#include <iostream>
#include "gameControls.h"
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <utility>
#include <windows.h>
#include <conio.h>
#include <format>

std::vector<std::vector<int>> map = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int main()
{

    SetConsoleOutputCP(CP_UTF8);

    bool animate = true;
    bool gameOver = false;
    bool clearedScreen = false;
    int mapWidth = map[0].size();
    int mapHeight = map.size();
    std::string block = u8"██";
    std::string snakeBod = u8"██";
    // std::string block = u8" ";
    // std::string snakeBod = u8" ";

    /**
     * FOR MORE SYMBOLS GO TO : https://www.alt-codes.net/square-symbols
     */

    std::pair<int, int> playerPos = {int(mapWidth / 2), int(mapHeight / 2)};
    std::vector<std::pair<int, int>> snake;
    std::vector<std::pair<int, int>> snakeSeg = {
        {int(mapWidth / 2), int(mapHeight / 2)},
        {int(mapWidth / 2), int(mapHeight / 2) - 1},
        {int(mapWidth / 2), int(mapHeight / 2) - 2},
    };
    std::pair<int, int> snakeDir = {1, 0};

    while (animate)
    {
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

        snakeControls(snakeDir);
        updateSnake(snakeSeg, snakeDir);
        detectCollision(snakeSeg[0], map, gameOver);

        if (gameOver)
            animate = false;

        for (int i = 0; i < map.size(); i++)
        {
            if (gameOver)
                break;
            for (int j = 0; j < map[0].size(); j++)
            {
                bool isSnake = false;
                for (const auto &seg : snakeSeg)
                {
                    if (j == seg.first && i == seg.second)
                    {
                        isSnake = true;
                        break;
                    }
                }

                if (isSnake)
                {
                    std::cout << "\033[31m" << snakeBod << "\033[0m";
                }
                else if (i == 0 || i == map.size() - 1 || j == 0 || j == map[0].size() - 1 && map[i][j] == 0)
                {
                    std::cout << "\033[35m" << block << "\033[0m";
                }
                else
                {
                    if (map[i][j] == 1)
                    {
                        std::cout << "\033[36m" << block << "\033[0m";
                    }
                    else if (map[i][j] == 0)
                    {
                        std::cout << "\033[35m" << block << "\033[0m";
                    }
                }
            }
            std::cout << std::endl;
        }

        /**
         * SNAKE INFORMATIONS
         */
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << "DIRECTION: [ X: " << snakeDir.first << " Y:" << snakeDir.second << " ]   " << std::endl;
        std::cout << std::endl;

        std::cout << "SNAKE BOD SEGMENTS [x, y]" << std::endl;
        for (int j = 0; j < snakeSeg.size(); j++)
        {
            if (j == 0)
            {
                std::cout << "[" << snakeSeg[j].first << ", " << snakeSeg[j].second << "] HEAD      " << std::endl;
            }
            else if (j == snakeSeg.size() - 1)
            {
                std::cout << "[" << snakeSeg[j].first << ", " << snakeSeg[j].second << "] TAIL      " << std::endl;
            }
            else
            {
                std::cout << "[" << snakeSeg[j].first << ", " << snakeSeg[j].second << "] BODY     " << std::endl;
            }
        }

        if (gameOver)
        {
            fullClearScreen();
            gameOverScreen();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

    return 0;
}