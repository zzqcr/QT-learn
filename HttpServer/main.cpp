#include "mainwindow.h"

#include <QApplication>
#include <QMutex>
#include <QFile>
#include <QDir>


//重定向qdebug输出到文件
void myMessageHandle(QtMsgType , const QMessageLogContext& , const QString& msg)
{
    static QMutex mut; //多线程打印时需要加锁
    QMutexLocker locker(&mut);
    QFile file("log.txt");
    if(file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        QTextStream stream(&file);
        stream<<msg<<endl;
        file.close();
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置重定向操作的函数
//    qInstallMessageHandler(myMessageHandle);



    MainWindow w;
    w.show();
    return a.exec();
}
