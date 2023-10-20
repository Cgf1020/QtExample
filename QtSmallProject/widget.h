#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "MVC/mvc.h"
#include "QCustomplot/qcustomplotcurve.h"




QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void buttonClickedSlots();

private:
    void Init();

    void InitConnect();

    int findWidgetIndex(QString name);

private:
    Ui::Widget *ui;


    QCustomPlotCurve*   _QCustomPlotCurve{NULL};
    MVC*                _MVC{NULL};                       //MVC
};





















#endif // WIDGET_H
