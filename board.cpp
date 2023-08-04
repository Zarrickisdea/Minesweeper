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
            break; // Avoid accessing beyond the size of mineCandidateIndices
        }
        
        int index = mineCandidateIndices[i];
        tiles[index].isMine = true;
    }
}





