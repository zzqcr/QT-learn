#include "startwindow.h"
#include "ui_startwindow.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QMessageBox>
#include <fstream>
#include <QString>
StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    this->setFixedSize(400,600);
    this->setWindowTitle("开心打地鼠");

    QPixmap pix ;

    hammer->setParent(this);
    hammer->hide();
    //加载眩晕图片
    QLabel * xuanyun = new QLabel;
    xuanyun->setParent(this);
    pix.load(":/images/xuanyun.png");
    xuanyun->setPixmap(pix);
    xuanyun->setFixedSize(pix.width(),pix.height());
    xuanyun->move(-200,-200);


    // 加载难度和分数标签
    QLabel * label_score = new QLabel(this);
    pix.load(":/images/score.png");
    label_score->setPixmap(pix);
    label_score->setFixedSize(pix.width(),pix.height());
    label_score->move(0,30);
    QLabel * label_score_text = new QLabel(this);
    label_score_text->setFixedSize(50,pix.height());
    label_score_text->setFont(QFont("宋体",24,87));
    label_score_text->setStyleSheet("color:yellow");
    label_score_text->move(pix.width()+20,30);

    QLabel * label_time = new QLabel(this);
    pix.load(":/images/timer.png");
    label_time->setPixmap(pix);
    label_time->setFixedSize(pix.width(),pix.height());
    label_time->move(this->width()-pix.width()-50,30);
    QLabel * label_time_text = new QLabel(this);
    pix.load(":/images/timer.png");
    label_time_text->setFont(QFont("宋体",24,87));
    label_time_text->setFixedSize(50,pix.height());
    label_time_text->setStyleSheet("color:yellow");
    label_time_text->move(this->width()-40,30);


    QLabel * label_dif = new QLabel(this);
    label_dif->setFont(QFont("宋体",22,87));
    label_dif->setFixedSize(150,pix.height());
    label_dif->setStyleSheet("color:yellow");
    label_dif->move(0,label_score->height()+50);

    // 游戏结束功能
    QLabel * label_end = new QLabel(this);
    pix.load(":/images/end.png");
    label_end->setPixmap(pix);
    label_end->setFixedSize(pix.width(),pix.height());
    label_end->move(-200,-300);

    // 重新开始
    QPushButton *btn_restart = new QPushButton(this);
    pix.load(":/images/restart.png");
    btn_restart->setIcon(pix);
    btn_restart->setIconSize(QSize(pix.width(),pix.height()));
    btn_restart->setFixedSize(pix.width(),pix.height());//设置按钮大小
    btn_restart->setStyleSheet("QPushButton{border:0px;}");
    btn_restart->move(-200,-200);
    connect(btn_restart,&QPushButton::clicked,[=](){
        score = 0;
        QTimer::singleShot(500,this,[=](){
            for(int i=0;i<9;i++){
                mouse_arr[i]->reset();
            }
            btn_restart->move(-200,-200);
            label_end->move(-200,-200);
            time = 0;
        });
    });
    // 生成本地文件保存成绩
//    std::ofstream outfile;
//    outfile.open("D:\\c++\\game02\\score.txt");
//      if(outfile.is_open())
//      {
//          for(int i =0;i<5;i++){
//              outfile<< score_arr[i] <<std::endl;

//          }
//        outfile.close();

//      }



    //设置菜单栏功能
    connect(ui->actionesc,&QAction::triggered,[=](){
        delete this;
    });
    connect(ui->actionrestart,&QAction::triggered,[=](){

        QTimer::singleShot(200,this,[=](){
            btn_restart->move(-200,-200);
            label_end->move(-200,-200);
            for(int i=0;i<9;i++){
                mouse_arr[i]->reset();
            }
            time = 0;
        });
        score = 0;
    });

    connect(ui->actionback,&QAction::triggered,[=](){
        this->parentWidget()->show();
        delete this;
    });
    connect(ui->action1,&QAction::triggered,[=](){

        difficulty = 1;
        QTimer::singleShot(200,this,[=](){
            btn_restart->move(-200,-200);
            label_end->move(-200,-200);
            for(int i=0;i<9;i++){
                mouse_arr[i]->reset();
            }
            time = 0;
        });
        score = 0;
    });
    connect(ui->action2,&QAction::triggered,[=](){

        difficulty = 2;
        QTimer::singleShot(200,this,[=](){
            btn_restart->move(-200,-200);
            label_end->move(-200,-200);
            time = 0;
            for(int i=0;i<9;i++){
                mouse_arr[i]->reset();
            }
        });
        score = 0;
    });
    connect(ui->action3,&QAction::triggered,[=](){

        difficulty = 3;
        QTimer::singleShot(200,this,[=](){
            btn_restart->move(-200,-200);
            label_end->move(-200,-200);
            for(int i=0;i<9;i++){
                mouse_arr[i]->reset();
            }
            time = 0;
        });
        score = 0;
    });
    connect(ui->action4,&QAction::triggered,[=](){

        difficulty = 4;
        QTimer::singleShot(200,this,[=](){
            for(int i=0;i<9;i++){
                mouse_arr[i]->reset();
            }
            btn_restart->move(-200,-200);
            label_end->move(-200,-200);
            time = 0;
        });
        score = 0;
    });
    connect(ui->action5,&QAction::triggered,[=](){

        difficulty = 5;
        QTimer::singleShot(500,this,[=](){
            for(int i=0;i<9;i++){
                mouse_arr[i]->reset();
            }
            btn_restart->move(-200,-200);
            label_end->move(-200,-200);
            time = 0;
        });
        score = 0;
    });
    connect(ui->action6,&QAction::triggered,[=](){

        difficulty = 6;
        QTimer::singleShot(200,this,[=](){
            btn_restart->move(-200,-200);
            label_end->move(-200,-200);
            for(int i=0;i<9;i++){
                mouse_arr[i]->reset();
            }
            time = 0;
        });
        score = 0;
    });
    connect(ui->action7,&QAction::triggered,[=](){

        difficulty = 7;
        QTimer::singleShot(200,this,[=](){
            for(int i=0;i<9;i++){
                mouse_arr[i]->reset();
            }
            btn_restart->move(-200,-200);
            label_end->move(-200,-200);
            time = 0;
        });
        score = 0;
    });






    // 初始化地鼠
    mouse_arr[0]->setParent(this);
    mouse_arr[0]->move(20,220);
    connect(mouse1,&Mouse::clicked,[=](){
        if(mouse1->get_state() == 1){
            qDebug() <<"打中了";
            sound_jiao->play();
            xuanyun->move(mouse1->pos()-QPoint(-20,40));
            score +=1;
            hammer->show();
            hammer->move(mouse1->pos()-QPoint(-20,40));
            hammer->move(mouse1->pos()-QPoint(-20,40));
            hammer->change1();

            QTimer::singleShot(200,[=](){
                hammer->change2();
                hammer->hide();

                xuanyun->move(-200,-200);
            });
        }
        else{
            sound_hit->play();
            hammer->show();
            hammer->move(mouse1->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                hammer->change2();
                hammer->hide();
            });
        }
    });

    mouse_arr[1]->setParent(this);
    mouse_arr[1]->move(20,340);
    connect(mouse2,&Mouse::clicked,[=](){
        if(mouse2->get_state() == 1){
            qDebug() <<"打中了";
            sound_jiao->play();
            xuanyun->move(mouse2->pos()-QPoint(-20,40));
            hammer->move(mouse2->pos()-QPoint(-20,40));
            score +=1;
            hammer->change1();
            QTimer::singleShot(200,[=](){
                xuanyun->move(-200,-200);
                hammer->change2();
            });
        }
        else{
            sound_hit->play();
            hammer->show();
            hammer->move(mouse2->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                hammer->change2();
                hammer->hide();
            });
        }
    });

    mouse_arr[2]->setParent(this);
    mouse_arr[2]->move(20,460);
    connect(mouse3,&Mouse::clicked,[=](){
        if(mouse3->get_state() == 1){
            qDebug() <<"打中了";
            sound_jiao->play();
            xuanyun->move(mouse3->pos()-QPoint(-20,40));
            hammer->move(mouse3->pos()-QPoint(-20,40));
            hammer->change1();
            score +=1;
            QTimer::singleShot(200,[=](){
                xuanyun->move(-200,-200);
                hammer->change2();
            });
        }
        else{
            sound_hit->play();
            hammer->show();
            hammer->move(mouse3->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                hammer->change2();
                hammer->hide();
            });
        }
    });

    mouse_arr[3]->setParent(this);
    mouse_arr[3]->move(140,220);
    connect(mouse4,&Mouse::clicked,[=](){
        if(mouse4->get_state() == 1){
            qDebug() <<"打中了";
            sound_jiao->play();
            xuanyun->move(mouse4->pos()-QPoint(-20,40));
            score +=1;
            hammer->move(mouse4->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                xuanyun->move(-200,-200);
                hammer->change2();
            });
        }
        else{
            sound_hit->play();
            hammer->show();
            hammer->move(mouse4->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                hammer->change2();
                hammer->hide();
            });
        }
    });

    mouse_arr[4]->setParent(this);
    mouse_arr[4]->move(140,340);
    connect(mouse5,&Mouse::clicked,[=](){
        if(mouse5->get_state() == 1){
            qDebug() <<"打中了";
            sound_jiao->play();
            xuanyun->move(mouse5->pos()-QPoint(-20,40));
            score +=1;
            hammer->move(mouse5->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                xuanyun->move(-200,-200);
                hammer->change2();
            });
        }
        else{
            sound_hit->play();
            hammer->show();
            hammer->move(mouse5->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                hammer->change2();
                hammer->hide();
            });
        }
    });

    mouse_arr[5]->setParent(this);
    mouse_arr[5]->move(140,460);
    connect(mouse6,&Mouse::clicked,[=](){
        if(mouse6->get_state() == 1){
            qDebug() <<"打中了";
            sound_jiao->play();
            xuanyun->move(mouse6->pos()-QPoint(-20,40));
            score +=1;
            hammer->move(mouse6->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                xuanyun->move(-200,-200);
                hammer->change2();
            });
        }
        else{
            sound_hit->play();
            hammer->show();
            hammer->move(mouse6->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                hammer->change2();
                hammer->hide();
            });
        }
    });

    mouse_arr[6]->setParent(this);
    mouse_arr[6]->move(260,220);
    connect(mouse7,&Mouse::clicked,[=](){
        if(mouse7->get_state() == 1){
            qDebug() <<"打中了";
            sound_jiao->play();
            xuanyun->move(mouse7->pos()-QPoint(-20,40));
            score +=1;
            hammer->move(mouse7->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                xuanyun->move(-200,-200);
                hammer->change2();
            });
        }
        else{
            sound_hit->play();
            hammer->show();
            hammer->move(mouse7->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                hammer->change2();
                hammer->hide();
            });
        }
    });

    mouse_arr[7]->setParent(this);
    mouse_arr[7]->move(260,340);
    connect(mouse8,&Mouse::clicked,[=](){
        if(mouse8->get_state() == 1){
            qDebug() <<"打中了";
            sound_jiao->play();
            xuanyun->move(mouse8->pos()-QPoint(-20,40));
            hammer->move(mouse8->pos()-QPoint(-20,40));
            score +=1;
            hammer->change1();
            QTimer::singleShot(200,[=](){
                xuanyun->move(-200,-200);
                hammer->change2();
            });
        }
        else{
            sound_hit->play();
            hammer->show();
            hammer->move(mouse8->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                hammer->change2();
                hammer->hide();
            });
        }
    });

    mouse_arr[8]->setParent(this);
    mouse_arr[8]->move(260,460);
    connect(mouse9,&Mouse::clicked,[=](){
        if(mouse9->get_state() == 1){
            qDebug() <<"打中了";
            sound_jiao->play();
            xuanyun->move(mouse9->pos()-QPoint(-20,40));
            hammer->move(mouse9->pos()-QPoint(-20,40));
            score +=1;
            hammer->change1();
            QTimer::singleShot(200,[=](){
                xuanyun->move(-200,-200);
                hammer->change2();
            });
        }
        else{
            sound_hit->play();
            hammer->show();
            hammer->move(mouse9->pos()-QPoint(-20,40));
            hammer->change1();
            QTimer::singleShot(200,[=](){
                hammer->change2();
                hammer->hide();
            });
        }
    });


    // 设置定时器
    QTimer * timer1 = new QTimer (this);
    timer1->start(25);
    mouse_id = rand()%9;
//    difficulty = 1;

    connect(timer1,&QTimer::timeout,[=](){
        if(time/1000 == 30){
            label_end->move(this->width()*0.5-label_end->width()*0.5,250);
            label_end->raise();
            btn_restart->move(this->width()*0.5-btn_restart->width()*0.5,400);
            btn_restart->raise();
            emit game_end();
            rank();
            return;

            qDebug() << "游戏结束";
        }

   //        qDebug() << mouse_id << "状态" << mouse_arr[mouse_id].get_state();
        label_score_text->setNum(score);
        if(time%1000 ==0){
            label_time_text->setNum(time/1000);
            label_dif->setText("难度："+QString::number(difficulty));
        }


        // 下一个地鼠生成间隔时间

        if(time%(2000-difficulty*200) ==0){
            mouse_id = rand()%9;
        }
        // 地鼠改变状态时间
        if(time%(1000-difficulty*100) == 0){
            mouse_arr[mouse_id]->change_state();
        }
        mouse_arr[mouse_id]->change();

        time = time + 25;
    });



}

void StartWindow::mouseMoveEvent(QMouseEvent *ev){
    this->centralWidget()->setMouseTracking(true);
    this->setMouseTracking(true);
    if (ev->x()>0 && ev->x() <this->width()){
        x = ev->x();
    }
    else if (ev->x()<=0){
        x = 0;
    }
    else{
        x=400;
    }
    if (ev->y()>0 && ev->y() <this->height()){
        y = ev->y();
    }
    else if (ev->y()<=0){
        y = 0;
    }
    else{
        y=600;
    }
//    qDebug() << "鼠标移动到了"  << x << y ;
}
void StartWindow::paintEvent(QPaintEvent *){
    QPixmap pix;
    pix.load(":/images/forest.png");
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
void StartWindow::mousePressEvent(QMouseEvent *ev){
    hammer->show();

    hammer->move(ev->x(),ev->y()-100);
    qDebug() << ev;
    sound_hit->play();
    hammer->change1();
    QTimer::singleShot(200,[=](){
        hammer->change2();
    });

}

void StartWindow::mouseReleaseEvent(QMouseEvent *ev){
//    hammer->change2();
//    hammer->hide();
}

void StartWindow::setdifficulty(int dif){
    difficulty = dif;
}
int StartWindow::get_score(){
    return score;
}

void StartWindow::rank(){

    // 读数据并且排序
    std::ifstream infile;
    infile.open("D:\\c++\\game02\\score.txt"); //myfile.bat是存放数据的文件名
      if(infile.is_open())

      {
          int i = 0;
          int s = 0 ;
          while(infile >> s){
             score_arr[i] = s;
             i +=1;
          }
          infile.close();
      }
      for(int i=0;i<5;i++){
          if(score>score_arr[i]){
              if(i==4 || score<score_arr[i+1]){
                  int temp = score_arr[i];
                  score_arr[i] = score;
                  for(int j =0;j<i-1;j++){
                      score_arr[j] = score_arr[j+1];
                  }
                  score_arr[i-1] = temp;
              }
          }
      }

    //  写入排序后的数据到本地
    std::ofstream outfile;
    outfile.open("D:\\c++\\game02\\score.txt");
      if(outfile.is_open())
      {
          for(int i =0;i<5;i++){
              outfile<< score_arr[i] <<std::endl;

          }
        outfile.close();

      }
      // 初始化数组
      for(int i =0;i<5;i++){
          score_arr[i] =0;
      }

}

StartWindow::~StartWindow()
{
    delete ui;
}
