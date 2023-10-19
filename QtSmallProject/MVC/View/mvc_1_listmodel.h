#ifndef MVC_1_LISTMODEL_H
#define MVC_1_LISTMODEL_H

#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include <QStandardItemModel>

#include "../Model/customlistmodel.h"
#include "../Delegate/customitemdelegate.h"

namespace Ui {
class MVC_1_ListModel;
}

class MVC_1_ListModel : public QWidget
{
    Q_OBJECT

public:
    explicit MVC_1_ListModel(QWidget *parent = nullptr);
    ~MVC_1_ListModel();


private slots:
    void on_insert_btn_clicked();

    void on_add_btn_clicked();

    void on_delete_btn_clicked();

    void on_display_btn_clicked();

    void on_comboBox_activated(int index);

private:
    void Init();

private:
    Ui::MVC_1_ListModel *ui;

//    std::variant<QStringListModel*, CustomListModel*> listModel_;
    int modelIndex_{0};

    QStringListModel*   _listModel{NULL};           //使用的是默认的 Model
    CustomListModel*    _CustomListModel{NULL};     //自定义的 ListModel

    QStandardItemModel* _StandardItemModel{NULL};   //使用 QStandardItemModel
    CustomItemDelegate* _CustomItemDelegate{NULL};


    QStringList         _stringList;
};

#endif // MVC_1_LISTMODEL_H
