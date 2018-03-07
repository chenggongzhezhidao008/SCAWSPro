#include "messagesend.h"
#include <QDebug>

void MessageSend::dataUnit3616MessageDue(QString headName, SC_COMMD commd)
{
    // 3600信息
    //1.3616设备信息获取
    if(headName == "SC_3616Configure_Get"){
        qDebug()<<"SC_3616Configure_get >>";
        addMessageHead("1","00124","1011173512","3616CFG","1","02L",commd);
    }
    else if(headName == "_3616_IP_set"){
        qDebug()<<"_3616_IP_set >>";
        addMessageHead("1","00124","1011173512","3616CFG ","1","02L",commd);
    }
    //2.3616设备信息设置
    else if(headName == "SC_3616Configure_Set"){
        qDebug()<<"SC_3616Configure_set >>";
        addMessageHead("1","00124","1011173512","3616CFG","1","02L",commd);
    }
    //3.3616设备支持的传感器驱动
    else if(headName == "SC_DUSLIBLIST_Get"){
        qDebug()<<"SC_DUSLIBLIST_Get >>";
        addMessageHead("1","00124","1011173512","DUSLIBLIST","1","02L",commd);
    }
    //4.3616设备已经打开的模块
    else if(headName == "SC_OpenModuleList_Get"){
        qDebug()<<"SC_OpenModuleList_Get >>";
        addMessageHead("1","00124","1011173512","3616CFG","1","001",commd);
    }
    //获取3616设备支持的模块信息
    else if(headName == "SC_DUSLIBLIST_Get"){
        qDebug()<<"SC_DUSLIBLIST_Get >>";
        addMessageHead("1","00124","1011173512","DUSLIBLIST","1","02L",commd);
    }
    //所有传感器信息
    //1.传感器信息列表
    else if(headName == "SC_DUSSENSORLIST_Get"){
        // qDebug()<<"okokokok. >>";
        addMessageHead("1","00124","1476960126","DUSSENSORLIST","1","001",commd);
    }

    //各传感器配置
    //1.各大传感器位置信息设置
    else if(headName == "SC_SensorLocation_Set"){
        qDebug()<<"SC_3616Configure_set >>";
        addMessageHead("1","00124","1011173512","SENSORCFG" ,"1","02L",commd);
    }

    //2.各大传感器位置信息查询
    else if(headName == "SC_SensorLocation_Get"){
        qDebug()<<"SC_SensorLocation_Get >>";
        addMessageHead("1","00124","1011173512","SENSORCFG" ,"1","02L",commd);
    }

    //1.各大传感器的ID设置
    else if(headName == "SC_SensorID_Set"){
        qDebug()<<"SC_SensorID_Set >>";
        addMessageHead("1","00124","1011173512","SENSORCFG","1","02L",commd);
    }

    //2.各大传感器的ID查询
    else if(headName == "SC_SensorID_Get"){
        qDebug()<<"SC_SensorID_Get >>";
        addMessageHead("1","00124","1011173512","SENSORCFG","1","02L",commd);
    }

    // 风传感器id查询
    else if(headName == "SC_WIND_IDAsk"){
        qDebug()<<"SC_WIND_IDAsk >>";
        addMessageHead("1","00124","1011173512","WINDCFG","1","02L",commd);
    }

    //1.传感器的模块的开启和关闭
    else if(headName == "SC_Sensor_Open"){
        qDebug()<<"sensor open or close. >>";
        addMessageHead("1","00124","1011173512","3616CFG","1","001",commd);
    }

    //1.添加一个传感器设备
    else if(headName == "SC_Sensor_Add"){
        qDebug()<<"sensor add. >>";
        addMessageHead("1","00124","1011173512","3616CFG","1","001",commd);
    }

    // 通讯参数信息查询
    else if(headName == "SC_Serial_Get"){
        addMessageHead("1","00124","1011173512","3616CFG","1","02L",commd);
    }

    //通讯参数信息设置
    else if(headName == "SC_Serial_Set"){
        addMessageHead("1","00124","1011173512","3616CFG","1","02L",commd);
    }

    //各个传感器是否在线
    //1. rvr 传感器
    else if(headName == "SC_RVR_Alive_Get"){
        addMessageHead("1","00124","1011173512","VISSTATUS","1","02L",commd);
    }

    //2.humtemp 传感器
    else if(headName == "SC_HUMITEMP_Alive_Get"){
        addMessageHead("1","00124","1011173512","HUMITEMPSTATUS","1","02L",commd);
    }

    //3. wind传感器传
    else if(headName == "SC_WIND_Alive_Get"){
        addMessageHead("1","00124","1011173512","WINDSTATUS","1","02L",commd);
    }

    // 传感器消息传输模式操作
    // SC_WIND_MesModSet
    else if(headName == "SC_WIND_MesModSet"){
        addMessageHead("1","00124","1011173512","WINDCFG","1","02L",commd);
    }

    // 温湿度传感器 消息传输模式（待改）
    else if(headName == "SC_temp&humi_Alive_Get"){
        addMessageHead("1","00124","1011173512","WINDSTATUS","1","02L",commd);
    }

    // metar
    // 1.AFTN 设置
    else if(headName == "SC_AFTN_Config_Set"){
        qDebug()<<"SC_AFTN_Config_Set >>";
        addMessageHead("1","00124","1011173512","AFTNCFG","1","02L",commd);
    }
    //Observer send Metar to ForCaster
    else if(headName == "SC_AFTN_MessageSend_Set"){
        qDebug()<<"send AFTN metar context to ForCaster>>";
        addMessageHead("1","00124","1011173512","AFTNCFG","1","02L",commd);
    }

    // test port commd
    // test 1 机场信息参数配置
    else if(headName == "AirPortInfoSet"){
        qDebug()<<"AirPortInfoSet >>";
        addMessageHead("1","00124","1011173512","AirPortInfoSet","1","NULL",commd);
    }
    // test 2 机场信息参数查询
    else if(headName == "AirPortInfoGet"){
        qDebug()<<"AirPortInfoGet >>";
        addMessageHead("1","00124","1011173512","AirPortInfoGet","1","NULL",commd);
    }
    // test 3 跑道信息设置
    else if(headName == "RunWayInfoSet"){
        qDebug()<<"RunWayInfoSet >>";
        addMessageHead("1","00124","1011173512","RunWayInfoSet","1","13",commd);
    }
    // test 4 跑道信息查询
    else if(headName == "RunWayInfoGet"){
        qDebug()<<"RunWayInfoGet >>";
        addMessageHead("1","00124","1011173512","RunWayInfoGet","1","13",commd);
    }
    // test 5 传感器匹配跑道设置
    else if(headName == "SensorRunWayMatchSet"){
        qDebug()<<"SensorRunWayMatchSet >>";
        addMessageHead("1","00124","1011173512","SensorRunWayMatchSet","1","13",commd);
    }
    // test 6 传感器匹配跑道查询
    else if(headName == "SensorRunWayMatchGet"){
        qDebug()<<"SensorRunWayMatchGet >>";
        addMessageHead("1","00124","1011173512","SensorRunWayMatchGet","1","13",commd);
    }
    // ForCaster send Metar to 3616 deceieve
    else if(headName == "SC_MetarForecasterTo3616"){
        qDebug()<<"SC_MetarForecasterTo3616";
        addMessageHead("1","00124","1011173512","AFTNMES","1","02L",commd);
    }
    //Observer send Meater to 3616.
    else if(headName == "SC_MetarOKToSendOut"){
        qDebug()<<"SC_MetarOKToSendOut";
        addMessageHead("1","00124","1011173512","AFTNMES","1","02L",commd);
    }
    else if(headName == "ExternSensorAdd"){
        qDebug()<<"ExternSensorAdd";
        addMessageHead("1","00124","1011173512","ExternSensorAdd","1","13",commd);
    }
    else if(headName == "ExternSensorDelete"){
        qDebug()<<"ExternSensorDelete";
        addMessageHead("1","00124","1011173512","ExternSensorDelete","1","13",commd);
    }
    else if(headName == "ExternSensorListAsk"){
        qDebug()<<"ExternSensorListAsk";
        addMessageHead("1","00124","1011173512","ExternSensorListAsk","1","13",commd);
    }

    // 数据补偿部分
    else if(headName == "SC_RVR_MakeUpSet"){
        qDebug()<<"SC_RVR_MakeUpSet";
        addMessageHead("1","00124","1011173512","VR800CFG","1","02L",commd);
    }
    else if(headName == "PolluteAD_a"){
        qDebug()<<"PolluteAD_a";
        addMessageHead("1","00124","1011173512","VR800CFG","1","02L",commd);
    }
    else if(headName == "SpotADMax"){
        qDebug()<<"SpotADMax";
        addMessageHead("1","00124","1011173512","VR800CFG","1","02L",commd);
    }
    else if(headName == "StandardADMax"){
        qDebug()<<"StandardADMax";
        addMessageHead("1","00124","1011173512","VR800CFG","1","02L",commd);
    }
    else if(headName == "MorCalculate_a"){
        qDebug()<<"MorCalculate_a";
        addMessageHead("1","00124","1011173512","VR800CFG","1","02L",commd);
    }
    else if(headName == "VR800CorrectAsk"){
        qDebug()<<"VR800CorrectAsk";
        addMessageHead("1","00124","1011173512","VR800CFG","1","02L",commd);
    }
    else if(headName == "SC_RVR_MakeUpAsk"){
        qDebug()<<"SC_RVR_MakeUpAsk";
        addMessageHead("1","00124","1011173512","VR800CFG","1","02L",commd);
    }
    else{

    }
}










































