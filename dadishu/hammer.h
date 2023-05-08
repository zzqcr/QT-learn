#ifndef HAMMER_H
#define HAMMER_H

#include <QPushButton>

class Hammer : public QPushButton
{
    Q_OBJECT
public:
    Hammer();
    void change1();
    void change2();
private:
    QStringList str_list = {":/images/chuizi_0.png",":/images/chuizi_2.png",};
    QPixmap pix;
    int i = 0;
    int state = 0;

signals:

};

#endif // HAMMER_H
