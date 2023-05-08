#ifndef AI_H
#define AI_H
#include <QPoint>
#include "chessboard.h"
struct POINTS{//�������λ��,[0]�������,[9]�������
    QPoint pos[10];
    int score[10];//�˴����ӵľ��Ʒ���
};
struct DECISION{
    QPoint pos;//λ��
    int eval;//�Է���������
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
