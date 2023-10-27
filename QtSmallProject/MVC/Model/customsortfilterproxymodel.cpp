#include "customsortfilterproxymodel.h"

#include <QDebug>

CustomSortFilterProxyModel::CustomSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{

}

void CustomSortFilterProxyModel::setFilterAlarmType(TESTMVC::AlarmType alarmType) noexcept
{
    alarmType_ = alarmType;
    filterSet_.insert(static_cast<int>(TESTMVC::ItemColumnRole::AlarmTypeColumn));
    invalidateFilter();
}

void CustomSortFilterProxyModel::setFilterAlarmDate(QDate fromDate, QDate toDate) noexcept
{
    fromDate_ = fromDate;
    toDate_ = toDate;
    filterSet_.insert(static_cast<int>(TESTMVC::ItemColumnRole::AlarmTimeColumn));
    invalidateFilter();
}

void CustomSortFilterProxyModel::CancelAllFilterConditions()
{
    filterSet_.clear();

    /*调用这个函数会  调用filterAcceptsRow() 函数   来重置过滤*/
    invalidateFilter();
}

bool CustomSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if(filterSet_.isEmpty())
        return QSortFilterProxyModel::filterAcceptsRow(source_row,source_parent);

    //获取的 data
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    QVariant var = index.data(static_cast<int>(TESTMVC::ItemRole::TableItemRole));
    TESTMVC::TableItemData itemData = var.value<TESTMVC::TableItemData>();

    for(auto it = filterSet_.begin(); it != filterSet_.end(); it++)
    {
        TESTMVC::ItemColumnRole filterColunm = static_cast<TESTMVC::ItemColumnRole>(*it);

        switch (filterColunm) {
        case TESTMVC::ItemColumnRole::AlarmTimeColumn:
        {
            if(!dateInRange(itemData.dataTime.date()))
                return false;
        }
            break;
        case TESTMVC::ItemColumnRole::AlarmTypeColumn:
        {
            if(itemData.alarmType != alarmType_ && alarmType_ != TESTMVC::AlarmType::NONE)
                return false;
        }
            break;
        default:
            break;
        }
    }
    return true;
}

bool CustomSortFilterProxyModel::dateInRange(QDate date) const
{
    return (!fromDate_.isValid() || date >= fromDate_) && (!toDate_.isValid() || date <= toDate_);
}
