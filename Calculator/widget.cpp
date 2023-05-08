#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <iostream>
#include <QVector>
#include "infix2suffix.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("计算器");
// 绑定数字按键
    setFixedSize(400,600);
    connect(ui->Num0,&QPushButton::clicked,[this](){OnClicked(Num,"0");});
    connect(ui->Num1,&QPushButton::clicked,[this](){OnClicked(Num,"1");});
    connect(ui->Num2,&QPushButton::clicked,[this](){OnClicked(Num,"2");});
    connect(ui->Num3,&QPushButton::clicked,[this](){OnClicked(Num,"3");});
    connect(ui->Num4,&QPushButton::clicked,[this](){OnClicked(Num,"4");});
    connect(ui->Num5,&QPushButton::clicked,[this](){OnClicked(Num,"5");});
    connect(ui->Num6,&QPushButton::clicked,[this](){OnClicked(Num,"6");});
    connect(ui->Num7,&QPushButton::clicked,[this](){OnClicked(Num,"7");});
    connect(ui->Num8,&QPushButton::clicked,[this](){OnClicked(Num,"8");});
    connect(ui->Num9,&QPushButton::clicked,[this](){OnClicked(Num,"9");});

    //绑定运算符
    connect(ui->Sum,&QPushButton::clicked,[this](){OnClicked(Op,"+");});
    connect(ui->Sub,&QPushButton::clicked,[this](){OnClicked(Op,"-");});
    connect(ui->Mul,&QPushButton::clicked,[this](){OnClicked(Op,"*");});
    connect(ui->Div,&QPushButton::clicked,[this](){OnClicked(Op,"/");});
    connect(ui->Radical,&QPushButton::clicked,[this](){OnClicked(SingleOp,"√");});
    connect(ui->Oppnums,&QPushButton::clicked,[this](){OnClicked(SingleOp,"±");});
    // 绑定括号
    connect(ui->Left,&QPushButton::clicked,[this](){OnClicked(Brackets,"(");});
    connect(ui->Right,&QPushButton::clicked,[this](){OnClicked(Brackets,")");});



    // 绑定其他
    connect(ui->Del,&QPushButton::clicked,[this](){OnClicked(Del,"del");});
    connect(ui->Clear,&QPushButton::clicked,[this](){OnClicked(Clear,"clear");});
    connect(ui->Dot,&QPushButton::clicked,[this](){OnClicked(Dot,".");});
    connect(ui->Equal,&QPushButton::clicked,[this](){OnClicked(Equal,"=");});

    //绑定功能键
    connect(ui->color,&QAction::triggered,[=](){
        QColor color = QColorDialog::getColor(QColor(0,0,0));
        QPalette bgpal (this->palette());
//        bgpal.setColor(QPalette::Window,color);  // 窗口背景色
//        bgpal.setColor(QPalette::Base,color);  // 基础色（不知道是什么用）
        bgpal.setColor(QPalette::Button,color); //按钮背景色（设置了没用）
//        bgpal.setColor(QPalette::WindowText,color); // 前景色 (设置了也没啥用)
        bgpal.setColor(QPalette::ButtonText,color); // 按钮字体颜色
        bgpal.setColor(QPalette::Text,color);  // 文本颜色
        this->setPalette(bgpal);
    });

    connect(ui->font,&QAction::triggered,[=](){
        bool flag;
        QFont font = QFontDialog::getFont(&flag,QFont("SimSun-ExtB",18));
        ui->centralwidget->setFont(font);
    });

    connect(ui->kaifa,&QAction::triggered,[=](){
        QMessageBox::about(this,"开发人员","------------------------------\n-----开发人员：赵自强-----\n------------------------------");

    });
    connect(ui->version,&QAction::triggered,[=](){
        QMessageBox::about(this,"版本","版本号v1.0\n修复了若干bug，还有若干bug\n暂无可用更新");

    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::calculation(){
    qDebug() <<"中缀"<< infix;
    infix2suffix suffix;
    QVector <QString> counts;
    counts = suffix.infixTosuffix(infix);
    QVector <double> result;
    for(int i=0;i<counts.size();i++){
        if (counts[i]>="0" && counts[i] <="9"){
            result.push_back(counts[i].toDouble());
        }

        else{
            QString op = counts[i];
            if(op == "+"){
                result[result.size()-2]=result[result.size()-2] + result[result.size()-1];
                result.pop_back();
            }
            if(op == "-"){
                result[result.size()-2]=result[result.size()-2] - result[result.size()-1];
                result.pop_back();
            }
            if(op == "*"){
                result[result.size()-2]=result[result.size()-2] * result[result.size()-1];
                result.pop_back();
            }
            if(op == "/"){
                result[result.size()-2]=result[result.size()-2] / result[result.size()-1];
                result.pop_back();
            }
            if(op == "√"){
                result[result.size()-1]=sqrt(result[result.size()-1]);
            }
            if(op == "±"){
                result[result.size()-1]= -result[result.size()-1];
            }
        }
    }


    return result.back();
}

void MainWindow::OnClicked(ButtonType _type,QString _btn){

    if(_type == Num || _type == Dot){

        if((count.isEmpty() || count.back() == ".") &&  _type == Dot ){
            QMessageBox::warning(this,"错误","小数点应该在数字后面");
            return;
        }

        if(_btn =="0" && count.isEmpty() && !infix.isEmpty() && infix.back() == "/" ){
            QMessageBox::warning(this,"错误","除法分母不能为0");
            return;
        }

        count += _btn;

    }
    if(_type == Op){
        if(!count.isEmpty()){
            if(count.back() == "."){
                QMessageBox::warning(this,"错误","小数点后需要有数字");
                return;
            }
            infix.push_back(count);
            count.clear();
            infix.push_back(_btn);
        }
        else{
            if(infix.isEmpty()){
                QMessageBox::warning(this,"错误","左运算符不能为空");
                return;
            }
            else if((infix.back() >= 42 && infix.back() <= 47) || infix.back() == "("){
                QMessageBox::warning(this,"错误","左运算符不能为空");
                 return;

            }
            else{
                infix.push_back(_btn);
            }

        }
    }
    if(_type == Brackets){
        brackets.push_back(_btn);

        if(!count.isEmpty()){
            if(count.back() == "."){
                QMessageBox::warning(this,"错误","小数点后需要有数字");
                return;
            }
            infix.push_back(count);
            count.clear();
            infix.push_back(_btn);
        }
        else{
            infix.push_back(_btn);
        }
    }

    if(_type == SingleOp){
        if(infix.isEmpty() && count.isEmpty()){
            infix.push_back(_btn);
        }
        else if (infix.isEmpty() && !count.isEmpty()) {
            QMessageBox::warning(this,"错误","需要在运算数前面");
            return;

        }
        else if( line.back() >="0" || line.back() == ")" || line.back() =="."){ // 检测是否在运算符的后面
           QMessageBox::warning(this,"错误","符号使用错误");
           return;
    }
        else{
            infix.push_back(_btn);
        }


    }

    if(_type == Clear){
        line.clear();
        infix.clear();
        count.clear();
        brackets.clear();
        ui->lineEdit->setText("0");
        return;
    }

    if(_type ==Equal){
        if(infix.isEmpty()){
            return;
        }
        JudgeBrackets judge; // 判断左右括号是否匹配
        if(!judge.judgeBrackets(brackets)){
            QMessageBox::warning(this,"错误","左右括号不匹配");
            return;
        }

        if(!count.isEmpty()){
            infix.push_back(count);
            count.clear();
            double result = calculation();
            ui->lineEdit->setText(QString::number(result));
            line.clear();
            infix.clear();
            brackets.clear();
            line = QString::number(result);
            count = QString::number(result);
            return;
        }
        else{
            if(infix.back()>=42 && infix.back() <= 47){  // 判断最后一个字符是不是运算符
                QMessageBox::warning(this,"错误","右运算符不能为空");
                return;
            }
            double result = calculation();
            ui->lineEdit->setText(QString::number(result));
            line.clear();
            infix.clear();
            brackets.clear();
            line = QString::number(result);
            count = QString::number(result);
            return;
        }

    }
    if(_type == Del){
        if(line.isEmpty()){
            return;
        }
        if(line.back()>="0" && line.back()<="9" && !count.isEmpty()){ // 最后的是数字，且操作数不为空，删除操作数最后一个数字
            line.chop(1);
            count.chop(1);
            ui->lineEdit->setText(line);
            return;
        }
        else if(line.back() =="."){ // 最后是点，删除点
            line.chop(1);
            count.chop(1);
            ui->lineEdit->setText(line);
            return;
        }
        else if(line.back() =="+" || line.back() =="-" || line.back() == "√"|| line.back() == "*"|| line.back() == "/"||line.back() == "±"){ //最后是操作符
            infix.pop_back();
            line.chop(1);
            ui->lineEdit->setText(line);
            return;
        }
        else if(line.back() == "(" || line.back() == ")"){ // 最后是括号
            infix.pop_back();
            line.chop(1);
            brackets.chop(1);
            ui->lineEdit->setText(line);
            return;
        }
        else{
            if(!infix.isEmpty()){
                infix.back().chop(1);
                line.chop(1);
                ui->lineEdit->setText(line);
                return;
            }
            else{
                return;
            }

        }

    }
    line += _btn;
    ui->lineEdit->setText(line);




}
