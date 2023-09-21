#include "webtransport.h"
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>

WebTransport::WebTransport(QObject *parent)
    : QObject{parent}
{

}

WebTransport *WebTransport::instance()
{
    static WebTransport* self = nullptr;
    static QMutex lock;
    if (!self)
    {
        QMutexLocker locker(&lock);
        if (!self)
        {
            self = new WebTransport;
        }
    }
    return self;
}

void WebTransport::msgToQt(const QString &msg)
{
    qDebug() << "Qt接收到的信息: " << msg;

    //将此消息发送出去
    QString str = "Qt发送的消息：通信建立完成";
    emit receviedJsMsg(str);
}
