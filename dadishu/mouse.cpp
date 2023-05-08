#include "mouse.h"
#include <QDebug>
Mouse::Mouse()
{
    pix.load(str_list[0]);
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setFixedSize(pix.width(),pix.height());//设置按钮大小
    this->setStyleSheet("QPushButton{border:0px;}");

}


void Mouse::change(){
    if(state == 1){
        if(i<8){
           qDebug() << "地鼠冒头";

            pix.load(str_list[i]);
            this->setIcon(pix);
            this->setIconSize(QSize(pix.width(),pix.height()));
            this->setFixedSize(pix.width(),pix.height());//设置按钮大小
            this->setStyleSheet("QPushButton{border:0px;}");
            i +=1;
        }
//        else if(i ==8){
//            state = 1;

//        }

    }

    // 如果状态为1

    else if(state == 0){
        if(i >0){
            i -=1;
            pix.load(str_list[i]);
            this->setIcon(pix);
            this->setIconSize(QSize(pix.width(),pix.height()));
            this->setFixedSize(pix.width(),pix.height());//设置按钮大小
            this->setStyleSheet("QPushButton{border:0px;}");
        }
//        else if(i ==0){
//            state =0;
//        }

    }
}

int Mouse::get_state(){
    return state;
}
void Mouse::reset(){
    pix.load(str_list[0]);
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setFixedSize(pix.width(),pix.height());//设置按钮大小
    this->setStyleSheet("QPushButton{border:0px;}");
    state =0;
    i = 0;
}
void Mouse::change_state(){
    if(state == 0){
        state =1;
    }
    else if(state == 1){
        state =0;
    }

}
