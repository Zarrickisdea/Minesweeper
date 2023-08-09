#include "game.hpp"

Game::Game() : board(GetSize()) {}

int Game::GetSize() const {
  Opening();
  int size = ValidateSize();
  return size;
}

void Game::Opening() const {
  std::cout << heading;
  std::cout << linebreak;
  std::cout << rules;
  std::cout << list;
  std::cout << linebreak;
}

int Game::ValidateSize() const {
  int temp = 0;

  while (true) {
    std::cout << std::endl;
    std::cout << "Enter a size: " << std::endl;

    if (std::cin >> temp && temp >= 9) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break;
    } else {
      std::cout << "Invalid input. Please enter a number greater than or equal to 9." << std::endl;
      std::cin.clear(); // Clear error state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  
  return temp;
}

int Game::GetMove() const {
  int x = 0;
  int y = 0;
  int s = board.GetSize();

  while (true) {
    std::cout << std::endl;
    std::cout << "Enter your move (row column):" << std::endl;

    if (std::cin >> x >> y) {
      if (x >= 1 && x <= s && y >= 1 && y <= s) {
        break;
      } else {
        std::cout << "Invalid move. Please enter numbers within the board's dimensions." << std::endl;
      }
    } else {
      std::cout << "Invalid input. Please enter two integers." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  int index = (x - 1) * s + (y - 1);
  return index;
}

void Game::Start() {
  std::cout << linebreak;
  board.Display();
  int firstMove = GetMove();

  board.FirstMove(firstMove);
}

void Game::Update() {
  do
  {
    std::cout << linebreak;
    board.Display();

    int move = GetMove();

    board.ExecuteMove(move);
  } while (!board.GetState() and !board.CheckWin());

  if (board.CheckWin()) {
    EndCard(win);
  }
  else
  {
    EndCard(lose);
  }
}

void Game::EndCard (const std::string& ending) {
    board.RevealAllTiles();
    std::cout << linebreak;
    std::cout << ending << std::endl;
    board.Display();
    std::cout << linebreak;
}

const std::string Game::heading = R"( __  __  ____  _  _  ____  ___  _    _  ____  ____  ____  ____  ____ 
(  \/  )(_  _)( \( )( ___)/ __)( \/\/ )( ___)( ___)(  _ \( ___)(  _ \
 )    (  _)(_  )  (  )__) \__ \ )    (  )__)  )__)  )___/ )__)  )   /
(_/\/\_)(____)(_)\_)(____)(___/(__/\__)(____)(____)(__)  (____)(_)\_)
)";

const std::string Game::rules = R"(██████  ██    ██ ██      ███████ ███████ 
██   ██ ██    ██ ██      ██      ██      
██████  ██    ██ ██      █████   ███████ 
██   ██ ██    ██ ██      ██           ██ 
██   ██  ██████  ███████ ███████ ███████

)";

const std::string Game::linebreak = R"( 
 _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ 
|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|

)";

const std::string Game::list = R"(
1. Please enter a number above or equal to 9 to create your own board.
2. The board consists of randomly placed mines.
3. Open every unmined tile to win.
4. The game is over if you pick a mine.
5. The tiles have numbers that show the number of mines around it.
6. To make a move when prompted, type in the row and column number.
)";

const std::string Game::lose = R"(

█▄█ █▀█ █ █   █ █ █ ▀█▀   ▄▀█   █▀▄▀█ █ █▄ █ █▀▀          
 █  █▄█ █▄█   █▀█ █  █    █▀█   █ ▀ █ █ █ ▀█ ██▄ ▄ ▄ ▄ ▄ ▄

)";

const std::string Game::win = R"(
█▀▀ █▀█ █▄ █ █▀▀ █▀█ ▄▀█ ▀█▀ █ █ █   ▄▀█ ▀█▀ █ █▀█ █▄ █ █▀ █ █ █
█▄▄ █▄█ █ ▀█ █▄█ █▀▄ █▀█  █  █▄█ █▄▄ █▀█  █  █ █▄█ █ ▀█ ▄█ ▄ ▄ ▄

█▄█ █▀█ █ █   █ █ █ █▀█ █▄ █ █ █ █
 █  █▄█ █▄█   ▀▄▀▄▀ █▄█ █ ▀█ ▄ ▄ ▄
)";