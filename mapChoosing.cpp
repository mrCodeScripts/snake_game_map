#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <utility>
#include <conio.h>
#include <windows.h>

void cursorTotop()
{
    static const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordinate = {0, 0};
    SetConsoleCursorPosition(hout, coordinate);
}

int main()
{
    std::vector<std::pair<int, std::string>> mapChoosing = {
        {1, "Shit"},
        {0, "Shit"},
        {0, "Shit"},
        {0, "Shit"},
        {0, "Shit"},
        {0, "Shit"},
        {0, "Shit"},
        {0, "Shit"},
        {0, "Shit"},
    };

    bool animate = true;
    int chosenIndex = 0;

    while (animate)
    {
// cursorTotop();
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        for (int i = 0; i < mapChoosing.size(); i++)
        {
            if (i == chosenIndex)
            {
                std::cout << "\033[1;32m" << mapChoosing[i].second << "\033[0m" << std::endl;
            }
            else
            {
                std::cout << "\033[32m" << mapChoosing[i].second << std::endl;
            }
        }

        if (_kbhit())
        {
            int k = _getch();

            if (k == 0 || k == 224) // arrow keys
            {
                int arrow = _getch(); // get the real arrow key code
                switch (arrow)
                {
                case 72: // up
                    chosenIndex--;
                    if (chosenIndex < 0)
                        chosenIndex = mapChoosing.size() - 1;
                    break;
                case 80: // down
                    chosenIndex++;
                    if (chosenIndex >= mapChoosing.size())
                        chosenIndex = 0;
                    break;
                }
            }
            else
            {
                // optional: handle other keys
                if (k == 'e' || k == 'E')
                    animate = false;
            }
        }
    }
    return 0;
}