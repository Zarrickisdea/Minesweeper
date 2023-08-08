#include "board.hpp"

Board::Board(int dimension) : size(dimension), destroyed(false), minecount(0), randomEngine(std::random_device{}()) {
    tiles.resize(dimension * dimension);
}

int Board::GetSize() const { return size; }

bool Board::GetState() const { return destroyed; }

bool Board::CheckWin() const {
    for (const Tile& tile : tiles) {
        if (!tile.isMine && tile.tilestate == TileState::Hidden) {
            return false;
        }
    }
    return true;
}

void Board::Separator() const
{
    std::cout << std::setw(5) << "+" << std::setw(4 * size) << std::setfill('-') << "+" << std::setfill(' ') << std::endl;
}

void Board::PrintColumnNumbers() const {
    std::cout << std::setw(3) << " ";

    for (int j = 0; j < size; ++j) {
        std::cout << std::setw(4) << j + 1;
    }
    std::cout << std::endl;
}

void Board::Display() const {
    std::cout << std::endl;

    PrintColumnNumbers();
    Separator();

    for (int i = 0; i < size; ++i) {
        std::cout << std::setw(3) << i + 1 << " ";

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

        std::cout << "| " << std::setw(2) << i + 1 << " " << std::endl;

        if (i < size - 1) {
          Separator();
        }
    }

    Separator();
    PrintColumnNumbers();
}

bool Board::IsValid (int row, int column) {
    return row >= 1 && row <= size && column >= 1 && column <= size; 
}

void Board::RevealAllTiles() {
    for (Tile& tile : tiles) {
        tile.tilestate = TileState::Revealed;
    }
}

void Board::PlaceMines(int& playerSelectedIndex) {
    // 20% of the board is mines
    int totalMines = tiles.size() * 0.2;
    std::stack<int> mineStack;

    std::uniform_int_distribution<int> dist(0, tiles.size() - 1);

    for (int i = 0; i < totalMines; ++i) {
        int index = dist(randomEngine);
        if (index == playerSelectedIndex) {
            continue;
        }
        
        tiles[index].isMine = true;
        mineStack.push(index);
        minecount++;
    }

    CalculateDistances(mineStack);
}

void Board::CalculateDistances(std::stack<int>& mineStack) {
    while (!mineStack.empty()) {
        int mineIndex = mineStack.top();
        mineStack.pop();

        int mineRow = mineIndex / size + 1;
        int mineCol = mineIndex % size + 1;

        // Update distanceFromMine for neighboring tiles
        for (int r = -1; r <= 1; ++r) {
            for (int c = -1; c <= 1; ++c) {
                int neighborRow = mineRow + r;
                int neighborCol = mineCol + c;

                if (IsValid(neighborRow, neighborCol)) {
                    int neighborIndex = (neighborRow - 1) * size + (neighborCol - 1);

                    if (neighborIndex != mineIndex && !tiles[neighborIndex].isMine) { // Check if neighborIndex is not the mineIndex
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
            int mineRow = (playerSelectedIndex / size) + 1;
            int mineCol = (playerSelectedIndex % size) + 1;
            Reveal(mineRow, mineCol);
        }
    }
    else
    {
        std::cout << "Invalid tile selected." << std::endl;
    }
}

void Board::Reveal(int row, int column) {
    if (!IsValid(row, column))
    {
        return;
    }

    int index = (row - 1) * size + (column - 1);
    Tile& tile = tiles[index];

    if (tile.tilestate == TileState::Revealed)
    {
        return;
    }

    tile.tilestate = TileState::Revealed;

    if (tile.distanceFromMine == 0 && !tile.isMine) {
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