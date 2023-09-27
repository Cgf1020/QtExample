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

    CreateWaveProgressBar();



}

void Widget::CreateWaveProgressBar()
{
    _WaveProgressBar = new WaveProgressBar(this);

    ui->WaveProgressBar_page->layout()->addWidget(_WaveProgressBar);
}


void Widget::on_WaveProgressBar_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

