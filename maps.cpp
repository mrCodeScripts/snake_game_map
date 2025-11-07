#include "headers/maps.h"
#include <vector>
#include <string>

std::vector<std::pair<std::string, std::vector<std::vector<int>>>> maps = {
    {"Open XL Arena", // mostly free space
     []()
     {
         std::vector<std::vector<int>> map(50, std::vector<int>(50, 1));
         // outer walls
         for (int i = 0; i < 50; i++)
         {
             map[0][i] = 0;
             map[49][i] = 0;
             map[i][0] = 0;
             map[i][49] = 0;
         }
         return map;
     }()},

    {"Cross Walls XL", // simple cross inside
     []()
     {
         std::vector<std::vector<int>> map(50, std::vector<int>(50, 1));
         for (int i = 0; i < 50; i++)
         {
             map[0][i] = 0;
             map[49][i] = 0;
             map[i][0] = 0;
             map[i][49] = 0;
         }
         // vertical line
         for (int i = 10; i < 40; i++)
             map[i][25] = 0;
         // horizontal line
         for (int j = 10; j < 40; j++)
             map[25][j] = 0;
         return map;
     }()},

    {"Diagonal Split XL", // two diagonals
     []()
     {
         std::vector<std::vector<int>> map(50, std::vector<int>(50, 1));
         for (int i = 0; i < 50; i++)
         {
             map[0][i] = 0;
             map[49][i] = 0;
             map[i][0] = 0;
             map[i][49] = 0;
         }
         for (int i = 5; i < 45; i++)
         {
             map[i][i] = 0;
             map[i][49 - i] = 0;
         }
         return map;
     }()},

    {"Island Blocks XL", // scattered wall clusters
     []()
     {
         std::vector<std::vector<int>> map(50, std::vector<int>(50, 1));
         for (int i = 0; i < 50; i++)
         {
             map[0][i] = 0;
             map[49][i] = 0;
             map[i][0] = 0;
             map[i][49] = 0;
         }
         for (int i = 10; i < 20; i++)
             for (int j = 10; j < 20; j++)
                 map[i][j] = 0;
         for (int i = 30; i < 40; i++)
             for (int j = 30; j < 40; j++)
                 map[i][j] = 0;
         for (int i = 15; i < 25; i++)
             for (int j = 35; j < 45; j++)
                 map[i][j] = 0;
         return map;
     }()},

    {"Maze Snippet XL", // more compact internal walls
     []()
     {
         std::vector<std::vector<int>> map(50, std::vector<int>(50, 1));
         for (int i = 0; i < 50; i++)
         {
             map[0][i] = 0;
             map[49][i] = 0;
             map[i][0] = 0;
             map[i][49] = 0;
         }
         for (int i = 5; i < 45; i += 5)
         {
             for (int j = 5; j < 45; j += 5)
                 map[i][j] = 0;
         }
         return map;
     }()},
};
