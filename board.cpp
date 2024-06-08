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

    // Sprawdź, czy to było bicie
    int dx = toX - fromX;
    int dy = toY - fromY;
    if (abs(dx) == 2 && abs(dy) == 2) {
        int captureX = fromX + dx / 2;
        int captureY = fromY + dy / 2;
        delete grid[captureX][captureY];
        grid[captureX][captureY] = nullptr;

        // Sprawdzenie podwójnego bicia
        int newToX = toX + (dx / 2);
        int newToY = toY + (dy / 2);
        if (newToX >= 0 && newToX < 8 && newToY >= 0 && newToY < 8) {
            if (isValidMove(toX, toY, newToX, newToY)) {
                movePiece(toX, toY, newToX, newToY);
            }
        }
    }

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


bool Board::isCapture(int fromX, int fromY, int toX, int toY) const {
    int middleX = (fromX + toX) / 2;
    int middleY = (fromY + toY) / 2;
    Piece* middlePiece = grid[middleX][middleY];
    return (middlePiece != nullptr && middlePiece->getColor() != grid[fromX][fromY]->getColor());
}

bool Board::isValidMove(int fromX, int fromY, int toX, int toY) const {
    // Sprawdź, czy pole docelowe mieści się na planszy
    if (toX < 0 || toX >= 8 || toY < 0 || toY >= 8) {
        return false;
    }

    // Sprawdź, czy pole źródłowe i docelowe są różne
    if (fromX == toX && fromY == toY) {
        return false;
    }

    // Sprawdź, czy pole źródłowe zawiera pionka
    Piece* piece = grid[fromX][fromY];
    if (piece == nullptr) {
        return false;
    }

    // Sprawdź, czy pole docelowe jest puste
    if (grid[toX][toY] != nullptr) {
        return false;
    }

    // Określ kierunek ruchu
    int dy = toY - fromY;
    if (piece->getColor() == PieceColor::White && dy >= 0) {
        return false; // Białe pionki mogą poruszać się tylko w dół
    }
    if (piece->getColor() == PieceColor::Black && dy <= 0) {
        return false; // Czarne pionki mogą poruszać się tylko w górę
    }

    // Ruchy pionków typu Man
    if (piece->getType() == PieceType::Man) {
        int dx = toX - fromX;

        // Ruchy o jedno pole w przód
        if (abs(dx) == 1 && abs(dy) == 1) {
            return true;
        }

        // Bicie - ruchy o dwa pola w przód
        if (abs(dx) == 2 && abs(dy) == 2) {
            int captureX = fromX + dx / 2;
            int captureY = fromY + dy / 2;
            Piece* capturePiece = grid[captureX][captureY];
            if (capturePiece != nullptr && capturePiece->getColor() != piece->getColor()) {
                return true;
            }
        }

        // Podwójne bicie - sprawdzenie następnych pól
        if (abs(dx) == 2 && abs(dy) == 2) {
            int middleX = fromX + dx / 2;
            int middleY = fromY + dy / 2;
            Piece* middlePiece = grid[middleX][middleY];
            if (middlePiece != nullptr && middlePiece->getColor() != piece->getColor()) {
                int nextX = toX + (dx / 2);
                int nextY = toY + (dy / 2);
                if (nextX >= 0 && nextX < 8 && nextY >= 0 && nextY < 8 && grid[nextX][nextY] == nullptr) {
                    return true;
                }
            }
        }
    }

    // Ruchy damki (King)
    if (piece->getType() == PieceType::King) {
        // Damka może poruszać się o dowolną liczbę pól po przekątnej, jeśli wszystkie po drodze są puste
        int dx = toX - fromX;
        int dy = toY - fromY;
        if (abs(dx) == abs(dy)) {
            int stepX = dx / abs(dx);
            int stepY = dy / abs(dy);
            int x = fromX + stepX;
            int y = fromY + stepY;
            while (x != toX && y != toY) {
                if (grid[x][y] != nullptr) {
                    return false;
                }
                x += stepX;
                y += stepY;
            }
            return true;
        }

        // Sprawdzenie bicia przez damkę
        if (abs(dx) > 1 && abs(dy) > 1 && abs(dx) == abs(dy)) {
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

    return false; // Ruch nie spełnia żadnych warunków
}





bool Board::isMoveValid(int fromX, int fromY, int toX, int toY) const {
    return isValidMove(fromX, fromY, toX, toY);
}

const std::vector<std::vector<Piece*>>& Board::getBoard() const {
    return grid;
}
