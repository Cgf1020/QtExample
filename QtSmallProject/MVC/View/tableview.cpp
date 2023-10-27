#include "tableview.h"
#include "ui_tableview.h"

#include <QDebug>
#include <QStandardItem>
#include <QLabel>
#include <QMessageBox>
#include <QVariant>
#include <QTime>
#include <QComboBox>
#include "../mvcGlobalDefine.h"
#include "Control/ImageDialog/imagedialog.h"



TableView::TableView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableView)
{
    ui->setupUi(this);

    Init();

    InitTable();

    InitConnect();
}

TableView::~TableView()
{
    delete ui;
}

void TableView::addRowData()
{
    for(int i = 0; i < 10; i++)
    {
        TESTMVC::TableItemData data;

        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int n = qrand() % 10;    //产生5以内的随机数
        data.deviceId = QString("%1").arg(n);
        data.dataTime = QDateTime::currentDateTime().addDays(n);

        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int n1 = qrand() % 4 + 1;    //产生5以内的随机数
        data.alarmType = static_cast<TESTMVC::AlarmType>(n1);
        data.imagePath = ":/pic/3.png";
        data.playblackUrl = "https://baidu.com";


        model_->insertRow(0);

        //信息列
        {
            QStandardItem* item = new QStandardItem(data.deviceId);
            item->setEditable(false);
            item->setData(QVariant::fromValue(data), static_cast<int>(TESTMVC::ItemRole::TableItemRole));       //设置数据
            item->setData(QVariant::fromValue(TESTMVC::ItemColumnRole::InfoData), static_cast<int>(TESTMVC::ItemRole::ColumnRole));       //设置列的属性
            model_->setItem(0, static_cast<int>(TESTMVC::ItemColumnRole::InfoData), item);
        }

        //复选框列
        {
            QStandardItem* item = new QStandardItem();
            item->setCheckable(true);
            model_->setItem(0,static_cast<int>(TESTMVC::ItemColumnRole::CheckboxColumn), item);
        }

        //警报编号列
        {
            model_->setItem(0, static_cast<int>(TESTMVC::ItemColumnRole::DeviceIdColumn), new QStandardItem(data.deviceId));
        }

        //警报时间
        {
            model_->setItem(0, static_cast<int>(TESTMVC::ItemColumnRole::AlarmTimeColumn), new QStandardItem(data.dataTime.toString("yyyy-MM-dd HH:mm:ss")));
        }

        //警报类型
        {
            model_->setItem(0, static_cast<int>(TESTMVC::ItemColumnRole::AlarmTypeColumn), new QStandardItem(TESTMVC::AlarmTypeToString(data.alarmType)));
        }

        //快照
        {
            model_->setItem(0, static_cast<int>(TESTMVC::ItemColumnRole::SnapshotColumn), new QStandardItem(data.imagePath));
        }

        //视频回放
        {
            model_->setItem(0, static_cast<int>(TESTMVC::ItemColumnRole::SnapshotColumn), new QStandardItem(data.playblackUrl));
        }

        //操作
        {
        }
    }
}

void TableView::TableItemClickEvent(const QModelIndex &index)
{
    qDebug() << "TableItemClickEvent " << index.row() << ", " << index.column();

    if(index.column() == static_cast<int>(TESTMVC::ItemColumnRole::SnapshotColumn))
    {
        //弹出模态窗口
        ImageDialog widget;
        widget.Init(":/image/delete.png");
        widget.exec();
    }
    else if(index.column() == static_cast<int>(TESTMVC::ItemColumnRole::PlaybackColumn))
    {
        //弹出模态窗口
        ImageDialog widget;
        widget.Init(":/image/delete.png");
        widget.exec();
    }
}

void TableView::Init()
{
    //创建自定义的头
    CustomHeaderView_ = new CustomHeaderView(Qt::Horizontal, ui->tableView);
    ui->tableView->setHorizontalHeader(CustomHeaderView_);


    // 标准的模型
    model_ = new QStandardItemModel(ui->tableView);

    model_->setHorizontalHeaderLabels(tableHeader_);        //设置表头

    // 创建委托代理
    tableDelegate_ = new TableDelegate(ui->tableView);
    tableDelegate_->setModel(model_);
    ui->tableView->setItemDelegate(tableDelegate_);

    // 创建排序和过滤代理
    proxyModel_ = new CustomSortFilterProxyModel(ui->tableView);
    proxyModel_->setSourceModel(model_);

    // 设置视图显示模型
    ui->tableView->setModel(proxyModel_);

    {
        ui->fromDateEdit->setEnabled(false);
        ui->toDateEdit->setEnabled(false);
    }
}

void TableView::InitTable()
{
    // 必须要设置此项，否则样式表的hover无法生效
    ui->tableView->setMouseTracking(true);

    /*隐藏复选框列*/
    ui->tableView->setColumnHidden(0, true);

    //设置允许点击表头进行排序：这里设置好之后是 点击所有的列点击都会排序的, 某一列的话是 QTableView::sortByColumn(这种的又会造成 点击表头的时候没有那个 排序的箭头指示)
    ui->tableView->setSortingEnabled(true);

    //初始化某一列的排序，升序或者降序
    ui->tableView->sortByColumn(1, Qt::SortOrder::DescendingOrder);

    /*设置最后一行是否拉伸填充*/
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    /*点击表时不对表头进行光亮*/
    ui->tableView->horizontalHeader()->setHighlightSections(false);

    /*设置无边框*/
    ui->tableView->setFrameShape(QFrame::NoFrame);

    /*设置显示子网格线*/
    ui->tableView->setShowGrid(false);

    /*格子线样式*/
    ui->tableView->setGridStyle(Qt::SolidLine);

    /*设置交替行颜色--允许交替行颜色*/
    ui->tableView->setAlternatingRowColors(true);

    /*设置垂直头不可见*/
    ui->tableView->verticalHeader()->setVisible(false);

    /*设置样式*/
    QFont font;
    font.setFamily("微软雅黑");
    ui->tableView->horizontalHeader()->setFont(font);

    /*设置表头字体大小、去除边框、设置背景色*/
    ui->tableView->horizontalHeader()->setStyleSheet(QString(
        "QHeaderView::section{\
            border: 2px solid;\
            border: none;\
            background-color: #272f49;\
            color: white;\
            font-size: 15px;}\
        QHeaderView::down-arrow{\
            subcontrol-position: center right;\
            image: url(:/image/down_arrow.png);\
            padding-right: 8px;}\
        QHeaderView::up-arrow{\
            subcontrol-position: center right;\
            image: url(:/image/up-arrow.png);\
            padding-right: 8px;}"));


//    /*设置样式*/
//    ui->tableView->setProperty("tableview",true);
//    /*设置默认行高*/
//    ui->tableView->verticalHeader()->setDefaultSectionSize(rowHeight);
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

//    /*设置单元格的编辑器是否一直显示：但是只要是经过排序或者是筛选就失效，不清楚为什么*/
//    ui->tableView->openPersistentEditor(model_->index(0, 3));
//    ui->tableView->openPersistentEditor(model_->index(0, 5));


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

void TableView::InitConnect()
{
    /*处理TableView 的点击事件
     * 1. 快照点击
     * 2. 回放点击
     */
    connect(ui->tableView, &QTableView::clicked, this, &TableView::TableItemClickEvent);

    /*表头点击事件
    */
    connect(CustomHeaderView_, &CustomHeaderView::columnSectionClicked, this, [&](int column, bool checked){
        //遍历行
        for(int row = 0; row < proxyModel_->rowCount(); row++)
        {
            QModelIndex dataModelxIndex = proxyModel_->mapToSource(proxyModel_->index(row, column));
            QStandardItem *item = model_->item(dataModelxIndex.row(), dataModelxIndex.column());

            //获取指定列当前行的item,根据checked设置选中状态
            if(checked)
                item->setCheckState(Qt::Checked);
            else
                item->setCheckState(Qt::Unchecked);
        }
    });

//    // 表头排序事件
//    connect(CustomHeaderView_, &CustomHeaderView::sortIndicatorChanged, this, [&](int logicalIndex, Qt::SortOrder order){
//        qDebug() << "sortIndicatorChanged " << logicalIndex;

//        model_->sort(logicalIndex, order);
//    });


    /* 处理时间查询 连接
     * 1.起始时间
     * 2.结束时间
    */
    connect(ui->fromDateEdit, &QDateTimeEdit::dateChanged, this, [&](const QDate &date){
        if(formDateState)
            proxyModel_->setFilterAlarmDate(date, ui->toDateEdit->date());
        else
            proxyModel_->setFilterAlarmDate(date, QDate().currentDate());
    });

    connect(ui->toDateEdit, &QDateTimeEdit::dateChanged, this, [&](const QDate &date){
        if(toDateState)
            proxyModel_->setFilterAlarmDate(ui->fromDateEdit->date(), date);
        else
            proxyModel_->setFilterAlarmDate(QDate(), date);
    });

    //警报类型 点击
    connect(ui->alarmType_comboBox, QOverload<int>::of(&QComboBox::activated), this, [&](int index){
        proxyModel_->setFilterAlarmType(static_cast<TESTMVC::AlarmType>(index));
    });

    // CheckBox
    connect(ui->startTime_checkBox, &QCheckBox::stateChanged, this, [&](int state){
        formDateState = state;
        if(formDateState)
            ui->fromDateEdit->setEnabled(true);
        else
            ui->fromDateEdit->setEnabled(false);
    });
    connect(ui->endTime_checkBox, &QCheckBox::stateChanged, this, [&](int state){
        toDateState = state;
        if(toDateState)
            ui->toDateEdit->setEnabled(true);
        else
            ui->toDateEdit->setEnabled(false);
    });

    // 取消查询按钮
    connect(ui->CancelQuery_btn, &QPushButton::pressed, this, [&](){
        proxyModel_->CancelAllFilterConditions();

        ui->startTime_checkBox->setCheckState(Qt::CheckState::Unchecked);
        ui->endTime_checkBox->setCheckState(Qt::CheckState::Unchecked);
        ui->fromDateEdit->setEnabled(false);
        ui->toDateEdit->setEnabled(false);
        ui->alarmType_comboBox->setCurrentIndex(0);
    });
}

void TableView::on_delete_btn_clicked()
{
    for(int row = 0; row < proxyModel_->rowCount();)
    {
        QModelIndex dataModelxIndex = proxyModel_->mapToSource(proxyModel_->index(row, 1));
        QStandardItem *item = model_->item(dataModelxIndex.row(), dataModelxIndex.column());

        if(item->checkState() == Qt::Checked)
            model_->removeRow(item->row());
    }

    CustomHeaderView_->setColumnCheckState(false);
}

