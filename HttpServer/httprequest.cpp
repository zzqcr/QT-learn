#include "httprequest.h"

HttpRequest::HttpRequest()
{

}

void HttpRequest::readSocketData(QTcpSocket * socket)
{
    qDebug()<<__FUNCTION__;
    QByteArray data = socket->readAll();
    qDebug()<<__FUNCTION__<<u8"读取数据为"<<data;
    if (!data.contains("\r\n"))
    {
        socket->write(u8"http协议格式不正确");
        qDebug(u8"HttpRequest: http协议格式不正确");

        return;
    }

    QString strData (data.trimmed());

    data.clear();
    if (!strData.isEmpty())
    {
        QStringList list = strData.split("\r\n\r\n");
        QStringList hearList;
        if(list.size()==1){
            hearList = list.at(0).split("\r\n");
        }
        else {
            hearList = list.at(0).split("\r\n");
            m_requestBodyData = list.at(1).toUtf8();
        }
        if(hearList.size()>0){
            QStringList list =  hearList.at(0).split(" ");
            // 判断http协议行的格式是否正确
            if(list.size()==3){
                m_requestLine.method = hearList.at(0).split(" ").at(0).trimmed();
                m_requestLine.url = hearList.at(0).split(" ").at(1).trimmed();
                m_requestLine.version = hearList.at(0).split(" ").at(2).trimmed();
                qDebug()<<__FUNCTION__<<"read requestLine ok"<<m_requestLine.method<<m_requestLine.url<< m_requestLine.version;
            }
            else {
                socket->write(u8"http协议格式不正确");
                qDebug(u8"HttpRequest: http协议格式不正确");
                return;
            }

        }
        else {
            qDebug()<<__FUNCTION__<<"read requestLine false";
        }

        for(int i=1;i<hearList.size();i++){
            if(hearList.at(i).contains(':')){
                m_requestHeader.insert(hearList.at(i).split(":").at(0).trimmed(),hearList.at(i).split(":").at(1).trimmed());
            }
        }

    }
}


HttpLine HttpRequest::getRequestLine()
{
    return m_requestLine;
}

QMap<QString, QString> HttpRequest::getRequestHeader()
{
    return m_requestHeader;
}

QByteArray HttpRequest::getRequestBody()
{
    return m_requestBodyData;
}

QString HttpRequest::getVersion()
{
    return m_requestLine.version;
}

QString HttpRequest::getMethod()
{
    return m_requestLine.method;
}

QString HttpRequest::getUrl()
{
    return m_requestLine.url;
}

