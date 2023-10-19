#include "mvc_1_listmodel.h"
#include "ui_mvc_1_listmodel.h"

#include <QDebug>
#include <QInputDialog>
#include <QDateTime>
#include <QLineEdit>

MVC_1_ListModel::MVC_1_ListModel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MVC_1_ListModel)
{
    ui->setupUi(this);

    Init();
}

MVC_1_ListModel::~MVC_1_ListModel()
{
    delete ui;
}


void MVC_1_ListModel::Init()
{
    _listModel = new QStringListModel(this);
    _CustomListModel = new CustomListModel(this);
    _StandardItemModel = new QStandardItemModel(this);
    _CustomItemDelegate = new CustomItemDelegate(ui->listView_3);

    _stringList << "a" << "b" << "c" << "d" << "e" << "f" << "g" << "h" << "i" << "j" << "k";

    //跟数据联系起来
    _listModel->setStringList(_stringList);

    ui->listView->setModel(_listModel);

    ui->listView_2->setModel(_listModel);

    ui->listView_3->setModel(_StandardItemModel);
    ui->listView_3->setItemDelegate(_CustomItemDelegate);
}


void MVC_1_ListModel::on_insert_btn_clicked()
{
    /*插入数据
     *1. Model应该是提供接口了
     *2. Model添加完数据之后  回给 View 通知来显示数据
     *另一种我想的思路
     *1. 数据库中添加数据
     *2. Model检测到
     *3. 通知View显示
     */


    //1.获取当前的项
    QModelIndex modelIndex = ui->listView->currentIndex();

    //2.
    ui->listView->model()->insertRow(modelIndex.row() + 1);

    QModelIndex index = ui->listView->model()->index(modelIndex.row() + 1, 0);

    QString LineText = ui->lineEdit->text();

    // 设置显示文字
    ui->listView->model()->setData(index, LineText,Qt::DisplayRole);

    // 设置对其方式
    ui->listView->model()->setData(index,Qt::AlignRight,Qt::TextAlignmentRole);

    // 设置当前选中行
    ui->listView->setCurrentIndex(index);
}


void MVC_1_ListModel::on_add_btn_clicked()
{
    {
        //想法 跟 insert数据一样的
        //    _stringList << "我的测试数据";

        // 在尾部插入一行

        ui->listView->model()->insertRow(_listModel->rowCount());

        // 获取最后一行的索引
        QModelIndex index = ui->listView->model()->index(_listModel->rowCount()-1, 0);

        //获取LineEdit的文本内容
        QString LineText = ui->lineEdit->text();

        // 设置显示文字
        ui->listView->model()->setData(index, LineText, Qt::DisplayRole);

        ui->listView->setCurrentIndex(index);
        // 设置当前行选中
        ui->lineEdit->clear();
    }

    //listView_3
    {
        QDateTime current_time;
        QStandardItem* item = new QStandardItem();
        CustomItemData item_data;
        item_data.iconPath = ":mainwnd/navbar/profile.svg";
        item_data.title = "test";
        item_data.subTitle = current_time.currentDateTime().toString("yy-MM-dd");
        item_data.content = current_time.currentDateTime().toString("hh:mm:ss");
        item_data.time = current_time.currentDateTime().toString("ddd");
        item->setData(QVariant::fromValue(item_data),
                           Qt::UserRole + 1);


        _StandardItemModel->appendRow(item);
//        _StandardItemModel->appendRow(item_data);

    }

    {
//        bool is0K;
//        QString text = QInputDialog::getText(NULL, "Insert", "please input new data:", QLineEdit::Normal,  "You are inserting new data.", &is0K);
//        if(is0K)
//        {

//        }
    }
}

void MVC_1_ListModel::on_delete_btn_clicked()
{
    // 获取当前行的ModelIndex
    QModelIndex index = ui->listView->currentIndex();

    // 删除选中行
    ui->listView->model()->removeRow(index.row());
}


void MVC_1_ListModel::on_display_btn_clicked()
{
    // 显示数据模型文本到QPlainTextEditvoid

    QStringList pList;

    if(modelIndex_ == 0)
    {
        // 获取数据模型的StringList
        pList = _listModel->stringList();
    }
    else
    {
        // 获取数据模型的StringList
        pList = _CustomListModel->stringList();
    }

    // 先清空文本框
    ui->plainTextEdit->clear();

    // 循环追加数据
    for(int x=0; x < pList.count(); x++)
    {
        ui->plainTextEdit->appendPlainText(pList.at(x) + QString(","));
    }
}


void MVC_1_ListModel::on_comboBox_activated(int index)
{
    modelIndex_ = index;
    //设置使用当前那个  Model

    if(modelIndex_ == 0)
    {
        _listModel->setStringList(_stringList);
        ui->listView->setModel(_listModel);
        ui->listView_2->setModel(_listModel);
    }
    else
    {
        _CustomListModel->setStringList(_stringList);
        ui->listView->setModel(_CustomListModel);
        ui->listView_2->setModel(_CustomListModel);
    }
}

