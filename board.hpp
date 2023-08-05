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
  int GetSize() const;
  bool GetState() const;
  void Display() const;
  void CalculateDistances(std::stack<int>& mineStack);
  void PlaceMines(int& playerSelectedIndex);
  void ExecuteMove(int& playerSelectedIndex);
  void FirstMove(int& playerSelectedIndex);
  void Reveal(int row, int column);

  private:
  int size;
  bool destroyed;

  std::vector<Tile> tiles;

  std::mt19937 randomEngine;

  void Separator() const;
};