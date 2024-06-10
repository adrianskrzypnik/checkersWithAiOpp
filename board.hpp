#ifndef ALGO3_BOARD_HPP
#define ALGO3_BOARD_HPP

#include <vector>
#include "piece.hpp"

struct MoveResult {
    bool isValid;
    bool isCapture;
};

class Board {
public:
    Board();
    Piece* getPiece(int x, int y);
    Piece* getPieceAt(int x, int y) const;
    MoveResult movePiece(int fromX, int fromY, int toX, int toY);
    bool isMoveValid(int fromX, int fromY, int toX, int toY) const;
    bool isCapture(int fromX, int fromY, int toX, int toY) const;
    const std::vector<std::vector<Piece*>>& getBoard() const;
    void setupBoard();
    bool canCaptureAgain(int fromX, int fromY) const;
    bool canAnyPieceCapture(PieceColor color) const;

private:
    std::vector<std::vector<Piece*>> grid;
    bool isValidMove(int fromX, int fromY, int toX, int toY) const;
};

#endif //ALGO3_BOARD_HPP