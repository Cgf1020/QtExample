#include "qcustomplotcurve.h"
#include "ui_qcustomplotcurve.h"

#include <QDebug>

QCustomPlotCurve::QCustomPlotCurve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCustomPlotCurve)
{
    ui->setupUi(this);

    InitForm();
}

QCustomPlotCurve::~QCustomPlotCurve()
{
    delete ui;
}

void QCustomPlotCurve::addGraph(QString name)
{
    //画布上添加曲线
    QCPGraph* Graph = _QCustomPlot->addGraph();
    Graph->setName(name);
}

void QCustomPlotCurve::setYaxisName(QString title)
{
    _QCustomPlot->yAxis->setLabel(title);
}

void QCustomPlotCurve::onQCustomPlotMouseWheel(QWheelEvent *event)
{
    _isEescaleAxes = false;

    if (_QCustomPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        _QCustomPlot->axisRect()->setRangeZoom(_QCustomPlot->xAxis->orientation());
    else if (_QCustomPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        _QCustomPlot->axisRect()->setRangeZoom(_QCustomPlot->yAxis->orientation());
    else
        _QCustomPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
}

void QCustomPlotCurve::onQCustomPlotMouseMove(QMouseEvent *event)
{
    // 如果是鼠标左键按下
    if(event->button() == Qt::LeftButton)
    {
        _isEescaleAxes = false;
    }
}

void QCustomPlotCurve::onQCustomPlotMousePress(QMouseEvent *event)
{
    // 如果是鼠标左键按下
    if(event->button() == Qt::RightButton)
    {
        _isEescaleAxes = true;
        _QCustomPlot->replot();
    }
}

void QCustomPlotCurve::InitForm()
{
    //功能
    {
        //创建画布
        _QCustomPlot = new QCustomPlot(this);
        this->layout()->addWidget(_QCustomPlot);

        //添加标题
        QCPTextElement *plotTitle = new QCPTextElement(_QCustomPlot);
        plotTitle->setText("导线温度曲线");
        plotTitle->setFont(QFont("宋体", 16, QFont::Bold));
        _QCustomPlot->plotLayout()->insertRow(0);
        _QCustomPlot->plotLayout()->addElement(0, 0, plotTitle);


        //设置使用时间刻度轴
        QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
        dateTimeTicker->setDateTimeFormat("yyyy-M-d h:m:s");      //设置x轴刻度显示格式
        dateTimeTicker->setTickCount(5);                        //时间轴 设置显示的刻度数量
        dateTimeTicker->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);
        _QCustomPlot->xAxis->setTicker(dateTimeTicker);
        _QCustomPlot->xAxis->setTickLabelRotation(30);//设置刻度标签顺时针旋转30度

        //可以进行鼠标位置 放大缩小 拖拽 放大缩小坐标系
        _QCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);
    }

    //操作设置
    {
        //设置 Y轴范围 !!! 启动了 自适应功能的话 这设置不生效 rescaleAxes
        _QCustomPlot->yAxis->setRange(-30,30);

        _QCustomPlot->xAxis->setLabel("时间");
        _QCustomPlot->yAxis->setLabel("电线温度");
    }



    connect(_QCustomPlot, &QCustomPlot::mouseWheel, this, &QCustomPlotCurve::onQCustomPlotMouseWheel);
    connect(_QCustomPlot, &QCustomPlot::mouseMove, this, &QCustomPlotCurve::onQCustomPlotMouseMove);
    connect(_QCustomPlot, &QCustomPlot::mousePress, this, &QCustomPlotCurve::onQCustomPlotMousePress);



    //画布上添加曲线
    QCPGraph* Graph = _QCustomPlot->addGraph();
    Graph->setName("daf");

    QTimer* timerDrawLine = new QTimer();
    timerDrawLine->start(1000);
    connect(timerDrawLine,&QTimer::timeout,[=](){
        TimeoutHandler();
    });
}

void QCustomPlotCurve::TimeoutHandler()
{
    //获取曲线
    QCPGraph* Graph = _QCustomPlot->graph();

    //添加曲线坐标点
    QDateTime dateTime = QDateTime::currentDateTime();
    double  now = dateTime.toTime_t();//当前时间转化为秒
    Graph->addData(now, qSin(Graph->dataCount()/50.0)+qSin(Graph->dataCount()/50.0/0.3843)*0.25);

    if(_isEescaleAxes)
    {
        _QCustomPlot->rescaleAxes(true);    //自适应坐标范围 x 和 y轴   曲线  ==》   xAxis->rescale() &&  Graph->rescaleValueAxis(false, true);
        _QCustomPlot->xAxis->setRange(now - 1 * 5, now);
    }

    //刷新函数
    _QCustomPlot->replot();
}





