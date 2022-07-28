#include "Chess.h"
#include <cstdio>
#include <algorithm>

namespace Chess {

ChessPiece::ChessPiece(PieceType piece, Color color, uint8_t horizontal, uint8_t vertical) noexcept
:mPiece(piece)
,mColor(color)
,mHorizontal(horizontal)
,mVertical(vertical)
{}

const char* ChessPiece::GetPieceSymbol() const {
    switch (mPiece)
    {
    case king:
        return mColor == white ? "\u2654" : "\u265A";
    case queen:
        return mColor == white ? "\u2655" : "\u265B";
    case rook:
        return mColor == white ? "\u2656" : "\u265C";
    case bishop:
        return mColor == white ? "\u2657" : "\u265D";
    case knight:
        return mColor == white ? "\u2658" : "\u265E";
    case pawn:
        return mColor == white ? "\u2659" : "\u265F";
    }
    return nullptr;
}

const char ChessBoard::horizontalPos[] = "abcdefgh";

ChessBoard::ChessBoard() {
    for(int i = 0; i < 8; ++i){
        mPieces.push_back(ChessPiece((PieceType::pawn), Color::white, horizontalPos[i], 2));
        mPieces.push_back(ChessPiece((PieceType::pawn), Color::black, horizontalPos[i], 7));
    }
    mPieces.push_back(ChessPiece((PieceType::rook), Color::white, 'a', 1));
    mPieces.push_back(ChessPiece((PieceType::rook), Color::white, 'h', 1));
    mPieces.push_back(ChessPiece((PieceType::rook), Color::black, 'a', 8));
    mPieces.push_back(ChessPiece((PieceType::rook), Color::black, 'h', 8));

    mPieces.push_back(ChessPiece((PieceType::knight), Color::white, 'b', 1));
    mPieces.push_back(ChessPiece((PieceType::knight), Color::white, 'g', 1));
    mPieces.push_back(ChessPiece((PieceType::knight), Color::black, 'b', 8));
    mPieces.push_back(ChessPiece((PieceType::knight), Color::black, 'g', 8));

    mPieces.push_back(ChessPiece((PieceType::bishop), Color::white, 'c', 1));
    mPieces.push_back(ChessPiece((PieceType::bishop), Color::white, 'f', 1));

    mPieces.push_back(ChessPiece((PieceType::bishop), Color::black, 'c', 8));
    mPieces.push_back(ChessPiece((PieceType::bishop), Color::black, 'f', 8));

    mPieces.push_back(ChessPiece((PieceType::queen), Color::white, 'd', 1));
    mPieces.push_back(ChessPiece((PieceType::queen), Color::black, 'd', 8));

    mPieces.push_back(ChessPiece((PieceType::king), Color::white, 'e', 1));
    mPieces.push_back(ChessPiece((PieceType::king), Color::black, 'e', 8));
}

const char *ChessBoard::GetSymbol(int vertical, int horizontal) const {
    auto result = std::find_if(mPieces.begin(), mPieces.end(), [vertical, horizontal](const ChessPiece &p) { 
        return p.getVerticalPos() == vertical && p.getHorizontalPos() == horizontalPos[horizontal-1]; 
        });
    
    if(result != std::end(mPieces))
        return result->GetPieceSymbol();
    
    return (vertical + horizontal) % 2 == 0 ? "\u25A0" : "\u25A1";
    
}

void ChessBoard::PrintChessBoard() const{
    for(int v = 8; v >= 1; --v) {
        putchar('0' + v);
        putchar(' ');
        for(int h = 1; h <= 8; ++h) {
            fprintf(stdout, "%s " , GetSymbol(v, h));
        }
        putchar('\n');
    }
    fputs("  ", stdout);
    for(unsigned int i = 0; i < sizeof(horizontalPos); ++i){
        putchar(horizontalPos[i]);
        putchar(' ');
    }
    putchar('\n');
}

} // Chess