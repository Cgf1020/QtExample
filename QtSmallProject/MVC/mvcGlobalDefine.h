#ifndef MVCGLOBALDEFINE_H
#define MVCGLOBALDEFINE_H


#include <QObject>
#include <QDateTime>

namespace TESTMVC
{
    // 绘制角色
    enum class ItemRole
    {
        ColumnRole = Qt::UserRole + 100,         //类的类型
        TableItemRole
    };

    /*Table 列 的类型*/
    enum class ItemColumnRole
    {
        InfoData = 0,                            //信息数据列
        CheckboxColumn,                          // 复选框列
        DeviceIdColumn,                           //设备编号列
        AlarmTimeColumn,                          //警报时间列
        AlarmTypeColumn,                          //警报类型列
        SnapshotColumn,                           //快照列
        PlaybackColumn,                           //回放列
        OperateColumn,                            //操作列
    };

    /*警报类型*/
    enum class AlarmType
    {
        NONE = 0,
        Fire,               //火灾
        HighCover,          //高空遮挡物
        OverTemperature,    //温度过高
        IceCover            //冰覆盖
    };

    /*每一行的 各列的数据*/
    typedef struct TableItemData{
        QString     deviceId;       //设备id
        AlarmType   alarmType;      //报警类型
        QDateTime   dataTime;       //报警时间
        QString     imagePath;      //报警快照
        QString     playblackUrl;   //视频回放地址
    } TableItemData;


    QString AlarmTypeToString(AlarmType type);

}


//将自定义的数据结构注册，否则不可设置为Item的数据。Qt提供了注册自定义数据的宏
Q_DECLARE_METATYPE(TESTMVC::TableItemData)    //自定义结构体WItemData
Q_DECLARE_METATYPE(TESTMVC::ItemColumnRole)



#endif // MVCGLOBALDEFINE_H
