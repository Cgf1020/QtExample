#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWebChannel/QtWebChannel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void InitMap();



private:
    Ui::Widget *ui;


    QWebChannel*        _channel;
};
#endif // WIDGET_H
