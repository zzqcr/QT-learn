#ifndef LANBATTLE_H
#define LANBATTLE_H

#include <QWidget>
#include "mybtn.h"
#include "chessboard.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QLineEdit>
#include <QHBoxLayout>
class LANBattleHost;
class LANBattleSlave;
class ChooseRoomWidget :public QWidget
{
  Q_OBJECT
public:
    ChooseRoomWidget();
    LANBattleSlave *getSlave();
    LANBattleHost *getHost();

private:
    MyBtn * btnHost;
    MyBtn * btnSlave;
    LANBattleSlave *slave;
    LANBattleHost *host;

};

class LANBattleHost : public ChessBoard
{
    Q_OBJECT
public:
    LANBattleHost();
    void init() override;

    void initServer();
    void reStart();
    void paintEvent( QPaintEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *ev)override;

    void showWin();


public slots:
    void errorSlot(QAbstractSocket::SocketError);
    void sendMessage(QVector<QVector<int>> newChessPos);
    void readMessage();
signals:
    void windowClosed();
private:
    bool isBlack = true;  // 判断你是白子还是黑子
    bool isYourTurn = true;  // 判断当前是不是你的回合
    bool isConnect = false; // 判断是不是正在连接
    QTcpSocket * socket;
    QTcpServer * server;
    QByteArray jsonBytes;
    bool isALl = true;
};

class LANBattleSlave :public ChessBoard
{
    Q_OBJECT
public:
    LANBattleSlave();
    void init() override;
    void initwidgetIP();
    void reStart();
    void paintEvent( QPaintEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *ev)override;


    void showWin();


public slots:
    void readMessage();
    void sendMessage(QVector<QVector<int>> newChessPos);
signals:
    void windowClosed();
private:
    bool isBlack = false;  // 判断你是白子还是黑子
    bool isYourTurn = false;  // 判断当前是不是你的回合
    bool isConnect; // 判断是不是正在连接
    QByteArray jsonBytes;
    bool isALl = true;
    QString mIP;
    QTcpSocket * socket;
    QWidget * widgetIP;
    QLineEdit *lineEdit;
    MyBtn * btnOk;
};


#endif // LANBATTLE_H
