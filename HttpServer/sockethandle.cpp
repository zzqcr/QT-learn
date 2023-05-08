#include "sockethandle.h"
#include <QTime>
SocketHandle::SocketHandle()
{

    m_socket = new QTcpSocket;
    m_httpRequest = new HttpRequest;
    connect(m_socket,&QTcpSocket::readyRead,this,&SocketHandle::handleReadyread);
    connect(m_socket,&QTcpSocket::disconnected,this,[=](){
        qDebug()<<"socket disconnected";
        m_socket->close();
        emit canChangeJobType(1);
    });



}

SocketHandle::~SocketHandle()
{
    qDebug()<<__FUNCTION__;
    m_socket->close();
    m_socket->deleteLater();
    delete m_httpRequest;

}

void SocketHandle::setSocket(qintptr handle)
{
    m_socket->setSocketDescriptor(handle);
}

void SocketHandle::handleReadyread()
{
    qDebug()<<__FUNCTION__<<this->thread();
    m_httpRequest->readSocketData(m_socket);
    // 下面开始写判断函数,根据url判断访问的网站
    qDebug()<<m_httpRequest->getUrl();
    if(m_httpRequest->getUrl()==""){

    }
    else {
//        // 为了测试，假设每个socket都进行两次冒泡排序操作
//        QTime time;
//        time.start();
//        QVector<int> arr;
//        for(int i=0;i<1000;i++){
//            arr.append(qrand()%1000);
//        }
//        int len = arr.size();
//        for (int i = 0; i < len - 1; i++) {
//            for (int j = 0; j < len - 1 - i; j++) {
//                if (arr[j] > arr[j+1]) {        // 相邻元素两两对比
//                    int temp = arr[j+1];        // 元素交换
//                    arr[j+1] = arr[j];
//                    arr[j] = temp;
//                }
//            }
//        }

//        for (int i = 0; i < len - 1; i++) {
//            for (int j = 0; j < len - 1 - i; j++) {
//                if (arr[j] < arr[j+1]) {        // 相邻元素两两对比
//                    int temp = arr[j+1];        // 元素交换
//                    arr[j+1] = arr[j];
//                    arr[j] = temp;
//                }
//            }
//        }
//        qDebug()<<u8"用时"<<time.elapsed();


        m_socket->write(QString(u8"HTTP/1.1 200 OK\r\nserver: ZZQServer\r\n\r\n你访问的网站是%1%2").
                        arg(m_httpRequest->getUrl().split('/').back(),QString("\r\n")).toUtf8());
    }
    // 判断不同的ip地址 m_socket->peerAddress()
    m_socket->close();

}

