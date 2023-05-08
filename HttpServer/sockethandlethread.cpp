#include "sockethandlethread.h"


SocketHandleThread::SocketHandleThread()
{
    // 先注册qintptr类型
    qRegisterMetaType<SocketHandleThread *>("SocketHandleThread");
    qDebug()<<__FUNCTION__;
    m_thread = new QThread;
    connect(m_thread, SIGNAL(finished()), this, SLOT(thread_done()));
    this->moveToThread(m_thread);
    m_thread->start();
    timer = new QTimer;
    connect(timer,&QTimer::timeout,this,&SocketHandleThread::handleTimerOut);
    timer->start(1000); // 1s检测一次
    timer->moveToThread(m_thread);
}

SocketHandle *SocketHandleThread::addConnect()
{
    qDebug()<<__FUNCTION__;
    SocketHandle * newHandle = new SocketHandle;
    connect(newHandle,&SocketHandle::canChangeJobType,this,[=](int jobType){
        updateConnect(newHandle,jobType);
        if(jobType>0) emit oneSocketHandleClose(this);
    });
    connections.insert(newHandle,1);
    return newHandle;


}

void SocketHandleThread::updateConnect(SocketHandle *client, int jobType)
{
    qDebug()<<__FUNCTION__;
    if(connections.contains(client)){
        connections[client] = jobType;
    }
}

void SocketHandleThread::setSocket(qintptr handle)
{
    qDebug()<<__FUNCTION__;
    auto index = connections.begin();
    for(;index!=connections.end();index++){
        if(index.value() >0){
            index.key()->setSocket(handle);
            index.value() =0;
            return ;
        }
    }
    SocketHandle * sockethandle = addConnect();
    sockethandle->setSocket(handle);
    connections[sockethandle] =0;

}

void SocketHandleThread::handleTimerOut()
{
    qDebug()<<__FUNCTION__;
    // 每1s遍历一次，超过timerout不活跃的将被删除
    auto index = connections.begin();

    if(connections.empty()) return;
    for(;index!=connections.end();){
        if(index.value() >0 && index.value()<=m_timerOut)
        index.value() =index.value()+1;
        else if (index.value()>m_timerOut) {

            index.key()->deleteLater();
            index = connections.erase(index);
            continue;
        }
        index++;
    }
}

void SocketHandleThread::thread_done()
{
    auto index = connections.begin();
    for(;index!=connections.end();index++){
        index.key()->deleteLater();
    }
    qDebug()<<__FUNCTION__;
}
