#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->Init();

    InitConnect();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::buttonClickedSlots()
{
    QObject* obj = sender();

    if(obj == ui->CustomPlot_btn)
    {
        //1. 判断是不是当前的MVC页面
        if(ui->CustomPlot_btn->text() == ui->stackedWidget->currentWidget()->objectName())
        {
            return ;
        }

        //2. 判断存在当前页面不
        if(int Index = this->findWidgetIndex(ui->CustomPlot_btn->text()); Index != -1)
        {
            ui->stackedWidget->setCurrentIndex(Index);
            return;
        }

        //3. 插入一个页面
        ui->stackedWidget->addWidget(_QCustomPlotCurve);
        _MVC->setObjectName(ui->CustomPlot_btn->text());
        ui->stackedWidget->setCurrentWidget(_QCustomPlotCurve);
    }
    else if(obj == ui->MVC_btn)
    {
        //1. 判断是不是当前的MVC页面
        if(ui->MVC_btn->text() == ui->stackedWidget->currentWidget()->objectName())
        {
            return ;
        }

        //2. 判断存在当前页面不
        if(int Index = this->findWidgetIndex(ui->MVC_btn->text()); Index != -1)
        {
            ui->stackedWidget->setCurrentIndex(Index);
            return;
        }

        //3. 插入一个页面
        ui->stackedWidget->addWidget(_MVC);
        _MVC->setObjectName(ui->MVC_btn->text());
        ui->stackedWidget->setCurrentWidget(_MVC);
    }
}

void Widget::Init()
{
    {
        _QCustomPlotCurve = new QCustomPlotCurve(this);
        _QCustomPlotCurve->hide();
    }

    {
        _MVC = new MVC(this);
        _MVC->hide();
    }

}

void Widget::InitConnect()
{
    //初始化 CustomPlot按钮链接
    connect(ui->CustomPlot_btn, &QPushButton::pressed, this, &Widget::buttonClickedSlots);

    connect(ui->MVC_btn, &QPushButton::pressed, this, &Widget::buttonClickedSlots);
}

int Widget::findWidgetIndex(QString name)
{
    int widgetIndex = -1;

    for(int i = 0; i < ui->stackedWidget->count(); i++)
    {
        if(ui->stackedWidget->widget(i)->objectName() == name)
        {
            widgetIndex = i;
        }
    }

    return widgetIndex;
}



//void Widget::CreateMVC()
//{
//    _MVC = new MVC(this);
//    ui->MVC_page->layout()->addWidget(_MVC);
//}



//void Widget::on_MVC_btn_clicked()
//{
//    if(!_MVC)
//    {
//        CreateMVC();
//    }
//    ui->stackedWidget->setCurrentWidget(ui->MVC_page);
//}

