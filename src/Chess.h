#pragma once

#include <cstdint>

namespace Chess {

enum Color {
    black,
    white
};

enum PieceType {
    pawn,               // Пешка
    knight,             // Конь
    bishop,             // Слон
    rook,               // Ладья
    queen,              // Ферзь
    king                // Король
};

class ChessPiece {
private:
    PieceType mPiece;
    Color mColor;
    uint8_t mHorizontal;
    uint8_t mVertical;

public:
    ChessPiece() = delete;
    ChessPiece(const PieceType& piece) = delete;
    ChessPiece(PieceType&& piece) = delete;
    ChessPiece& operator=(const PieceType& piece) = delete;
    ChessPiece& operator=(PieceType&& piece) = delete;

    ChessPiece(PieceType piece, Color color, uint8_t horizontal, uint8_t vertical) noexcept;


    void MoveTo(char horizontal, uint8_t vertical);
    
    const char *GetPieceSymbol() const;
};

}   // Chess