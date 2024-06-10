// AI.cpp

#include "ai.hpp"
#include <limits>

std::pair<int, int> AI::getBestMove(Board& board) {
    std::pair<int, int> bestMove;
    int bestValue = std::numeric_limits<int>::min();
    int depth = 3; // głębokość przeszukiwania drzewa gry

    auto possibleMoves = board.getAllPossibleMoves(); // Załóżmy, że ta funkcja zwraca możliwe ruchy

    for (const auto& move : possibleMoves) {
        board.makeMove(move);
        int value = minimax(board, depth, false); // AI jest graczem minimalizującym
        board.undoMove(move);

        if (value > bestValue) {
            bestValue = value;
            bestMove = move;
        }
    }

    return bestMove;
}

int AI::minimax(Board& board, int depth, bool maximizingPlayer) {
    if (depth == 0 || board.isGameOver()) {
        return evaluate(board);
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        auto possibleMoves = board.getAllPossibleMoves();
        for (const auto& move : possibleMoves) {
            board.makeMove(move);
            int eval = minimax(board, depth - 1, false);
            board.undoMove(move);
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        auto possibleMoves = board.getAllPossibleMoves();
        for (const auto& move : possibleMoves) {
            board.makeMove(move);
            int eval = minimax(board, depth - 1, true);
            board.undoMove(move);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}

int AI::evaluate(Board& board) {
    // Prosta funkcja oceny, która przydziela punkty na podstawie pozycji pionków na planszy
    int whiteScore = board.countWhitePieces();
    int blackScore = board.countBlackPieces();
    return whiteScore - blackScore;
}
