#include "widget.h"
#include "infix2suffix.h"
#include <QApplication>
#include <qtranslator.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator tran;
    tran.load("C:\\Qt\\Qt5.14.2\\5.14.2\\mingw73_64\\translations\\qt_zh_CN.qm");//相对路径.
    QApplication::installTranslator(&tran);
    MainWindow w;
    w.show();
    return a.exec();
}
