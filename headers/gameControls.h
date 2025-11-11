#ifndef GAMECTRL_H
#define GAMECTRL_H

#include <utility>
#include <vector>
#include <string>

void goToTop();
void hideCursor();
void showCursor();
void snakeControls(std::pair<int, int> &snakeDir, bool &animate);
void updateSnake(std::vector<std::pair<int, int>> &snakeSeg, std::pair<int, int> &snakeDir);
void detectCollision(std::pair<int, int> &head, std::vector<std::vector<int>> &map, bool &gameOver);
void chooseMap(std::vector<std::vector<int>> &map);
void fullClearScreen();
void gameOverScreen();
void renderGame (std::vector<std::vector<int>> &map, std::vector<std::pair<int, int>> &snakeSeg, std::string &snakeBod, std::string &block, bool &gameOver, std::string &frame);
int randomNumber(int max, int min);
void gameInformations(std::pair<int, int> &snakeDir, std::vector<std::pair<int, int>> &snakeSeg);
void generateFoods(std::vector<std::vector<int>> &map, int maxFood);
void gameDone();
void gameStartIntroduction();

#endif