#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include <QByteArray>
#include <QObject>
#include <QTcpSocket>
// 解析http协议的类,http由请求行，请求头和请求数据组成
struct HttpLine{
    QString version;
    QString method;
    QString url;
};
class HttpRequest
{


public:
    HttpRequest();
    void readSocketData(QTcpSocket * socket);
    HttpLine getRequestLine();
    QMap<QString,QString> getRequestHeader();
    QByteArray getRequestBody();
    QString getVersion();
    QString getMethod();
    QString getUrl();

private:
    HttpLine m_requestLine;
    QMap<QString,QString> m_requestHeader;
    QByteArray m_requestBodyData;

};

#endif // HTTPREQUEST_H
