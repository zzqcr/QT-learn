#ifndef MYBTN_H
#define MYBTN_H

#include <QPushButton>
class MyBtn : public QPushButton
{
    Q_OBJECT
public:
    MyBtn(QWidget *parent=nullptr, QString norImg="");
    void zoom();
    void zoom1();
    void zoom2();
//    void mousePressEvent(QMouseEvent *ev);
//    void mouseReleaseEvent(QMouseEvent *ev);
    void resizeEvent(QResizeEvent *ev);



private:
    QString m_norImg;


signals:

};

#endif // MYBTN_H
