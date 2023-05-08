#ifndef INFIX2SUFFIX_H
#define INFIX2SUFFIX_H
#include <QVector>
#include <QDebug>
#include <math.h>

class infix2suffix //中缀表达式转后缀表达式
{
public:
    infix2suffix();
    QVector<QString> infixTosuffix(QVector<QString> infix);  //输入中缀表达式

private:
    int level(QString op); // 判断运算符优先级
    QVector <QString> stack;
    QVector<QString> suffix; // 后缀表达式



};

#endif // INFIX2SUFFIX_H
