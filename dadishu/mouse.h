#ifndef MOUSE_H
#define MOUSE_H

#include <QPushButton>
#include <QPixmap>
class Mouse : public QPushButton
{
    Q_OBJECT
public:
    Mouse();
    void change(); // 改变状态的动画
    int get_state();  // 获得状态
    void change_state();  // 改变状态
    void reset();


signals:

private:
    QStringList str_list = {":/images/laoshu_0.png",":/images/laoshu_0.png",
                            ":/images/laoshu_1.png",":/images/laoshu_1.png",
                            ":/images/laoshu_3.png",":/images/laoshu_3.png",
                            ":/images/laoshu_4.png",":/images/laoshu_4.png"};
    QPixmap pix;
    int state = 0; // 设置状态
    int i = 0;
};

#endif // MOUSE_H
