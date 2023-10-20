#ifndef QQItemDelegate_H
#define QQItemDelegate_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QListView>


#include "qqlistdefines.h"

namespace qqfriendlist
{



class QQItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QQItemDelegate(QObject *parent = nullptr);

public:

    //自定义的Item 操作
    enum ItemRole
    {
        PosRole = Qt::UserRole + 10000, // 位置
        MousePressRole,                 // 点击
        MouseHoverRole,                 // hover
    };

    // 操作行为
    struct OperateActions
    {
        bool isHovered{ false };
        bool isPressed{ false };
        bool isSelected{ false };
        int mousePosX{ 0 };
        int mousePosY{ 0 };
    };

    /*渲染
     * @painter: 数据项的绘制全部由它完成
     * @option: 数据项在视图小部件中绘制的各项参数,如坐标、状态、图标... 较为重要的（我们要用的）就是坐标和状态，其中坐标信息包含在rect中，状态信息包含在state中。
     * @index: 数据项的数据模型
    */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;


    /*返回Item窗口大小，重写以单独设置Item大小
    */
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
    // hover的role
    /****************************************!
     * @brief  根据鼠标位置 判断hover的role是哪个 并返回
     * @param  [in]  const QPoint & pos 鼠标位置
     * @param  [in]  const QStyleOptionViewItem & option
     * @param  [in]  const QModelIndex & index 索引位置
     * @return int
     ****************************************/
    int getHoverEventRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex &index) const;

    // 点击的role
    /****************************************!
     * @brief  返回点击的Item的角色
     * @param  [in]  const QPoint & pos
     * @param  [in]  const QStyleOptionViewItem & option
     * @param  [in]  const QModelIndex & index
     * @return int
     ****************************************/
    int getMouseEventRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex &index) const;


public slots:
    // view上层调用这两个函数
    int hoverEvent(QHoverEvent* hoverEvent, QAbstractItemView* view, const QStyleOptionViewItem& option, const QModelIndex& modelIndex);
    int mouseEvent(QMouseEvent* mouseEvent, QAbstractItemView* view, const QStyleOptionViewItem& option, const QModelIndex& modelIndex);

private:
    // 获取当前Item的行为状态信息
    OperateActions getOperateActions(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    // 绘制群组
    void paintGroup(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    // 绘制联系人
    void paintContact(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;


signals:




private:
    int border_radius;
    int butWidth;

};


}
#endif // QQItemDelegate_H
