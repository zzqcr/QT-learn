#include "lanbattle.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include <QJsonDocument>
#include <QtCore>
#include <QScreen>
#include <QSize>
#include <QGuiApplication>
ChooseRoomWidget::ChooseRoomWidget()
{
    this->resize(350,200);
    this->setWindowTitle("局域网对战");
    btnHost = new MyBtn(this,":/res/host.png");
    btnSlave = new MyBtn(this,":/res/slave.png");
    btnHost->resize(351*0.8,91*0.8);
    btnSlave->resize(351*0.8,91*0.8);
    btnHost->move(40,10);
    btnSlave->move(40,this->height()*0.6);
    slave = new LANBattleSlave;
    host = new LANBattleHost;
    connect(btnHost,&QPushButton::clicked,[=](){  
        host->initServer();
        host->show();
//        this->close();
    });
    connect(btnSlave,&QPushButton::clicked,[=](){
        slave->initwidgetIP();
        this->close();
    });
}

LANBattleSlave *ChooseRoomWidget::getSlave()
{
    return slave;
}

LANBattleHost *ChooseRoomWidget::getHost()
{
    return host;
}

LANBattleHost::LANBattleHost()
{
    socket = new QTcpSocket;
    server = new QTcpServer(this);
    init();
    update();
}

void LANBattleHost::init()
{
    this->setFixedSize(770,610);
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

void LANBattleHost::initServer()
{
    connect(server,&QTcpServer::newConnection,[=](){
        qDebug()<<"新连接";
//        if(isConnect) return ;
        qDebug()<<__func__<<"连接成功";
        QMessageBox::about(nullptr,"提示","玩家二加入");
        socket = server->nextPendingConnection();
        isConnect = true;
        connect(socket,SIGNAL(readyRead()),this,SLOT(readMessage()));
        connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(errorSlot(QAbstractSocket::SocketError)));
        connect(socket,&QTcpSocket::disconnected,[=]{
            isConnect = false;
            reStart();
        });//客户端断开连接时

    });
    if(server->listen(QHostAddress::Any,6666)) qDebug()<<__func__<<"listen ok";


}

void LANBattleHost::reStart()
{

    chessPos.clear();

    for(int i=0;i<ChessBoardRow;i++){
        QVector<int>row;
        for(int j=0;j<ChessBoardColumn;j++){
            row.push_back(0);
        }
        chessPos.push_back(row);
    }
    isBlack = true;  // 判断你是白子还是黑子
    isYourTurn = true;  // 判断当前是不是你的回合
    mWIN=0;
    update();

}

void LANBattleHost::paintEvent(QPaintEvent *ev)
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
    painter.drawImage(QRectF(620,10,149,158),QImage(":/res/renwu.png"));

    painter.drawText(QRectF(620,168,149,50),"玩家一");
    if(isConnect){
        painter.drawImage(QRectF(620,300,149,158),QImage(":/res/renwu.png"));
        painter.drawText(QRectF(620,458,149,50),"玩家二");
    }
}

void LANBattleHost::mousePressEvent(QMouseEvent *ev)
{
    if(!isYourTurn) return;
    if(ev->pos().x()>610) return;
    QPoint point = checkChessPos(ev->pos());
    if(point.x()==-1||point.y()==-1) return;
    if(chessPos[point.x()][point.y()] !=0)return; // 不能重复落子在一个位置
    // 如果是黑子
    if(isBlack){
        chessPos[point.x()][point.y()] = 1;

        if(checkWin(point.x(),point.y(),1)){
            mWIN = 1;

        }
        sendMessage(chessPos);
        showWin();
    }
    // 如果是白子
    else if(!isBlack){
        chessPos[point.x()][point.y()] = 2;

        if(checkWin(point.x(),point.y(),2)){
            mWIN = 2;
        }
        sendMessage(chessPos);
        showWin();
    }
}

void LANBattleHost::mouseReleaseEvent(QMouseEvent *event)
{
    update();
}

void LANBattleHost::closeEvent(QCloseEvent *ev)
{
    server->close();
    socket->close();
    emit windowClosed();
}

void LANBattleHost::sendMessage(QVector<QVector<int> > newChessPos)
{
    isYourTurn = false;
    if(socket->isOpen()){
        QJsonObject json;
        QVector<int> v;
        QJsonArray arr;

        for(int i=0;i<newChessPos.size();i++){
            QJsonArray arr1;
            for(int j=0;j<newChessPos.at(i).size();j++){
                arr1.push_back(newChessPos.at(i).at(j));
            }
            arr.push_back(arr1);
        }
        json.insert("棋子位置",arr);
        json.insert("胜利者",mWIN);
        QJsonDocument jsonDocument;
        jsonDocument.setObject(json);
        socket->write(jsonDocument.toJson());
        socket->flush();
    }
}

void LANBattleHost::showWin()
{
    if(mWIN==0)return;
    else if (mWIN==1) {
        QMessageBox::information(nullptr,"获胜","恭喜黑子获胜");
    }
    else {
        QMessageBox::information(nullptr,"获胜","恭喜白子获胜");
    }
    reStart();
}

void LANBattleHost::readMessage()
{
    if(isALl){
        jsonBytes = socket->readAll();
    }
    else {
        jsonBytes.append(socket->readAll());
    }

    if(jsonBytes.size()<3726){
        isALl = false;
        return;
    }
    else {
        isALl = true;
    }
    qDebug()<<jsonBytes.size();
    QJsonDocument jsonDoc=QJsonDocument::fromJson(jsonBytes);
    qDebug()<<"jsondoc"<<jsonDoc;
    if(jsonDoc.isObject()){
        QJsonObject jsonObject=jsonDoc.object();
        QJsonArray arr = jsonObject["棋子位置"].toArray();
        qDebug()<<arr;
        for(int i=0;i<chessPos.size();i++){
            QJsonArray arr1 = arr[i].toArray();
            for(int j=0;j<chessPos.at(i).size();j++){
                chessPos[i][j] = arr1[j].toInt();
            }
        }

        mWIN = jsonObject["胜利者"].toInt();
    }
    showWin();
    isYourTurn = true;
    update();

}

void LANBattleHost::errorSlot(QAbstractSocket::SocketError)
{
    qDebug()<<"服务器端错误"<<server->errorString();
}

LANBattleSlave::LANBattleSlave()
{
    socket = new QTcpSocket;
    widgetIP = new QWidget;
    lineEdit = new QLineEdit(widgetIP);
    btnOk = new MyBtn(widgetIP,":/res/anniu1.png");
    btnOk->resize(114,29);
    init();
    update();
}

void LANBattleSlave::init()
{
    this->setFixedSize(770,610);
    // 初始化每个位置的棋子为空
    chessPos.clear();

    for(int i=0;i<ChessBoardRow;i++){
        QVector<int>row;
        for(int j=0;j<ChessBoardColumn;j++){
            row.push_back(0);
        }
        chessPos.push_back(row);
    }
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(socket,&QTcpSocket::disconnected,[=]{
        isConnect = false;
//        QMessageBox::about(nullptr,"提示","房间已销毁");
        this->close();
    });//客户端断开连接时

}

void LANBattleSlave::initwidgetIP()
{


    lineEdit->resize(200,29);
    btnOk->move(210,0);
    widgetIP->setWindowFlags(widgetIP->windowFlags()| Qt::WindowStaysOnTopHint);
    widgetIP->setWindowModality(Qt::WindowModality::ApplicationModal);
    widgetIP->setWindowTitle("连接主机");
    QScreen *screen = QGuiApplication::primaryScreen();
    widgetIP->move(screen->size().width()*0.5-150,screen->size().height()*0.4);
    widgetIP->show();

    connect(btnOk,&QPushButton::clicked,[=](){
        mIP = lineEdit->text();
        qDebug()<<"ip"<<mIP;
        socket->connectToHost(mIP,6666);
        if(!socket->waitForConnected(3000)) {
            qDebug()<<"连接失败";
            return ;
        }
        else {
            qDebug()<<"连接成功";
        }
//        isConnect = true;
        widgetIP->close();
        this->show();
    });

}

void LANBattleSlave::reStart()
{
    chessPos.clear();

    for(int i=0;i<ChessBoardRow;i++){
        QVector<int>row;
        for(int j=0;j<ChessBoardColumn;j++){
            row.push_back(0);
        }
        chessPos.push_back(row);
    }
    isBlack = false;  // 判断你是白子还是黑子
    isYourTurn = false;  // 判断当前是不是你的回合
    mWIN=0;
    update();
}



void LANBattleSlave::paintEvent(QPaintEvent *ev)
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
    painter.drawImage(QRectF(620,10,149,158),QImage(":/res/renwu.png"));

    painter.drawText(QRectF(620,168,149,50),"玩家一");
    if(isConnect){
        painter.drawImage(QRectF(620,300,149,158),QImage(":/res/renwu.png"));
        painter.drawText(QRectF(620,458,149,50),"玩家二");
    }
}

void LANBattleSlave::mousePressEvent(QMouseEvent *ev)
{
    if(!isYourTurn) return;
    if(ev->pos().x()>610) return;
    QPoint point = checkChessPos(ev->pos());
    if(point.x()==-1||point.y()==-1) return;
    if(chessPos[point.x()][point.y()] !=0)return; // 不能重复落子在一个位置
    // 如果是黑子
    if(isBlack){
        chessPos[point.x()][point.y()] = 1;

        if(checkWin(point.x(),point.y(),1)){
            mWIN = 1;

        }
        sendMessage(chessPos);
        showWin();
    }
    // 如果是白子
    else if(!isBlack){
        chessPos[point.x()][point.y()] = 2;

        if(checkWin(point.x(),point.y(),2)){
            mWIN = 2;
        }
        sendMessage(chessPos);
        showWin();
    }
}

void LANBattleSlave::mouseReleaseEvent(QMouseEvent *event)
{
    update();
}

void LANBattleSlave::closeEvent(QCloseEvent *ev)
{

    socket->close();
    emit windowClosed();
}

void LANBattleSlave::sendMessage(QVector<QVector<int> > newChessPos)
{
    isYourTurn = false;
    if(socket->isOpen()){
        QJsonObject json;
        QVector<int> v;
        QJsonArray arr;

        for(int i=0;i<newChessPos.size();i++){
            QJsonArray arr1;
            for(int j=0;j<newChessPos.at(i).size();j++){
                arr1.push_back(newChessPos.at(i).at(j));
            }
            arr.push_back(arr1);
        }
        json.insert("棋子位置",arr);
        json.insert("胜利者",mWIN);
        QJsonDocument jsonDocument;
        jsonDocument.setObject(json);
        socket->write(jsonDocument.toJson());
        socket->flush();
    }
}

void LANBattleSlave::showWin()
{
    if(mWIN==0)return;
    else if (mWIN==1) {
        QMessageBox::information(nullptr,"获胜","恭喜黑子获胜");
    }
    else {
        QMessageBox::information(nullptr,"获胜","恭喜白子获胜");
    }
    reStart();
}

void LANBattleSlave::readMessage()
{
    if(isALl){
        jsonBytes = socket->readAll();
    }
    else {
        jsonBytes.append(socket->readAll());
    }

    if(jsonBytes.size()<3726){
        isALl = false;
        return;
    }
    else {
        isALl = true;
    }

    QJsonDocument jsonDoc=QJsonDocument::fromJson(jsonBytes);
    if(jsonDoc.isObject()){
        QJsonObject jsonObject=jsonDoc.object();
        QJsonArray arr = jsonObject["棋子位置"].toArray();

        for(int i=0;i<chessPos.size();i++){
            QJsonArray arr1 = arr[i].toArray();
            for(int j=0;j<chessPos.at(i).size();j++){
                chessPos[i][j] = arr1[j].toInt();
            }
        }

        mWIN = jsonObject["胜利者"].toInt();
    }
    showWin();
    update();
    isYourTurn = true;

}
