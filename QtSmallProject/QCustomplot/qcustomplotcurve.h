#ifndef QCUSTOMPLOTCURVE_H
#define QCUSTOMPLOTCURVE_H




/* QCustomPlot 学习
 * QCPGraph 为折线图 https://blog.csdn.net/u010258235/article/details/108482979
 * https://blog.csdn.net/qq_23208659/article/details/117031802
 *
*/


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
    QCPItemTracer*      _tracer;

    bool                _isEescaleAxes{true};     //是否调整范围自适应坐标轴， 滚轮事件、拖动事件的时候不调整
};

#endif // QCUSTOMPLOTCURVE_H
