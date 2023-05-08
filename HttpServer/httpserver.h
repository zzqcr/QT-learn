#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QTcpServer>
#include "connectpool.h"
// 负责监听端口，分发连接
class HttpServer : public QTcpServer
{
    Q_OBJECT
public:
    HttpServer(QObject *parent =nullptr);
    ~HttpServer();
    bool startListen(int port);
    void incomingConnection(qintptr handle)override;
};

#endif // HTTPSERVER_H
