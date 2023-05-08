#ifndef RANK_LABEL_H
#define RANK_LABEL_H

#include <QWidget>
#include <QLabel>
class Rank_label : public QWidget
{
    Q_OBJECT
public:
    explicit Rank_label(QWidget *parent = nullptr);
    void setRank(int score[5]);


private:
    QLabel * label1 = new QLabel(this);
    QLabel * label2 = new QLabel(this);
    QLabel * label3 = new QLabel(this);
    QLabel * label4 = new QLabel(this);
    QLabel * label5 = new QLabel(this);
    QLabel * label_list[5] = {label1,label2,label3,label4,label5};

signals:

};

#endif // RANK_LABEL_H
