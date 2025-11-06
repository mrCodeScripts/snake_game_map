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

void snakeControls(std::pair<int, int> &snakeDir)
{
    if (_kbhit())
    {
        char k = _getch();
        switch (k)
        {
        case 'w':
            snakeDir = {-1, 0};
            break;
        case 's':
            snakeDir = {1, 0};
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

void updateSnake(std::vector<std::pair<int, int>> &snakeSeg)
{
}

int main()
{

    SetConsoleOutputCP(CP_UTF8);

    bool animate = true;
    int mapWidth = 100;
    int mapHeight = 30;

    std::pair<int, int> playerPos = {int(mapWidth / 2), int(mapHeight / 2)};
    std::vector<std::pair<int, int>> snake;
    std::vector<std::pair<int, int>> snakeSeg = {
        {int(mapWidth / 2), int(mapHeight / 2)},
        {int(mapWidth / 2), int(mapHeight / 2) - 1},
        {int(mapWidth / 2), int(mapHeight / 2) - 2},
    };
    std::pair<int, int> snakeDir = {1, 0};

    std::string block = u8"█";
    std::string snakeBod = u8"▓";

    while (animate)
    {

// Clear the console (platform dependent)
/*
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
*/

        hideCursor();
        goToTop();
        snakeControls(snakeDir);

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
                            std::cout << "\033[35m" << u8"█" << "\033[0m";
                        }
                        else if (j == mapWidth - 1)
                        {
                            // std::cout << u8"╗";
                            std::cout << "\033[35m" << u8"█" << "\033[0m";
                        }
                        else
                            // std::cout << u8"═";
                            std::cout << "\033[35m" << u8"█" << "\033[0m";
                    }
                    else if (i == mapHeight - 1)
                    {
                        if (j == 0)
                        {
                            // std::cout << u8"╚";
                            std::cout << "\033[35m" << u8"█" << "\033[0m";
                        }
                        else if (j == mapWidth - 1)
                        {
                            // std::cout << u8"╝";
                            std::cout << "\033[35m" << u8"█" << "\033[0m";
                        }
                        else
                            // std::cout << u8"═";
                            std::cout << "\033[35m" << u8"█" << "\033[0m";
                    }
                    else
                    {
                        if (j == 0 || j == mapWidth - 1)
                            // std::cout << u8"║";
                            std::cout << "\033[35m" << u8"█" << "\033[0m";
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

        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

    return 0;
}