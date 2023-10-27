#include "tabledelegate.h"

#include <QDebug>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QImage>
#include <QPixmap>
#include <QStandardItemModel>
#include <QPainter>
#include <QColor>
#include <QCheckBox>
#include "../mvcGlobalDefine.h"


TableDelegate::TableDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

void TableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    QStyleOptionViewItem new_option(option);
//    new_option.displayAlignment = Qt::AlignCenter;        // 居中显示
//    if (new_option.state & QStyle::State_Selected) {
//        new_option.font.setBold(true);                    // 变为粗体
//    }
//    QStyledItemDelegate::paint(painter, new_option, index);


    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);


    //判断鼠标是否悬浮在item上
    QColor color;
    bool isHovered = (option.state& QStyle::State_MouseOver) == QStyle::State_MouseOver ? true : false;
    color = isHovered ? QColor("#f0f0f0") : QColor("#ffffff"); // hover时变灰
    // 背景色
    if(isHovered)
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(color);
        painter->drawRect(option.rect);
    }


    do{
        if(!index.isValid())
            break;

        //获取列号
        if(index.column() == static_cast<int>(TESTMVC::ItemColumnRole::SnapshotColumn))
        {
            painterSnapshot(painter, option, index);
        }
        else if(index.column() == static_cast<int>(TESTMVC::ItemColumnRole::PlaybackColumn))
        {
            painterPlaybackBtn(painter, option, index);
        }
        else if(index.column() == static_cast<int>(TESTMVC::ItemColumnRole::OperateColumn))
        {

        }
        else
        {
            break;
        }
        painter->restore();
        return;
    }while(0);

    QStyledItemDelegate::paint(painter, option, index);
    painter->restore();
}

QSize TableDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 120);
}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void TableDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    /*1.拿到数据  可以根据自己注册的数据去拿
     *2.设置到编辑器中
     */

    QStyledItemDelegate::setEditorData(editor, index);
}

void TableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //设置给模型，然后界面在显示出来
    QStyledItemDelegate::setModelData(editor, model, index);
}


bool TableDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void TableDelegate::deleteButtonClickEvent()
{
    qDebug() << "deleteButtonClickEvent";

    emit deleteButtonClickSignal();
}

void TableDelegate::painterSnapshot(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void TableDelegate::painterPlaybackBtn(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int painterWidth = (PlayBackBtnSize.width() > option.rect.width() - 8) ? (option.rect.width() - 8) : PlayBackBtnSize.width();
    int painterHeight = (PlayBackBtnSize.height() > option.rect.height() - 8) ? (option.rect.height() - 8) : PlayBackBtnSize.height();
    int min = qMin(painterWidth, painterHeight);
    int xOffset = (option.rect.width() - min) / 2;
    int yOffset = (option.rect.height() - min) / 2;

    QRect rect = QRect(option.rect.left() + xOffset, option.rect.top() + yOffset, min, min);
    QImage image(":/image/playback_btn.png");
    painter->drawImage(rect, image);
}



































