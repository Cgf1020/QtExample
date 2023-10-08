#include "curve.h"
#include "ui_curve.h"


#include <QDebug>
#include <QGridLayout>
#include <QGraphicsLayout>
#include <QTimer>
#include <QDateTime>
#include <QDateTimeAxis>

Curve::Curve(QString curveName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Curve),
    _curveName(curveName)
{
    ui->setupUi(this);


    //无边框
    //    setWindowFlag(Qt::FramelessWindowHint);


    this->InitChartView();

    this->InitStyleSheet();



    QTimer* timerDrawLine = new QTimer();
    timerDrawLine->start(1000);
    connect(timerDrawLine,&QTimer::timeout,[=](){

        static int i = 0;
        i++;


        if(i >= 30)
           {
            timerDrawLine->stop();
        }

        TimeoutHandler();
    });
}

Curve::~Curve()
{
    delete ui;
}

void Curve::addSpline(QString name)
{
    //1.创建曲线
    QSplineSeries* lineSeries = new QSplineSeries();
    lineSeries->setName(name);                  //设置曲线的名称
    _chart->addSeries(lineSeries);              //把曲线添加到QChart的实例chart中

    //2.把曲线关联到坐标轴
    lineSeries->attachAxis(_chart->axes(Qt::Horizontal).at(0));
    lineSeries->attachAxis(_chart->axes(Qt::Vertical).at(0));
}

void Curve::updateSpline(QString name, double yValue)
{
    QLineSeries* lineSeries = NULL;

    //获取曲线
    foreach (auto var, _SplineList) {
        if(var->name() == name)
        {
            lineSeries = var;

            //获取随机数
            qsrand(QTime::currentTime().second());
            int rand  = qrand() % 100;  //获取0~10之间的数

            //获取之前的ser
            lineSeries = (QLineSeries *)_chartView->chart()->series().at(0);


            QDateTime currentTime = QDateTime::currentDateTime();

            _chart->axes(Qt::Horizontal).at(0)->setMin(QDateTime::currentDateTime().addSecs(-1*30));


            QDateTimeAxis *axisX = dynamic_cast<QDateTimeAxis*>(_chart->axes(Qt::Horizontal).at(0));

            //更新数据
            lineSeries->append(axisX->max().toMSecsSinceEpoch(),rand);
        }
    }
}

void Curve::wheelEvent(QWheelEvent *event)
{
    const double factor = 1.5;  //缩放比例
    const QPoint curPos = event->pos();
    QPointF curVal = _chart->mapToValue(QPointF(curPos));

    QDateTimeAxis *axisX = dynamic_cast<QDateTimeAxis*>(_chart->axes(Qt::Horizontal).at(0));


    const double xMin = static_cast<double>(axisX->min().toMSecsSinceEpoch());
    const double xMax = static_cast<double>(axisX->max().toMSecsSinceEpoch());
    const double xCentral = curVal.x();

    double leftOffset;
    double rightOffset;


    qDebug() << "angleDelta x:" << event->angleDelta().x() << " y:" << event->angleDelta().y();

    if (event->angleDelta().y() > 0)
    {
        //放大
        leftOffset = 1.0 / factor * (xCentral - xMin);
        rightOffset = 1.0 / factor * (xMax - xCentral);

        _chart->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-5*30), QDateTime::currentDateTime().addSecs(5*30));
    }
    else
    {
        //缩小
        leftOffset = 1.0 * factor * (xCentral - xMin);
        rightOffset = 1.0 * factor * (xMax - xCentral);

        _chart->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-1*30), QDateTime::currentDateTime().addSecs(1*30));
    }
//    axisX->setRange(xCentral - leftOffset, xCentral + rightOffset);


}

void Curve::InitStyleSheet()
{
    ui->gridLayout->setContentsMargins(0, 0, 0, 0);


    //设置ChartView 的背景颜色 为 暗黑色
    _chartView->setStyleSheet("background-color:#242b3b;");

    //设置chart 的边缘为0
    _chartView->chart()->layout()->setContentsMargins(0, 0, 0, 0);

    //设置chart 的背景颜色
    _chart->setBackgroundVisible(false);
    //    _chartView->chart()->setBackgroundBrush(QColor(40,40,74));

    //设置标题字体和颜色
    _chartView->chart()->setTitleFont(QFont("Arial", 12));
    _chartView->chart()->setTitleBrush(Qt::yellow);

    //设置坐标轴线条粗细和颜色：
    _chartView->chart()->axes().at(0)->setLabelsColor(Qt::yellow);
    _chartView->chart()->axes().at(0)->setTitleBrush(Qt::yellow);
    _chartView->chart()->axes().at(1)->setLabelsColor(Qt::yellow);
    _chartView->chart()->axes().at(1)->setTitleBrush(Qt::yellow);


    //设置线的name
    //    QSplineSeries* line = static_cast<QSplineSeries*>(_chartView->chart()->series().at(0));

    //    //设置图例位置和字体大小：
    //    //    _chartView->chart()->legend()->setFont(QFont("Arial", 10));
    //    _chartView->chart()->legend()->setColor(Qt::yellow);
    //    _chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
}

void Curve::InitChartView()
{
    //初始化QChart   !!!不知道这个的抽象含义是什么
    _chart = new QChart();

    //创建曲线
    QSplineSeries* lineSeries = new QSplineSeries();
    lineSeries->setName("随机测试曲线");     //设置曲线的名称


    _chart->addSeries(lineSeries);            //把曲线添加到QChart的实例chart中
    _chart->setTitle(_curveName);

    //创建坐标轴
    QDateTimeAxis *axisX = new QDateTimeAxis(); //x轴为时间轴
    QValueAxis *axisY = new QValueAxis();

    axisX->setTitleText("时间(分:秒)");          //设置x坐标轴
    axisX->setGridLineVisible(false);           // 隐藏背景网格X轴框线
    axisX->setLabelsAngle(0);                   // x轴显示的文字倾斜角度
    axisX->setTickCount(10);                    // 轴上点的个数
    axisX->setFormat("mm:ss");

    axisY->setTickCount(10);                    //设置y坐标轴上的格点
    axisY->setMin(-5);
    axisY->setMax(20);
    axisY->setGridLineVisible(false);   //设置网格不显示

    QFont font("Microsoft YaHei",8,QFont::Normal);//设置坐标轴显示的名称  微软雅黑。字体大小8
    axisX->setTitleFont(font);
    axisY->setTitleFont(font);
    axisX->setTitleText("X-Test");
    axisY->setTitleText("mm:ss");

    _chart->addAxis(axisX,Qt::AlignBottom);          //将坐标轴添加到QChart 以什么方式添加的
    _chart->addAxis(axisY,Qt::AlignLeft);

    lineSeries->attachAxis(axisX);       //把曲线关联到坐标轴
    lineSeries->attachAxis(axisY);

    //创建画布
    _chartView = new QChartView(this);
    _chartView->setChart(_chart);                         //将chart添加到画布上
    _chartView->setRenderHint(QPainter::Antialiasing);   // 设置渲染：抗锯齿，如果不设置那么曲线就显得不平滑

    //设置栅格布局
    ui->gridLayout->addWidget(_chartView);




}

void Curve::TimeoutHandler()
{
    // 更新X轴的范围
    //获取当前时间
    QDateTime currentTime = QDateTime::currentDateTime();


    //获取随机数
    qsrand(QTime::currentTime().second());
    int rand  = qrand() % 100;  //获取0~10之间的数


    //获取初始化的qchart
    QChart *chart = _chartView->chart();

    //获取之前的ser
    QLineSeries* lineSeries = (QLineSeries *)_chartView->chart()->series().at(0);


    //更新数据
    lineSeries->append(currentTime.toMSecsSinceEpoch(),cos(rand));


//    chart->axes(Qt::Horizontal).at(0)->setRange(QDateTime::currentDateTime().addSecs(-1*30), QDateTime::currentDateTime().addSecs(2));

    chart->axes(Qt::Horizontal).at(0)->setMin(QDateTime::currentDateTime().addSecs(-1*30));
    chart->axes(Qt::Horizontal).at(0)->setMax(QDateTime::currentDateTime().addSecs(2));
}
