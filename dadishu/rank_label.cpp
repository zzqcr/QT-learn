#include "rank_label.h"
#include <QPixmap>
#include <QPushButton>
Rank_label::Rank_label(QWidget *parent) : QWidget(parent)
{

    this->setWindowTitle("排行榜");
    QPixmap pix;


    pix.load(":/images/ranks.png");
    QLabel * label = new QLabel(this);
    label->setPixmap(pix);
    label->setFixedSize(pix.width(),pix.height());
    label->move(0,0);
    pix.load(":/images/rank.png");
    this->setFixedSize(200,pix.height()*5+50);
    for(int i=0;i<5;i++){
//        label_list[i]->setPixmap(pix);
//        label_list[i]->setFixedSize(pix.width(),pix.height());
        label_list[i]->setFont(QFont("宋体",18,87));
        label_list[i]->move(20,pix.height()*i+5);

    }

    QPixmap pix2;
    pix2.load(":/images/back.png");
    QPushButton * back= new QPushButton(this);
    back->setIcon(pix2);
    back->setIconSize(QSize(pix2.width(),pix2.height()));
    back->setFixedSize(QSize(pix2.width(),pix2.height()));
    back->setStyleSheet("QPushButton{border:0px;}");
    back->move(this->width()-back->width(),pix.height()*5);
    connect(back,&QPushButton::clicked,[=](){
        this->close();
    });

}

void Rank_label::setRank(int score[5]){
    for(int i=0;i<5;i++){
        label_list[i]->raise();
        label_list[i]->setText(QString("第"+QString::number(i+1)+"名:"+QString::number(score[4-i])+"分"));
    }
}
