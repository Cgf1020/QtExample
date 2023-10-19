#ifndef LISTDELEGATE_H
#define LISTDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

namespace TESTMVC {

// 绘制角色
enum class ListItemRole
{
    IsGroupRole = Qt::UserRole + 500,   // 是否是群组
    GroupRole,
    IsItemRole,                         //是否为Item
    ItemRole,                         // 联系人信息
//    GroupNameRole,                      // 群组名称
//    ContactRole,                        // 联系人信息
//    IsExpandedRole,                     // 是否收起
//    VideoRole,                          // 视频通话role
//    SignatureRole,                      // 个性签名
//    PortraitRole,                       // 头像
};


typedef struct ListGroupData{
    QString title{""};
    int subWidgetNum{0};        //底下子控件的数量
    bool isExpande{false};      //是否展开
} ListGroupData;

typedef struct ListItemData{
    QString title{};            //标题
    int serialNumber{-1};       //序号
    QString headPath{};         //头像路径
} ListItemData;


class ListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ListDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

private:
    // 绘制群组
    void paintGroup(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    // 绘制联系人
    void paintItem(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

signals:

};
}

//将自定义的数据结构注册，否则不可设置为Item的数据。Qt提供了注册自定义数据的宏
Q_DECLARE_METATYPE(TESTMVC::ListGroupData)    //自定义结构体WItemData
Q_DECLARE_METATYPE(TESTMVC::ListItemData)    //自定义结构体WItemData


#endif // LISTDELEGATE_H
