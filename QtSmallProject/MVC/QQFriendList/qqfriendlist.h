#ifndef QQFRIENDLIST_H
#define QQFRIENDLIST_H

#include <QWidget>

#include <QStandardItemModel>

#include "qqlistdefines.h"
#include "qqitemdelegate.h"

#include "friendtree.h"

using namespace qqfriendlist;


namespace Ui {
class QQFriendList;
}

class QQFriendList : public QWidget
{
    Q_OBJECT

public:
    explicit QQFriendList(QWidget *parent = nullptr);
    ~QQFriendList();


public:

    //添加分组
    void addGroup(QString groupName);
protected:
    //注册时间过滤器
    bool eventFilter(QObject *watched, QEvent *event);


private:
    void InitUI();
    void initConnection();

    // 自定义的hover处理
    void onHoverHandle(const QModelIndex& index, int role);

    // 自定义的点击事件处理
    void onClickedHandle(const QModelIndex& index, int role);

signals:
    // 点击Item信号
    void signalClicked(const QModelIndex& iIndex);
    // 点击Item信号 具体到点到的Role
    void signalClicked(const QModelIndex& iIndex, int role);
    // 双击信号
    void signalDoubleClicked(const QModelIndex& iIndex);
    // hoverItem信号 具体到hover的Role
    void signalHover(const QModelIndex& iIndex, int role);


private:
    Ui::QQFriendList *ui;



    QStandardItemModel* m_model{ nullptr }; // model
    QQItemDelegate* m_delegate{ nullptr };


    FriendTree* FriendTree_;
};

#endif // QQFRIENDLIST_H
