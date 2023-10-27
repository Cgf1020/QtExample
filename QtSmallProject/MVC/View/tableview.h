#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "../Delegate/tabledelegate.h"
#include "../Delegate/btndelegate.h"
#include "../Model/customsortfilterproxymodel.h"
#include "customheaderview.h"



namespace Ui {
class TableView;
}

class TableView : public QWidget
{
    Q_OBJECT

public:
    explicit TableView(QWidget *parent = nullptr);
    ~TableView();

    void addRowData();

private slots:
    void TableItemClickEvent(const QModelIndex &index);

    void on_delete_btn_clicked();

private:
    void Init();
    void InitTable();
    void InitConnect();


private:
    Ui::TableView *ui;

    CustomHeaderView*   CustomHeaderView_{NULL};
    QStandardItemModel* model_{NULL};
    TableDelegate*  tableDelegate_{NULL};
    BtnDelegate*    BtnDelegate_{NULL};
    CustomSortFilterProxyModel*     proxyModel_{NULL};

    /*
     * TableView 表格 的 表头信息
    */
    QStringList tableHeader_{"InfoData", "状态", "警报编号", "警报时间", "警报类型", "快照", "回放", "操作"};

private:
    bool formDateState{false};
    bool toDateState{false};


};

#endif // TABLEVIEW_H
