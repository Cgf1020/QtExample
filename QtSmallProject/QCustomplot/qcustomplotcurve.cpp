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

void QCustomPlotCurve::addGraph(QString name, QColor color)
{
    //画布上添加曲线
    QCPGraph* Graph = _QCustomPlot->addGraph();
    Graph->setName(name);
    Graph->setLineStyle(QCPGraph::lsLine);
    Graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));

    QPen pen;
    pen.setWidthF(1.5);

    if(color.isValid())
    {
        pen.setColor(color);
    }
    else
    {
        //获取随机数
        int n = QRandomGenerator::global()->bounded(20);
        pen.setColor((Qt::GlobalColor)n);
    }
    Graph->setPen(pen);

//    int GraphCount = _QCustomPlot->graphCount();
//    _QCustomPlot->legend->addElement(0, GraphCount,  _QCustomPlot->legend->item(GraphCount));
////    _QCustomPlot->legend->addElement(1,0,plot->legend->item(2));
////    _QCustomPlot->legend->addElement(1,1,plot->legend->item(3));

}

void QCustomPlotCurve::setYaxisName(QString title)
{
    _QCustomPlot->yAxis->setLabel(title);
}

void QCustomPlotCurve::onQCustomPlotMouseWheel(QWheelEvent *event)
{
    _isEescaleAxes = false;

//    if (_QCustomPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))

    if (_QCustomPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        _QCustomPlot->axisRect()->setRangeZoom(_QCustomPlot->yAxis->orientation());
    else
        _QCustomPlot->axisRect()->setRangeZoom(_QCustomPlot->xAxis->orientation());
//        _QCustomPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
}

void QCustomPlotCurve::onQCustomPlotMouseMove(QMouseEvent *event)
{
    // 如果是鼠标左键按下
    if(event->buttons() &  Qt::LeftButton)
    {
        _isEescaleAxes = false;
    }
    else
    {
        // 获取鼠标所在位置的像素坐标
        QPoint pos = event->pos();
        // 将像素坐标转换为画布坐标系下的值
        double x = _QCustomPlot->xAxis->pixelToCoord(pos.x());
        double y = _QCustomPlot->yAxis->pixelToCoord(pos.y());

        //遍历曲线
        for (int i = 0; i < _QCustomPlot->graphCount(); ++i)
        {
            //判断哪一条曲线被选中
            if(_QCustomPlot->graph(i)->selected())
            {
                //显示锚点
                _tracer->setVisible(true);
                QCPGraph *graph = _QCustomPlot->graph(i);

                _tracer->setGraph(graph);//将锚点设置到被选中的曲线上
                _tracer->setGraphKey(x); //将游标横坐标设置成刚获得的横坐标数据x
                _tracer->setInterpolating(true); //游标的纵坐标可以通过曲线数据线性插值自动获得
                _tracer->updatePosition(); //使得刚设置游标的横纵坐标位置生效
                double xValue = _tracer->position->key();
                double yValue = _tracer->position->value();
                //显示tip框


                // 将数据点的值显示在QToolTip中
                QString text = QString("%1 x:%2,  y:%3")
                                   .arg(graph->name())
                                   .arg(QString::number(xValue))
                                   .arg(QString::number(yValue));
                QToolTip::showText(event->globalPos(), text, _QCustomPlot);
                break;
            }
            else
            {
                //没有曲线被选中，不显示锚点
                _tracer->setVisible(false);
            }}
        //重绘
        _QCustomPlot->replot();
    }
}

void QCustomPlotCurve::onQCustomPlotMousePress(QMouseEvent *event)
{
    // 如果是鼠标左键按下
    if(event->button() == Qt::RightButton)
    {
        _isEescaleAxes = true;
        _QCustomPlot->yAxis->setRange(-1,2);
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
        plotTitle->setTextColor(Qt::red);
        plotTitle->setFont(QFont("宋体", 16, QFont::Bold));
        _QCustomPlot->plotLayout()->insertRow(0);
        _QCustomPlot->plotLayout()->addElement(0, 0, plotTitle);

        //设置使用时间刻度轴
        QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
        dateTimeTicker->setDateTimeFormat("h:m:s");      //设置x轴刻度显示格式 yyyy-M-d h:m:s
        dateTimeTicker->setTickCount(5);                        //时间轴 设置显示的刻度数量
        dateTimeTicker->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);
        _QCustomPlot->xAxis->setTicker(dateTimeTicker);
        _QCustomPlot->xAxis->setTickLabelRotation(30);//设置刻度标签顺时针旋转30度

        //可以进行鼠标位置 放大缩小 拖拽 放大缩小坐标系
        _QCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);


        //鼠标悬浮曲线显示坐标点
        _tracer = new QCPItemTracer(_QCustomPlot);
        _tracer->setStyle(QCPItemTracer::tsCircle);
        _tracer->setPen(QPen(Qt::red));
        _tracer->setBrush(Qt::red);
        _tracer->setSize(6);

        _QCustomPlot->setMouseTracking(true);
    }

    //功能美化设置
    {
        //设置 Y轴范围 !!! 启动了 自适应功能的话 这设置不生效 rescaleAxes
        _QCustomPlot->yAxis->setRange(-1,2);

        _QCustomPlot->xAxis->setLabel("时间");
        _QCustomPlot->yAxis->setLabel("电线温度");
        _QCustomPlot->xAxis->setLabelColor(Qt::blue);
        _QCustomPlot->yAxis->setLabelColor(Qt::blue);//设置左轴为蓝色

        //设置轴的颜色
        _QCustomPlot->xAxis->setBasePen(QPen(QColor(109, 112, 139)));//设置下轴为红色
        _QCustomPlot->yAxis->setBasePen(QPen(Qt::blue));//设置左轴为蓝色
        _QCustomPlot->xAxis->setTickLabelColor(Qt::blue);    //设置刻度文字的颜色
        _QCustomPlot->yAxis->setTickLabelColor(Qt::blue);    //设置刻度文字的颜色


        QPen pen;
        pen.setColor(Qt::red);//主刻度红色
        pen.setWidth(2);//线宽2
        _QCustomPlot->xAxis->setTickPen(pen);
        _QCustomPlot->xAxis->setSubTickPen(QPen(Qt::blue));     //子刻度蓝色
//        _QCustomPlot->xAxis->setSubTickLengthIn(15);//子刻度向内延伸15
//        _QCustomPlot->xAxis->setSubTickLengthOut(5);//子刻度向外延伸5


        //设置背景透明
        _QCustomPlot->setBackground(Qt::transparent);
        _QCustomPlot->axisRect()->setBackground(Qt::transparent);

        //图例
        _QCustomPlot->legend->setVisible(true);
        _QCustomPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
        _QCustomPlot->legend->setBorderPen(Qt::NoPen);
        _QCustomPlot->legend->setBrush(QColor(255,255,255,0));//设置图例背景
        _QCustomPlot->legend->setFont(QFont("Helvetica", 5));
        int count = _QCustomPlot->plotLayout()->rowCount();
        // 设置图例行优先排列
        _QCustomPlot->legend->setFillOrder(QCPLayoutGrid::foColumnsFirst);
        // 设置六个图例自动换行
        _QCustomPlot->legend->setWrap(3);
        _QCustomPlot->legend->setMargins(QMargins(100,10,10,1));
        _QCustomPlot->plotLayout()->addElement(count,0,_QCustomPlot->legend);
        _QCustomPlot->plotLayout()->setRowStretchFactor(count, 0.001);



        //QCustomPlot中隐藏网格并仅显示零线
        _QCustomPlot->xAxis->grid()->setVisible(false);     //设置 x轴网格 不显示
//        _QCustomPlot->yAxis->grid()->setPen(Qt::NoPen);

        _QCustomPlot->yAxis->grid()->setPen(QPen(QColor(50, 50, 50), 1, Qt::PenStyle::SolidLine));//网格白色虚线
        _QCustomPlot->yAxis->grid()->setZeroLinePen(QPen(QColor(50, 50, 50), 1, Qt::PenStyle::SolidLine));

//            Graph->setLineStyle(QCPGraph::lsLine);
//        Graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
    }

    connect(_QCustomPlot, &QCustomPlot::mouseWheel, this, &QCustomPlotCurve::onQCustomPlotMouseWheel);
    connect(_QCustomPlot, &QCustomPlot::mouseMove, this, &QCustomPlotCurve::onQCustomPlotMouseMove);
    connect(_QCustomPlot, &QCustomPlot::mousePress, this, &QCustomPlotCurve::onQCustomPlotMousePress);

    //画布上添加曲线
    addGraph("test1");
    addGraph("test2");
    addGraph("test3");

    QTimer* timerDrawLine = new QTimer();
    timerDrawLine->start(1000);
    connect(timerDrawLine,&QTimer::timeout, this, [=](){
        TimeoutHandler();
    });
}

void QCustomPlotCurve::TimeoutHandler()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    double  now = dateTime.toTime_t();//当前时间转化为秒

    //获取曲线
    int graphCount = _QCustomPlot->graphCount();
    for(int i = 0; i < graphCount - 1; i++)
    {
        QCPGraph* Graph = _QCustomPlot->graph(i);

        if(Graph)
        {
            //添加曲线坐标点
            Graph->addData(now, 1.5);
        }
    }

    QCPGraph* Graph = _QCustomPlot->graph();
    //添加曲线坐标点
    Graph->addData(now, qSin(Graph->dataCount()/50.0)+qSin(Graph->dataCount()/50.0/0.3843)*0.25);

    if(_isEescaleAxes)
    {
        _QCustomPlot->xAxis->rescale();
//        _QCustomPlot->rescaleAxes(true);    //自适应坐标范围 x 和 y轴   曲线  ==》   xAxis->rescale() &&  Graph->rescaleValueAxis(false, true);
        _QCustomPlot->xAxis->setRange(now - 1 * 60 * 5, now);
    }

    //刷新函数
    _QCustomPlot->replot();
}





