#ifndef SOCKETHANDLE_H
#define SOCKETHANDLE_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include "httprequest.h"
// 用来控制socket的一些读写操作。一个连接一个socket。一个socket一个socketHandle
class SocketHandle :public QObject
{
    Q_OBJECT
public:
    SocketHandle();
    ~SocketHandle();
    void setSocket(qintptr handle);
public slots:
    void handleReadyread();
signals:
    void canChangeJobType(int jobType);
private:

    QTcpSocket * m_socket;
    int m_jobType =0; // 0代表繁忙，1代表不活跃，2代表不活跃了1s
    HttpRequest * m_httpRequest;



};

#endif // SOCKETHANDLE_H
