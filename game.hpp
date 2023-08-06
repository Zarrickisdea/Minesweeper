#pragma once

#include "board.hpp"
#include <limits>

class Game {
  public:
  Game(int size);
  void Start();
  void Update();

  private:
  Board board;

  int GetMove();
};