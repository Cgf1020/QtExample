#include "mvc.h"
#include "ui_mvc.h"

#include <QDebug>
#include <QPushButton>

MVC::MVC(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MVC)
{
    ui->setupUi(this);

    Init();

    InitConnect();
}

MVC::~MVC()
{
    delete ui;
}

void MVC::Init()
{





}

void MVC::InitConnect()
{
    //连接 ListView按钮
    connect(ui->ListView_btn, &QPushButton::clicked, this, &MVC::onButtonClick);

    connect(ui->QQFriendList_btn, &QPushButton::clicked, this, &MVC::onButtonClick);

    connect(ui->TableView_btn, &QPushButton::clicked, this, &MVC::onButtonClick);
}

void MVC::onButtonClick(bool checked)
{
    QObject* obj = sender();


    if(obj == ui->ListView_btn)
    {
        if(ui->ListView_btn->text() == ui->tabWidget->tabText(ui->tabWidget->currentIndex()))
            return;

        if(int tabIndex = this->findTabIndex(ui->ListView_btn->text());  tabIndex != -1)
        {
            ui->tabWidget->setCurrentIndex(tabIndex);
            return;
        }

        //创建插入
        if(!listView_)
        {
            listView_ = new TESTMVC::ListView(this);
            listView_->hide();
            for(int i = 0; i < 5; i++)
                listView_->AddGroup("分组");
        }

        ui->tabWidget->addTab(listView_, ui->ListView_btn->text());
        ui->tabWidget->setCurrentWidget(listView_);
    }
    else if(obj == ui->QQFriendList_btn)
    {
        if(ui->QQFriendList_btn->text() == ui->tabWidget->tabText(ui->tabWidget->currentIndex()))
            return;

        if(int tabIndex = this->findTabIndex(ui->QQFriendList_btn->text());  tabIndex != -1)
        {
            ui->tabWidget->setCurrentIndex(tabIndex);
            return;
        }

        //创建插入
        if(!FriendTree_)
        {
            FriendTree_ = new qqfriendlist::FriendTree(this);
            FriendTree_->hide();
            for(int i = 0; i < 5; i++)
                FriendTree_->addGroup("分组");
        }
        ui->tabWidget->addTab(FriendTree_, ui->QQFriendList_btn->text());
        ui->tabWidget->setCurrentWidget(FriendTree_);
    }
    else if(obj == ui->TableView_btn)
    {
        if(ui->TableView_btn->text() == ui->tabWidget->tabText(ui->tabWidget->currentIndex()))
            return;

        if(int tabIndex = this->findTabIndex(ui->TableView_btn->text());  tabIndex != -1)
        {
            ui->tabWidget->setCurrentIndex(tabIndex);
            return;
        }

        //创建插入
        if(!tableView_)
        {
            tableView_ =  new TableView(this);

            tableView_->addRowData();

            tableView_->hide();

        }
        ui->tabWidget->addTab(tableView_, ui->TableView_btn->text());
        ui->tabWidget->setCurrentWidget(tableView_);
    }

}

int MVC::findTabIndex(QString name)
{
    int tabIndex = -1;
    for (int i = 0; i < ui->tabWidget->count(); i++) {
        if (ui->tabWidget->tabText(i) == name) {
            tabIndex = i;
            break;
        }
    }
    return tabIndex;
}











