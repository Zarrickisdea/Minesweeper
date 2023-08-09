#pragma once

enum class TileState {
  Hidden,
  Revealed
};

class Tile {
  public:
  TileState tilestate;
  int distanceFromMine;
  bool isMine;

  Tile() : tilestate(TileState::Hidden), distanceFromMine(0), isMine(false) {};
};