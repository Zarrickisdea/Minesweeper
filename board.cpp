#include "board.hpp"

Board::Board(int dimension) : size(dimension), randomEngine(std::random_device{}()) {
    tiles.resize(dimension * dimension);
}

int Board::GetSize() { return size; }

void Board::Separator()
{
    std::cout << "+";
    for (int j = 0; j < size; ++j) {
        std::cout << "---+";
    }
    std::cout << std::endl;
}

void Board::Display() {
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

void Board::PlaceMines(int playerSelectedIndex) {
    // 20% of the board is mines
    int totalMines = tiles.size() * 0.2;

    std::vector<int> mineCandidateIndices;

    for (int i = 0; i < tiles.size(); ++i) {
        if (i != playerSelectedIndex) {
            mineCandidateIndices.push_back(i);
        }
    }

    std::shuffle(mineCandidateIndices.begin(), mineCandidateIndices.end(), randomEngine);

    for (int i = 0; i < totalMines; ++i) {
        if (i >= mineCandidateIndices.size()) {
            break;
        }
        
        int index = mineCandidateIndices[i];
        tiles[index].isMine = true;
    }

    CalculateDistances();
}

void Board::CalculateDistances() {
    std::stack<int> mineStack;

    for (int i = 0; i < tiles.size(); ++i) {
        if (tiles[i].isMine) {
            mineStack.push(i);
        }
    }

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
                    tiles[neighborIndex].distanceFromMine++;
                }
            }
        }
    }
}

void Board::ExecuteMove(int playerSelectedIndex) {
    
    if (tiles[playerSelectedIndex].tilestate == TileState::Hidden)
    {
        tiles[playerSelectedIndex].tilestate = TileState::Revealed;
    }
    else
    {
        std::cout << "Invalid tile selected." << std::endl;
    }

    // for (int i = 0; i < tiles.size(); ++i)
    // {
    //     tiles[i].tilestate = TileState::Revealed;
    // }
}