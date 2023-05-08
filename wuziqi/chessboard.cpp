#include "chessboard.h"
#include <QRect>
#include <QDebug>
#include <QMessageBox>
ChessBoard::ChessBoard()
{
    init();
    update();
}

void ChessBoard::init()
{
    this->setFixedSize(700,610);
    // 初始化每个位置的棋子为空
    chessPos.clear();
    for(int i=0;i<ChessBoardRow;i++){
        QVector<int>row;
        for(int j=0;j<ChessBoardColumn;j++){
            row.push_back(0);
        }
        chessPos.push_back(row);
    }

}

void ChessBoard::play()
{

}

QPoint ChessBoard::checkChessPos(QPoint pos)
{
    QRect chessRect(pos.x()-CellWidth*0.4,pos.y()-CellWidth*0.4,CellWidth*0.8,CellWidth*0.8);
    int left = (pos.x()-ChessBoardPadding)/CellWidth;
    int right = left+1;
    int top = (pos.y()-ChessBoardPadding)/CellWidth;
    int bottom = top+1;
    if(contains(chessRect ,QPoint(left*CellWidth+ChessBoardPadding,top*CellWidth+ChessBoardPadding))){
        return QPoint(top,left);
    }
    else if(contains(chessRect ,QPoint(left*CellWidth+ChessBoardPadding,bottom*CellWidth+ChessBoardPadding))){
        return QPoint(bottom,left);
    }
    else if (contains(chessRect ,QPoint(right*CellWidth+ChessBoardPadding,top*CellWidth+ChessBoardPadding))) {
        return QPoint(top,right);
    }
    else if (contains(chessRect ,QPoint(right*CellWidth+ChessBoardPadding,bottom*CellWidth+ChessBoardPadding))) {
        return QPoint(bottom,right);
    }
    else {
        return QPoint(-1,-1);
    }
}

bool ChessBoard::checkWin(int row, int colunm, int chessType)
{
    //判断水平方向有没有赢
    int start = colunm -4;
    if(start<0) start=0;
    int end = colunm+4;
    if(end>14)end=14;
    int num =0;
    for(int i=start;i<=end-4;i++){
        for(int j=i;j<=end;j++){

            if(chessType == chessPos[row][j]){
                num+=1;
                if(num==5){
                    return true;
                }

            }
            else {
                i=j;
                num =0;
            }

        }
    }

    // 判断垂直方向有没有赢
    start = row -4;
    if(start<0) start=0;
    end = row+4;
    if(end>14)end=14;
    num =0;
    for(int i=start;i<=end-4;i++){
        for(int j=i;j<=end;j++){

            if(chessType == chessPos[j][colunm]){
                num+=1;
                if(num==5){
                    return true;
                }

            }
            else {
                i=j;
                num =0;
            }

        }
    }

    //判断“\”斜角有没有获胜

    for(int i=0;i<5;i++){
        for(int j=i;j>i-5;j--){
            if(row+j<0)break;
            if(colunm+j<0)break;
            if(row+j>14)break;
            if(colunm+j>14)break;

            if(chessPos[row+j][colunm+j]==chessType){
                num+=1;
                if(num==5)return true;
            }
            else {
                num=0;
                break;
            }

        }
    }
    //判断“/”斜角有没有获胜

    for(int i=0;i<5;i++){
        for(int j=i;j>i-5;j--){
            if(row-j<0)break;
            if(colunm+j<0)break;
            if(row-j>14)break;
            if(colunm+j>14)break;
            if(chessPos[row-j][colunm+j]==chessType){
                num+=1;
                if(num==5)return true;
            }
            else {
                num=0;
                break;
            }

        }
    }
    return false;

}



void ChessBoard::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    painter.drawImage(QRectF(0,0,610,610),QImage(":/res/qipan.png"));

}

void ChessBoard::mousePressEvent(QMouseEvent *ev)
{

}

void ChessBoard::mouseReleaseEvent(QMouseEvent *event)
{
    update();

}

bool ChessBoard::contains(QRect rect, QPoint pos)
{
    if(pos.x()>=rect.x() &&pos.x()<=rect.x()+rect.width() && pos.y()>=rect.y()&&pos.y()<=rect.y()+rect.height()){
        return true;
    }
    else {

        return false;
    }
}

