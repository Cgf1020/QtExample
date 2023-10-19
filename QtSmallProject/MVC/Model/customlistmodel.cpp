#include "customlistmodel.h"

#include <QDebug>

CustomListModel::CustomListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

void CustomListModel::setStringList(const QStringList &strings)
{
    strList = strings;
}

QStringList CustomListModel::stringList() const
{
    return strList;
}

int CustomListModel::rowCount(const QModelIndex &parent) const
{
    return strList.count();
}

QVariant CustomListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    if (index.row() >= strList.size())
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole)
    {
        return strList.at(index.row());
    }
    else
    {
        return QVariant();
    }
}

bool CustomListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "CustomListModel::setData";

    if (index.isValid() && role == Qt::EditRole)
    {
        strList.replace(index.row(), value.toString());
        //通知view调用model中的data渲染界面
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool CustomListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    qDebug() << "CustomListModel::insertRows";

//    beginInsertRows(parent, )

//    strList.insert(row, "");

//    emit rowsInserted(parent,)

    return true;
}

bool CustomListModel::removeRows(int row, int count, const QModelIndex &parent)
{

    return true;
}

Qt::ItemFlags CustomListModel::flags(const QModelIndex &index) const
{
    //Qt::ItemIsEditable 代表你选择的这个数据是能编辑的


//    qDebug() << "CustomListModel::flags";


    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;     //设置item为可用 | 设置item可选择
    if (index.column() == 0)    //flags = Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;     //设置第一列的item为可用 | item可选择 | item用户可以选中
    {
        flags = Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;  //设置第一列的item为可用 | item可选择 | item用户可以选中
    }


    return flags;



//    if (!index.isValid())
//    {
//        return Qt::ItemIsEnabled;
//    }
//    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
