#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "startwindow.h"
#include <QPainter>
#include "rank_label.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    int score_arr[5]={0};

};
#endif // MAINWINDOW_H
