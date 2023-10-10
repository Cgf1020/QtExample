#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->Init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Init()
{
//    CreateMap();

//    CreateWaveProgressBar();

//    CreateThermometer();

//    CreateCurve();
}

void Widget::CreateCurve()
{
    _curve = new Curve(this);

    _curve->addSpline("随机测试曲线");


    ui->curve_page->layout()->addWidget(_curve);
}

void Widget::CreateMap()
{
    _Map = new Map(this);

    ui->map_page->layout()->addWidget(_Map);
}

void Widget::CreateWaveProgressBar()
{
    _WaveProgressBar = new WaveProgressBar(this);

    ui->WaveProgressBar_page->layout()->addWidget(_WaveProgressBar);
}

void Widget::CreateThermometer()
{
    _Thermometer = new Thermometer(this);
    _Thermometer->setValue(25.5);
    ui->thermometer_page->layout()->addWidget(_Thermometer);
}

void Widget::CreateBattery()
{
    _Battery = new Battery(this);
    ui->Battery_page->layout()->addWidget(_Battery);
}

void Widget::CreateDashboard()
{
    _Dashboard = new Dashboard("温度仪表盘", this);
    ui->wndu_dashboard_page->layout()->addWidget(_Dashboard);
}

void Widget::CreateQCustomPlotCurve()
{
    _QCustomPlotCurve = new QCustomPlotCurve(this);
    ui->QCustomPlot_page->layout()->addWidget(_QCustomPlotCurve);
}

void Widget::on_map_btn_clicked()
{
    if(!_Map)
    {
        CreateMap();
    }
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_WaveProgressBar_btn_clicked()
{
    if(!_WaveProgressBar)
    {
        CreateWaveProgressBar();
    }
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_pushButton_clicked()
{
    if(!_Thermometer)
    {
        CreateThermometer();
    }
    ui->stackedWidget->setCurrentIndex(2);
}


void Widget::on_pushButton_2_clicked()
{
    if(!_curve)
    {
        CreateCurve();
    }
    ui->stackedWidget->setCurrentWidget(ui->curve_page);
}


void Widget::on_Battery_btn_clicked()
{
    if(!_Battery)
        CreateBattery();

    ui->stackedWidget->setCurrentWidget(ui->Battery_page);
}

void Widget::on_wendu_dashboard_btn_clicked()
{
    if(!_Dashboard)
        CreateDashboard();

    ui->stackedWidget->setCurrentWidget(ui->wndu_dashboard_page);
}


void Widget::on_QCustomPlot_btn_clicked()
{
    if(!_QCustomPlotCurve)
    {
        CreateQCustomPlotCurve();
    }

    ui->stackedWidget->setCurrentWidget(ui->QCustomPlot_page);
}

