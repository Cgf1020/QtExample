#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QObject>
#include <QListView>
#include <QStandardItemModel>
#include <QMap>
#include <QList>


#include "../Delegate/listdelegate.h"

namespace TESTMVC {




class ListView : public QListView
{
    Q_OBJECT
public:
    explicit ListView(QWidget *parent = nullptr);

public:
    void AddGroup(QString title);



public:
    void Init();


signals:



private:
    QStandardItemModel* model_{NULL};
    ListDelegate*       delegata_{NULL};

    QMap<QStandardItem*, QList<QStandardItem*>> itemMap_;
};


}
#endif // LISTVIEW_H
