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
#include <algorithm>
#include <random>

void goToTop()
{
    static const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordinates = {0, 0};
    SetConsoleCursorPosition(hout, coordinates);
}

void hideCursor()
{
    HANDLE hcursor = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hcursor, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hcursor, &cursorInfo);
}

void showCursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInf;
    GetConsoleCursorInfo(handle, &cursorInf);
    cursorInf.bVisible = TRUE;
    SetConsoleCursorInfo(handle, &cursorInf);
}

void snakeControls(std::pair<int, int> &snakeDir, bool &animate)
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
        case 'e':
            animate = false;
        }
    }
}

void updateSnake(std::vector<std::pair<int, int>> &snakeSeg, std::pair<int, int> &snakeDir)
{
    std::pair<int, int> newHead = {snakeSeg[0].first + snakeDir.first, snakeSeg[0].second + snakeDir.second};
    snakeSeg.insert(snakeSeg.begin(), newHead);
    snakeSeg.pop_back();
}

void detectCollisionWall(std::pair<int, int> &head, std::vector<std::vector<int>> &map, bool &gameOver)
{
    // detect collision of wall
    // detect collision of body
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (head.second == i && head.first == j && map[i][j] == 0)
            {
                gameOver = true;
            }
        }
    }
}

void detectCollisionFood (std::vector<std::pair<int, int>> &snakeFoods, std::pair<int, int> &snakeHead, std::vector<std::pair<int, int>> &snakeSeg, int &score) {
    for (int i = 0; i < snakeFoods.size(); i++) {
        if (snakeHead.first == snakeFoods[i].first && snakeHead.second == snakeFoods[i].second) {
            std::pair<int, int> item = {snakeFoods[i].first, snakeFoods[i].second};
            auto it = std::find(snakeFoods.begin(), snakeFoods.end(), item);
            if (it != snakeFoods.end()) {
                snakeFoods.erase(it);
            } 
            score++;
            snakeSeg.push_back(snakeSeg.back()); // add length of the snake via .back() which coppies the last item and add it.
        }
    }
}

void chooseMap(std::vector<std::vector<int>> &map)
{
    bool hasChosen = false;
    bool inputError = false;
    int mapIndex = 0;
    bool initialClear = false;

    while (!hasChosen)
    {
        hideCursor();
        std::string frame;

        if (initialClear)
        {
            goToTop();
        }
        else
        {
            fullClearScreen();
            initialClear = true;
        }
        gameStartIntroduction();
        std::cout << "\033[1;32m"
                     "CHOOSE YOUR MAP! (use the numbers): "
                  << "\033[0m" << std::endl;
        for (int i = 0; i < maps.size(); i++)
        {
            if (mapIndex == i)
            {
                frame += std::string("\033[32m") + u8" ➤ MAP NAME: " + maps[i].first + "\033[0m \n";
            }
            else
            {
                frame += std::string("\033[32m") + "[" + std::to_string(i + 1) + "] MAP NAME: " + maps[i].first + "\033[0m \n";
            }
        }

        if (_kbhit())
        {
            int key = _getch();
            if (key == 0 || key == 224)
            {
                int arrow = _getch();
                switch (arrow)
                {
                case 72:
                    mapIndex--;
                    if (mapIndex < 0)
                        mapIndex = maps.size() - 1;
                    break;
                case 80:
                    mapIndex++;
                    if (mapIndex > maps.size() - 1)
                        mapIndex = 0;
                    break;
                }
            }
            else if (key == 13)
            {
                hasChosen = true;
            }
        }

        std::cout << frame << std::endl;
        // if (hasChosen) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    map = maps[mapIndex].second;
}

void fullClearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void gameOverScreen()
{
    std::cout << "\033[91m" << u8R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⠀⠀⢀⣤⣤⣤⣶⣶⣷⣤⣀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣶⣶⣶⠀⠀⠀⠀⣠⣾⣿⣿⡇⠀⣿⣿⣿⣿⠿⠛⠉⠉⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⠀⠀⠀⠀⠀⢀⣿⣿⣶⡀⠀⠀⠀⠀⠀⣾⣿⣿⣿⡄⠀⢀⣴⣿⣿⣿⣿⠁⢸⣿⣿⣿⣀⣤⡀⠀⠀⠀
⠀⠀⠀⠀⠀⣠⣴⣶⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⣼⣿⣿⣿⣧⠀⠀⠀⠀⢰⣿⣿⣿⣿⣇⣠⣿⣿⣿⣿⣿⡏⢠⣿⣿⣿⣿⣿⡿⠗⠂⠀⠀
⠀⠀⠀⣰⣾⣿⣿⠟⠛⠉⠉⠉⠉⠋⠀⠀⠀⣰⣿⣿⣿⣿⣿⣇⣠⣤⣤⣿⣿⣿⢿⣿⣿⣿⣿⢿⣿⣿⡿⠀⣼⣿⣿⡟⠉⠁⢀⣀⡄⠀⠀
⠀⢀⣾⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣴⣿⣿⣿⣿⡿⣿⣿⣿⡏⠈⢿⣿⣿⠏⣾⣿⣿⠃⢠⣿⣿⣿⣶⣶⣿⣿⣿⡷⠦⠀
⢠⣾⣿⡿⠀⠀⠀⣀⣠⣴⣶⣿⣿⡷⠀⣠⣿⣿⣿⣿⡿⠟⣿⣿⣿⣠⣿⣿⣿⠀⠀⠀⠀⠁⢸⣿⣿⡏⠀⣼⣿⣿⣿⠿⠛⠛⠉⠀⠀⠀⠀
⢸⣿⣿⠣⣴⣾⣿⣿⣿⣿⣿⣿⡿⠃⣰⣿⣿⣿⠋⠁⠀⠀⠸⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠸⠿⠿⠀⠀⠛⠛⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠸⣿⣿⣆⣉⣻⣭⣿⣿⣿⡿⠋⠀⠀⢿⣿⡿⠁⠀⠀⠀⠀⠀⠹⠟⠛⠛⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠙⠿⣿⣿⣿⣿⡿⠟⠋⠀⠀⠀⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣶⣶⣶⣶⣦⣄⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣷⠄⣤⣤⣤⣤⣶⣾⣷⣴⣿⣿⣿⣿⠿⠿⠛⣻⣿⣿⣷⡄
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣤⣄⠀⣶⣶⣤⡀⠀⠀⠀⠀⠀⠀⢀⣴⣿⠋⢠⣿⣿⣿⠿⠛⠋⠉⠛⣿⣿⣿⠏⢀⣤⣾⣿⣿⡿⠋⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣾⣿⣿⣿⣿⠓⢹⣿⣿⣷⠀⠀⠀⠀⢀⣶⣿⡿⠁⠀⣾⣿⣿⣟⣠⣤⠀⠀⢸⣿⣿⣿⣾⣿⣿⣿⡟⠋⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⡿⠛⠉⠸⣿⣦⡈⣿⣿⣿⡇⠀⠀⣰⣿⣿⡿⠁⠀⢸⣿⣿⣿⣿⣿⠿⠷⢀⣿⣿⣿⣿⡿⠛⣿⣿⣿⡀⠀⠀⠀
⠀⠀⠀⠀⢀⣼⣿⣿⡿⠋⠀⠀⠀⠀⣿⣿⣧⠘⣿⣿⣿⡀⣼⣿⣿⡟⠀⠀⢀⣿⣿⣿⠋⠁⠀⣀⣀⣼⣿⣿⡟⠁⠀⠀⠘⣿⣿⣧⠀⠀⠀
⠀⠀⠀⠀⣼⣿⣿⡟⠀⠀⠀⠀⠀⣠⣿⣿⣿⠀⢹⣿⣿⣿⣿⣿⡟⠀⠀⠀⣼⣿⣿⣷⣶⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠸⣿⣿⡆⠀⠀
⠀⠀⠀⠀⢹⣿⣿⣇⠀⠀⢀⣠⣴⣿⣿⣿⡿⠀⠈⣿⣿⣿⣿⡟⠀⠀⠀⢰⣿⣿⣿⠿⠟⠛⠉⠁⠸⢿⡟⠀⠀⠀⠀⠀⠀⠀⠘⠋⠁⠀⠀
⠀⠀⠀⠀⠈⢻⣿⣿⣿⣾⣿⣿⣿⣿⣿⠟⠁⠀⠀⠸⣿⣿⡿⠁⠀⠀⠀⠈⠙⠛⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠉⠛⠿⠿⠿⠿⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    )" << "\033[0m"
              << std::endl;
}

void renderGame(std::vector<std::vector<int>> &map, std::vector<std::pair<int, int>> &snakeSeg, std::string &snakeBod, std::string &block, bool &gameOver, std::vector<std::pair<int, int>> &snakeFoods, std::string &snakeFood, std::string &frame)
{
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

            bool isFood = false;
            for (const auto &food : snakeFoods)
            {
                if (j == food.first && i == food.second)
                {
                    isFood = true;
                    break;
                }
            }

            if (isSnake)
            {
                // std::cout << "\033[31m" << snakeBod << "\033[0m";
                frame += "\033[31m" + snakeBod + "\033[0m";
            }
            else if (isFood)
            {
                frame += "\033[35m" + snakeFood + "\033[0m";
            }
            else if (i == 0 || i == map.size() - 1 || j == 0 || j == map[0].size() - 1 && map[i][j] == 0)
            {
                // std::cout << "\033[35m" << block << "\033[0m";
                frame += "\033[35m" + block + "\033[0m";
            }
            else
            {
                if (map[i][j] == 1)
                {
                    // std::cout << "\033[36m" << block << "\033[0m";
                    frame += "\033[36m" + block + "\033[0m";
                }
                else if (map[i][j] == 0)
                {
                    // std::cout << "\033[35m" << block << "\033[0m";
                    frame += "\033[35m" + block + "\033[0m";
                }
            }
        }
        // std::cout << std::endl;
        frame += '\n';
    }

    std::cout << frame;
}

void deltaTime(std::chrono::high_resolution_clock::time_point &lastFrame, float &dt) {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = now - lastFrame;
    dt = elapsed.count();
    lastFrame = now;
}

void gameInformations(std::pair<int, int> &snakeDir, std::vector<std::pair<int, int>> &snakeSeg)
{
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
}

int randomNumber(int min, int max)
{
    std::random_device random_device;
    std::mt19937 seedGenerator(random_device());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(seedGenerator);
}

void generateFoods(std::vector<std::pair<int, int>> &foods,
                   std::vector<std::vector<int>> &map,
                   int &minFoods, int &maxFoods)
{

    // make a logic to check inputed min and max foods and adjust it based on the map
    std::vector<std::pair<int, int>> availableSpaces;

    for (int y = 0; y < map.size(); y++)
        for (int x = 0; x < map[y].size(); x++)
            if (map[y][x] == 1)
                availableSpaces.push_back({x, y});

    if (availableSpaces.empty())
        return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(availableSpaces.begin(), availableSpaces.end(), gen);

    int randFood = std::uniform_int_distribution<>(minFoods, maxFoods)(gen);
    randFood = std::min(randFood, (int)availableSpaces.size());

    foods.assign(availableSpaces.begin(), availableSpaces.begin() + randFood);
}

void gameDone()
{
    std::cout << "\033[92m" << u8R"(
   ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣀⢠⡤⠤⠖⠒⠒⠒⠲⣆⠀⠀⠀⠀⣾⠋⠉⠉⠛⢷⠀⣴⠖⠒⠤⣄⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⠤⠶⢺⣾⣏⠁⠀⠀⣧⣼⣇⣀⠀⠀⠀⡀⠀⠘⡆⠀⠀⢰⣏⠀⠀⠀⠀⠘⣿⡟⠀⠀⢠⢃⣼⡏⠉⠙⢳⡆⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣀⡤⠴⠒⠋⠙⣇⣿⠀⠀⠀⣿⣿⠀⠀⠀⢸⣿⣿⣿⠃⠀⢰⣿⡀⠀⠹⡄⠀⢸⣿⠀⠀⠀⠀⠀⢹⡇⠀⠀⢸⡿⣽⠀⠀⠀⡜⠀⣀⡤⠖⠓⠢⢤⣀⠀
⣠⡴⠒⠉⠁⠀⠀⠀⠀⠀⠸⣿⡇⠀⠀⠘⠛⠃⠀⠀⠈⡟⠉⣿⠀⠀⠘⠛⠃⠀⠀⢷⠀⢸⣿⠀⠀⢠⡀⠀⠀⠀⠀⠀⣿⢧⡇⠀⠀⠸⠗⠚⠁⠀⠀⠀⣀⣠⣾⠃
⣿⡇⠀⠀⠀⠀⠀⠀⣶⣶⣿⢿⢹⠀⠀⠀⢀⣀⠀⠀⠀⢳⠀⣿⠀⠀⢀⣀⣤⠀⠀⠘⣇⢸⡏⠀⠀⢸⣧⠀⠀⠀⠀⢸⣿⡿⠀⠀⢀⠀⠀⠀⢀⣤⣶⣿⠿⠛⠁⠀
⢧⣹⣶⣾⣿⡄⠀⠀⠸⡟⠋⠘⡜⡆⠀⠀⢻⣿⡇⠀⠀⢸⡀⣿⠀⠀⢸⣿⡿⡇⠀⠀⢸⣿⡇⠀⠀⢸⡿⡆⠀⠀⠀⣾⣿⠃⠀⠀⣾⡇⠀⠀⠈⡟⠉⠀⠀⠀⠀⠀
⠘⣿⡿⠿⢿⣧⠀⠀⠀⢳⡀⠀⣇⢱⠀⠀⠈⣿⣷⠀⣀⣸⣷⣿⣤⣤⣼⠋⣇⣹⣶⣶⣾⣿⡿⢲⣶⣾⡇⣿⣤⣀⣀⣿⡏⠀⠀⣼⡏⢧⠀⠀⠀⣇⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠸⡞⣇⠀⠀⠀⢧⠀⢸⣈⣷⣶⣶⣿⣿⣿⣿⣿⣿⣿⣽⣿⡏⢀⡼⠟⠛⠻⢿⡿⠿⠿⣿⣁⣿⣿⣿⣿⣿⣿⣿⣶⣴⢿⠁⢸⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢹⣼⣦⣤⣶⣿⠁⣀⣿⠿⠿⣿⣫⣿⠉⠁⠀⠀⠀⡏⠀⣴⠏⠀⠀⠀⠀⠀⠹⣆⠀⢠⣿⠀⠀⠀⢈⠟⢻⡿⠿⣅⣘⡆⣸⣇⠀⠀⢸⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠻⠿⠿⠛⠃⢠⣿⣷⣄⠀⠈⠙⠋⠀⠀⠀⠀⣸⢁⡾⠁⠀⠀⣠⣤⡀⠀⠀⠸⣤⡞⡇⠀⠀⠀⢸⣰⣿⠃⠀⠀⢹⣿⣿⣿⣿⣦⣼⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⢿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⣿⣾⠇⠀⠀⣸⣿⣿⢿⠀⠀⠀⣿⢁⡇⠀⠀⢀⣿⣿⡏⠀⠀⠀⡼⠀⢙⣿⠛⠻⣏⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿⣷⠀⠀⠀⠀⢸⡿⡿⠀⠀⠀⡏⢹⠟⡟⠀⠀⠀⡿⢸⠀⠀⠀⢸⣿⡿⠀⠀⠀⢠⠇⡰⢋⡏⠀⠀⠀⢙⡆⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⡿⡿⠀⠀⠀⠀⣸⡇⡇⠀⠀⠀⠻⠾⠞⠁⠀⠀⢀⡇⡏⠀⠀⠀⢸⣿⠃⠀⠀⠀⡼⣰⠃⡞⠀⠀⠀⠀⡾⠁⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡇⡇⠀⠀⠀⠀⣿⣇⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣃⡇⠀⠀⠀⠀⠀⠀⠀⠀⣼⣷⠃⣼⡀⠀⠀⢀⡞⠁⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢸⠃⠀⠀⠀⢀⡇⢿⣿⣧⣀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣽⣿⣷⣤⡞⠁⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣼⣤⣶⣶⣶⡿⠁⠈⢿⣿⣿⣿⣿⣿⣿⣿⠿⠃⢸⣿⣿⣷⣤⣄⣀⣀⣤⣾⣏⣤⡟⠁⠀⠈⠻⡍⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠿⠿⠿⠟⠛⠁⠀⠀⠀⠉⠛⠛⠛⠛⠉⠁⠀⠀⠀⠙⠿⢿⣿⣿⡿⠿⠋⢀⣿⣿⣧⡀⠀⠀⣠⡇⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
    )" << "\033[0m"
              << std::endl;
}

void gameStartIntroduction()
{
    std::cout << "\033[32m" << u8R"(
░██████╗███╗░░██╗░█████╗░██╗░░██╗███████╗  ░██████╗░░█████╗░███╗░░░███╗███████╗
██╔════╝████╗░██║██╔══██╗██║░██╔╝██╔════╝  ██╔════╝░██╔══██╗████╗░████║██╔════╝
╚█████╗░██╔██╗██║███████║█████═╝░█████╗░░  ██║░░██╗░███████║██╔████╔██║█████╗░░
░╚═══██╗██║╚████║██╔══██║██╔═██╗░██╔══╝░░  ██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░
██████╔╝██║░╚███║██║░░██║██║░╚██╗███████╗  ╚██████╔╝██║░░██║██║░╚═╝░██║███████╗
╚═════╝░╚═╝░░╚══╝╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝  ░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝
    )" << "\033[0m"
              << std::endl;
}
