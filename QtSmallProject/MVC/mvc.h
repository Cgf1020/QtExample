#ifndef MVC_H
#define MVC_H

#include <QWidget>


#include "mvc_1_listmodel.h"

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


private:
    Ui::MVC *ui;

    /*使用QListView 和 QStringListModel 来实现的 增删改查功能
    */
    MVC_1_ListModel*        _MVC_1_ListModel;
};

#endif // MVC_H
