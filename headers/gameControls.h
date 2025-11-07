#ifndef GAMECTRL_H
#define GAMECTRL_H

#include <utility>
#include <vector>

void goToTop();
void hideCursor();
void showCursor();
void snakeControls(std::pair<int, int> &snakeDir, bool &animate);
void updateSnake(std::vector<std::pair<int, int>> &snakeSeg, std::pair<int, int> &snakeDir);
void detectCollision(std::pair<int, int> &head, std::vector<std::vector<int>> &map, bool &gameOver);
void chooseMap(std::vector<std::vector<int>> &map);
void fullClearScreen();
void gameOverScreen();
int randomNumber(int max, int min);
void generateFoods(std::vector<std::vector<int>> &map, int maxFood);
void gameDone();

#endif