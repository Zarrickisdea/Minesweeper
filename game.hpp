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
  static const std::string heading;
  static const std::string rules;
  static const std::string linebreak;
  static const std::string list;
  static const std::string lose;
  static const std::string win;

  int GetMove() const;
  int GetSize() const;
  int ValidateSize() const;
  void Opening() const;
  void ExitPrompt() const;
  void EndCard(const std::string& ending);
};