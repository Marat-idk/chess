#include "Chess.h"
#include <cstdio>
#include <algorithm>
#include <unistd.h>
#include <iostream>
#include <limits>

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

bool ChessPiece::MoveTo(char horizontal, uint8_t vertical) {
    bool flag = false;
    switch (mPiece)
    {
    case pawn:
        if(mHorizontal == horizontal && vertical - mVertical > 0 && vertical - mVertical <= 2){
            mHorizontal = horizontal;
            mVertical = vertical;
            flag = true;
        }
        break;
    default:
        break;
    }
    return flag;
}

const char ChessBoard::horizontalPos[] = "abcdefgh";

ChessBoard::ChessBoard()
:mHorizontal(0)
,mVertical(0)
{
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

void ChessBoard::StartGame() {
    bool isGameEnded = false;
    ChessPiece *pPiece = nullptr;
    while(!isGameEnded) {
        PrintChessBoard();
        pPiece = PickPiece();
        GetMove();
        if(!(IsMoveLegal(mHorizontal, mVertical) && pPiece->MoveTo(mHorizontal, mVertical)))
           break;;
        sleep(2);
        isGameEnded = true; // MARK: must be deleted
    }
    PrintChessBoard();
}

ChessPiece *ChessBoard::GetChessPiece(char horizontal, int vertical) {
    auto result = std::find_if(mPieces.begin(), mPieces.end(), [vertical, horizontal](ChessPiece &p) {
       return p.getVerticalPos() == vertical && p.getHorizontalPos() == horizontal; 
    });
    return (result != mPieces.end()) ? &(*result) : nullptr;
}

const char *ChessBoard::GetSymbol(char horizontal, int vertical) {
    const ChessPiece *pChessPiece = GetChessPiece(horizontal, vertical);
    
    if(pChessPiece)
        return pChessPiece->GetPieceSymbol();
    
    return (vertical + horizontal) % 2 == 0 ? "\u25A0" : "\u25A1";
    
}

bool ChessBoard::IsMoveLegal(char horizontal, int vertical) {
    return GetChessPiece(horizontal, vertical) == nullptr;                  // если вернулось nullptr, значит на такой позиции нет элемента
}

void ChessBoard::PrintChessBoard() {
    puts("\033[2J\033[1;1H");
    for(int v = 8; v >= 1; --v) {
        putchar('0' + v);
        putchar(' ');
        for(int h = 1; h <= 8; ++h) {
            fprintf(stdout, "%s " , GetSymbol(horizontalPos[h-1], v));
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

ChessPiece *ChessBoard::PickPiece() {
    ChessPiece *pChessPiece = nullptr;
    while(!pChessPiece) {
        fputs("Choose your piece: ", stdout);
        char h;
        int v;
        h = fgetc(stdin);
        v = fgetc(stdin);
        v -= '0';
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        pChessPiece = GetChessPiece(h, v);
    }
    return pChessPiece;
}

bool ChessBoard::GetMove() {
    do{
        fputs("Choose piece move: ", stdout);
        mHorizontal = fgetc(stdin);
        mVertical = fgetc(stdin);
        mVertical -= '0';
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    }while(mHorizontal < 'a' || mHorizontal > 'h' || mVertical < 1 || mVertical > 8);
}

} // Chess