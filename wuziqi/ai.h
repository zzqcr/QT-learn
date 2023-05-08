#ifndef AI_H
#define AI_H
#include <QPoint>
#include "chessboard.h"
struct POINTS{//最佳落子位置,[0]分数最高,[9]分数最低
    QPoint pos[10];
    int score[10];//此处落子的局势分数
};
struct DECISION{
    QPoint pos;//位置
    int eval;//对分数的评估
};

class AI
{
public:
    AI();
    QPoint go();
    POINTS seekPoints(QVector<QVector<int>> board);
    DECISION analyse(QVector<QVector<int>>board, int depth);
    int evaluate(int row,int column);
    QVector<QVector<int> > reverseBoard(QVector<QVector<int>> board,QVector<QVector<int>> rBoard);
private:
    QVector<QVector< int>> mBoard;
};

#endif // AI_H
