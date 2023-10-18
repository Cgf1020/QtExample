#include "customitemdelegate.h"

#include <QDebug>>
#include <QPainter>
#include <QPainterPath>




CustomItemDelegate::CustomItemDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
    border_radius = 5;

    butWidth = 30;
}

void CustomItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    if (index.isValid())
    {
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setFont(QFont("Microsoft YaHei"));

        QVariant var = index.data(Qt::UserRole + 1);

        CustomItemData itemData = var.value<CustomItemData>();


        // Item 矩形区域
        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width());
        rect.setHeight(option.rect.height());

//        qDebug() << "CustomItemDelegate::paint rect: " << rect.x() << ", " << rect.y() <<"   " << rect.width() << ", " << rect.height();

        //绘制Item阴影
        painter->setPen(QPen(QColor("#c7c7c7")));
        painter->setBrush(QColor("#c7c7c7"));
        painter->drawRoundedRect(QRectF(rect.x()+4,rect.y()+4,rect.width(),rect.height()-8), border_radius, border_radius);


        // 鼠标悬停或者选中时改变背景色
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            painter->setPen(QPen(QColor("#c4f0ff")));
            painter->setBrush(QColor("#c4f0ff"));
            painter->drawRoundedRect(rect,border_radius,border_radius);
        }else if (option.state.testFlag(QStyle::State_Selected)) {
            painter->setPen(QPen(QColor("#e4f0ff")));
            painter->setBrush(QColor("#e4f0ff"));
            painter->drawRoundedRect(rect,border_radius,border_radius);
        }


        QPainterPath rowPath;
        int rowLineNum,rowHeight;
        {
            rowLineNum = 1;
            rowHeight = rect.height()/3;
            rowPath.moveTo(QPointF(rect.x(),rect.y() + rowHeight));
            rowPath.lineTo(QPointF(rect.width() + 5,rect.y() + rowHeight));
        }

        // 鼠标悬停或者选中时改变背景色
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            painter->setPen(QPen(QColor("#000000")));
        }else if (option.state.testFlag(QStyle::State_Selected)) {
            painter->setPen(QPen(QColor("#000000")));
        }else {
            painter->setPen(QPen(QColor("#000000")));
        }
        painter->drawPath(rowPath);        //绘制行线



        //绘制标题
        painter->drawText(QRectF(rect.x(),rect.y(),rect.width(),rowHeight), Qt::AlignCenter ,itemData.title);
        painter->setFont(QFont("Microsoft YaHei", 11));
        painter->drawText(QRectF(rect.x(),rect.y() + rowHeight * rowLineNum,rect.width(),rowHeight*1.2)
                          , Qt::AlignVCenter ,itemData.title);
        painter->setFont(QFont("Microsoft YaHei", 9));
        painter->drawText(QRectF(rect.x(),rect.y() + rowHeight * rowLineNum + rowHeight*1.2,rect.width(),rowHeight*0.8)
                          , Qt::AlignVCenter ,itemData.time);


        //绘制按钮
        int butHeight = (rowHeight * 2 - 15)/2;
        for(int i = 0; i < 2; i++){
            //绘制按钮阴影
            QRectF butShadowRect(rect.width() - butWidth - 8
                                 ,rect.y() + rowHeight * rowLineNum +(butHeight + 5)*i + 7
                                 ,50
                                 ,butHeight);
            painter->setPen(QPen(QColor("#c7c7c7")));
            painter->setBrush(QColor("#c7c7c7"));
            painter->drawRoundedRect(butShadowRect,border_radius,border_radius);


            //绘制按钮
            QRectF butRect(rect.width() - butWidth - 10
                           ,rect.y() + rowHeight * rowLineNum +(butHeight + 5)*i + 5
                           ,50
                           ,butHeight);
            //根据按钮选中状态绘制按钮
            if(i){
                painter->setPen(QPen(QColor("#8f9ae6")));
                painter->setBrush(QColor("#8f9ae6"));
            }else{
                painter->setPen(QPen(QColor("#FFFFFF")));
                painter->setBrush(QColor("#FFFFFF"));
            }
            painter->drawRoundedRect(butRect,border_radius,border_radius);

            //添加按钮文字
            painter->setPen(QPen(QColor("#000000")));
            painter->drawText(butRect,Qt::AlignCenter, "按钮");
        }


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

}

void CustomItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void CustomItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

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





