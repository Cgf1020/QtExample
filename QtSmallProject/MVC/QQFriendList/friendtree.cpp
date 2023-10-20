#include "friendtree.h"

#include <QHeaderView>
#include <QMessageBox>
#include <QEvent>
#include <QHoverEvent>
#include <QTime>


namespace qqfriendlist
{



FriendTree::FriendTree(QWidget *parent)
    : QTreeView{parent}
{
    initUi();
    initConnection();
}

void FriendTree::setValues(const std::vector<Group> &groups)
{
    m_model->clear();
    for (const auto& group : groups)
    {
        // 添加分组
        QStandardItem* item = new QStandardItem(group.groupName);
        item->setEditable(false);
        item->setData(group.groupName, Qt::ToolTipRole);
        item->setData(true, static_cast<int>(CustomRole::IsGroupRole));
        m_model->appendRow(item);
        for (const auto& contact : group.contactList)
        {
            // 分组下的联系人
            QStandardItem* contactItem = new QStandardItem(contact.name);
            contactItem->setEditable(false);
            contactItem->setData(contact.name, Qt::ToolTipRole);

            QVariant value{};
            value.setValue(contact);
            contactItem->setData(value, static_cast<int>(CustomRole::ContactRole));
            item->appendRow(contactItem);
        }
    }
}

void FriendTree::addGroup(QString groupName)
{
    // 添加分组
    QStandardItem* item = new QStandardItem(groupName);
    item->setEditable(false);
    item->setData(groupName, Qt::ToolTipRole);
    item->setData(true, static_cast<int>(CustomRole::IsGroupRole));
    m_model->appendRow(item);


    for (int i = 0; i < 3; i++)
    {
        // 分组下的联系人
        QStandardItem* contactItem = new QStandardItem("好友");
        contactItem->setEditable(false);
        contactItem->setData("好友", Qt::ToolTipRole);

        QVariant value{};
        Contact contact;
        value.setValue(contact);
        contactItem->setData(value, static_cast<int>(CustomRole::ContactRole));
        item->appendRow(contactItem);
    }
}

bool FriendTree::viewportEvent(QEvent *pEvent)
{
    bool result = QTreeView::viewportEvent(pEvent);
    QEvent::Type eventType = pEvent->type();
    int role = -1;

    switch (eventType)
    {
    case QEvent::HoverEnter:
    case QEvent::HoverLeave:
    case QEvent::HoverMove:
    {
        // hover 事件
        QHoverEvent* pHoverEvent = static_cast<QHoverEvent*>(pEvent);
        QModelIndex modelIndex = indexAt(pHoverEvent->pos());
        QStyleOptionViewItemV4 option = viewOptions();
        option.rect = visualRect(modelIndex);
        option.widget = this;

        QMetaObject::invokeMethod(qobject_cast<QQItemDelegate*>(itemDelegate(modelIndex)), "hoverEvent",
                                  Q_RETURN_ARG(int, role),
                                  Q_ARG(QHoverEvent*, pHoverEvent),
                                  Q_ARG(QAbstractItemView*, this),
                                  Q_ARG(QStyleOptionViewItem, option),
                                  Q_ARG(QModelIndex, modelIndex));
        {
            if (modelIndex.isValid())
            {
                // hover
                emit signalHover(modelIndex, role);
            }
        }
    }
    break;
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
    {
        int role = -1;
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(pEvent);
        QModelIndex modelIndex = indexAt(mouseEvent->pos());
        QStyleOptionViewItemV4 option = viewOptions();
        option.rect = visualRect(modelIndex);
        option.widget = this;

        QMetaObject::invokeMethod(qobject_cast<QQItemDelegate*>(itemDelegate(modelIndex)), "mouseEvent",
                                  Q_RETURN_ARG(int, role),
                                  Q_ARG(QMouseEvent*, mouseEvent),
                                  Q_ARG(QAbstractItemView*, this),
                                  Q_ARG(QStyleOptionViewItem, option),
                                  Q_ARG(QModelIndex, modelIndex));

        if (modelIndex.isValid())
        {
            if (eventType == QEvent::MouseButtonRelease &&
                Qt::LeftButton == mouseEvent->button())
            {
                // 左键按下
                if (role != -1)
                {
                    emit signalClicked(modelIndex, role);
                }
                else
                {
                    emit signalClicked(modelIndex);
                }
            }
            if (eventType == QEvent::MouseButtonDblClick &&
                Qt::LeftButton == mouseEvent->button())
            {
                // 左键双击
                emit signalDoubleClicked(modelIndex);
            }
        }
    }
    break;
    default:
        break;
    }

    return result;
}

void FriendTree::initUi()
{
    setWindowTitle("QQ好友列表");

    header()->hide();   // 隐藏表头
    setIndentation(0);  // 左边距设置为0
    setAnimated(true);  // 展开时动画

    m_model = new QStandardItemModel(this);
    setModel(m_model);
    m_delegate = new QQItemDelegate(this);
    setItemDelegate(m_delegate);
}

void FriendTree::initConnection()
{
    // 点击事件
    connect(this, &QTreeView::clicked, this, [&](const QModelIndex& index)
    {
        if (index.data(static_cast<int>(CustomRole::IsGroupRole)).toBool())
        {
            setExpanded(index, !isExpanded(index)); // 单击展开/收缩列表
        }
    });

    // 双击打开聊天
    connect(this, &QTreeView::doubleClicked, this, [&](const QModelIndex& index)
    {
        if (!index.data(static_cast<int>(CustomRole::IsGroupRole)).toBool())
        {
            // 不是分组Item才去处理双击事件
            auto info = index.data(static_cast<int>(CustomRole::ContactRole)).value<Contact>();
            QMessageBox msgBox;
            msgBox.setWindowTitle(QStringLiteral("双击打开聊天"));
            msgBox.setText(QStringLiteral("你好，") + info.name + QStringLiteral("。在不？"));
            msgBox.exec();
        }
    });

    // 展开时更换左侧的展开图标
    connect(this, &QTreeView::expanded, this, [&](const QModelIndex& index)
    {
        m_model->itemFromIndex(index)->setData(true, static_cast<int>(CustomRole::IsExpandedRole));
    });

    // 收起时更换左侧的展开图标
    connect(this, &QTreeView::collapsed, this, [&](const QModelIndex& index)
    {
        m_model->itemFromIndex(index)->setData(false, static_cast<int>(CustomRole::IsExpandedRole));
    });


    // 自定义hover事件
    connect(this, &FriendTree::signalHover, this, &FriendTree::onHoverHandle);

    // 自定义点击事件
    connect(this, QOverload<const QModelIndex&, int>::of(&FriendTree::signalClicked), this, &FriendTree::onClickedHandle);
}

void FriendTree::onHoverHandle(const QModelIndex &index, int role)
{
    if (index.data(static_cast<int>(CustomRole::IsGroupRole)).toBool())
    {
        return; // 群组的hover事件 退出
    }
    else
    {
        // 不同区域显示不同tooltip
        auto info = index.data(static_cast<int>(CustomRole::ContactRole)).value<Contact>();
        QString displayName{};
        switch (role)
        {
        case static_cast<int>(CustomRole::PortraitRole) : // 视频通话
        {
            displayName = QStringLiteral("鼠标移到头像上啦！");
            break;
        }
        case static_cast<int>(CustomRole::VideoRole) : // 视频通话
        {
            displayName = QStringLiteral("视频通话");
            break;
        }
        case static_cast<int>(CustomRole::SignatureRole) : // 个性签名
        {
            displayName = info.signature;
            break;
        }
        default:
        {
            // 默认tooltip显示用户名称+QQ号
//            qDebug() << "default";
            displayName = info.name + "(" + info.nickName + ")" + "(" + info.id + ")";
            break;
        }
        }

        m_model->itemFromIndex(index)->setData(displayName, Qt::ToolTipRole);
    }
}

void FriendTree::onClickedHandle(const QModelIndex &index, int role)
{
    // 不同区域显示不同tooltip
    auto info = index.data(static_cast<int>(CustomRole::ContactRole)).value<Contact>();
    switch (role)
    {
    case static_cast<int>(CustomRole::VideoRole) : // 视频通话
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(QStringLiteral("视频通话"));
        msgBox.setText(QTime::currentTime().toString("hh:mm:ss")
                       + QStringLiteral("，向") + info.name + QStringLiteral("发起视频通话。"));
        msgBox.exec();
        break;
    }
    default:
    {
        break;
    }
    }
}











}
