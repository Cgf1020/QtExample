#ifndef CURVE_H
#define CURVE_H


/*曲线坐标图
 *1.动态更新曲线
 *2.支持设置坐标轴刻度数量和范围
 *3.支持滚轮缩放                      待开发
 *4.支持鼠标悬停到线上显示坐标点             待开发          https://blog.csdn.net/lusanshui/article/details/84395651
 *
 *
 *
 *
 *
 *
 *
*/

#include <QWidget>
#include <QList>
#include <QChart>
#include <QChartView>
#include <QValueAxis>   //坐标轴类
#include <QSplineSeries>    //曲线类

//! 使用QChart需要使用对应的命名空间
//! 使用方法有如下两种（更改宏定义判断条件即可更换调用方法）
#if true
QT_CHARTS_USE_NAMESPACE     // 定义好的宏定义使用命名空间
#else
using namespace QtCharts;   // 常规使用命名空间的方法
#endif



namespace Ui {
class Curve;
}

class Curve : public QWidget
{
    Q_OBJECT

public:
    explicit Curve(QWidget *parent = nullptr);
    ~Curve();



public:
    /*添加 曲线
     * @name 曲线的名字
    */
    void addSpline(QString name);


    /* 更新曲线的坐标点
     * @name：曲线的标识
     * @yValue：曲线的y轴的值
    */
    void updateSpline(QString name, double yValue);

    /* 设置x轴
     * @xScalesNum: 刻度数量
     * @XScalesSpace: 刻度间隔   单位/s
    */
    void setXaxis(int xScalesNum, int XScalesSpace);

    /* 设置y轴
     * @
    */
    void setYaxis();

    //设置滚轮缩放系数
    void setScaleFactor(double scaleFactor) noexcept;


protected:
    //鼠标滚轮事件
    void wheelEvent(QWheelEvent *event) override;


private slots:
    void InitStyleSheet();

    void InitChartView();

    void TimeoutHandler();

private:
    //这个曲线坐标的名称
    QString         _curveName{"曲线坐标图"};
    int             _xScalesNum{ 6 };                   //x轴的刻度数量，默认为6个一个小时
    int             _XScalesSpace{ 5 };                   //刻度间隔   单位/s
    double          _scaleFactor{ 1 };                  //滚轮缩放系数


    //抽象意思应该是画布, 坐标 和 曲线在上面进行绘制
    QChartView*     _chartView;
    QChart*         _chart;     //


    QList<QSplineSeries*>       _SplineList;            //保存曲线图表上的曲线对象

private:
    Ui::Curve *ui;

};

#endif // CURVE_H
