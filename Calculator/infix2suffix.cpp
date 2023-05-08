#include "infix2suffix.h"


infix2suffix::infix2suffix(){

}
int infix2suffix::level(QString op){
    if(op == "*" || op == "/"){
        return 2;
    }
    else if(op == "+" || op == "-"){
        return 1;
    }
    else if(op == "√" || op =="±"){
        return 3;
    }
    else if(op =="("){
        return 0;
    }

}

  QVector<QString> infix2suffix::infixTosuffix(QVector<QString> infix){
    int size = infix.size();
    for (int i=0;i<size;i++){

        if(infix[i].back()>="0" && infix[i].back() <= "9"){  //判断是不是数字
            suffix.push_back(infix[i]);
        }
        else{
            QString op = infix[i];
            if(stack.isEmpty()){
                stack.push_back(op); // 如果为空，直接放进去
            }

            else if(op =="("){
                stack.push_back(op); //左括号直接入栈
            }

            else if(op ==")"){
                while(stack.back() != "("){
                    suffix.push_back(stack.back()); //把栈最上面的数弹出到后缀表达式
                    stack.pop_back();
                }
                stack.pop_back(); //左括号弹出不要
            }

            else if(op == "√"|| op =="±"){
                stack.push_back(op);
            }
            else{
                if(level(op)>level(stack.back())){
                    stack.push_back(op); // 如果操作数大于栈最上面的操作数，操作数入栈。

                }
                else{
                    suffix.push_back(stack.back());
                    stack.pop_back(); // 否则栈最上面的操作数弹出到后缀表达式
                    stack.push_back(op); //新的操作数入栈
                }
            }


        }

    }

    while(!stack.isEmpty()){
        suffix.push_back(stack.back());
        stack.pop_back(); // 最后如果栈不为空，输出栈里全部元素到后缀表达式
    }
    qDebug()<<"后缀" << suffix;
//    for(int i=0;i<suffix.size();i++){
//        qDebug() << suffix[i] ; //输出后缀表达式
//    }
    return suffix;
}
