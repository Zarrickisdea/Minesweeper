#pragma once

#include "tile.hpp"
#include <vector>
#include <set>
#include <stack>
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

class Board {
  public:
  Board (int dimension);
  int GetSize() const;
  bool GetState() const;
  void Display() const;
  bool CheckWin() const;
  void RevealAllTiles();
  void ExecuteMove(int& playerSelectedIndex);
  void FirstMove(int& playerSelectedIndex);

  private:
  int size;
  bool destroyed;
  int minecount;

  std::vector<Tile> tiles;

  std::mt19937 randomEngine;

  void Separator() const;
  void PrintColumnNumbers() const;
  void CalculateDistances(std::stack<int>& mineStack);
  void PlaceMines(int& playerSelectedIndex);
  void Reveal(int row, int column);
};