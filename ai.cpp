// ai.cpp

#include "ai.hpp"

std::pair<int, int> AI::getBestMove(Board& board) {
    int bestValue = -10000;
    std::pair<int, int> bestMove;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board.getPieceAt(i, j);
            if (piece != nullptr && piece->getColor() == PieceColor::White) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        if (board.isMoveValid(i, j, x, y)) {
                            Board tempBoard = board;
                            tempBoard.movePiece(i, j, x, y);
                            int moveValue = minimax(tempBoard, 0, false, -10000, 10000);
                            if (moveValue > bestValue) {
                                bestValue = moveValue;
                                bestMove = {i, j};
                            }
                        }
                    }
                }
            }
        }
    }
    return bestMove;
}

int AI::minimax(Board& board, int depth, bool maximizingPlayer, int alpha, int beta) {
    if (depth == 3) {
        return evaluateBoard(board);
    }

    if (maximizingPlayer) {
        int maxEval = -10000;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Piece* piece = board.getPieceAt(i, j);
                if (piece != nullptr && piece->getColor() == PieceColor::White) {
                    for (int x = 0; x < 8; ++x) {
                        for (int y = 0; y < 8; ++y) {
                            if (board.isMoveValid(i, j, x, y)) {
                                Board tempBoard = board;
                                tempBoard.movePiece(i, j, x, y);
                                int eval = minimax(tempBoard, depth + 1, false, alpha, beta);
                                maxEval = std::max(maxEval, eval);
                                alpha = std::max(alpha, eval);
                                if (beta <= alpha) {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        return maxEval;
    } else {
        int minEval = 10000;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Piece* piece = board.getPieceAt(i, j);
                if (piece != nullptr && piece->getColor() == PieceColor::Black) {
                    for (int x = 0; x < 8; ++x) {
                        for (int y = 0; y < 8; ++y) {
                            if (board.isMoveValid(i, j, x, y)) {
                                Board tempBoard = board;
                                tempBoard.movePiece(i, j, x, y);
                                int eval = minimax(tempBoard, depth + 1, true, alpha, beta);
                                minEval = std::min(minEval, eval);
                                beta = std::min(beta, eval);
                                if (beta <= alpha) {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        return minEval;
    }
}

int AI::evaluateBoard(const Board& board) {
    int score = 0;
    for (const auto& row : board.getBoard()) {
        for (const auto& piece : row) {
            if (piece != nullptr) {
                if (piece->getColor() == PieceColor::White) {
                    score += (piece->getType() == PieceType::King) ? 5 : 1;
                } else {
                    score -= (piece->getType() == PieceType::King) ? 5 : 1;
                }
            }
        }
    }
    return score;
}
