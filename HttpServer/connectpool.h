#ifndef CONNECTPOOL_H
#define CONNECTPOOL_H

#include <QObject>
#include "sockethandlethread.h"
#include <QMap>
#include <QMutex>
// 设置一个线程池管理多个线程
class ConnectPool : public QObject
{
    Q_OBJECT
public:
    static ConnectPool * instance();

    SocketHandleThread * getSocketHandleThread();
    void setMaxThread(int maxNum);
    int getMaxThread();

    SocketHandleThread * addThread();
    void setMaxConnect(int maxNum);
    int getMaxconnect();
    void timerEvent(QTimerEvent *ev);
    bool isFull();
    void close();
signals:
    void closeAll();


protected:



private:
    int m_maxThread =4;
    int m_maxConnect =150;
    int m_curConnect =0;
    QMap<SocketHandleThread*,int> threads;
    QMutex mutex;

};

#endif // CONNECTPOOL_H
