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
    char mHorizontal;
    uint8_t mVertical;
public:
    ChessPiece() = delete;
    ChessPiece(const PieceType& piece) = delete;
    ChessPiece(PieceType&& piece) = delete;
    ChessPiece& operator=(const PieceType& piece) = delete;
    ChessPiece& operator=(PieceType&& piece) = delete;

    ChessPiece(PieceType piece, Color color, uint8_t horizontal, uint8_t vertical) noexcept;

    inline char getHorizontalPos() const { return mHorizontal; }
    inline uint8_t getVerticalPos() const { return mVertical; }

    // возвращает false, если ход не допустим для фигуры
    // иначе - перемещает фигуру и возвращает true
    bool MoveTo(char horizontal, uint8_t vertical);
    
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

    void StartGame();

    const char *GetSymbol(int vertical, int horizontal) const;

    // проверка, явялется ли ход допустимым для данной фигуры
    bool IsMoveLegal(int vertical, int horizontal) const;

    void PrintChessBoard() const;

    // удаление фигуры из вектора, если она была съедена
    void DeletePiece(int vertical, int horizontal);
};

}   // Chess