#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QDebug>
#include <QPixmap>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(400,600);
    this->setWindowTitle("开心打地鼠");


    QPixmap pix;
    pix.load(":/images/start1.png");
    ui->start->setIcon(pix);
    ui->start->setIconSize(QSize(pix.width(),pix.height()));
    ui->start->setFixedSize(QSize(pix.width(),pix.height()));
    ui->start->setStyleSheet("QPushButton{border:0px;}");
    ui->start->move(this->width()*0.5-pix.width()*0.5,270);


    pix.load(":/images/rank_btn.png");
    ui->btn_rank->setIcon(pix);
    ui->btn_rank->setIconSize(QSize(pix.width(),pix.height()));
    ui->btn_rank->setFixedSize(QSize(pix.width(),pix.height()));
    ui->btn_rank->setStyleSheet("QPushButton{border:0px;}");
    ui->btn_rank->move(this->width()-pix.width()-10,480);

    connect(ui->start, &QPushButton::clicked,[=](){
        StartWindow * startWindow = new StartWindow(this);
         this->close();
        startWindow->show();
    });


    connect(ui->shuoming,&QAction::triggered,[=](){
        QMessageBox::about(this,"游戏说明","操控鼠标在30s内取得更高的分数吧！\n游戏作者：赵自强\n游戏版本V1.0");
    });
    connect(ui->tuichu,&QAction::triggered,[=](){
        this->close();

    });

    std::ifstream ifs;
    ifs.open("D:\\c++\\game02\\score.txt");
    if(ifs.is_open()){
        int i =0;
        int s = 0 ;
        while (ifs >> s) {
            score_arr[i] = s;
            i +=1;
        }
    }
    else{
        qDebug() << "暂无记录";
    }
    ifs.close();
    Rank_label *rankwindow = new Rank_label(this);
    rankwindow->close();
    connect(ui->btn_rank,&QPushButton::clicked,[=](){
        std::ifstream ifs;
        ifs.open("D:\\c++\\game02\\score.txt");
        if(ifs.is_open()){
            int i =0;
            int s = 0 ;
            while (ifs >> s) {
                score_arr[i] = s;
                i +=1;
            }
        }
        else{
            qDebug() << "暂无记录";
        }
        ifs.close();
        rankwindow->setRank(score_arr);
        rankwindow->move(100,200);
        rankwindow->show();
    });
}
void MainWindow::paintEvent(QPaintEvent *){
    QPixmap pix;
    pix.load(":/images/forest.png");
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
MainWindow::~MainWindow()
{
    delete ui;
}

