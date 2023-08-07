#pragma once

#include "board.hpp"
#include <limits>

class Game {
  public:
  Game();
  void Start();
  void Update();

  private:
  Board board;
  static std::string heading;
  static std::string rules;
  static std::string linebreak;
  static std::string list;

  int GetMove() const;
  int GetSize() const;
  int ValidateSize() const;
  void Opening() const;
  void EndCard(std::string ending);
};