#include "listview.h"

#include <QDebug>


namespace TESTMVC {



ListView::ListView(QWidget *parent)
    : QListView{parent}
{
    Init();
}

void ListView::AddGroup(QString title)
{
    ListGroupData groupData;
    groupData.title = title;

    QStandardItem* item = new QStandardItem();

    item->setEditable(false);
    item->setData(QVariant::fromValue(groupData), static_cast<int>(ListItemRole::GroupRole));
    item->setData(true, static_cast<int>(ListItemRole::IsGroupRole));

    model_->appendRow(item);

    QList<QStandardItem*> list;
    list.clear();
    itemMap_[item] = list;

    for(int i = 0; i < 3; i++)
    {
        ListItemData itemData;
        itemData.title = "好友";

        QStandardItem* subItem = new QStandardItem();

        subItem->setEditable(false);
        subItem->setData(QVariant::fromValue(itemData), static_cast<int>(ListItemRole::ItemRole));
        subItem->setData(false, static_cast<int>(ListItemRole::IsGroupRole));
        subItem->setData(true, static_cast<int>(ListItemRole::IsItemRole));

        model_->appendRow(subItem);
        this->setRowHidden(model_->indexFromItem(subItem).row(), true);

        itemMap_[item].append(subItem);
    }
}

void ListView::Init()
{
    model_ = new QStandardItemModel(this);

    this->setModel(model_);

    delegata_ = new ListDelegate(this);

    this->setItemDelegate(delegata_);

    // 展开时更换左侧的展开图标
    connect(this, &ListView::clicked, this, [&](const QModelIndex& index){
        //判断是不是 group
        if(index.data(static_cast<int>(ListItemRole::IsGroupRole)).toBool())
        {
            //更新值
            QVariant var = index.data(static_cast<int>(ListItemRole::GroupRole));
            ListGroupData groupData = var.value<ListGroupData>();
            groupData.isExpande = !groupData.isExpande;
            var.setValue<ListGroupData>(groupData);
            model_->setData(index, var, static_cast<int>(ListItemRole::GroupRole));

            if(groupData.isExpande)
            {
                foreach (auto item, itemMap_[model_->itemFromIndex(index)]) {
                    this->setRowHidden(model_->indexFromItem(item).row(), false);
                }
            }
            else
            {
                foreach (auto item, itemMap_[model_->itemFromIndex(index)]) {
                    this->setRowHidden(model_->indexFromItem(item).row(), true);
                }
            }
        }
    });
}












}
