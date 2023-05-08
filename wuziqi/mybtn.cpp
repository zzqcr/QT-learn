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
    // ������̬����
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    // �����������
    animation->setDuration(200);
    // ��ʼλ��
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    // ����λ��
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    // ���õ�������
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();



}

void MyBtn::zoom2(){
    // ������̬����
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    // �����������
    animation->setDuration(200);
    // ��ʼλ��
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    // ����λ��
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    // ���õ�������
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();


}


void MyBtn::resizeEvent(QResizeEvent *ev)
{
    this->setIconSize(this->size());
}

