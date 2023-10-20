#include "multilevelmenu.h"
#include "ui_multilevelmenu.h"

#include <QDebug>


MultiLevelMenu::MultiLevelMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiLevelMenu)
{
    ui->setupUi(this);

    init();
}

MultiLevelMenu::~MultiLevelMenu()
{
    delete ui;
}

void MultiLevelMenu::addTopLevelItem(QString name)
{
    //创建顶层节点
    QTreeWidgetItem *topItem = new QTreeWidgetItem(ui->treeWidget);
    topItem->setText(0, name);
    topItem->setCheckState(0, Qt::Checked);

    ui->treeWidget->addTopLevelItem(topItem);
}

void MultiLevelMenu::addSubLevelItem(QString name)
{
    //获取当前的父节点的item
    QTreeWidgetItem *item = ui->treeWidget->currentItem();

    QTreeWidgetItem *item11 = new QTreeWidgetItem(item);

    item11->setText(0, name);

    //设置数据,可以带多种数据
    item11->setData(0, Qt::UserRole, 100/*人员数量*/);
    item11->setData(0, Qt::UserRole+1, u8"肖恩"/*负责人名字*/);
}


void MultiLevelMenu::init()
{
    //隐藏treeWidget的Header
    ui->treeWidget->setHeaderHidden(true);


    //打开右键菜单属性
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);


    //New 一个新的按钮
    QPushButton *topLevelButton = new QPushButton("Top Level Button");
    auto topLevelItem = new QTreeWidgetItem();     //创建一个 TreeItem 容器用于后来装载控件
    ui->treeWidget->addTopLevelItem(topLevelItem); //目的是添加一行 Item
    //设置 Item 内控件，0 是第几列
    ui->treeWidget->setItemWidget(topLevelItem, 0, topLevelButton);




    //添加顶层节点
    QTreeWidgetItem *topItem1 = new QTreeWidgetItem(ui->treeWidget);
    topItem1->setText(0,u8"角色");
//    topItem1->setCheckState(0, Qt::Checked);
    ui->treeWidget->addTopLevelItem(topItem1);

    //右键菜单
    m_menu = new QMenu(ui->treeWidget);
    m_menu->addAction(u8"添加");
    m_menu->addAction(u8"删除");

    QTreeWidgetItem *item11 = new QTreeWidgetItem(topItem1);
    item11->setText(0,u8"野蛮人");
//    item11->setCheckState(0, Qt::Checked);
    //设置数据,可以带多种数据
    item11->setData(0,Qt::UserRole,100/*人员数量*/);
    item11->setData(0,Qt::UserRole+1,u8"肖恩"/*负责人名字*/);

    //获得数据
    item11->data(0,Qt::UserRole).toInt();
    item11->data(0,Qt::UserRole+1).toString();

    QTreeWidgetItem *item12 = new QTreeWidgetItem(topItem1);
    item12->setText(0,u8"猎魔人");
    QTreeWidgetItem *item13 = new QTreeWidgetItem(topItem1);
    item13->setText(0,u8"死灵法师");

    QTreeWidgetItem *item14 = new QTreeWidgetItem(topItem1);
    item14->setText(0,u8"圣骑士");

    QTreeWidgetItem *item15 = new QTreeWidgetItem(topItem1);
    item15->setText(0,u8"女巫");

    QTreeWidgetItem *item16 = new QTreeWidgetItem(topItem1);
    item16->setText(0,u8"武行者");








    QTreeWidgetItem *topItem2 = new QTreeWidgetItem(ui->treeWidget);
    topItem2->setText(0,u8"技能");
    topItem2->setCheckState(0,Qt::Checked);
    ui->treeWidget->addTopLevelItem(topItem2);

    QTreeWidgetItem *item21 = new QTreeWidgetItem(topItem2);
    item21->setText(0,u8"旋风斩");
    item21->setCheckState(0,Qt::Checked);
    QTreeWidgetItem *item22 = new QTreeWidgetItem(topItem2);
    item22->setText(0,u8"狂暴冲锋");
    item22->setCheckState(0,Qt::Checked);
    QTreeWidgetItem *item23 = new QTreeWidgetItem(topItem2);
    item23->setText(0,u8"不灭之怒");
    item23->setCheckState(0,Qt::Checked);

    QTreeWidgetItem *item24 = new QTreeWidgetItem(topItem2);
    item24->setText(0,u8"疾奔");
    item24->setCheckState(0,Qt::Checked);

    QTreeWidgetItem *item25 = new QTreeWidgetItem(topItem2);
    item25->setText(0,u8"狂乱");
    item25->setCheckState(0,Qt::Checked);

    QTreeWidgetItem *item26 = new QTreeWidgetItem(topItem2);
    item26->setText(0,u8"先祖之锤");
    item26->setCheckState(0,Qt::Checked);

    QTreeWidgetItem* childItem111 = new QTreeWidgetItem(item11);
    childItem111->setCheckState(0, Qt::Unchecked);
    childItem111->setText(0, u8"装备");

    QTreeWidgetItem* childItem1111 = new QTreeWidgetItem(childItem111);
    childItem1111->setText(0, u8"头盔");

    QTreeWidgetItem* childItem1112 = new QTreeWidgetItem(childItem111);
    childItem1112->setText(0, u8"胸甲");

    QTreeWidgetItem* childItem1113 = new QTreeWidgetItem(childItem111);
    childItem1113->setText(0, u8"肩甲");

    QTreeWidgetItem* childItem1114 = new QTreeWidgetItem(childItem111);
    childItem1114->setText(0, u8"裤子");

    QTreeWidgetItem* childItem1115 = new QTreeWidgetItem(childItem111);
    childItem1115->setText(0, u8"主手");

    QTreeWidgetItem* childItem1116 = new QTreeWidgetItem(childItem111);
    childItem1116->setText(0, u8"副手");

    //设置展开
    ui->treeWidget->expandAll();
}

void MultiLevelMenu::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    qDebug() << "column: " << column;
}






















void MultiLevelMenu::on_pushButton_clicked()
{
    addSubLevelItem("dafa");
}

