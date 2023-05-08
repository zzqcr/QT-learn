#include "mybtn.h"
#include <QPropertyAnimation>
MyBtn::MyBtn( QWidget *parent,QString norImg){
    this->setParent(parent);
    m_norImg = norImg;
    QPixmap pix;
    pix.load(m_norImg);


    this->setStyleSheet("QPushButton{border:0px;}");

    this->setIcon(pix);

    this->setIconSize(this->size());

}

void MyBtn::zoom()
{
    zoom1();
    zoom2();

}

void MyBtn::zoom1(){
    // 创建动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    // 创建动画间隔
    animation->setDuration(200);
    // 起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    // 结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    // 设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();



}

void MyBtn::zoom2(){
    // 创建动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    // 创建动画间隔
    animation->setDuration(200);
    // 起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    // 结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    // 设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();


}


void MyBtn::resizeEvent(QResizeEvent *ev)
{
    this->setIconSize(this->size());
}

