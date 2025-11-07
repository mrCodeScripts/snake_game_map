#ifndef GAMECTRL_H
#define GAMECTRL_H

#include <utility>
#include <vector>

void goToTop();
void hideCursor();
void showCursor();
void snakeControls(std::pair<int, int> &snakeDir);
void updateSnake(std::vector<std::pair<int, int>> &snakeSeg, std::pair<int, int> &snakeDir);
void detectCollision(std::pair<int, int> &head, std::vector<std::vector<int>> &map, bool &gameOver);
void fullClearScreen();
void gameOverScreen();

#endif