#include "btndelegate.h"

#include <QIcon>
#include <QApplication>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>
#include <QDesktopWidget>
#include <QToolTip>
#include <QDebug>



BtnDelegate::BtnDelegate(QObject *parent)
    : QStyledItemDelegate{parent},
    playBackBtn(new QPushButton())
{
    m_btnNames << "编辑" << "删除";


//    playBackBtn->setStyleSheet("QPushButton{border-width: 0px;\
//                                position: absolute;\
//                                left: 0px;\
//                                top: 0px;\
//                                max-width: 80px;\
//                                width:80px;\
//                                height: 30px;\
//                                background: inherit;\
//                                background-color: rgba(255, 255, 255, 0);\
//                                border-width: 1px;\
//                                border-style: solid;\
//                                border-color: red;\
//                                border-radius: 10px;\
//                                font-size: 11px;\
//                                color: red;}\
//                                QPushButton:hover{background-color:red; color:#FFFFFF;}");
}

void BtnDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);

    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;


//    QStyledItemDelegate::paint(painter, viewOption, index);

    // 绘制按钮
    QStyleOptionButton button;
    //QRect(option.rect.left() + nHalf + m_nWidth * i + m_nSpacing * i, option.rect.top() + nTop,  m_nWidth, m_nHeight);

    QRect IconRect(option.rect.left() + 10, option.rect.top() + 10,
                   option.rect.width() - 20, option.rect.height() - 20);

    button.rect =  IconRect;
    button.state |= QStyle::State_Enabled;
    button.iconSize = QSize(32, 32);
    button.icon = QIcon(QString(":/image/playback_btn.png"));


//    if (button.rect.contains(m_mousePoint))
//    {
//        if (m_nType == 0)
//        {
//            button.state |= QStyle::State_MouseOver;
//        }
//        else if (m_nType == 1)
//        {
//            button.state |= QStyle::State_Sunken;
//        }
//    }
    QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter, playBackBtn.data());
}

bool BtnDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QMouseEvent *pEvent = static_cast<QMouseEvent *> (event);
    m_mousePoint = pEvent->pos();

    // 还原鼠标样式
    QApplication::restoreOverrideCursor();

    // 鼠标位于按钮之上
    QStyleOptionButton button;


    QRect IconRect(option.rect.left() + 10, option.rect.top() + 10,
                   option.rect.width() - 20, option.rect.height() - 20);

    button.rect =  IconRect;

    bool bRepaint = false;

    if (!button.rect.contains(m_mousePoint))
        return bRepaint;

    bRepaint = true;

    switch (event->type())
    {
        // 鼠标滑过
        case QEvent::MouseMove:
        {
            m_nType = 0;

            // 设置鼠标样式为手型
            QApplication::setOverrideCursor(Qt::PointingHandCursor);
//            QToolTip::showText(pEvent->globalPos(), "回放链接");
            break;
        }
        // 鼠标按下
        case QEvent::MouseButtonPress:
        {
            m_nType = 1;
//            emit open(index);
            break;
        }
        // 鼠标释放
        case QEvent::MouseButtonRelease:
        {
            break;
        }
        case QEvent::Leave:
        {
            qDebug() << "鼠标 离开事件";
            // 还原鼠标样式
            QApplication::restoreOverrideCursor();
            break;
        }
        default:
            break;
    }

    return bRepaint;
}
