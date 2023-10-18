#include "mvc.h"
#include "ui_mvc.h"

MVC::MVC(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MVC)
{
    ui->setupUi(this);

    Init();
}

MVC::~MVC()
{
    delete ui;
}

void MVC::Init()
{
    //1.
    _MVC_1_ListModel = new MVC_1_ListModel(this);
    ui->tabWidget->addTab(_MVC_1_ListModel, "_MVC_1_ListModel");



}
