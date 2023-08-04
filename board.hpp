#pragma once

#include "tile.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

class Board {
  public:
  Board (int dimension);
  int GetSize();
  void Display();
  void Separator();
  void PlaceMines(int playerSelectedIndex);

  private:
  std::vector<Tile> tiles;
  int size;
  std::mt19937 randomEngine;
};