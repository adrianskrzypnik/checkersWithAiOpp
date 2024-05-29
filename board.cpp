// board.cpp

#include "board.hpp"
#include <iostream>

Board::Board() : grid(8, std::vector<Piece*>(8, nullptr)) {
    setupBoard();
}

Piece* Board::getPiece(int x, int y) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        return nullptr;
    }
    return grid[x][y];
}

Piece* Board::getPieceAt(int x, int y) const {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        return nullptr;
    }
    return grid[x][y];
}

bool Board::movePiece(int fromX, int fromY, int toX, int toY) {
    if (!isMoveValid(fromX, fromY, toX, toY)) {
        return false;
    }
    Piece* piece = grid[fromX][fromY];
    grid[toX][toY] = piece;
    grid[fromX][fromY] = nullptr;

    // Promote to king if reaching the last row
    if (piece->getType() == PieceType::Man && (toY == 0 || toY == 7)) {
        piece->promote();
    }
    return true;
}

void Board::setupBoard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 1) {
                if (j < 3) {
                    grid[i][j] = new Piece(PieceColor::Black, PieceType::Man);
                } else if (j > 4) {
                    grid[i][j] = new Piece(PieceColor::White, PieceType::Man);
                }
            }
        }
    }
}

bool Board::isValidMove(int fromX, int fromY, int toX, int toY) const {
    // Check bounds and move validity
    if (toX < 0 || toX >= 8 || toY < 0 || toY >= 8) return false;
    if (grid[toX][toY] != nullptr) return false;

    Piece* piece = grid[fromX][fromY];
    if (piece == nullptr) return false;

    int dx = toX - fromX;
    int dy = toY - fromY;

    if (piece->getType() == PieceType::Man) {
        if (piece->getColor() == PieceColor::White && dy != -1) return false;
        if (piece->getColor() == PieceColor::Black && dy != 1) return false;
    }

    return (abs(dx) == 1 && abs(dy) == 1);
}

bool Board::isMoveValid(int fromX, int fromY, int toX, int toY) const {
    return isValidMove(fromX, fromY, toX, toY);
}

const std::vector<std::vector<Piece*>>& Board::getBoard() const {
    return grid;
}