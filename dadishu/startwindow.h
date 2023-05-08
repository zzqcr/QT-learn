#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "mouse.h"
#include <QMouseEvent>
#include <QSound>
#include "hammer.h"
#include <QVector>
namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *);
    void setdifficulty(int dif);
    int get_score();
    void rank();
    void get_rank();


private:
    Ui::StartWindow *ui;
    Mouse *mouse1 = new Mouse;
    Mouse *mouse2 = new Mouse;
    Mouse *mouse3 = new Mouse;
    Mouse *mouse4 = new Mouse;
    Mouse *mouse5 = new Mouse;
    Mouse *mouse6 = new Mouse;
    Mouse *mouse7 = new Mouse;
    Mouse *mouse8 = new Mouse;
    Mouse *mouse9 = new Mouse;
    Mouse *mouse_arr[9] = {mouse1,mouse2,mouse3,mouse4,mouse5,mouse6,mouse7,mouse8,mouse9} ;
    int time = 0;
    int mouse_id = 0;
    int difficulty = 1;
    int x = 0; // 鼠标位置
    int y = 0;
    int score =0;
    QSound *sound_hit = new QSound(":/sounds/qiao.wav");
    QSound *sound_jiao = new QSound(":/sounds/jiaosheng.wav");
    Hammer *hammer = new Hammer;
    int score_arr[5]={0};

signals:
    void game_end();
    void back();

};

#endif // STARTWINDOW_H
