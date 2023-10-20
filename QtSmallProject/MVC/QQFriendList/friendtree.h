#ifndef FRIENDTREE_H
#define FRIENDTREE_H

#include <QObject>
#include <QTreeView>
#include <QStandardItemModel>

#include "qqlistdefines.h"
#include "qqitemdelegate.h"

namespace qqfriendlist
{


class FriendTree : public QTreeView
{
    Q_OBJECT
public:
    explicit FriendTree(QWidget *parent = nullptr);


    // 赋值
    void setValues(const std::vector<Group>& groups);

    //添加分组
    void addGroup(QString groupName);

protected:
    bool viewportEvent(QEvent* pEvent) override;

private:
    void initUi();
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
    QStandardItemModel* m_model{ nullptr }; // model
    QQItemDelegate* m_delegate{ nullptr };


};


}
#endif // FRIENDTREE_H
