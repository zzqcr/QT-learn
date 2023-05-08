#include "manvsman.h"
#include <QMessageBox>
#include <QDebug>
ManVsMan::ManVsMan()
{
    init();
    update();
}

void ManVsMan::init()
{
    this->setFixedSize(610,610);
    // 初始化每个位置的棋子为空
    chessPos.clear();
    isBlack = true;
    for(int i=0;i<ChessBoardRow;i++){
        QVector<int>row;
        for(int j=0;j<ChessBoardColumn;j++){
            row.push_back(0);
        }
        chessPos.push_back(row);
    }

}

void ManVsMan::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);

    painter.drawImage(QRectF(0,0,610,610),QImage(":/res/qipan.png"));
    for(int i=0;i<chessPos.size();i++){
        for(int j=0;j<chessPos.at(i).size();j++){
            if(chessPos.at(i).at(j)==1){
                painter.drawImage(QRectF(j*CellWidth-22+ChessBoardPadding,i*CellWidth-22+ChessBoardPadding,44,44),QImage(":/res/heizi.png"));
            }
            else if (chessPos.at(i).at(j)==2) {
                painter.drawImage(QRectF(j*CellWidth-22+ChessBoardPadding,i*CellWidth-22+ChessBoardPadding,44,44),QImage(":/res/baizi.png"));

            }
        }
    }
}

void ManVsMan::mousePressEvent(QMouseEvent *ev)
{
    if(ev->pos().x()>610) return;
    QPoint point = checkChessPos(ev->pos());

    if(point.x()==-1||point.y()==-1) return;
    if(chessPos[point.x()][point.y()] !=0)return; // 不能重复落子在一个位置
    if(point.x()!=-1&&point.y()!=-1 && isBlack){
        chessPos[point.x()][point.y()] = 1;
        if(checkWin(point.x(),point.y(),1)){
            mWIN = 1;
            QMessageBox::information(nullptr,"获胜","恭喜黑子获胜");
            init();
            return;

        }
        isBlack =!isBlack;
    }
    else if(point.x()!=-1&&point.y()!=-1 && !isBlack){
        chessPos[point.x()][point.y()] = 2;
        if(checkWin(point.x(),point.y(),2)){
            mWIN = 2;
            QMessageBox::information(nullptr,"获胜","恭喜白子获胜");
            init();
            return;
        }
        isBlack =!isBlack;
    }
}

void ManVsMan::mouseReleaseEvent(QMouseEvent *event)
{
    update();
}

void ManVsMan::closeEvent(QCloseEvent *ev)
{
    emit windowClosed();
}
