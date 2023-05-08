#include "ai.h"
#include <QPoint>
#include <QDebug>
AI::AI()
{

}

QPoint AI::go()
{

}




DECISION AI::analyse(QVector<QVector<int>>board, int depth){ //找这一层中最该下的字的价值和位置
    if(depth==3){

        POINTS P=seekPoints(board);
        DECISION D;
        D.pos = P.pos[0];
        D.eval =  -P.score[0];
        if(P.score[0]>50000)
        qDebug()<<board;
        qDebug()<<depth<<P.pos[0]<<P.score[0]<<P.pos[1]<<P.score[1];
        return D;
    }
    if(depth%2==0){//max层,我方(白)决策
        QVector<QVector<int>> sameBoard = board;
        POINTS P=seekPoints(sameBoard);
        sameBoard[P.pos[0].x()][P.pos[0].y()]=2;//模拟己方落子
        DECISION max;
        max.eval= analyse(sameBoard,depth+1).eval+P.score[0];
        max.pos = P.pos[0];
        for(int i=1;i<10;++i){
            board[P.pos[i].x()][P.pos[i].y()]=2;//模拟己方落子,不能用board,否则可能改变board的信息
            int a=analyse(sameBoard,depth+1).eval;
            if(a+P.score[i]>max.eval) {
                max.eval = a+P.score[i];
                max.pos = P.pos[i];
            }
            board[P.pos[i].x()][P.pos[i].y()]=0;//还原落子

        }
        qDebug()<<"max" <<depth<<max.pos<<max.eval;
        return max;

    }


    else{//min层,敌方(黑)决策
        QVector <QVector<int>> rBoard;
        rBoard = reverseBoard(board,rBoard);
        POINTS P=seekPoints(rBoard);//找对于黑子的最佳位置,需要将棋盘不同颜色反转,因为seekPoint是求白色方的最佳位置
        QVector <QVector<int>> sameBoard = board;
        sameBoard[P.pos[0].x()][P.pos[0].y()]=1;
        DECISION min;
        min.eval=analyse(sameBoard,depth+1).eval-P.score[0];
        min.pos = P.pos[0];
        rBoard[P.pos[0].x()][P.pos[0].y()]=0;
        for(int i=1;i<10;++i){
            sameBoard[P.pos[i].x()][P.pos[i].y()]=2;//模拟敌方落子
            int a=analyse(sameBoard,depth+1).eval;
            if(a+P.score[i]<min.eval){
                min.eval=a-P.score[i];
                min.pos = P.pos[i];

            }
            sameBoard[P.pos[i].x()][P.pos[i].y()]=0;//还原落子

        }
        qDebug()<<"min" <<depth<<min.pos<<min.eval;
        return min;

    }
}


POINTS AI::seekPoints(QVector<QVector<int>> board){
    mBoard = board;
    int worth[15][15];
    POINTS best_points;



    // 算出在每个地方落子时的价值
    for(int i=0;i<15;++i){
        for(int j=0;j<15;++j){
           // 如果可以落子，计算落子的价值
            if(board[i][j]==0){
                worth[i][j]=evaluate(i,j);
            }
            // 如果不可以落子，价值为0
            else {
                worth[i][j] = 0;
            }
        }
    }

    // 计算出前10个价值最高的落子点
    int w;
    for(int k=0;k<10;++k){
        w =0;
        for(int i=0;i<15;++i){
            for(int j=0;j<15;++j){
                if(worth[i][j]>w){
                    w=worth[i][j];
                    QPoint tmp(i,j);
                    best_points.pos[k]=tmp;
                }
            }
        }
        best_points.score[k]=w;
        worth[best_points.pos[k].x()][best_points.pos[k].y()]=0;//清除掉上一点,计算下一点的位置和分数
    }

    return best_points;
}

int AI::evaluate(int row, int column)
{

     //统计玩家或AI连子
     int personNum = 0;    //玩家
     int botNum = 0;   //AI
     int emptyNum = 0; //各方向空白位数


     //清空评分数组
     int value = 0;

     //空白点计算
     if(row >= 0 && column >= 0 ){
       //遍历四个方向，然后分别计算正反四个方向
       int directs[4][2] = {{1,0}, {1,1}, {0,1}, {-1,1}};

       for(int k = 0; k < 4; k++){
         int x = directs[k][0];
         int y = directs[k][1];

         //重置
         personNum = 0;
         botNum = 0;
         emptyNum = 0;

         //对黑棋评分(正向)
         for(int i = 1; i <= 4; i++){
           if(row + i * y >= 0 && row + i * y < 15 && column + i * x >= 0 && column + i * x < 15 && mBoard[row + i * y][column + i * x] == 1){
             //玩家的子
             personNum++;

           }else if(row + i * y >= 0 && row + i * y < 15 &&column + i * x >= 0 && column + i * x < 15 && mBoard[row + i * y][column + i * x] == 0){
             //空白位
             emptyNum++;
             break;    //遇到空白位置停止该方向搜索

           }else{
             break;    //出边界或遇到白棋停止搜索
           }


         }

         //对黑棋评分(反向)
         for(int i = 1; i<= 4; i++){
           if(row - i * y >= 0 && row - i * y < 15 && column - i * x >= 0 && column - i * x <15 && mBoard[row - i * y][column - i * x] == 1){
             personNum++;
           }
           else if(row - i * y >= 0 && row - i * y <15 && column - i * x >= 0 && column - i * x < 15 &&mBoard[row -i * y][column - i * x] == 0){
             emptyNum++;
             break;
           }
           else{
             break;
           }
         }


         if(personNum == 1){
           value += 10;
         }
         else if(personNum == 2){
           if(emptyNum == 1){
             //死2
             value += 20;
           }
           else if(emptyNum == 2){
             //活2
             value += 30;
           }
         }
         else if(personNum == 3){
           if(emptyNum == 1){
             //死3
             value += 50;
           }else if (emptyNum == 2){
             //活3
             value += 200;
           }
         }
         else if(personNum == 4){
           value += 20000;
         }
         emptyNum = 0; //清空

         //对白棋评分（正向）
         for(int i = 1; i <= 4; i++){
           if(row + i * y > 0 && row + i * y < 15 &&column + i * x > 0
                   && column + i * x < 15 &&mBoard[row + i * y][column + i * x] == 2){
             botNum++;
           }else if(row + i * y >0 && row + i * y < 15 &&
                   column + i * x > 0 && column + i * x < 15 &&
                   mBoard[row + i * y][column + i *x] == 0){
             emptyNum++;
             break;
           }else{
             break;
           }
         }
         //白棋评分(反向)
         for(int i = 1; i <= 4; i++){
           if(row - i * y > 0 && row - i * y <15 &&column - i * x > 0 && column - i * x < 15
                   &&mBoard[row - i * y][column -i * x] == 2){
             botNum++;
           }else if (row - i * y >0 && row - i * y < 15 &&
                     column - i * x > 0 && column - i * x < 15 &&
                    mBoard[row - i * y][column - i * x] == 0){
             emptyNum++;
             break;
           }else{
             break;    //出边界
           }
         }

         if(botNum == 0){
           //连1
           value += 5;
         }else if(botNum == 1){
           //活2
             if(emptyNum==2)value += 15;
             else if (emptyNum==1) {
                 value +=5;
             }
         }else if(botNum == 2){
           if(emptyNum == 1){
             //死3
             value += 25;
           }else if(emptyNum == 2){
             //活3
             value += 60;
           }
         }else if(botNum == 3){
           if(emptyNum == 1){
             //死4
             value += 60;
           }else if(emptyNum == 2){
             //活4
             value += 400;
           }
         }else if(botNum >= 4){
           //活5
           value += 50000;
         }

       }

     }
    return value;

}



QVector<QVector<int> > AI::reverseBoard(QVector<QVector<int> > board, QVector<QVector<int> > rBoard)
{
    qDebug()<<"rb2"<<rBoard;
    rBoard = board;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board.at(i).size();j++){
            if(board.at(i).at(j) ==0){
                rBoard[i][j]=0;
            }
            else if (board.at(i).at(j) ==1) {
                rBoard[i][j]=2;
            }
            else {
                rBoard[i][j]=1;
            }
        }
    }
    return rBoard;
}
