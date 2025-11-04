#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <utility>
#include <windows.h>

int main () {

    SetConsoleOutputCP(CP_UTF8);

    bool animate = true;
    int mapWidth = 10;
    int mapHeight = 10;

    std::pair<int, int> playerPos = {int(mapWidth / 2), int(mapHeight / 2)};

    char block = ' ';

    std::pair<int, int> snakeDir = {0, 1};
    
    while (animate) {

        // Clear the console (platform dependent)
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapWidth; j++) {
                /*
                if (i == 0 || i == mapHeight) {
                    if (i == 0 && j == 0) std::cout << u8"╔";
                    if (i == 0 && j == (mapWidth - 1)) std::cout << u8"╗";
                    if (i == (mapHeight - 1) && j == 0) std::cout << u8"╚";
                    if (i == (mapHeight - 1) && j == (mapWidth - 1)) std::cout << u8"╝";
                } else {
                }
                */

                if (i == 0) {
                    if (j == 0) { 
                        std::cout << u8"╔";
                    } else if (j == mapWidth - 1) {
                        std::cout << u8"╗";
                    } else std::cout << u8"═";
                } else if (i == mapHeight - 1) {
                    if (j == 0) {
                        std::cout << u8"╚";
                    } else if (j == mapWidth - 1) {
                        std::cout << u8"╝";
                    } else std::cout << u8"═";
                } else {
                    if (j == 0 || j == mapWidth - 1) std::cout << u8"║";
                    else std::cout << block;
                }
            }
            std::cout << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}