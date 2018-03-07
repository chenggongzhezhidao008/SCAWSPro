#include "deveicestate.h"

deveiceStateControl::deveiceStateControl(QWidget *parent) :
    QWidget(parent)
{
    titleMap[1] = "状态";
    titleMap[2] = "类型";
    titleMap[3] = "ID号";
    titleMap[4] = "位置";
    titleMap[5] = "备注";

    m_modelMap[1 ] = "HMP155";
    m_modelMap[2 ] = "HMP155";
    m_modelMap[3 ] = "HMP155";
    m_modelMap[4 ] = "HMP155";
    m_modelMap[5 ] = "HMP155";
    m_modelMap[6 ] = "HMP155";
    m_modelMap[7 ] = "WMT52";
    m_modelMap[8 ] = "WMT52";
    m_modelMap[9 ] = "WMT52";
    m_modelMap[10] = "WMT52";
    m_modelMap[11] = "WMT52";
    m_modelMap[12] = "VR800";
    m_modelMap[13] = "VR800";
    m_modelMap[14] = "VR800";
    m_modelMap[15] = "VR800";

    modeStateMap[1 ] = "open";
    modeStateMap[2 ] = "open";
    modeStateMap[3 ] = "open";
    modeStateMap[4 ] = "open";
    modeStateMap[5 ] = "open";
    modeStateMap[6 ] = "NULL";
    modeStateMap[7 ] = "NULL";
    modeStateMap[8 ] = "NULL";
    modeStateMap[9 ] = "NULL";
    modeStateMap[10] = "NULL";
    modeStateMap[11] = "NULL";
    modeStateMap[12] = "NULL";
    modeStateMap[13] = "NULL";
    modeStateMap[14] = "NULL";
    modeStateMap[15] = "NULL";

    cardMap[1 ] = "卡号01";
    cardMap[2 ] = "卡号02";
    cardMap[3 ] = "卡号03";
    cardMap[4 ] = "卡号04";
    cardMap[5 ] = "卡号05";
    cardMap[6 ] = "卡号06";
    cardMap[7 ] = "卡号07";
    cardMap[8 ] = "卡号08";
    cardMap[9 ] = "卡号09";
    cardMap[10] = "卡号10";
    cardMap[11] = "卡号11";
    cardMap[12] = "卡号12";
    cardMap[13] = "卡号13";
    cardMap[14] = "卡号14";
    cardMap[15] = "卡号15";
    cardMap[16] = "卡号16";

    sensorStateMap[1 ] = "Online";
    sensorStateMap[2 ] = "Online";
    sensorStateMap[3 ] = "Online";
    sensorStateMap[4 ] = "Online";
    sensorStateMap[5 ] = "Online";
    sensorStateMap[6 ] = "Online";
    sensorStateMap[7 ] = "Online";
    sensorStateMap[8 ] = "Online";
    sensorStateMap[9 ] = "Off";
    sensorStateMap[10] = "Off";
    sensorStateMap[11] = "Off";
    sensorStateMap[12] = "Off";
    sensorStateMap[13] = "Off";
    sensorStateMap[14] = "Connect";
    sensorStateMap[15] = "Connect";
    sensorStateMap[16] = "Connect";

    m_sensorNameMap[1 ] = "Wind1";
    m_sensorNameMap[2 ] = "Wind2";
    m_sensorNameMap[3 ] = "Wind3";
    m_sensorNameMap[4 ] = "Wind4";
    m_sensorNameMap[5 ] = "Wind5";
    m_sensorNameMap[6 ] = "Wind6";
    m_sensorNameMap[7 ] = "Wind7";
    m_sensorNameMap[8 ] = "Wind8";
    m_sensorNameMap[9 ] = "Wind9";
    m_sensorNameMap[10] = "RVR10";
    m_sensorNameMap[11] = "RVR11";
    m_sensorNameMap[12] = "RVR12";
    m_sensorNameMap[13] = "RVR13";
    m_sensorNameMap[14] = "clod14";
    m_sensorNameMap[15] = "clod15";
    m_sensorNameMap[16] = "clod16";

    sensorIdMap[1 ] = "1";
    sensorIdMap[2 ] = "2";
    sensorIdMap[3 ] = "3";
    sensorIdMap[4 ] = "4";
    sensorIdMap[5 ] = "5";
    sensorIdMap[6 ] = "6";
    sensorIdMap[7 ] = "7";
    sensorIdMap[8 ] = "8";
    sensorIdMap[9 ] = "9";
    sensorIdMap[10] = "10";
    sensorIdMap[11] = "11";
    sensorIdMap[12] = "12";
    sensorIdMap[13] = "13";
    sensorIdMap[14] = "14";
    sensorIdMap[15] = "15";
    sensorIdMap[16] = "16";

    beyonRunWayMap[1 ] = "跑道03";
    beyonRunWayMap[2 ] = "跑道03";
    beyonRunWayMap[3 ] = "跑道03";
    beyonRunWayMap[4 ] = "跑道03";
    beyonRunWayMap[5 ] = "跑道03";
    beyonRunWayMap[6 ] = "跑道03";
    beyonRunWayMap[7 ] = "跑道03";
    beyonRunWayMap[8 ] = "跑道03";
    beyonRunWayMap[9 ] = "跑道03";
    beyonRunWayMap[10] = "跑道27";
    beyonRunWayMap[11] = "跑道27";
    beyonRunWayMap[12] = "跑道27";
    beyonRunWayMap[13] = "跑道27";
    beyonRunWayMap[14] = "跑道06";
    beyonRunWayMap[15] = "跑道06";
    beyonRunWayMap[16] = "跑道24";

    m_init_push_button();
    m_init_size();
    m_init_instance();
}
