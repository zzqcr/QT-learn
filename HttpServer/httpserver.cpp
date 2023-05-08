#include "httpserver.h"

HttpServer::HttpServer(QObject *parent)
{
    this->setParent(parent);
    // 先注册qintptr类型
    qRegisterMetaType<qintptr>("qintptr");
}

HttpServer::~HttpServer()
{
    ConnectPool::instance()->close();
}

bool HttpServer::startListen(int port)
{
    return this->listen(QHostAddress::Any,port);

}

void HttpServer::incomingConnection(qintptr handle)
{
    qDebug()<<__FUNCTION__;
    SocketHandleThread * socketThread = ConnectPool::instance()->getSocketHandleThread();
    if (socketThread)
    {
        // 在其他线程里执行setSocket 并把参数传过去
        QMetaObject::invokeMethod(socketThread, "setSocket", Qt::QueuedConnection, Q_ARG(qintptr,handle));
    }
    else
    {
        // Reject the connection
        qDebug("HttpServer: Too many incoming connections");
        QTcpSocket* socket=new QTcpSocket(this);
        socket->setSocketDescriptor(handle);
        connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
        socket->write("HTTP/1.1 503 too many connections\r\nConnection: close\r\n\r\nToo many connections\r\n");
        socket->disconnectFromHost();
    }
}
