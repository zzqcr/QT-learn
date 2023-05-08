#ifndef MANVSAI_H
#define MANVSAI_H

#include <QWidget>
#include "chessboard.h"
#include "ai.h"
class ManVsAI :public ChessBoard
{
    Q_OBJECT
public:
    ManVsAI();
    void init() override;
    void paintEvent( QPaintEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *ev)override;
private:
    bool isBlack = true;// ╨звссеох
    AI ai;
signals:
    void windowClosed();
};

#endif // MANVSAI_H
