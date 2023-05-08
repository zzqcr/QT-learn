#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new HttpServer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_start_clicked()
{
    if(server->startListen(ui->lineEdit_port->text().toInt())){
        qDebug()<<__FUNCTION__<<"listen ok";
    }
    else {
        qDebug()<<__FUNCTION__<<"listen fasle";
    }
}
