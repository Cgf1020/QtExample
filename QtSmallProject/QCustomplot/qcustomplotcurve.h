#ifndef QCUSTOMPLOTCURVE_H
#define QCUSTOMPLOTCURVE_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class QCustomPlotCurve;
}

class QCustomPlotCurve : public QWidget
{
    Q_OBJECT

public:
    explicit QCustomPlotCurve(QWidget *parent = nullptr);
    ~QCustomPlotCurve();

    /* 添加曲线
    */
    void addGraph(QString name);

    /* 设置y轴的标题
    */
    void setYaxisName(QString title);

private slots:
    //QCustomPlot 滚轮事件
    void onQCustomPlotMouseWheel(QWheelEvent *event);

    //QCustomPlot 鼠标移动事件
    void onQCustomPlotMouseMove(QMouseEvent *event);

    //QCustomPlot 鼠标点击事件
    void onQCustomPlotMousePress(QMouseEvent *event);



private:
    void InitForm();

    void TimeoutHandler();


private:
    Ui::QCustomPlotCurve *ui;

    QCustomPlot*        _QCustomPlot;
    bool                _isEescaleAxes{true};     //是否调整范围自适应坐标轴， 滚轮事件、拖动事件的时候不调整
};

#endif // QCUSTOMPLOTCURVE_H
