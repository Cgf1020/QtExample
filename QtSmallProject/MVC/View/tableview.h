#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QWidget>

#include "../Delegate/tabledelegate.h"
#include <QStandardItemModel>

namespace Ui {
class TableView;
}

class TableView : public QWidget
{
    Q_OBJECT

public:
    explicit TableView(QWidget *parent = nullptr);
    ~TableView();


private:
    void Init();

    void InitTable();
private:
    Ui::TableView *ui;

    QStandardItemModel* model_{NULL};
    TableDelegate*  tableDelegate_{NULL};
};

#endif // TABLEVIEW_H
