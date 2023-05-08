#ifndef WIDGET_H
#define WIDGET_H
#include <QMainWindow>
#include <QWidget>
#include <QColorDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <judgebrackets.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
enum ButtonType {
    Num, //数字
    Op, // 运算符
    SingleOp, //单边运算符
    Dot, //点
    Equal, //等于
    Clear, //清空
    Del, //删除
    Brackets, //括号
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QString line = "";
    QString count = "";
    QVector <QString> infix; // 中缀
    QVector <QString> suffix; //后缀
    QString brackets = ""; // 记录表达式里的括号



public slots:
    void OnClicked(ButtonType _type,QString _btn);
    double calculation();
};
#endif // WIDGET_H
