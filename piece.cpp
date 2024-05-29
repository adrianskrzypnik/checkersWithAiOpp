// piece.cpp

#include "piece.hpp"

Piece::Piece(PieceColor color, PieceType type) : color(color), type(type) {}

PieceColor Piece::getColor() const {
    return color;
}

PieceType Piece::getType() const {
    return type;
}

void Piece::promote() {
    if (type == PieceType::Man) {
        type = PieceType::King;
    }
}
