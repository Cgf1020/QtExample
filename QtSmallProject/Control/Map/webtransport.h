#ifndef WEBTRANSPORT_H
#define WEBTRANSPORT_H

#include <QObject>

class WebTransport : public QObject
{
    Q_OBJECT

    explicit WebTransport(QObject *parent = nullptr);

public:
    // 获取实例
    static WebTransport* instance();
signals:
    // 向js发送信号
    void msgToJs(const QString& msg);


    // 将从js接收的数据发送出去  发送给外边接受的人
    void receviedJsMsg(const QString& msg);

public slots:

    // js调用此函数，接收js传入的数据
    void msgToQt(const QString& msg);

};



#endif // WEBTRANSPORT_H
