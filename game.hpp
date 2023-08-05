#pragma once

#include "board.hpp"
#include <limits>

class Game {
  public:
  Game(int size);
  int GetMove();
  void Start();
  void Update();

  private:
  Board board;
};