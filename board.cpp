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



MoveResult Board::movePiece(int fromX, int fromY, int toX, int toY) {
    MoveResult result;
    result.isValid = false;
    result.isCapture = false;

    if (!isValidMove(fromX, fromY, toX, toY)) {
        return result;
    }

    Piece* piece = grid[fromX][fromY];
    grid[toX][toY] = piece;
    grid[fromX][fromY] = nullptr;

    int dx = toX - fromX;
    int dy = toY - fromY;

    if (piece->getType() == PieceType::Man) {
        if (abs(dx) == 2 && abs(dy) == 2) {
            int captureX = fromX + dx / 2;
            int captureY = fromY + dy / 2;
            delete grid[captureX][captureY];
            grid[captureX][captureY] = nullptr;
            result.isCapture = true;
        }
    }

    if (piece->getType() == PieceType::King) {
        if (abs(dx) == abs(dy)) {
            int stepX = dx / abs(dx);
            int stepY = dy / abs(dy);
            int x = fromX + stepX;
            int y = fromY + stepY;
            bool hasCaptured = false;
            while (x != toX && y != toY) {
                if (grid[x][y] != nullptr) {
                    if (hasCaptured || grid[x][y]->getColor() == piece->getColor()) {
                        return result; // Invalid move if the king tries to capture more than one piece
                    }
                    delete grid[x][y];
                    grid[x][y] = nullptr;
                    result.isCapture = true;
                    hasCaptured = true;
                }
                x += stepX;
                y += stepY;
            }
        }
    }

    if (piece->getType() == PieceType::Man && (toY == 0 || toY == 7)) {
        piece->promote();
    }

    result.isValid = true;
    return result;
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
    if (toX < 0 || toX >= 8 || toY < 0 || toY >= 8) {
        return false;
    }

    if (fromX == toX && fromY == toY) {
        return false;
    }

    Piece* piece = grid[fromX][fromY];
    if (piece == nullptr) {
        return false;
    }

    if (grid[toX][toY] != nullptr) {
        return false;
    }

    int dx = toX - fromX;
    int dy = toY - fromY;

    if (piece->getType() == PieceType::Man) {
        if (piece->getColor() == PieceColor::White && dy >= 0) {
            return false;
        }
        if (piece->getColor() == PieceColor::Black && dy <= 0) {
            return false;
        }

        if (abs(dx) == 1 && abs(dy) == 1) {
            return true;
        }

        if (abs(dx) == 2 && abs(dy) == 2) {
            int captureX = fromX + dx / 2;
            int captureY = fromY + dy / 2;
            Piece* capturePiece = grid[captureX][captureY];
            if (capturePiece != nullptr && capturePiece->getColor() != piece->getColor()) {
                return true;
            }
        }
    }

    if (piece->getType() == PieceType::King) {
        if (abs(dx) == abs(dy)) {
            int stepX = dx / abs(dx);
            int stepY = dy / abs(dy);
            int x = fromX + stepX;
            int y = fromY + stepY;
            bool hasCaptured = false;
            while (x != toX && y != toY) {
                if (grid[x][y] != nullptr) {
                    if (hasCaptured || grid[x][y]->getColor() == piece->getColor()) {
                        return false;
                    }
                    hasCaptured = true;
                }
                x += stepX;
                y += stepY;
            }
            return true;
        }
    }

    return false;
}


bool Board::canCaptureAgain(int fromX, int fromY) const {
    Piece* piece = grid[fromX][fromY];
    if (piece == nullptr) {
        return false;
    }


    for (int i = 0; i < 8; ++i) {
        if (piece->getType() == PieceType::Man) {
            int directions[4][2] = {{-2, -2}, {-2, 2}, {2, -2}, {2, 2}};
            int toX = fromX + directions[i][0];
            int toY = fromY + directions[i][1];
            if (isValidMove(fromX, fromY, toX, toY) && isCapture(fromX, fromY, toX, toY)) {
                return true;
            }
            if (i>5){
                break;
            }
        }
        if (piece->getType() == PieceType::King) {
            int directions[8][2] = {{-2, -2}, {-2, 2}, {2, -2}, {2, 2}, {-3, -3}, {-3, 3}, {3, -3}, {3, 3}};
            int stepX = directions[i][0];
            int stepY = directions[i][1];
            int x = fromX + stepX;
            int y = fromY + stepY;
            while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                if (isCapture(fromX, fromY, x, y)) {
                    return true;
                }
                if (grid[x][y] != nullptr) {
                    break;
                }
                x += stepX;
                y += stepY;
            }
        }
    }
    return false;
}



bool Board::isCapture(int fromX, int fromY, int toX, int toY) const {
    Piece* piece = grid[fromX][fromY];
    if (piece == nullptr || grid[toX][toY] != nullptr) {
        return false;
    }

    int middleX = (fromX + toX) / 2;
    int middleY = (fromY + toY) / 2;
    Piece* middlePiece = grid[middleX][middleY];
    if (middlePiece == nullptr || middlePiece->getColor() == piece->getColor()) {
        return false;
    }

    if (piece->getType() == PieceType::Man) {
        int dx = toX - fromX;
        int dy = toY - fromY;
        if (abs(dx) == 2 && abs(dy) == 2) {
            return true;
        }
    } else if (piece->getType() == PieceType::King) {
        int dx = toX - fromX;
        int dy = toY - fromY;
        if (abs(dx) == abs(dy)) {
            int stepX = dx / abs(dx);
            int stepY = dy / abs(dy);
            int x = fromX + stepX;
            int y = fromY + stepY;
            bool hasCaptured = false;
            while (x != toX && y != toY) {
                if (grid[x][y] != nullptr) {
                    if (hasCaptured || grid[x][y]->getColor() == piece->getColor()) {
                        return false;
                    }
                    hasCaptured = true;
                }
                x += stepX;
                y += stepY;
            }
            return hasCaptured;
        }
    }
    return false;
}


bool Board::canAnyPieceCapture(PieceColor color) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = grid[i][j];
            if (piece != nullptr && piece->getColor() == color) {
                if (canCaptureAgain(i, j)) {
                    return true;
                }
            }
        }
    }
    return false;
}



bool Board::isMoveValid(int fromX, int fromY, int toX, int toY) const {
    return isValidMove(fromX, fromY, toX, toY);
}

const std::vector<std::vector<Piece*>>& Board::getBoard() const {
    return grid;
}