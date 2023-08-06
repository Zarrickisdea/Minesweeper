#include "board.hpp"

Board::Board(int dimension) : size(dimension), destroyed(false), randomEngine(std::random_device{}()) {
    tiles.resize(dimension * dimension);
}

int Board::GetSize() const { return size; }

bool Board::GetState() const { return destroyed; }

void Board::Separator() const
{
    std::cout << "+";
    for (int j = 0; j < size; ++j) {
        std::cout << "---+";
    }
    std::cout << std::endl;
}

void Board::Display() const {
    Separator();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int index = i * size + j;
            const Tile& tile = tiles[index];

            std::cout << "|";
            switch (tile.tilestate) {
                case TileState::Hidden:
                    std::cout << " . ";
                    break;

                case TileState::Revealed:
                    if (tile.isMine) {
                        std::cout << " M ";
                    } else {
                        std::cout << " " << tile.distanceFromMine << " ";
                    }
                    break;
            }
        }

        std::cout << "|" << std::endl;

        if (i < size - 1) {
          Separator();
        }
    }

    Separator();
}

void Board::PlaceMines(int& playerSelectedIndex) {
    // 20% of the board is mines
    int totalMines = tiles.size() * 0.2;
    std::stack<int> mineStack;

    // Generate random indices for mine placement
    std::uniform_int_distribution<int> distribution(0, tiles.size() - 1);
    std::set<int> chosenIndices;

    while (chosenIndices.size() < totalMines) {
        int randomIndex = distribution(randomEngine);
        if (randomIndex != playerSelectedIndex && tiles[randomIndex].tilestate == TileState::Hidden) {
            chosenIndices.insert(randomIndex);
            mineStack.push(randomIndex);
            tiles[randomIndex].isMine = true;
        }
    }

    CalculateDistances(mineStack);
}

void Board::CalculateDistances(std::stack<int>& mineStack) {

    while (!mineStack.empty()) {
        int mineIndex = mineStack.top();
        mineStack.pop();

        int mineRow = mineIndex / size;
        int mineCol = mineIndex % size;

        // Update distanceFromMine for neighboring tiles
        for (int r = -1; r <= 1; ++r) {
            for (int c = -1; c <= 1; ++c) {
                int neighborRow = mineRow + r;
                int neighborCol = mineCol + c;
                int neighborIndex = neighborRow * size + neighborCol;

                if (neighborRow >= 0 && neighborRow < size && neighborCol >= 0 && neighborCol < size) {
                    if (!tiles[neighborIndex].isMine) {
                    tiles[neighborIndex].distanceFromMine++;
                    }
                }
            }
        }
    }
}

void Board::ExecuteMove(int& playerSelectedIndex) {
    
    if (tiles[playerSelectedIndex].tilestate == TileState::Hidden)
    {
        if (tiles[playerSelectedIndex].isMine)
        {
            destroyed = true;
        }
        else 
        {
            int mineRow = playerSelectedIndex / size;
            int mineCol = playerSelectedIndex % size;
            Reveal(mineRow, mineCol);
        }
    }
    else
    {
        std::cout << "Invalid tile selected." << std::endl;
    }
}

void Board::Reveal(int row, int column) {
    if (row < 0 || row >= size || column < 0 || column >= size)
    {
        return;
    }

    int index = row * size + column;
    Tile& tile = tiles[index];

    if (tile.tilestate == TileState::Revealed)
    {
        return;
    }

    tile.tilestate = TileState::Revealed;

    if (tile.distanceFromMine == 0) {
        for (int r = -1; r <= 1; ++r) {
            for (int c = -1; c <= 1; ++c) {
                if (r == 0 && c == 0) {
                    continue;
                }
                Reveal(row + r, column + c);
            }
        }
    }
}

void Board::FirstMove(int& playerSelectedIndex) {
    if (tiles[playerSelectedIndex].tilestate == TileState::Hidden)
    {
        tiles[playerSelectedIndex].tilestate = TileState::Revealed;
    }
    PlaceMines(playerSelectedIndex);
}