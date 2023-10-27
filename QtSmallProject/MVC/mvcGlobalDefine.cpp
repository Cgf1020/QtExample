#include "mvcGlobalDefine.h"
#include <unordered_map>



namespace TESTMVC {

QString AlarmTypeToString(AlarmType type)
{
    QString str;
    switch (type) {
    case AlarmType::Fire:
        str = "火灾";
        break;
    case AlarmType::HighCover:
        str = "高空遮挡物";
        break;
    case AlarmType::OverTemperature:
        str = "温度过高";
        break;
    case AlarmType::IceCover:
        str = "冰覆盖";
        break;
    default:
        break;
    }
    return str;
}



/*Table 列 和  string  互转*/
//    static const std::unordered_map<ItemColumnRole, std::string> ItemColumnRoleEnumToString = {
//        {ItemColumnRole::DeviceIdColumn, "设备编号"},
//        {ItemColumnRole::AlarmTimeColumn, "警报时间"},
//        {ItemColumnRole::AlarmTypeColumn, "警报类型"},
//        {ItemColumnRole::SnapshotColumn, "快照"},
//        {ItemColumnRole::PlaybackColumn, "回放"},
//        {ItemColumnRole::OperateColumn, "操作"},
//    };

/*警报类型 和  string  互转*/
//    const std::unordered_map<AlarmType, std::string> AlarmEnumToString = {
//        {AlarmType::NONE, ""},
//        {AlarmType::Fire, "火灾"},
//        {AlarmType::HighCover, "高空遮挡物"},
//        {AlarmType::OverTemperature, "温度过高"},
//        {AlarmType::IceCover, "冰覆盖"},
//    };

//    const std::unordered_map<std::string, AlarmType> AlarmStringToEnum = {
//        {"火灾", AlarmType::Fire},
//        {"高空遮挡物", AlarmType::HighCover},
//        {"温度过高", AlarmType::OverTemperature},
//         {"冰覆盖", AlarmType::IceCover},
//         };


}
