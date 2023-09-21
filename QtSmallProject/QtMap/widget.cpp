#include "widget.h"
#include "ui_widget.h"
#include <QDebug>


#include "webtransport.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->InitMap();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::InitMap()
{
    //创建QWebChannel
    _channel = new QWebChannel(this);


    /*应该是向通道注册对象，以便 js能够调用  注册通信类对像
     * js应该是 创建一个 webChannel对象 然后就能通信了吧,这个名称需要和 js中的对应上
    */
    _channel->registerObject(QStringLiteral("WebTransport"), WebTransport::instance());

    //将QWebChannel 对象设置到网页载体QWebEnginePage中
    ui->widget->page()->setWebChannel(_channel);

    //加载html文件 D:\MyCode\QtExample\QtSmallProject\QtMap\res\map_res  这个不清楚为啥不能使用  qrc:/map_res/index.html  or   :/map_res/index.html
    ui->widget->page()->load(QUrl("file:///D:/MyCode/QtExample/QtSmallProject/QtMap/res/map_res/index.html"));
}

