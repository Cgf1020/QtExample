#include "qqfriendlist.h"
#include "ui_qqfriendlist.h"

#include <QDebug>
#include <QHeaderView>
#include <QMessageBox>
#include <QHoverEvent>
#include <QTime>

//namespace
//{
//// 群组名称
//std::vector < std::string > groups{ "我的家人", "我的朋友", "高中校友", "CSU", "铁道学院" };
//// 家人数据
//std::vector < std::string > familys{ "老爸", "老妈", "哥哥", "姑姑", "小姨" };
//// 朋友数据
//std::vector < std::string > friends{ "伟哥", "郭渣", "忘恩", "菜包", "小弟" };
//// 高中同学
//std::vector < std::string > highSchool{ "海洋", "宽宽", "嗯恩", "振", "小羊转" };
//// CSU
//std::vector < std::string > csu{ "张老师", "费老师", "刘老师", "胡老师", "郑老师" };
//// 铁道学院
//std::vector < std::string > csru{ "政委", "胜总", "小飞飞", "大兵", "逗比鱼" };

//        // 信息列表
//        std::vector<std::vector < std::string >> contactBasicInfo{ familys , friends, highSchool, csu, csru };
//}

// 生成测试数据
//auto createFriendDatas = [&]()
//{
//    static int qqNumber = 396396396; // 起始qq号
//    std::vector<Group> groupList{};
//    for (int i = 0; i < groups.size(); i++)
//    {
//        // 创建5个分组
//        Group group{};
//        group.groupName = QString::fromLocal8Bit(groups[i].c_str());

//        for (auto j = 0; j < contactBasicInfo[i].size(); j++)
//        {
//            Contact contact{};
//            contact.name = contact.nickName = QString::fromLocal8Bit(contactBasicInfo[i][j].c_str());
//            contact.id = QString::number(qqNumber++);
//            contact.sex = ((j+1) % 2 == 0); // 生成性别
//            contact.isVip = (j % 2 == 0);
//            contact.onlineState = OnlineState(j);
//            group.contactList.emplace_back(std::move(contact));
//        }

//        groupList.emplace_back(std::move(group));
//    }

//    return groupList;
//};






QQFriendList::QQFriendList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQFriendList)
{
    ui->setupUi(this);


    FriendTree_ = new FriendTree(this);


    for(int i = 0; i < 5; i++)
    {
        FriendTree_->addGroup("分组");
    }

    this->layout()->addWidget(FriendTree_);

//    InitUI();
//    initConnection();
}

QQFriendList::~QQFriendList()
{
    delete ui;
}

void QQFriendList::addGroup(QString groupName)
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

bool QQFriendList::eventFilter(QObject *watched, QEvent *event)
{
    if(ui->treeView == watched)
    {
        QEvent::Type eventType = event->type();

//        qDebug() << " treeView::eventFilter type = " << eventType;

        switch (eventType)
        {
        case QEvent::HoverEnter:
        case QEvent::HoverLeave:
        case QEvent::HoverMove:
        {
            qDebug() << " treeView::eventFilter:HoverMove";

            // hover 事件
            QHoverEvent* pHoverEvent = static_cast<QHoverEvent*>(event);
            QModelIndex modelIndex = ui->treeView->indexAt(pHoverEvent->pos());

            if (modelIndex.isValid())
            {
                // hover
//                emit signalHover(modelIndex, role);
                onHoverHandle(modelIndex, -1);
            }
        }
        break;
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        {

        }
        break;
        default:
            break;
        }

    }

    return QWidget::eventFilter(watched, event);
}

void QQFriendList::InitUI()
{
    ui->treeView->setWindowTitle("QQ好友列表");

    ui->treeView->header()->hide();   // 隐藏表头
    ui->treeView->setIndentation(0);  // 左边距设置为0
    ui->treeView->setAnimated(true);  // 展开时动画

    m_model = new QStandardItemModel(this);
    ui->treeView->setModel(m_model);
    m_delegate = new QQItemDelegate(this);
    ui->treeView->setItemDelegate(m_delegate);

    // 给控件注册事件过滤器
//    ui->treeView->installEventFilter(this);
}

void QQFriendList::initConnection()
{
    // 点击事件
    connect(ui->treeView, &QTreeView::clicked, this, [&](const QModelIndex& index)
    {
        qDebug() << "treeView 点击事件";
        if (index.data(static_cast<int>(CustomRole::IsGroupRole)).toBool())
        {
            ui->treeView->setExpanded(index, !ui->treeView->isExpanded(index)); // 单击展开/收缩列表
        }
    });

    // 双击打开聊天
    connect(ui->treeView, &QTreeView::doubleClicked, this, [&](const QModelIndex& index)
    {
        qDebug() << "treeView 双击事件";
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
    connect(ui->treeView, &QTreeView::expanded, this, [&](const QModelIndex& index)
    {
        m_model->itemFromIndex(index)->setData(true, static_cast<int>(CustomRole::IsExpandedRole));
    });

    // 收起时更换左侧的展开图标
    connect(ui->treeView, &QTreeView::collapsed, this, [&](const QModelIndex& index)
    {
        m_model->itemFromIndex(index)->setData(false, static_cast<int>(CustomRole::IsExpandedRole));
    });
}

void QQFriendList::onHoverHandle(const QModelIndex &index, int role)
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
            qDebug() << "default";
            displayName = info.name + "(" + info.nickName + ")" + "(" + info.id + ")";
            break;
        }
        }

        m_model->itemFromIndex(index)->setData(displayName, Qt::ToolTipRole);
    }
}

void QQFriendList::onClickedHandle(const QModelIndex &index, int role)
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















