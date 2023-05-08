#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "manvsman.h"
#include <QPushButton>
#include "mybtn.h"
#include "lanbattle.h"
#include "manvsai.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MyBtn;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *ev);
    void initWindow();
    void connects();
    ~MainWindow();



private:
    Ui::MainWindow *ui;

    MyBtn * btnBenDi;
    MyBtn * btnJvYuWang;
    MyBtn * btnHuLianWang;
    MyBtn * btnRenJi;
    MyBtn * btnWenHao;


};

#endif // MAINWINDOW_H

