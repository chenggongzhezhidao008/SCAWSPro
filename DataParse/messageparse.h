#ifndef MESSAGEPARSE_H
#define MESSAGEPARSE_H

#include <QObject>
#include <QByteArray>

typedef QList<QByteArray> DataList;

#include <QMap>
typedef QMap<QString,QString> DataMap;
typedef QMap<QString,DataMap> SensorMap;

class MessageParse : public QObject
{
    Q_OBJECT
public:
    explicit MessageParse(QObject *parent = 0);
    void setUserType(QString userType);

signals:
    void windDataSignal(SensorMap senMap); //风的数据信号
    void humiTempDataSignal(SensorMap senMap); //温湿度数据信号
    void rvrDataSignal(SensorMap senMap); //能见度和跑到视程数据信号
    void cloudDataSignal(SensorMap senMap); //云数据信号
    void atmospherePressDataSignal(SensorMap senMap); //大气压数据信号
    void rainDataSignal(SensorMap senMap); //降雨量数据信号
    void phenomenaWeatherDataSignal(SensorMap senMap); //（PW）天气现象数据信号
    void prevailingVisibilityDataSignal(SensorMap senMap);//(PV)主导能见度数据信号
    void BIASLIGHTDataSignal(SensorMap senMap);//背景光亮度数据信号
    void manualInputDataDataSignal(SensorMap senMap);//人工输入数据信号

    // 状态解析链接告警系统，进行设备状态信息监控（用处）
    void windStatusSignal(SensorMap senMap); //风的状态信号
    void humiTempStatusSignal(SensorMap senMap); //温湿度状态信号
    void rvrStatusSignal(SensorMap senMap); //能见度和跑到视程状态信号
    void cloudStatusSignal(SensorMap senMap); //云状态信号
    void atmospherePressStatusSignal(SensorMap senMap); //大气压状态信号
    void rainStatusSignal(SensorMap senMap); //降雨量状态信号

    //
    void allModlesInformationSignal(SensorMap senMap);
    void allSensorsInformationSignal(SensorMap senMap);
    void telegramAskSubSignal(SensorMap senMap);
    void telegramShowSubSignal(SensorMap senMap);

    // test port config
    void airportBackInfor(SensorMap senMap);
    void runWayBackInfor(SensorMap senMap);
    void MatchBackInfor(SensorMap senMap);

    // 3616 自身配置文档V10 信号
    void Configure3616Signal(SensorMap senMap);
    void sensorStatusSignal(SensorMap senMap);
    void sensorLIBsSignal(SensorMap senMap);
    void serialCardParamersSignal(SensorMap senMap);
    void openModelSignal(QString senMap);
    void state36Signal(QString senMap);
    void backLightSignal(QString senMap);

    //预报员接受未加趋势Metar报
    void notTrendMetar(QString Metar);

    //观测员接受趋势报
    void trendTrendMetar(QString trend);

    // 外部传感器的操作处理
    void ExternSensorAddBackSignal(SensorMap sensorMap);
    void ExternSensorDeleteBackSignal(SensorMap sensorMap);
    void ExternSensorInfoListSignale(SensorMap sensorList);

    // VR800大透仪数据修正补偿返回信号
    void VR800CFGBack(QString options);
    void VR800CorrectBack(DataMap map);

public slots:
    void getMessageBarry(QByteArray message);//获取消息

private:
    // show debug information
    void outputShowdebugImformation(DataList dataList);

    //数据
    void messageParse(QByteArray message);// 消息格式解析
    void sensorParse(DataList dataList);// 传感器解析
    void windDataParse(DataList dataList); // 风的数据解析
    void humiTempDataParse(DataList datalist); // 温湿度数据解析
    void rvrDataParse(DataList datalist); // 能见度和跑到视程数据解析
    void cloudDataParse(DataList dataList); // 云数据解析
    void atmospherePressDataParse(DataList dataList); // 大气压数据解析
    void rainDataParse(DataList datalist); // 降雨量数据解析
    void phenomenaWeatherDataParse(DataList datalist); //（PW）天气现象数据解析
    void prevailingVisibilityDataParse(DataList datalist);// (PV)主导能见度数据解析
    void manualInputDataDataParse(DataList dataList);// 人工输入数据解析
    void backgroundLightDataParse(DataList datalist);// 背景光数据解析


    // 设备 部分
    //void allSensorsInforMation(DataList datalist);//扫描1~16号卡片上运行的传感器信息
    //void AllSupplyModlesInformation(DataList datalist);// 所有3616模块信息部分
    void telegramDataParse(DataList dataList);//电报信息

    //test port back infor
    void airPortInformatiom(DataList dataList);//机场信息
    void runWayInformatiom(DataList dataList);//跑道信息
    void matchSensorAndRunwayInformatiom(DataList dataList);//传感器跑道匹配信息

    // 3616 自身配置文档V10
    // H1. 3616CFG
    void SC_SensorOpen_Back(DataList datalist); //新传感器模块的开启
    void SC_SensorAdd_Back(DataList datalist); //增加一个已有类型的sensor
    void SC_Serial_Back(DataList datalist); //某一个板卡的串口参数
    void SC_3616Configure_Back(DataList datalist);//设备的IP地址、设备的ID号、设备对应的机场ID号
    void SC_OpenModuleList_Get(DataList datalist);//返回打开的模块

    // H2.SENSORCFG
    void SC_SensorLocation_Back(DataList datalist);//传感器的 位置配置

    // H3.DUSSENSORLIST
    void SC_HeartBeat3616(DataList datalist);// 返回当前3616主设备装状态
    void SC_DUSSENSORLIST_Back(DataList datalist);//查询当前3616传感器连接状态
    void SC_DUSLIBLIST_Back(DataList datalist);//查询当前3616所有的传感器库


    // TXT数据接入配置(合肥)CFG  标准配置数据文档 附件9
    void CLOUDConfigBack(DataList dataList);
    void HUMITEMPConfigBack(DataList dataList);
    void PRESSConfigBack(DataList dataList);
    void RAINConfigBack(DataList dataList);
    void VISConfigBack(DataList dataList);
    void WINDConfigBack(DataList dataList);
    void PWConfigBack(DataList dataList);
    void PVConfigBack(DataList dataList);

    //VR800大透仪数据修正配置
    void VR800CFG(DataList dataList);

    //虚拟传感器处理
    void ExternSensorAddBack(DataList dataList);
    void ExternSensorDeleteBack(DataList dataList);
    void ExternSensorListBack(DataList dataList);
    void ExternSensorInfo(DataList dataList);

    //状态
    void windstatusParse(DataList datalist); //风的状态解析
    void humiTempstatusParse(DataList datalist); //温湿度状态解析
    void rvrstatusParse(DataList datalist); //能见度和跑到视程状态解析
    void cloudstatusParse(DataList datalist); //云状态解析
    void atmospherePressstatusParse(DataList datalist); //大气压状态解析
    void rainstatusParse(DataList datalist); //降雨量状态解析

    //设备信息
    void allSensorsInfo(DataList dataList);

private:
    QString userType;
    void intUserType();

    //out sensor rows
    int _number_out_sensror;
    SensorMap _m_out_sMap;
    void init_out_sensor_value();
};

#endif // MESSAGEPARSE_H
