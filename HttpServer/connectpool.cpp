#include "connectpool.h"

Q_GLOBAL_STATIC(ConnectPool, pool)
ConnectPool *ConnectPool::instance()
{
    return pool;
}

SocketHandleThread *ConnectPool::getSocketHandleThread()
{
    static int allConnect=0;
    qDebug()<<u8"当前连接数"<<m_curConnect;
    qDebug()<<u8"总连接数"<<allConnect;

    if(isFull()) return nullptr;
    if(threads.size()<m_maxThread) {
        m_curConnect++;
        return addThread();
    }
    allConnect++;
    mutex.lock();
    auto index = threads.begin();
    int min =m_maxConnect;
    for(;index!=threads.end();index++){
        if(index.value() <min){
            min =index.value();
        }
    }
    for(index =threads.begin();index!=threads.end();index++){
        if(index.value() ==min){
            qDebug()<<u8"连接数+1";
            m_curConnect++;
            index.value()++;
            mutex.unlock();
            return index.key();
        }
    }
    mutex.unlock();
    return nullptr;
}

void ConnectPool::setMaxConnect(int maxNum)
{
    m_maxConnect = maxNum;
}

int ConnectPool::getMaxconnect()
{
    return m_maxConnect;
}

void ConnectPool::setMaxThread(int maxNum)
{
    m_maxThread = maxNum;
}

int ConnectPool::getMaxThread()
{
    return m_maxThread;
}

SocketHandleThread *ConnectPool::addThread()
{
    mutex.lock();
    if(threads.size()<m_maxThread){
        SocketHandleThread * newThread = new SocketHandleThread;
        connect(newThread,&SocketHandleThread::oneSocketHandleClose,this,[=](SocketHandleThread* ptr){
            qDebug()<<u8"连接数-1";
            m_curConnect --;
            threads[ptr]--;
        });
        connect(this,&ConnectPool::closeAll,newThread,&SocketHandleThread::thread_done);
        threads.insert(newThread,0);
        mutex.unlock();
        return newThread;
    }
    mutex.unlock();
    return nullptr;
}

void ConnectPool::timerEvent(QTimerEvent *ev)
{


}

bool ConnectPool::isFull()
{
    if(m_curConnect==m_maxConnect) return true;
    else {
        return false;
    }
}

void ConnectPool::close()
{
    qDebug()<<__FUNCTION__;
    emit closeAll();
}




