#ifndef JUDGEBRACKETS_H
#define JUDGEBRACKETS_H
#include <QString>
#include <QStack>

class JudgeBrackets
{
public:
    JudgeBrackets();
    bool judgeBrackets(QString s);

private:
    QStack <char> bracketStack;
};

#endif // JUDGEBRACKETS_H
