#include "game.hpp"
#include <iostream>
#include "ai.hpp"

Game::Game() : currentPlayer(PieceColor::White) {}

void Game::playTwoPlayers() {
    while (true) {
        printBoard();
        int fromX, fromY, toX, toY;
        std::cout << "Player " << (currentPlayer == PieceColor::White ? "White" : "Black") << "'s turn. ";
        std::cout << "Enter move (fromX fromY toX toY): ";
        std::cin >> fromX >> fromY >> toX >> toY;

        if (makeMove(fromX, fromY, toX, toY)) {
            switchPlayer();
        } else {
            std::cout << "Invalid move. Try again.\n";
        }
    }
}

void Game::playWithAI() {
    AI ai;
    while (true) {
        if (currentPlayer == PieceColor::Black) { // AI
            std::pair<int, int> bestMove = ai.getBestMove(board);
            int aiFromX = bestMove.first;
            int aiFromY = bestMove.second;
            int aiToX = bestMove.first + 1; // Przykładowy ruch AI (zmień według potrzeb)
            int aiToY = bestMove.second + 1; // Przykładowy ruch AI (zmień według potrzeb)

            if (board.isMoveValid(aiFromX, aiFromY, aiToX, aiToY)) {
                board.movePiece(aiFromX, aiFromY, aiToX, aiToY);
                switchPlayer();
            } else {
                std::cout << "AI made an invalid move.\n";
                // Dodaj kod obsługujący sytuację, gdy AI wykona nieprawidłowy ruch
            }
        } else { // Gracz
            printBoard();
            int fromX, fromY, toX, toY;
            std::cout << "Player White's turn. Enter move (fromX fromY toX toY): ";
            std::cin >> fromX >> fromY >> toX >> toY;

            if (makeMove(fromX, fromY, toX, toY)) {
                switchPlayer();
            } else {
                std::cout << "Invalid move. Try again.\n";
            }
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
