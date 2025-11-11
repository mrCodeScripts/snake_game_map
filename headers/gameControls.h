#ifndef GAMECTRL_H
#define GAMECTRL_H

#include <utility>
#include <vector>
#include <chrono>

void goToTop();
void hideCursor();
void showCursor();
void snakeControls(std::pair<int, int> &snakeDir, bool &animate);
void updateSnake(std::vector<std::pair<int, int>> &snakeSeg, std::pair<int, int> &snakeDir);
void detectCollisionWall(std::pair<int, int> &head, std::vector<std::vector<int>> &map, bool &gameOver);
void detectCollisionFood(std::vector<std::pair<int, int>> &snakeFoods, std::pair<int, int> &snakeHead, std::vector<std::pair<int, int>> &snakeSeg, int &score);
void chooseMap(std::vector<std::vector<int>> &map);
void fullClearScreen();
void gameOverScreen();
void deltaTime(std::chrono::high_resolution_clock::time_point &lastFrame, float &dt);
void renderGame (std::vector<std::vector<int>> &map, std::vector<std::pair<int, int>> &snakeSeg, std::string &snakeBod, std::string &block, bool &gameOver, std::vector<std::pair<int, int>> &snakeFoods, std::string &snakeFood, std::string &frame);
int randomNumber(int max, int min);
void gameInformations(std::pair<int, int> &snakeDir, std::vector<std::pair<int, int>> &snakeSeg);
void generateFoods(std::vector<std::pair<int, int>> &foods, std::vector<std::vector<int>> &map, int &minFoods, int &maxFoods);
void gameDone();
void gameStartIntroduction();

#endif