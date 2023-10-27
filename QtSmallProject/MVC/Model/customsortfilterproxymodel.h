#ifndef CUSTOMSORTFILTERPROXYMODEL_H
#define CUSTOMSORTFILTERPROXYMODEL_H



/*自定义的 排序 筛选 Model
 *
 *
 *
 *
 *支持的功能
 *1.支持多个筛选条件, 只支持筛选列，对每个列进行过滤
 *2.日期过滤：参考 Qt的demo  customsortfiltermodel 工程
 *3.
*/



#include <QObject>
#include <QSortFilterProxyModel>
#include <QDate>
#include <QSet>
#include "../mvcGlobalDefine.h"


class CustomSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit CustomSortFilterProxyModel(QObject *parent = nullptr);

    /*设置警报过滤条件
     */
    void setFilterAlarmType(TESTMVC::AlarmType alarmType = TESTMVC::AlarmType::NONE) noexcept;

    /* 设置日期过滤条件
     * @fromDate:
     * @toDate:
    */
    void setFilterAlarmDate(QDate fromDate = QDate(), QDate toDate = QDate().currentDate()) noexcept;

    /* 取消所有的过滤条件
    */
    void CancelAllFilterConditions();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;



signals:




private:
    bool dateInRange(QDate date) const;

private:
    /*过滤列表集合*/
    QSet<int> filterSet_;

    /*警报类型*/
    TESTMVC::AlarmType alarmType_;

    /*日期过滤条件*/
    QDate fromDate_;
    QDate toDate_;

};

#endif // CUSTOMSORTFILTERPROXYMODEL_H
