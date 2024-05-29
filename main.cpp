#include <iostream>
#include "game.hpp"
#include "ai.hpp"

void printMenu() {
    std::cout << "Choose game mode:\n";
    std::cout << "1. Two players\n";
    std::cout << "2. Play against AI\n";
    std::cout << "Enter your choice (1 or 2): ";
}

int main() {
    int gameMode;
    printMenu();
    std::cin >> gameMode;

    while (gameMode != 1 && gameMode != 2) {
        std::cout << "Invalid choice. Please enter 1 or 2: ";
        std::cin >> gameMode;
    }

    Game game;
    if (gameMode == 1) {
        game.playTwoPlayers();
    } else {
        game.playWithAI();
    }

    return 0;
}
