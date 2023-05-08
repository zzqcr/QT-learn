#ifndef CHESS_H
#define CHESS_H
#include <QPoint>
#include <QObject>

enum ChessType{
    CHESS_EMPTY = 0,
    CHESS_BLACK = 1,
    CHESS_WHITE = 2,
};
class Chess
{

public:
    Chess(QPoint &pos,ChessType type);
    QPoint pos();
    ChessType type();

private:
    QPoint mPos;
    ChessType mType;

};

#endif // CHESS_H
