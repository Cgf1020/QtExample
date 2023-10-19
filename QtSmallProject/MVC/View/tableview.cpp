#include "tableview.h"
#include "ui_tableview.h"


#include <QStandardItem>

TableView::TableView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableView)
{
    ui->setupUi(this);

    Init();
}

TableView::~TableView()
{
    delete ui;
}

void TableView::Init()
{
    QStringList columnNames;
    columnNames<< "QSpinBox" << "QComboBox" << "QCheckBox"<< "···";

    model_ = new QStandardItemModel(4, 2);
    model_->setHorizontalHeaderLabels(columnNames);
    ui->tableView->setModel(model_);


    tableDelegate_ = new TableDelegate(this);
    ui->tableView->setItemDelegateForColumn(0, tableDelegate_);

//    for (int row = 0; row < 3; ++row) {
//        for (int column = 0; column < 3; ++column) {
//            QModelIndex index = model_->index(row, column, QModelIndex());
//            model_->setData(index, QVariant((row + 1) * (column + 1)));
//        }
//    }
}

void TableView::InitTable()
{
//    /*设置样式*/
//    ui->tableView->setProperty("model",true);
//    /*设置默认行高*/
//    ui->tableView->verticalHeader()->setDefaultSectionSize(rowHeight);
//    /*设置交替行颜色--允许交替行颜色*/
//    ui->tableView->setAlternatingRowColors(true);
//    /*设置水平/垂直滚动模式--一次滚动一个项目*/
//    ui->tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
//    ui->tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
//    /*设置选择行为--每次选择只有一整行*/
//    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    /*设置拖放行为--不允许拖放*/
//    ui->tableView->setDragDropMode(QAbstractItemView::NoDragDrop);
//    /*设置选择模式--只能选择一个项目*/
//    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
//    /*设置Tab导航键--允许使用Tab键导航，shift+tab反向导航*/
//    ui->tableView->setTabKeyNavigation(true);
//    /*设置是否自动换行--取消自动换行*/
//    ui->tableView->setWordWrap(false);
//    /*设置文本省略模式--省略号不会出现在文本中*/
//    ui->tableView->setTextElideMode(Qt::ElideNone);
//    /*设置左上角全选按钮--禁用*/
//    ui->tableView->setCornerButtonEnabled(false);
//    /*设置是否支持表头排序--应该和表头是否可以单击保持一致*/
//    ui->tableView->setSortingEnabled(isSorting);
//    /*设置是否显示网格线*/
//    ui->tableView->setShowGrid(isShowGrid);
//    /*设置垂直表头是否可见*/
//    ui->tableView->verticalHeader()->setVisible(verticalHeadVisible);
//    /*设置选中一行表头是否加粗--不加粗*/
//    ui->tableView->horizontalHeader()->setHighlightSections(false);
//    /*设置最后一行是否拉伸填充*/
//    ui->tableView->horizontalHeader()->setStretchLastSection(isLastTensile);
//    /*设置行标题最小宽度尺寸*/
//    ui->tableView->horizontalHeader()->setMinimumSectionSize(0);
//    /*设置行标题最小高度*/
//    ui->tableView->horizontalHeader()->setFixedHeight(rowHeight);

//    /*设置表头是否可以单击--不可单击*/
//#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
//    ui->tableView->horizontalHeader()->setSectionsClickable(isSorting);
//#else
//    ui->tableView->horizontalHeader()->setClickable(false);
//#endif

//    /*是否可编辑*/
//    if(Editable)
//    {
//        ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
//    }
//    else
//    {
//        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    }
}
