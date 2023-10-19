#include "customitemdelegate.h"

#include <QDebug>
#include <QPainter>




CustomItemDelegate::CustomItemDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

void CustomItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    if (index.isValid())
    {

        QVariant var = index.data(Qt::UserRole+1);
        CustomItemData itemData = var.value<CustomItemData>();
    }
    painter->restore();
}

QSize CustomItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 120);
}

QWidget *CustomItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void CustomItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QStyledItemDelegate::setEditorData(editor, index);
}

void CustomItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QStyledItemDelegate::setModelData(editor, model, index);
}

void CustomItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}


//        QPainterPath painter_path;
//        painter_path.moveTo(rect.topRight());
//        painter_path.lineTo(rect.topLeft());
//        painter_path.quadTo(rect.topLeft(), rect.topLeft());
//        painter_path.lineTo(rect.bottomLeft());
//        painter_path.quadTo(rect.bottomLeft(), rect.bottomLeft());
//        painter_path.lineTo(rect.bottomRight());
//        painter_path.quadTo(rect.bottomRight(), rect.bottomRight());
//        painter_path.lineTo(rect.topRight());
//        painter_path.quadTo(rect.topRight(), rect.topRight());
//        QRectF flag_rect(rect.width() - 25, rect.y()+5, 25, 25);
//        // 鼠标悬停或者选中时改变背景色
//        if (option.state.testFlag(QStyle::State_MouseOver))
//        {
////            painter->drawImage(flag_rect, QImage(":mainwnd/col1/refresh.svg"));
//            painter->setPen(QPen(QColor("#c4f0ff")));
//            painter->setBrush(QColor("#c4f0ff"));
//            painter->drawPath(painter_path);
//        }
//        if (option.state.testFlag(QStyle::State_Selected))
//        {
//            painter->setPen(QPen(QColor(Qt::blue)));
//            painter->setBrush(QColor(Qt::blue));
//            painter->drawPath(painter_path);
//        }
//        //draw mail content
//        QRectF mail_icon_rect(rect.left() + 5, rect.top() + 15, 35, 35);
//        QRectF mail_title_rect(rect.left() + 45, rect.top() + 5,
//                               rect.width() - 65,20);
//        QRectF mail_subtitle_rect(rect.left()+45,rect.top()+25,rect.width()-40,20);
//        QRectF mail_content_rect(rect.left() + 45, rect.top() + 45,
//                                 rect.width() - 50, 18);
//        QRect mail_date_rect(rect.width()-20, rect.top() + 45, 30, 18);
//        painter->drawImage(mail_icon_rect, QImage(itemData.iconPath));
//        painter->setPen(QPen(Qt::black));
//        painter->setFont(QFont("Microsoft YaHei",12));
//        painter->drawText(mail_title_rect, itemData.title);
//        painter->setPen(QPen(Qt::red));
//        painter->setFont(QFont("Microsoft YaHei", 10));
//        painter->drawText(mail_subtitle_rect, itemData.subTitle);
//        painter->setPen(QPen(Qt::darkGray));
//        painter->setFont(QFont("Microsoft YaHei", 10));
//        painter->drawText(mail_content_rect, itemData.content);
//        painter->drawText(mail_date_rect, itemData.time);





