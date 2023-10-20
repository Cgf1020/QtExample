#include "qqitemdelegate.h"

#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QEvent>
#include <QHoverEvent>

#include "DelegatePainter.h"

namespace qqfriendlist
{

const int kGroupItemHeight{ 35 };
const int kContactItemHeight{ 60 };

const QRect kGroupPullIconRect{ 10,12,11,11 }; // 群组下拉图标
const QRect kGroupNameRect{ 30,0,200,35 };	   // 群组名称

const QRect kContactPortraitRect{ 10,10,40,40 }; // 联系人头像
const QRect kContactNameRect{ 60,10,200,20 };	 // 联系人名字
const QRect kSignatureRect{ 60,30,160,20 };		 // 联系人个性签名
const QRect kVipIconRect{ 60,30,30,12 };		 // 联系人VIP图标
const QRect kOnlineStateIconRect{ 40,35,14,14 }; // 在线状态图标
const QRect kVideoIconRect{ 0,25,20,13 };	     // 视频通话图标




QQItemDelegate::QQItemDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
    border_radius = 5;

    butWidth = 30;
}

void QQItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    OperateActions operateActions = getOperateActions(option, index);
    QColor color;
    color = (operateActions.isHovered) ? QColor("#f0f0f0") //背景色选中
            : (!operateActions.isSelected && operateActions.isHovered) ? QColor("lightblue") // hover
                                                                       : QColor("#ffffff");
    if (index.data(static_cast<int>(CustomRole::IsGroupRole)).toBool())
    {
        paintGroup(painter, option, index);
        return;
    }
    else
    {
        paintContact(painter, option, index); // 绘制联系人
    }
}

QSize QQItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);

    if (index.data(static_cast<int>(CustomRole::IsGroupRole)).toBool())
    {
        return QSize(size.width(), kGroupItemHeight); // 群组Item高度
    }

    return QSize(size.width(), kContactItemHeight);   // 联系人Item高度
}

int QQItemDelegate::getHoverEventRole(const QPoint &pos, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    qDebug() << "QQItemDelegate::getHoverEventRole";

    // 视频通话图标位置
    QRect videoRect(option.rect.left() + option.rect.width() - kVideoIconRect.width() - 16, option.rect.top() + kVideoIconRect.y(),
                    kVideoIconRect.width(), kVideoIconRect.height());
    if (!index.data(static_cast<int>(CustomRole::IsGroupRole)).toBool() && videoRect.contains(pos))
    {
        return static_cast<int>(CustomRole::VideoRole);
    }

    // 个性签名
    QRect signatureRect(option.rect.left() + kSignatureRect.x(), option.rect.top() + kSignatureRect.y(),
                        kSignatureRect.width(), kSignatureRect.height());
    if (!index.data(static_cast<int>(CustomRole::IsGroupRole)).toBool() && signatureRect.contains(pos))
    {
        return static_cast<int>(CustomRole::SignatureRole);
    }

    // 头像
    QRect contactHeadPortraitRect(option.rect.left() + kContactPortraitRect.x(), option.rect.top() + kContactPortraitRect.y(),
                                  kContactPortraitRect.width(), kContactPortraitRect.height());
    if (!index.data(static_cast<int>(CustomRole::IsGroupRole)).toBool() && contactHeadPortraitRect.contains(pos))
    {
        return static_cast<int>(CustomRole::PortraitRole);
    }
    return -1;
}

int QQItemDelegate::getMouseEventRole(const QPoint &pos, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    qDebug() << "QQItemDelegate::getMouseEventRole";

    // 视频通话图标位置
    QRect videoRect(option.rect.left() + option.rect.width() - kVideoIconRect.width() - 16, option.rect.top() + kVideoIconRect.y(),
                    kVideoIconRect.width(), kVideoIconRect.height());
    if (!index.data(static_cast<int>(CustomRole::IsGroupRole)).toBool() && videoRect.contains(pos))
    {
        return static_cast<int>(CustomRole::VideoRole);
    }

    return -1;
}

int QQItemDelegate::hoverEvent(QHoverEvent *hoverEvent, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &modelIndex)
{
//    qDebug() << "QQItemDelegate::hoverEvent";

    if (nullptr == hoverEvent || nullptr == view || !modelIndex.isValid())
    {
        return -1;
    }

    auto curModel = view->model();
    if (nullptr == curModel)
    {
        return -1;
    }
    auto pos = hoverEvent->pos();

    auto eventType = hoverEvent->type();
    switch (eventType)
    {
    case QEvent::HoverEnter:
    case QEvent::HoverLeave:
        break;
    case QEvent::HoverMove:
    {
        curModel->setData(modelIndex, pos, ItemRole::PosRole); // 获取位置

        switch (eventType)
        {
        case QHoverEvent::HoverMove:
            curModel->setData(modelIndex, option.rect.contains(pos) ? true : false, ItemRole::MouseHoverRole);
            break;
        case QHoverEvent::HoverLeave:
        case QHoverEvent::Leave:
            curModel->setData(modelIndex, false, ItemRole::MousePressRole);
            curModel->setData(modelIndex, false, ItemRole::MouseHoverRole);
            break;
        case QHoverEvent::HoverEnter:
            curModel->setData(modelIndex, true, ItemRole::MouseHoverRole);
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }

    view->update(modelIndex);

    if (option.rect.contains(pos))
    {
        // hover 的role
        return getHoverEventRole(pos, option, modelIndex);
    }

    return -1;
}

int QQItemDelegate::mouseEvent(QMouseEvent *mouseEvent, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &modelIndex)
{
//    qDebug() << "QQItemDelegate::mouseEvent";

    if (nullptr == mouseEvent || nullptr == view || !modelIndex.isValid())
    {
        return -1;
    }

    auto curModel = view->model();
    if (nullptr == curModel)
    {
        return -1;
    }

    auto pos = mouseEvent->pos();

    curModel->setData(modelIndex, pos, ItemRole::PosRole);

    auto eventType = mouseEvent->type();
    switch (eventType)
    {
    case QMouseEvent::MouseMove:
        curModel->setData(modelIndex, true, ItemRole::MouseHoverRole);
        break;
    case QMouseEvent::MouseButtonPress:
        curModel->setData(modelIndex, true, ItemRole::MousePressRole);
        break;
    case QMouseEvent::MouseButtonRelease:
        curModel->setData(modelIndex, true, ItemRole::MousePressRole);
        break;
    default:
        break;
    }

    view->update(modelIndex);

    if (option.rect.contains(pos))
    {
        // 点到的区域
        return getMouseEventRole(pos, option, modelIndex);
    }

    return -1;
}



QQItemDelegate::OperateActions QQItemDelegate::getOperateActions(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    OperateActions oa{};
    oa.isSelected = (option.state& QStyle::State_Selected) == QStyle::State_Selected ? true : false;
    oa.isHovered = (option.state& QStyle::State_MouseOver) == QStyle::State_MouseOver ? true : false;
    oa.isPressed = index.data(ItemRole::MousePressRole).toBool();
    oa.mousePosX = index.data(ItemRole::PosRole).toPoint().x();
    oa.mousePosY = index.data(ItemRole::PosRole).toPoint().y();

    return oa;
}

void QQItemDelegate::paintGroup(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    publicgui::DelegatePainter delegatePainter;
    OperateActions operateActions = getOperateActions(option, index);
    QColor color;
    color = (operateActions.isHovered) ? QColor("#f0f0f0") : QColor("#ffffff"); // hover时变灰

    // 背景色
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawRect(option.rect);

    // 下拉列表图标
    QRect pullIconRect(option.rect.left() + kGroupPullIconRect.x(), option.rect.top() + kGroupPullIconRect.y(),
                       kGroupPullIconRect.width(), kGroupPullIconRect.height());
    QString pullIconPath{ ":/svg/expand_down.svg" };
    if (!index.data(static_cast<int>(CustomRole::IsExpandedRole)).toBool())
    {
        pullIconPath = ":/svg/expand_right.svg";
    }
    delegatePainter.paintSvgImage(painter, pullIconPath, pullIconRect);

    // 群组名称
    QRect nameRect(option.rect.left() + kGroupNameRect.x(), option.rect.top() + kGroupNameRect.y(), kGroupNameRect.width(), kGroupNameRect.height());
    delegatePainter.paintText(painter, option, index, Qt::DisplayRole, Qt::AlignLeft, QColor("black"), nameRect, 13);
}

void QQItemDelegate::paintContact(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    publicgui::DelegatePainter delegatePainter;
    OperateActions operateActions = getOperateActions(option, index);
    QColor backgroundColor;
    if (operateActions.isHovered && !operateActions.isSelected)
    {
        backgroundColor = QColor("#f2f2f2");
    }
    else if (operateActions.isSelected)
    {
        backgroundColor = QColor("#ebebeb");
    }
    else
    {
        backgroundColor = QColor("#ffffff");
    }

    // 背景色
    painter->setPen(Qt::NoPen);
    painter->setBrush(backgroundColor);
    painter->drawRect(option.rect);

    // 联系人信息
    auto info = index.data(static_cast<int>(CustomRole::ContactRole)).value<Contact>();

    // 联系人头像
    {
        QRect contactHeadPortraitRect(option.rect.left() + kContactPortraitRect.x(), option.rect.top() + kContactPortraitRect.y(),
                                      kContactPortraitRect.width(), kContactPortraitRect.height());
        QString contactHeadPortraitPath{ ":/svg/portrait_boy.svg" };//:/svg/portrait_boy.svg
        if (!info.sex)
        {
            contactHeadPortraitPath = ":/svg/portrait_girl.svg";
        }
        delegatePainter.paintSvgImage(painter, contactHeadPortraitPath, contactHeadPortraitRect);
    }

    // 联系人名称
    {
        QRect nameRect(option.rect.left() + kContactNameRect.x(), option.rect.top() + kContactNameRect.y(),
                       kContactNameRect.width(), kContactNameRect.height());
        QColor nameColor{ "black" };
        if (info.isVip) // 是vip
        {
            nameColor = QColor("#ff0000");
        }
        delegatePainter.paintText(painter, option, index, Qt::DisplayRole,
                                  Qt::AlignLeft, nameColor, nameRect, 13, info.name + "(" + info.nickName + ")");
    }

    // 个性签名
    {
        QRect signatureRect(option.rect.left() + kSignatureRect.x(), option.rect.top() + kSignatureRect.y(),
                            kSignatureRect.width(), kSignatureRect.height());
        delegatePainter.paintText(painter, option, index, Qt::DisplayRole,
                                  Qt::AlignLeft, QColor("black"), signatureRect, 13, info.signature);
    }


    // 在线状态图标
    {
        QRect onlineStateIconRect(option.rect.left() + kOnlineStateIconRect.x(), option.rect.top() + kOnlineStateIconRect.y(),
                                  kOnlineStateIconRect.width(), kOnlineStateIconRect.height());
        QString onlineStateIconPath{ ":/svg/online-im.svg" };
        switch (info.onlineState)
        {
        case OnlineState::Busy:
        {
            onlineStateIconPath = ":/svg/busy-im.svg";
            break;
        }
        case OnlineState::Leave:
        {
            onlineStateIconPath = ":/svg/leave-im.svg";
            break;
        }
        case OnlineState::Online:
        {
            break;
        }
        default:break;
        }
        // 防背景透明 先把背景处理了 用背景色backgroundColor画一个圆形区域
        painter->setPen(Qt::NoPen);
        painter->setBrush(backgroundColor);
        painter->drawRoundedRect(onlineStateIconRect, onlineStateIconRect.width() / 2, onlineStateIconRect.height() / 2);

        delegatePainter.paintSvgImage(painter, onlineStateIconPath, onlineStateIconRect);
    }

    // 视频通话
    {
        // 只有hover状态才会显示视频通话图标
        if (operateActions.isHovered)
        {
            QRect videoRect(option.rect.left() + option.rect.width() - kVideoIconRect.width() - 16, option.rect.top() + kVideoIconRect.y(),
                            kVideoIconRect.width(), kVideoIconRect.height());
            delegatePainter.paintSvgImage(painter, ":/svg/video.svg", videoRect);
        }
    }
}





}
