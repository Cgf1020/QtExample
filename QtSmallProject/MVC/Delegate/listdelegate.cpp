#include "listdelegate.h"

#include <QDebug>
#include <QPainter>





namespace  TESTMVC {

const int ListGroupItemHeight{ 35 };               //分组的高
const QRect ListGroupIconRect{ 10,12,11,11 };   // 群组下拉图标  x,y,w,h
const QRect ListGroupNameRect{ 30,0,200,35 };	    // 群组名称
const QRect ListGroupSubWidgetNumRect{ 220,5,100,25 };	    // 群组显示的子控件的数量

const int ListItemHeight{ 35 };                     //item的高
const QRect ListItemIconRect{ 10,10,10,10 };        // 联系人头像
const QRect ListItemNameRect{ 30,10,200,20 };	 // 联系人名字
//const QRect kSignatureRect{ 60,30,160,20 };		 // 联系人个性签名
//const QRect kVipIconRect{ 60,30,30,12 };		 // 联系人VIP图标
//const QRect kOnlineStateIconRect{ 40,35,14,14 }; // 在线状态图标
//const QRect kVideoIconRect{ 0,25,20,13 };	     // 视频通话图标




ListDelegate::ListDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

void ListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    qDebug() << "ListDelegate::paint";

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    if (index.isValid())
    {
        //1.判断是不是群组
        if(index.data(static_cast<int>(ListItemRole::IsGroupRole)).toBool())
        {
            paintGroup(painter, option, index);
        }
        else
        {
            paintItem(painter, option, index);
        }

//        QVariant var = index.data(Qt::UserRole+1);
//        CustomItemData itemData = var.value<CustomItemData>();
    }
    painter->restore();


//    return QStyledItemDelegate::paint(painter, option, index);
}

QSize ListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    if (index.isValid())
    {
        //1.判断是不是群组
        if(index.data(static_cast<int>(ListItemRole::IsGroupRole)).toBool())
        {
            return QSize(option.rect.width(), ListGroupItemHeight);   // 分组的高
        }
        return QSize(option.rect.width(), ListItemHeight);   // 分组的高
    }

    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *ListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

//    editor->setGeometry(option.rect.x(), option.rect.y(), option.rect.width(), option.rect.height());

    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}

void ListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QStyledItemDelegate::setEditorData(editor, index);
}

void ListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QStyledItemDelegate::setModelData(editor, model, index);
}

void ListDelegate::paintGroup(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    qDebug() << "ListDelegate::paintGroup index = " << index.row();
//    qDebug() << "option xy:" << option.rect.x() << ", " << option.rect.y();
//    qDebug() << "option wh:" << option.rect.width() << ", " << option.rect.height();
//    qDebug() << "option ltrd:" << option.rect.left() << ", " << option.rect.top();

//    qDebug() << "ListGroupIconRect xy:" << ListGroupIconRect.x() << ", " << ListGroupIconRect.y();
//    qDebug() << "ListGroupIconRect wh:" << ListGroupIconRect.width() << ", " << ListGroupIconRect.height();

    QVariant var = index.data(static_cast<int>(ListItemRole::GroupRole));
    ListGroupData groupData = var.value<ListGroupData>();

    //1. 绘制图标
    QString imagePath = ":/image/fold_black.png";

    if(groupData.isExpande)
    {
        imagePath = ":/image/expand_black.png";
    }
    QImage image(imagePath);

    QRect IconRect(option.rect.left() + ListGroupIconRect.x(), option.rect.top() + ListGroupIconRect.y(),
                       ListGroupIconRect.width(), ListGroupIconRect.height());

//    qDebug() << "IconRect " << IconRect.x() <<", " <<IconRect.y() << ", " << IconRect.width() << ", " <<IconRect.height();
    painter->drawImage(IconRect, image);


    //2. 绘制文本
    QFont font = painter->font();
    font.setFamily("microsoft yahei");
    font.setPixelSize(15);
    painter->setFont(font);

    QRect nameRect(option.rect.left() + ListGroupNameRect.x(), option.rect.top() + ListGroupNameRect.y(), ListGroupNameRect.width(), ListGroupNameRect.height());
    painter->drawText(nameRect, Qt::AlignCenter, groupData.title);
}

void ListDelegate::paintItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    qDebug() << "ListDelegate::paintItem index = " << index.row();

    QVariant var = index.data(static_cast<int>(ListItemRole::ItemRole));
    ListItemData itemData = var.value<ListItemData>();

    // 联系人图标
    {
        QRect itemIconRect(option.rect.left() + ListItemIconRect.x(), option.rect.top() + ListItemIconRect.y(),
                                      ListItemIconRect.width(), ListItemIconRect.height());
        QImage image(":/image/item_right_balck.png");
        painter->drawImage(itemIconRect, image);
    }

    // 联系人名称
    {
        QRect nameRect(option.rect.left() + ListItemNameRect.x(), option.rect.top() + ListItemNameRect.y(),
                       ListItemNameRect.width(), ListItemNameRect.height());
        painter->drawText(nameRect, Qt::AlignCenter, itemData.title);
    }
}



}
