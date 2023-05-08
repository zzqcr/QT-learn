#include "chess.h"

Chess::Chess(QPoint &pos, ChessType type)
{
    mPos = pos;
    mType = type;
}

QPoint Chess::pos()
{
    return mPos;
}

ChessType Chess::type()
{
    return  mType;
}

