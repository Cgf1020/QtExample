#ifndef MVC_H
#define MVC_H

#include <QWidget>

#include "View/listview.h"
#include "View/tableview.h"
#include "QQFriendList/friendtree.h"

namespace Ui {
class MVC;
}

class MVC : public QWidget
{
    Q_OBJECT

public:
    explicit MVC(QWidget *parent = nullptr);
    ~MVC();


private:
    void Init();

    void InitConnect();


    void onButtonClick(bool checked);

    int findTabIndex(QString name);

private:
    Ui::MVC *ui;

    TESTMVC::ListView*  listView_{NULL};

    qqfriendlist::FriendTree*         FriendTree_{NULL};

    TableView* tableView_{NULL};
};

#endif // MVC_H
