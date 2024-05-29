// game.cpp

#include "game.hpp"
#include <iostream>

Game::Game() : currentPlayer(PieceColor::White) {}

void Game::play() {
    while (true) {
        printBoard();
        int fromX, fromY, toX, toY;
        std::cout << "Enter move (fromX fromY toX toY): ";
        std::cin >> fromX >> fromY >> toX >> toY;

        if (makeMove(fromX, fromY, toX, toY)) {
            switchPlayer();
        } else {
            std::cout << "Invalid move. Try again.\n";
        }
    }
}

void Game::printBoard() {

    std::cout << " ";
    for (int i = 0; i < 8; ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    for (int j = 0; j < 8; ++j) {
        std::cout << j <<" ";//wyswietlan nie indeksu z lewej storny planszy
        for (int i = 0; i < 8; ++i) {
            Piece* piece = board.getPiece(i, j);
            if (piece == nullptr) {
                std::cout << ".";
            } else if (piece->getColor() == PieceColor::White) {
                std::cout << (piece->getType() == PieceType::Man ? "w" : "W");
            } else {
                std::cout << (piece->getType() == PieceType::Man ? "b" : "B");
            }
            std::cout << " ";
        }
        std::cout << j <<" "<<"\n";//wyswietlan nie indeksu z prawej storny planszy
    }

    std::cout << "  ";
    for (int i = 0; i < 8; ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == PieceColor::White) ? PieceColor::Black : PieceColor::White;
}

bool Game::makeMove(int fromX, int fromY, int toX, int toY) {
    Piece* piece = board.getPiece(fromX, fromY);
    if (piece == nullptr || piece->getColor() != currentPlayer) {
        return false;
    }
    return board.movePiece(fromX, fromY, toX, toY);
}
