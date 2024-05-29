#ifndef ALGO3_GAME_HPP
#define ALGO3_GAME_HPP

#include "board.hpp"

class Game {
public:
    Game();
    void playTwoPlayers();
    void playWithAI();
private:
    Board board;
    PieceColor currentPlayer;

    void switchPlayer();
    bool makeMove(int fromX, int fromY, int toX, int toY);
    void printBoard();
};


#endif //ALGO3_GAME_HPP
