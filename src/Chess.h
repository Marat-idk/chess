#pragma once

#include <cstdint>
#include <vector>

namespace Chess {

enum Color {
    black,
    white
};

enum PieceType {
    king,               // Король
    queen,              // Ферзь
    rook,               // Ладья
    bishop,             // Слон
    knight,             // Конь
    pawn                // Пешка
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

class ChessBoard {
private:
    std::vector<ChessPiece> mPieces;

    static const char horizontalPos[];
public:
    ChessBoard();
    ChessBoard(const ChessBoard& piece) = delete;
    ChessBoard(ChessBoard&& piece) = delete;
    ChessBoard& operator=(const ChessBoard& piece) = delete;
    ChessBoard& operator=(ChessBoard&& piece) = delete;

    void PrintChessBoard() const;
};

}   // Chess