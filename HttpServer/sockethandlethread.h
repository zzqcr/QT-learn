#ifndef SOCKETHANDLETHREAD_H
#define SOCKETHANDLETHREAD_H

#include <QObject>
#include "sockethandle.h"
#include <QMutex>
#include <QTimer>

// 设置一个线程管理多个连接
class SocketHandleThread : public QObject
{
    Q_OBJECT
public:
    SocketHandleThread();
    SocketHandle * addConnect();
    void updateConnect(SocketHandle* client,int jobType);

    void handleTimerOut();

public slots:
    void thread_done();
    void setSocket(qintptr handle);
signals:
    void oneSocketHandleClose(SocketHandleThread * ptr);
private:
    QThread * m_thread;
    QMap<SocketHandle*,int> connections;// 0 是繁忙，大于0是不活跃的时间
    QMutex mutex;
    QTimer *timer;
    int m_timerOut = 3; // 3s


};

#endif // SOCKETHANDLETHREAD_H
