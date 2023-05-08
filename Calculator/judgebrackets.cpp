#include "judgebrackets.h"

JudgeBrackets::JudgeBrackets()
{

}

bool JudgeBrackets::judgeBrackets(QString s){
    for(int i=0;i<s.size();i++){
        if(s[i] == "("){
            bracketStack.push('('); //左括号入栈
        }
        else{
            if(!bracketStack.isEmpty()){ // 右括号则出栈一个左括号
                bracketStack.pop();
            }
            else{ // 若栈空则不匹配
                return false;
            }
        }
    }
    return bracketStack.isEmpty(); //匹配结束后，如果栈不空，则左括号多了，栈空则返回true
}
