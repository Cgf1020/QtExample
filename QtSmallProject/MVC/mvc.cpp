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
    listView_ = new TESTMVC::ListView(this);

    for(int i = 0; i < 5; i++)
        listView_->AddGroup("分组");


    tableView_ = new TableView(this);



    this->layout()->addWidget(tableView_);
    this->layout()->addWidget(listView_);
}
