#include "hammer.h"
#include <QTimer>
#include <QDebug>
Hammer::Hammer()
{
    pix.load(str_list[0]);
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setFixedSize(pix.width(),pix.height());//设置按钮大小
    this->setStyleSheet("QPushButton{border:0px;}");

}

void Hammer::change1(){
    this->show();
    this->raise();
    qDebug() << "敲"  ;
    pix.load(str_list[1]);
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setFixedSize(pix.width(),pix.height());//设置按钮大小
    this->setStyleSheet("QPushButton{border:0px;}");


}
void Hammer::change2(){
    qDebug() <<"起来";

    pix.load(str_list[0]);
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setFixedSize(pix.width(),pix.height());//设置按钮大小
    this->setStyleSheet("QPushButton{border:0px;}");
    this->hide();

}
