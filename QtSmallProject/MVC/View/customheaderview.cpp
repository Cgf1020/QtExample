#include "customheaderview.h"

#include <QDebug>
#include <QPainter>
#include <QCheckBox>


CustomHeaderView::CustomHeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent)
{
    // 设置Section可点击，若不设置则不能发出sectionClicked信号
    this->setSectionsClickable(true);

    // sectionClicked(表头选择点击事件)
    connect(this, &QHeaderView::sectionClicked, [=](int logicalIndex)
    {
//        qDebug() << "CustomHeaderView Clicked " << logicalIndex;
        if(logicalIndex == 1)
        {
            isOn = !isOn;
            //发出信号
            emit columnSectionClicked(logicalIndex, isOn);
        }

        //设置表头进行排序
        if(logicalIndex == 2 || logicalIndex == 3 || logicalIndex == 4)
        {
            static bool bSortAsc = true;

            Qt::SortOrder order = bSortAsc ? (Qt::AscendingOrder) : (Qt::DescendingOrder);

            this->setSortIndicatorShown(true);
            this->setSortIndicator(logicalIndex, order);

            bSortAsc = !bSortAsc;
        }
        else
        {
            this->setSortIndicatorShown(false);
        }
    });
}

void CustomHeaderView::setColumnCheckable(int column, bool checkable)
{
}

void CustomHeaderView::setColumnCheckState(bool state)
{
    isOn = state;
    updateSection(1);
}

void CustomHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();    //保存当前画笔状态
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore(); //恢复保存的画笔状态

    if(logicalIndex == 1)
    {
        QStyleOptionButton styleOption;
        styleOption.rect = rect.adjusted(3, 0, 0, 0);
        styleOption.state = QStyle::State_Enabled;

        if(isOn)
            styleOption.state = QStyle::State_On;
        else
            styleOption.state = QStyle::State_Off;

        //调用this的style对象绘制复选框
        this->style()->drawControl(QStyle::CE_CheckBox, &styleOption, painter);
    }
}












