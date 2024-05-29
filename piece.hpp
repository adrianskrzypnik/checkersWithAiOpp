#ifndef ALGO3_PIECE_HPP
#define ALGO3_PIECE_HPP

enum class PieceType { Man, King };
enum class PieceColor { Black, White };

class Piece {
public:
    Piece(PieceColor color, PieceType type);

    PieceColor getColor() const;
    PieceType getType() const;
    void promote();

private:
    PieceColor color;
    PieceType type;
};

#endif //ALGO3_PIECE_HPP
