#ifndef MANVSMAN_H
#define MANVSMAN_H

#include <QWidget>
#include "chessboard.h"

// 本地双人对战
class ManVsMan :public ChessBoard
{
    Q_OBJECT
public:
    ManVsMan();
    void init() override;
    void paintEvent( QPaintEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *ev)override;
private:
    bool isBlack = true;// 黑子优先
signals:
    void windowClosed();

};

#endif // MANVSMAN_H
