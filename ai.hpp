#ifndef ALGO3_AI_HPP
#define ALGO3_AI_HPP

#include "board.hpp"
#include <utility>

class AI {
public:
    std::pair<int, int> getBestMove(Board& board);

private:
    int minimax(Board& board, int depth, bool maximizingPlayer);
    int evaluate(Board& board);
};

#endif //ALGO3_AI_HPP
