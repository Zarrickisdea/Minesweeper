#pragma once

#include "tile.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include <random>
#include <algorithm>

class Board {
  public:
  Board (int dimension);
  int GetSize();
  void Display();
  void CalculateDistances();
  void PlaceMines(int playerSelectedIndex);
  void ExecuteMove(int playerSelectedIndex);

  private:
  std::vector<Tile> tiles;
  int size;
  std::mt19937 randomEngine;
  void Separator();
};