#include "tabledelegate.h"

#include <QDebug>
#include <QSpinBox>


TableDelegate::TableDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

void TableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::paint(painter, option, index);
}

QSize TableDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 120);
}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "TableDelegate::createEditor";

    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(100);

    return editor;
    //    return QStyledItemDelegate::createEditor(parent, option, index);
}

void TableDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "TableDelegate::updateEditorGeometry";

//    editor->setGeometry(option.rect);
    editor->setGeometry(option.rect.x() + 40, option.rect.y(), option.rect.width() - 80, option.rect.height());
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    /*1.拿到数据  可以根据自己注册的数据去拿
     *2.设置到编辑器中
     */

    qDebug() << "TableDelegate::setEditorData";

    if(!index.isValid())
    {
        qDebug() << "TableDelegate::setEditorData  is not Valid";
        return;
    }

    int value = index.data(Qt::EditRole).toInt();

    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);

    spinBox->setValue(value);
}

void TableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //设置给模型，然后界面在显示出来
    qDebug() << "TableDelegate::setModelData";

    if(!index.isValid())
    {
        qDebug() << "TableDelegate::setModelData  is not Valid";
        return;
    }

    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    int value = spinBox->value();

    model->setData(index, value, Qt::EditRole);
}























