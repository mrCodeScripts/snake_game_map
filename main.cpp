#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <utility>
#include <windows.h>
#include <conio.h>
#include <format>

void goToTop() {
    static const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordinates = {0, 0};
    SetConsoleCursorPosition(hout, coordinates);
}

void hideCursor () {
    HANDLE hcursor = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hcursor, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hcursor, &cursorInfo);
}

void showCursor () {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInf;
    GetConsoleCursorInfo(handle, &cursorInf);
    cursorInf.bVisible = TRUE;
    SetConsoleCursorInfo(handle, &cursorInf);
}

void snakeControls(std::pair<int, int> &snakeDir)
{
    if (_kbhit())
    {
        char k = _getch();
        switch (k)
        {
        case 'w':
            snakeDir = {0, -1}; 
            break;
        case 's':
            snakeDir = {0, 1};
            break;
        case 'a':
            snakeDir = {-1, 0};
            break;
        case 'd':
            snakeDir = {1, 0};
            break;
        }
    }
}

void updateSnake(std::vector<std::pair<int, int>> &snakeSeg, std::pair<int, int> &snakeDir)
{
    std::pair<int, int> newHead = {snakeSeg[0].first + snakeDir.first, snakeSeg[0].second + snakeDir.second};

    snakeSeg.insert(snakeSeg.begin(), newHead);
    snakeSeg.pop_back();
}

int main()
{

    SetConsoleOutputCP(CP_UTF8);

    bool animate = true;
    bool clearedScreen = false;
    int mapWidth = 50;
    int mapHeight = 30;
    std::string block = u8"⬛";
    std::string snakeBod = u8"⬛";

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
        if (!clearedScreen) {
            #ifdef _WIN32 
                system("cls");
            #else
                system("clear");
            #endif
            clearedScreen = true;
        } else {
            goToTop();
        }
        snakeControls(snakeDir);
        updateSnake(snakeSeg, snakeDir);

        for (int i = 0; i < mapHeight; i++)
        {
            for (int j = 0; j < mapWidth; j++)
            {
                bool isASnakeBod = false;
                for (const auto &seg : snakeSeg)
                {
                    if (j == seg.first && i == seg.second)
                    {
                        isASnakeBod = true;
                    }
                }

                if (isASnakeBod)
                {
                    std::cout << "\033[31m" << snakeBod << "\033[0m";
                }
                else
                {
                    if (i == 0)
                    {
                        if (j == 0)
                        {
                            // std::cout << u8"╔";
                            // std::cout << "\033[35m" << u8"█" << "\033[0m";
                            std::cout << "\033[35m" << block << "\033[0m";
                        }
                        else if (j == mapWidth - 1)
                        {
                            // std::cout << u8"╗";
                            // std::cout << "\033[35m" << u8"█" << "\033[0m";
                            std::cout << "\033[35m" << block << "\033[0m";
                        }
                        else
                            // std::cout << u8"═";
                            // std::cout << "\033[35m" << u8"█" << "\033[0m";
                            std::cout << "\033[35m" << block << "\033[0m";
                    }
                    else if (i == mapHeight - 1)
                    {
                        if (j == 0)
                        {
                            // std::cout << u8"╚";
                            // std::cout << "\033[35m" << u8"█" << "\033[0m";
                            std::cout << "\033[35m" << block << "\033[0m";
                        }
                        else if (j == mapWidth - 1)
                        {
                            // std::cout << u8"╝";
                            // std::cout << "\033[35m" << u8"█" << "\033[0m";
                            std::cout << "\033[35m" << block << "\033[0m";
                        }
                        else
                            // std::cout << u8"═";
                            // std::cout << "\033[35m" << u8"█" << "\033[0m";
                            std::cout << "\033[35m" << block << "\033[0m";
                    }
                    else
                    {
                        if (j == 0 || j == mapWidth - 1)
                            // std::cout << u8"║";
                            // std::cout << "\033[35m" << u8"█" << "\033[0m";
                            std::cout << "\033[35m" << block << "\033[0m";
                        else

                            /**
                             * 🧠 Explanation:

    \033[ = escape sequence introducer

    31m = red

    32m = green

    33m = yellow

    34m = blue

    35m = magenta

    36m = cyan

    0m = reset to default color
                             */
                            std::cout << "\033[36m" << block << "\033[0m";
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
        for  (int j = 0; j < snakeSeg.size(); j++) {
            if (j == 0) {
                std::cout << "[" << snakeSeg[j].first << ", " << snakeSeg[j].second << "] HEAD      " << std::endl;
            } else if (j == snakeSeg.size() - 1) {
                std::cout << "[" << snakeSeg[j].first << ", " << snakeSeg[j].second << "] TAIL      " << std::endl;
            } else {
                std::cout << "[" << snakeSeg[j].first << ", " << snakeSeg[j].second << "] BODY     " << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

    return 0;
}