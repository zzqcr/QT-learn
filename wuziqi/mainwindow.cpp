#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("五子棋对战");
    btnBenDi = new MyBtn(this,":/res/bendi.png");
    btnJvYuWang = new MyBtn(this,":/res/jvyuwang.png");
    btnHuLianWang = new MyBtn(this,":/res/hulianwang.png");
    btnRenJi = new MyBtn(this,":/res/renji.png");
    btnWenHao = new MyBtn(this,":/res/wenhao.png");


    initWindow();
    connects();

}

void MainWindow::resizeEvent(QResizeEvent *ev)
{

}

void MainWindow::initWindow()
{

    this->setFixedSize(QSize(780,900));
    QLabel * background = new QLabel(this);
    background->setPixmap(QPixmap(":/res/beijing.jpeg"));
    background->resize(this->size());
    background->lower();


    btnBenDi->resize(351*0.7,197*0.7);
    btnJvYuWang->resize(351*0.7,197*0.7);
    btnHuLianWang->resize(351*0.7,197*0.7);
    btnRenJi->resize(351*0.7,197*0.7);
    btnWenHao->resize(52,56);


    btnBenDi->move(this->width()*0.5-150,this->height()*0.2);
    btnJvYuWang->move(this->width()*0.5-150,this->height()*0.4);
    btnHuLianWang->move(this->width()*0.5-150,this->height()*0.6);
    btnRenJi->move(this->width()*0.5-150,this->height()*0.8);
    btnWenHao->move(680,800);
}

void MainWindow::connects()
{
    connect(btnBenDi,&MyBtn::clicked,[=](){
        btnBenDi->zoom();
        ManVsMan *benDiChessBoard = new ManVsMan;

        connect(benDiChessBoard,&ManVsMan::windowClosed,[=](){
            this->show();
        });
        QTimer::singleShot(500,this,[=](){
            benDiChessBoard->show();
            this->hide();
        });

    });

    connect(btnJvYuWang,&MyBtn::clicked,[=](){
        btnJvYuWang->zoom();
        ChooseRoomWidget *chooseRoomWidget = new ChooseRoomWidget;

        connect(chooseRoomWidget->getHost(),&LANBattleHost::windowClosed,[=](){
            this->show();
        });
        connect(chooseRoomWidget->getSlave(),&LANBattleSlave::windowClosed,[=](){
            this->show();
        });
        QTimer::singleShot(500,this,[=](){
            chooseRoomWidget->show();
            this->hide();
        });

    });

    connect(btnRenJi,&MyBtn::clicked,[=](){
        btnRenJi->zoom();
        ManVsAI * AIChessBoard = new ManVsAI;

        connect(AIChessBoard,&ManVsAI::windowClosed,[=](){
            this->show();
        });
        QTimer::singleShot(500,this,[=](){
            AIChessBoard->show();
            this->hide();
        });

    });

    connect(btnWenHao,&MyBtn::clicked,[=](){
        btnWenHao->zoom();
        QTimer::singleShot(500,this,[=](){
            QMessageBox::about(nullptr,"帮助","-------------------   \n"
                                            "---版本：1.0.0---   \n"
                                            "---作者：ZZQ ---   \n"
                                            "-------------------   ");
        });

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}




