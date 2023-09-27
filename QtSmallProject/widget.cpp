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
    CreateMap();

    CreateWaveProgressBar();

    CreateThermometer();
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

void Widget::on_map_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_WaveProgressBar_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

