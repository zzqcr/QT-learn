#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include "chess.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#define ChessBoardRow 15
#define ChessBoardColumn 15
const float CellWidth=40;
const float ChessBoardPadding = 25;



class ChessBoard :public QWidget
{
    Q_OBJECT
public:
    ChessBoard();
    virtual void init();
    void play();
    QPoint checkChessPos(QPoint pos); // 检查落子是否有效，如果有效返回落子在第几行第几列
    bool checkWin(int row,int colunm,int chessType);
    void paintEvent( QPaintEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool contains(QRect rect, QPoint pos);
protected:
    QVector<QVector<int>> chessPos; // 记录每个位置是黑子还是白子还是空
    int mWIN = 0;

signals:
    void manCanGo();
    void AICango();
private:



};

#endif // CHESSBOARD_H
