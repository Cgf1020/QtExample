#ifndef QQLISTDEFINES_H
#define QQLISTDEFINES_H


#include <QObject>
#include <QMetaType>
#include <QStyledItemDelegate>
#include <QString>

namespace qqfriendlist {

    //qq好友的现在状态
    enum class OnlineState
    {
        Online, // 在线
        Leave,  // 离开
        Busy,   // 忙碌
    };

    //好友的信息结构
    typedef struct Contact
    {
        QString name{""};           //名字
        int sex{0};                 //性别 0：男 1：女
        QString nickName{""};       //昵称
        QString id{""};             //QQ号
        QString signature{QStringLiteral("新年快乐，心想事成")};        //个性签名
        QString headPortrait{};     //头像路径
        OnlineState onlineState{ OnlineState::Online };             // 在线状态
        bool isVip{ 0 };                    // VIP类型 0不是vip; 1 vip; 2 svip
    }Contact;


    // 分组
    typedef struct Group
    {
        QString groupName{};                    // 组名字
        std::vector<Contact> contactList{};     // 联系人列表
    }Group;

    // 绘制角色
    enum class CustomRole
    {
        IsGroupRole = Qt::UserRole + 1000, // 是否是群组
        GroupNameRole,                     // 群组名称
        ContactRole,                       // 联系人信息
        IsExpandedRole,                    // 是否收起
        VideoRole,                         // 视频通话role
        SignatureRole,                     // 个性签名
        PortraitRole,                      // 头像
    };


}

//将自定义的数据结构注册，否则不可设置为Item的数据。Qt提供了注册自定义数据的宏
Q_DECLARE_METATYPE(qqfriendlist::Contact)



#endif // QQLISTDEFINES_H
