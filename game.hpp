#ifndef ALGO3_GAME_HPP
#define ALGO3_GAME_HPP

#include "board.hpp"

class Game {
public:
    Game();
    void play();

private:
    Board board;
    PieceColor currentPlayer;

    void printBoard();
    void switchPlayer();
    bool makeMove(int fromX, int fromY, int toX, int toY);
};


#endif //ALGO3_GAME_HPP
