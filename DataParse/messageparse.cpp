#include "messageparse.h"
#include <QDebug>
#include <QTime>
#include <QDateTime>

MessageParse::MessageParse(QObject *parent) :
    QObject(parent)
{
    init_out_sensor_value();
}

void MessageParse::setUserType(QString userType)
{
    this->userType.clear();
    this->userType = userType;
    qDebug()<<"========================allot Message Parse Power";
    qDebug()<<"========================user typed is :"<<this->userType;
}

void MessageParse::getMessageBarry(QByteArray message)
{
    //qDebug()<<"recive message data1:"<<message.toHex();
    message.remove(0,1);
    message.remove(((message.length())-2),2);
    //qDebug()<<"recive message data2:"<<message.toHex();
    messageParse(message);
}

void MessageParse::outputShowdebugImformation(DataList dataList)
{
    DataList headList;
    for(int len = 0 ;len < dataList.length(); len++){
        headList = (dataList.value(len)).split(char(0x7c));
        qDebug()<<QString("sensorsInfo index %1:").arg(len)<<headList ;
        headList.clear();
    }
}

void MessageParse::messageParse(QByteArray message)
{
    char before[] = { 0x03, 0x02};
    QByteArray beforeBarry(before,2);
    char after[] = { 0x03};
    QByteArray afterBarry(after,1);
    message.replace(beforeBarry,afterBarry);
    //qDebug()<<"recive message data3:"<<message.toHex();
    DataList dataList = message.split(char(0x03));
    //qDebug()<<"recive dataList data:"<<dataList;
    sensorParse(dataList);
    dataList.clear();
}

void MessageParse::sensorParse(DataList dataList)
{
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    QString sensorFlag = (QString)(headDataList.value(3));
    sensorFlag = sensorFlag.trimmed();
    //qDebug()<<"messages time ====>>:"<<QTime::currentTime().toString("HH/mm:ss");
    //qDebug()<<"messages head ====>>:"<<sensorFlag<<sensorFlag.toUtf8().toHex();
    QString optionStr;
    if(sensorFlag == "CLOUD"){
        //qDebug()<<"SC CLOUD";
        cloudDataParse(dataList);
    }
    else if(sensorFlag == "HUMITEMP"){
        //qDebug()<<"SC HUMITEMP";
        humiTempDataParse(dataList);
    }
    else if(sensorFlag == "PRESS"){
        //qDebug()<<"SC PRESS";
        atmospherePressDataParse(dataList);
    }
    else if(sensorFlag == "RAIN"){
        //qDebug()<<"SC RAIN";
        rainDataParse(dataList);
    }
    else if(sensorFlag == "VIS"){
        //qDebug()<<"SC VIS";
        rvrDataParse(dataList);
        //outputShowdebugImformation(dataList);
    }
    else if(sensorFlag == "WIND"){
        //qDebug()<<"SC wind";
        windDataParse(dataList);
        //outputShowdebugImformation(dataList);
    }
    else if(sensorFlag == "PW" || sensorFlag == "FS11P"){
        //qDebug()<<"SC PW";
        phenomenaWeatherDataParse(dataList);
        //outputShowdebugImformation(dataList);
    }
    else if(sensorFlag == "PV"){
        //qDebug()<<"SC PV";
        prevailingVisibilityDataParse(dataList);
    }
    else if(sensorFlag == "BIASLIGHT"){
        qDebug()<<"SC BIASLIGHT";
        backgroundLightDataParse(dataList);
        //outputShowdebugImformation(dataList);
    }
    else if(sensorFlag == "Manual"){
        qDebug()<<"SC Manual";
        manualInputDataDataParse(dataList);
    }
    else if(sensorFlag == "HUMITEMPSTATUS"){
        qDebug()<<"SC hum and temp status";
        humiTempstatusParse(dataList);
    }
    else if(sensorFlag == "PRESSSTATUS"){
        qDebug()<<"SC press status";
        ///;
    }
    else if(sensorFlag == "RAINSTATUS"){
        qDebug()<<"SC rain status";
        rainstatusParse(dataList);
    }
    else if(sensorFlag == "VISSTATUS"){
        qDebug()<<"SC vis status";
        rvrstatusParse(dataList);
    }
    else if(sensorFlag == "WINDSTATUS"){
        qDebug()<<"SC wind status";
        windstatusParse(dataList);
    }
    else if(sensorFlag == "PWSTATUS"){
        //qDebug()<<"SC pw status";
        ////;
    }
    else if(sensorFlag == "3600ASTATUS"){
        qDebug()<<"SC 3600 status";
        /////;
    }
    else if(sensorFlag == "EQUIPMENTSTATUS"){
        SC_HeartBeat3616(dataList);
        //outputShowdebugImformation(dataList);
    }
    else if(sensorFlag == "DUSSENSORLIST"){
        qDebug()<<"SC 3600 DUSSENSORLIST";
        allSensorsInfo(dataList);
        optionStr.clear();
        optionStr = ((dataList.value(2)).split(char(0x7c))).value(0);
        if(optionStr == "SC_DUSSENSORLIST_Back"){
            SC_DUSSENSORLIST_Back(dataList);
            outputShowdebugImformation(dataList);
        }
        else if(optionStr == ""){

        }
        /////;
    }
    else if(sensorFlag == "COMLINESTATUS"){
        qDebug()<<"SC comline status";
        /////;
    }
    else if(sensorFlag == "3616CFG"){
        qDebug()<<"you are doing 3616 config now.";
        optionStr.clear();
        optionStr = ((dataList.value(2)).split(char(0x7c))).value(0);
        if(optionStr == "SC_SensorOpen_Back"){
            SC_SensorOpen_Back(dataList);
            //outputShowdebugImformation(dataList);
        }
        else if(optionStr == "SC_SensorAdd_Back"){
            SC_SensorAdd_Back(dataList);
            //outputShowdebugImformation(dataList);
        }
        else if(optionStr == "SC_Serial_Back"){
            SC_Serial_Back(dataList);
            //outputShowdebugImformation(dataList);
        }
        else if(optionStr == "SC_3616Configure_Back"){
            SC_3616Configure_Back(dataList);
            //outputShowdebugImformation(dataList);
        }
        else if(optionStr == "SC_OpenModuleList_Back"){
            SC_OpenModuleList_Get(dataList);
            //outputShowdebugImformation(dataList);
        }
        //outputShowdebugImformation(dataList);
    }
    else if(sensorFlag == "SENSORCFG"){
        qDebug()<<"you are doing sensor config now.";
        optionStr.clear();
        optionStr = ((dataList.value(2)).split(char(0x7c))).value(0);
        if(optionStr == "SC_SensorLocation_Back"){
            SC_SensorLocation_Back(dataList);
            // outputShowdebugImformation(dataList);
        }
        else if(optionStr == ""){
            return ;
        }
        else if(optionStr == ""){
            return ;
        }
        //outputShowdebugImformation(dataList);
    }
    else if(sensorFlag == "DUSLIBLIST"){
        qDebug()<<"DUS LIB LIST";
        optionStr.clear();
        optionStr = ((dataList.value(2)).split(char(0x7c))).value(0);
        if(optionStr == "SC_DUSLIBLIST_Back"){
            SC_DUSLIBLIST_Back(dataList);
            // outputShowdebugImformation(dataList);
        }
        else if(optionStr == ""){
            return ;
        }
        //outputShowdebugImformation(dataList);
    }
    else if(sensorFlag == "AFTNCFG"){
        qDebug()<<"AFTN 配置";
        outputShowdebugImformation(dataList);
    }
    else if(sensorFlag == "AFTNMES"){   // Metar
        outputShowdebugImformation(dataList);
        telegramDataParse(dataList);
    }
    else if(sensorFlag == "AFTNSTATE"){
        qDebug()<<"错报/正确报消息.";
        outputShowdebugImformation(dataList);
    }
    //Test port CFG
    else if(sensorFlag == "AirPortInfoBack"){
        //outputShowdebugImformation(dataList);
        airPortInformatiom(dataList);
    }
    else if(sensorFlag == "RunWayInfoBack"){
        //outputShowdebugImformation(dataList);
        runWayInformatiom(dataList);
    }
    else if(sensorFlag == "SensorRunWayMatchBack"){
        //outputShowdebugImformation(dataList);
        matchSensorAndRunwayInformatiom(dataList);
    }
    //CFG Partment
    else if(sensorFlag == "CLOUDConfigBack"){
        outputShowdebugImformation(dataList);
        CLOUDConfigBack(dataList);
        qDebug()<<"CLOUDConfigBack";
    }
    else if(sensorFlag == "HUMITEMPConfigBack"){
        outputShowdebugImformation(dataList);
        HUMITEMPConfigBack(dataList);
        qDebug()<<"HUMITEMPConfigBack";
    }
    else if(sensorFlag == "PRESSConfigBack"){
        outputShowdebugImformation(dataList);
        PRESSConfigBack(dataList);
        qDebug()<<"PRESSConfigBack";
    }
    else if(sensorFlag == "RAINConfigBack"){
        outputShowdebugImformation(dataList);
        RAINConfigBack(dataList);
        qDebug()<<"RAINConfigBack";
    }
    else if(sensorFlag == "VISConfigBack"){
        outputShowdebugImformation(dataList);
        VISConfigBack(dataList);
        qDebug()<<"VISConfigBack";
    }
    else if(sensorFlag == "WINDConfigBack"){
        outputShowdebugImformation(dataList);
        WINDConfigBack(dataList);
        qDebug()<<"WINDConfigBack";
    }
    else if(sensorFlag == "PWConfigBack"){
        outputShowdebugImformation(dataList);
        PWConfigBack(dataList);
        qDebug()<<"PWConfigBack";
    }
    else if(sensorFlag == "PVConfigBack"){
        outputShowdebugImformation(dataList);
        PVConfigBack(dataList);
        qDebug()<<"PVConfigBack";
    }
    else if(sensorFlag == "VR800CFG"){
        VR800CFG(dataList);
        outputShowdebugImformation(dataList);
    }
    // 增加传感器的操作
    else if(sensorFlag == "ExternSensorAddBack"){
        //qDebug()<<"out sensor add succeed! ";
        ExternSensorAddBack(dataList);
        outputShowdebugImformation(dataList);
    }
    // 删除传感器操作
    else if(sensorFlag == "ExternSensorDeleteBack"){
        ExternSensorDeleteBack(dataList);
        outputShowdebugImformation(dataList);
    }
    // 查询传感器操作
    else if(sensorFlag == "ExternSensorListBack")
    {   // 只返回一个外部传感器的长度
        ExternSensorListBack(dataList);
        outputShowdebugImformation(dataList);
    }
    else{
        qDebug()<<"Extern sensor:"<<sensorFlag;
        // must deal head Ctx
        if(sensorFlag.length() > 16)
        {
            QString _split_head;
            _split_head = sensorFlag.mid(0,16);
            if(_split_head == "ExternSensorInfo")
            {   // 返回外部传感器的具体个数信息
                ExternSensorInfo(dataList);
                outputShowdebugImformation(dataList);
            }
        }
    }
    headDataList.clear();
    return;
}

void MessageParse::windDataParse(DataList dataList)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["windVersion"] = (QString)(headDataList.value(0));
    hMap["windUnixTime"] = (QString)(headDataList.value(2));
    hMap["WindID"] = (QString)(headDataList.value(4));
    dMap["WindID"] = (QString)(headDataList.value(4));
    //qDebug()<<"wind data:"<<dataList.value(0);
    for(int i = 1;i < dataList.length();i++){

        //test debug message
        //qDebug()<<"wind data:"<<dataList.value(i);
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":" + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");//test used
    sMap["windHead"] = hMap;
    sMap["windData"] = dMap;
    //qDebug()<<"wind datas:"<<sMap;
    emit windDataSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::humiTempDataParse(DataList datalist)
{
    //    for(int i = 0;i < datalist.length();i++){
    //        qDebug()<<"SC data"+QString("%1:").arg(i)<<datalist.value(i) + "\n";
    //    }
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (datalist.value(0)).split(char(0x7c));
    hMap["humAndTempVersion"] = (QString)(headDataList.value(0));
    hMap["humAndTempUnixTime"] = (QString)(headDataList.value(2));
    hMap["humAndTempID"] = (QString)(headDataList.value(4));
    dMap["humAndTempID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < datalist.length();i++){
        DataList subList = (datalist.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":" + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");//test used
    sMap["humAndTempHead"] = hMap;
    sMap["humAndTempData"] = dMap;
    emit humiTempDataSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::rvrDataParse(DataList datalist)
{
    //    for(int i = 0;i < datalist.length();i++){
    //        qDebug()<<"SC data"+QString("%1:").arg(i)<<datalist.value(i);
    //        qDebug()<<"SC \n";
    //    }
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (datalist.value(0)).split(char(0x7c));
    hMap["VISVersion"] = (QString)(headDataList.value(0));
    hMap["VISUnixTime"] = (QString)(headDataList.value(2));
    hMap["VISID"] = (QString)(headDataList.value(4));
    dMap["VISID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < datalist.length();i++){
        DataList subList = (datalist.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":" + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");//test used
    sMap["VISHead"] = hMap;
    sMap["VISData"] = dMap;
    emit rvrDataSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::cloudDataParse(DataList dataList)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["CloudVersion"] = (QString)(headDataList.value(0));
    hMap["CloudUnixTime"] = (QString)(headDataList.value(2));
    hMap["CloudID"] = (QString)(headDataList.value(4));
    dMap["CloudID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":" + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");//test used
    sMap["CloudHead"] = hMap;
    sMap["CloudData"] = dMap;
    emit cloudDataSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::atmospherePressDataParse(DataList dataList)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["PressVersion"] = (QString)(headDataList.value(0));
    hMap["PressUnixTime"] = (QString)(headDataList.value(2));
    hMap["PressID"] = (QString)(headDataList.value(4));
    dMap["PressID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":" + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");//test used
    sMap["PressHead"] = hMap;
    sMap["PressData"] = dMap;
    emit atmospherePressDataSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::rainDataParse(DataList datalist)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (datalist.value(0)).split(char(0x7c));
    hMap["RainVersion"] = (QString)(headDataList.value(0));
    hMap["RainUnixTime"] = (QString)(headDataList.value(2));
    hMap["RainID"] = (QString)(headDataList.value(4));
    dMap["RainID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < datalist.length();i++){
        DataList subList = (datalist.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":" + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");//test used
    sMap["RainHead"] = hMap;
    sMap["RainData"] = dMap;
    emit rainDataSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::phenomenaWeatherDataParse(DataList datalist)
{
    //qDebug()<<"天气现象仪数据！";
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (datalist.value(0)).split(char(0x7c));
    hMap["PWVersion"] = (QString)(headDataList.value(0));
    hMap["PWUnixTime"] = (QString)(headDataList.value(2));
    hMap["PWID"] = (QString)(headDataList.value(4));
    dMap["PWID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < datalist.length();i++){
        DataList subList = (datalist.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == "")
        {   //数据无单位处理 = data
            dMap[dataName] = (QString)(subList.value(3));
        }
        else
        {  //数据带单位处理 = data:unit
            dMap[dataName] = (QString)(subList.value(3))
                    + ":" + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc()
            .toString("yyyy/MM/dd/hh/mm/ss");
    sMap["PWHead"] = hMap;
    sMap["PWData"] = dMap;
    emit phenomenaWeatherDataSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::prevailingVisibilityDataParse(DataList datalist)
{
    //qDebug()<<"主导能见度数据！";
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (datalist.value(0)).split(char(0x7c));
    hMap["PVVersion"] = (QString)(headDataList.value(0));
    hMap["PVUnixTime"] = (QString)(headDataList.value(2));
    hMap["PVID"] = (QString)(headDataList.value(4));
    dMap["PVID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < datalist.length();i++){
        DataList subList = (datalist.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3))
                    + ":" + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc()
            .toString("yyyy/MM/dd/hh/mm/ss");
    sMap["PVHead"] = hMap;
    sMap["PVData"] = dMap;
    emit prevailingVisibilityDataSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::manualInputDataDataParse(DataList /*dataList*/)
{

}

void MessageParse::backgroundLightDataParse(DataList datalist)
{
    //数据存储处理
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (datalist.value(0)).split(char(0x7c));
    hMap["BIASLIGHTVersion"] = (QString)(headDataList.value(0));
    hMap["BIASLIGHTUnixTime"] = (QString)(headDataList.value(2));
    hMap["BIASLIGHTID"] = (QString)(headDataList.value(4));
    dMap["BIASLIGHTID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < datalist.length();i++){
        DataList subList = (datalist.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3))
                    + ":" + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc()
            .toString("yyyy/MM/dd/hh/mm/ss");
    sMap["BIASLIGHTHead"] = hMap;
    sMap["BIASLIGHTData"] = dMap;
    emit BIASLIGHTDataSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();

    // 显示处理
    QString commandStr = "Data_BIASLIGHT:Store>";
    DataList subList;
    QString dataName;
    QString dataValue;
    for(int i = 0;i < datalist.length();i++){
        if(i == 1||i == 2||i == 3||i == 4){
            continue;
        }
        subList.clear();
        dataName.clear();
        dataValue.clear();
        subList = (datalist.value(i)).split(char(0x7c));
        if(i == 0){
            commandStr = commandStr + "BIASLIGHTid" + "|" + (QString)(subList.value(4)) +"/";
            continue;
        }
        dataName = (QString)(subList.value(0));
        dataValue = (QString)(subList.value(3));
        commandStr = commandStr + dataName + "|" + dataValue +"/";
    }
    emit backLightSignal(commandStr);
}

void MessageParse::telegramDataParse(DataList dataList)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    QString subOptionStr;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["TelegramVersion"] = (QString)(headDataList.value(0));
    hMap["TelegramUnixTime"] = (QString)(headDataList.value(2));
    hMap["TelegramID"] = (QString)(headDataList.value(4));
    dMap["TelegramID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if(i == 2){
            subOptionStr = dataName;
        }
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":" + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");//test used
    sMap["TelegramHead"] = hMap;
    sMap["TelegramData"] = dMap;
    if(subOptionStr == "SC_AFTN_30min_Req")
    {   // 3616 编报触发时间命令
        if(userType == "观测员"){
            emit telegramAskSubSignal(sMap);
        }
    }
    else if(subOptionStr == "SC_AFTN_RxMessage_Back")
    {
        // 3616 接受外部电报上报的电报内容
        emit telegramShowSubSignal(sMap);
    }
    else if(subOptionStr == "SC_MetarToForecaster")
    {   // 预报员在添加趋势前，接受来自观测员的Metar报。
        if(userType == "预报员"){
            QString notTrendMeterStr;
            notTrendMeterStr = dMap["SC_MetarToForecaster"].split(":").value(0).trimmed();
            emit notTrendMetar(notTrendMeterStr);
            qDebug()<<"趋势请求报++++"<<notTrendMeterStr;
        }
        else{
            return ;
        }
    }
    else if(subOptionStr == "SC_MetarForecasterToObserver")
    {   // 观测员接受预报员发来的趋势报字段
        if(userType == "观测员"){
            QString trendMeterStr; //SC_MetarForcasterToObserver
            trendMeterStr = dMap["SC_MetarForecasterToObserver"].split(":").value(0).trimmed();
            //trendMeterStr = dMap["Metar"].split(":").value(0).trimmed();
            emit trendTrendMetar(trendMeterStr);
        }
    }
    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::airPortInformatiom(DataList dataList)
{
    //qDebug()<<"AirPortInfor Context";
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["AirPortVersion"] = (QString)(headDataList.value(0));
    hMap["AirPortUnixTime"] = (QString)(headDataList.value(2));
    //    hMap["TelegramID"] = (QString)(headDataList.value(4));
    //    dMap["TelegramID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        dMap[dataName] = (QString)(subList.value(3));
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");//test used
    sMap["AirportHead"] = hMap;
    sMap["AirportData"] = dMap;

    emit airportBackInfor(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::runWayInformatiom(DataList dataList)
{
    //qDebug()<<"runWayInfor Context";
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["runWayVersion"] = (QString)(headDataList.value(0));
    hMap["runWayUnixTime"] = (QString)(headDataList.value(2));
    //    hMap["TelegramID"] = (QString)(headDataList.value(4));
    //    dMap["TelegramID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        dMap[dataName] = (QString)(subList.value(3));
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");//test used
    sMap["runWayHead"] = hMap;
    sMap["runWayData"] = dMap;

    emit runWayBackInfor(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::matchSensorAndRunwayInformatiom(DataList dataList)
{
    //qDebug()<<"MatchInfor Context";
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["MatchVersion"] = (QString)(headDataList.value(0));
    hMap["MatchUnixTime"] = (QString)(headDataList.value(2));
    //    hMap["TelegramID"] = (QString)(headDataList.value(4));
    //    dMap["TelegramID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        dMap[dataName] = (QString)(subList.value(3));
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");//test used
    sMap["MatchHead"] = hMap;
    sMap["MatchData"] = dMap;

    emit MatchBackInfor(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::SC_SensorOpen_Back(DataList /*datalist*/)
{
    qDebug()<<"新传感器模块的开启";
}

void MessageParse::SC_SensorAdd_Back(DataList /*datalist*/)
{
    qDebug()<<"增加一个已有类型的sensor";
}

void MessageParse::SC_Serial_Back(DataList datalist)
{
    //qDebug()<<"某一个板卡的串口参数";
    SensorMap sMap;
    DataMap dMap;
    DataList subList;
    subList = (datalist.value(2)).split(char(0x7c));
    dMap["CardId"] = (QString)(subList.value(3));
    for(int i = 5;i < datalist.length();i++){
        subList.clear();
        subList = (datalist.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        dMap[dataName] = (QString)(subList.value(3));
        subList.clear();
    }
    sMap["CardParamerData"] = dMap;
    emit serialCardParamersSignal(sMap);
    //qDebug()<<"36 卡参数"<<sMap;
    sMap.clear();
    dMap.clear();
}

void MessageParse::SC_3616Configure_Back(DataList datalist)
{
    //qDebug()<<"设备的IP地址、设备的ID号、设备对应的机场ID号";
    SensorMap sMap;
    DataMap dMap;
    DataList subList;
    for(int i = 3;i < datalist.length();i++){
        subList.clear();
        subList = (datalist.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        dMap[dataName] = (QString)(subList.value(3));
        subList.clear();
    }
    sMap["CFG36Data"] = dMap;
    emit Configure3616Signal(sMap);
    //qDebug()<<"36 设备参数"<<sMap;
    sMap.clear();
    dMap.clear();
}

/*   ---------------------------
 *   function descriptions
 *  数据传输规定：
 *   1.附件9消息指定命令名称=命令头
 *   2.命令内容分隔符 ":" = 命令头与命令操作值的分隔符
 *   3.命令数据分隔符 ">" = 命令与单元与数据部分的分隔符
 *   4.数据分隔符 "/" = 每个数据之间的分隔符
 *   5.数据内容分隔符 "|" = 数据名称与数据值之间的分隔符
 *   格式：
 *   command:optionValue>dtataName1|dataValue1/dtataName2|dataValue2/.......
 *   样例：
 *   Airport_Data:Store>airportName|合肥机场/airportId|1/.......
 *   6.数据值中的分隔符","
 *   ---------------------------
 */
void MessageParse::SC_OpenModuleList_Get(DataList datalist)
{
    QString commandStr = "Data_openlib:Store>";
    DataList subList;
    QString dataName;
    QString dataValue;
    for(int i = 5;i < datalist.length();i++){
        subList.clear();
        dataName.clear();
        dataValue.clear();
        subList = (datalist.value(i)).split(char(0x7c));
        dataValue = (QString)(subList.value(3));
        commandStr = commandStr + dataValue +"|open/";
    }
    emit openModelSignal(commandStr);
    qDebug()<<"打开库信息:"<<commandStr;
}

void MessageParse::SC_SensorLocation_Back(DataList /*datalist*/)
{
    qDebug()<<"传感器的 位置配置";
}

void MessageParse::SC_HeartBeat3616(DataList datalist)
{
    QString commandStr = "Data_36heartBeat:Store>";
    DataList subList;
    QString dataName;
    QString dataValue;
    for(int i = 1;i < (datalist.length() - 2);i++){
        subList.clear();
        dataName.clear();
        dataValue.clear();
        subList = (datalist.value(i)).split(char(0x7c));
        dataName = (QString)(subList.value(0));
        dataValue = (QString)(subList.value(3));
        commandStr = commandStr + dataName + "|" + dataValue +"/";
    }
    emit state36Signal(commandStr);
}

void MessageParse::SC_DUSSENSORLIST_Back(DataList datalist)
{
    //qDebug()<<"查询当前3616传感器连接状态";
    SensorMap sMap;
    DataMap dMap;
    DataList subList;
    for(int i = 4;i < datalist.length();i++){
        subList.clear();
        subList = (datalist.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        dMap[dataName] = (QString)(subList.value(3));
        subList.clear();
    }
    sMap["CNN36Data"] = dMap;
    emit sensorStatusSignal(sMap);
    //qDebug()<<"传感器链接参数"<<sMap;
    sMap.clear();
    dMap.clear();
}

void MessageParse::SC_DUSLIBLIST_Back(DataList datalist)
{
    //qDebug()<<"查询当前3616所有的传感器库";
    SensorMap sMap,cfgMap;
    DataMap hMap;
    DataMap dMap,cfgdMap;
    DataList headDataList = (datalist.value(0)).split(char(0x7c));
    hMap["DUSVersion"] = (QString)(headDataList.value(0));
    hMap["DUSUnixTime"] = (QString)(headDataList.value(2));
    hMap["DUSID"] = (QString)(headDataList.value(4));
    dMap["DUSID"] = (QString)(headDataList.value(4));
    int index = 1;
    for(int i = 1;i < datalist.length();i++){
        DataList subList = (datalist.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if(dataName == "Libname"){
            dataName = dataName + QString("%1").arg(index);
            if((QString)(subList.value(4)) == ""){
                dMap[dataName] = (QString)(subList.value(3));
            }
            else{
                dMap[dataName] = (QString)(subList.value(3)) + ":"
                        + (QString)(subList.value(4));
            }
            if(i >= 4){
                cfgdMap[dataName] = (QString)(subList.value(3));
            }
            index++;
        }
        subList.clear();
    }
    sMap["DUSHead"] = hMap;
    sMap["DUSData"] = dMap;
    emit allModlesInformationSignal(sMap);
    cfgMap["LibCFGData"] = cfgdMap;
    emit sensorLIBsSignal(cfgMap);
    //qDebug()<<"cfgMap:"<<cfgMap;
    sMap.clear();
    cfgMap.clear();
    cfgdMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::CLOUDConfigBack(DataList /*dataList*/)
{

}

void MessageParse::HUMITEMPConfigBack(DataList /*dataList*/)
{

}

void MessageParse::PRESSConfigBack(DataList /*dataList*/)
{

}

void MessageParse::RAINConfigBack(DataList /*dataList*/)
{

}

void MessageParse::VISConfigBack(DataList /*dataList*/)
{

}

void MessageParse::WINDConfigBack(DataList /*dataList*/)
{

}

void MessageParse::PWConfigBack(DataList /*dataList*/)
{

}

void MessageParse::PVConfigBack(DataList /*dataList*/)
{

}

void MessageParse::VR800CFG(DataList dataList)
{
    DataMap dMap;
    for(int i = 2;i < dataList.length();i++)
    {
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        dMap[dataName] = (QString)(subList.value(3));
        subList.clear();
    }
    QStringList keyList;
    keyList = dMap.keys();
    int len;
    len = keyList.length();
    QString keyStr;
    if(len > 0){
        if(keyList.contains("VR800CorrectBack")){
             emit VR800CorrectBack(dMap);
             return ;
        }
        for(int n = 0;n < len;n++)
        {
            keyStr.clear();
            keyStr = keyList.value(n);
            qDebug()<<"污染返回"<<keyStr;
            if(keyStr == "SC_RVR_MakeUpBack"||keyStr == "TemMakeUpEn"){
                // 传值格式 ">" 分隔命令与数据
                // "/" 分隔每个数据单元,"="分隔键与值
                QString value;
                value = "SC_RVR_MakeUpBack=" +dMap["SC_RVR_MakeUpBack"]
                        +"/TemMakeUpEn=" +dMap["TemMakeUpEn"];
                emit VR800CFGBack(QString("SC_RVR_MakeUpSet>%1").arg(value));
                return ;
            }
            if(keyStr == "PolluteAD_a"||keyStr == "PolluteAD_b"){
                emit VR800CFGBack("PolluteAD_a");
                return ;
            }
            if(keyStr == "SpotADMax"){
                emit VR800CFGBack("SpotADMax");
                return ;
            }
            if(keyStr == "StandardADMax"){
                emit VR800CFGBack("StandardADMax");
                return ;
            }
            if(keyStr == "MorCalculate_a"||keyStr == "MorCalculate_b"){
                emit VR800CFGBack("MorCalculate_a");
                return ;
            }
//            if(keyStr == "VR800CorrectBack"){
//                emit VR800CorrectBack(dMap);
//                qDebug()<<"VR800:返回参数"<<dMap;
//                return ;
//            }
        }
    }
    dMap.clear();
}

void MessageParse::ExternSensorAddBack(DataList dataList)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["AddESensor"] = (QString)(headDataList.value(0));
    hMap["AddESensorTime"] = (QString)(headDataList.value(2));
    hMap["AddESensorId"] = (QString)(headDataList.value(4));
    dMap["AddESensorId"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":"
                    + (QString)(subList.value(4));
        }
        subList.clear();
    }
    sMap["AddESensorHead"] = hMap;
    sMap["AddESensorData"] = dMap;
    emit ExternSensorAddBackSignal(sMap);
    headDataList.clear();
    hMap.clear();
    dMap.clear();
    sMap.clear();
}

void MessageParse::ExternSensorDeleteBack(DataList dataList)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["DelESensor"] = (QString)(headDataList.value(0));
    hMap["DelESensorTime"] = (QString)(headDataList.value(2));
    hMap["DelESensorId"] = (QString)(headDataList.value(4));
    dMap["DelESensorId"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":"
                    + (QString)(subList.value(4));
        }
        subList.clear();
    }
    sMap["DelESensorHead"] = hMap;
    sMap["DelESensorData"] = dMap;
    emit ExternSensorDeleteBackSignal(sMap);
    headDataList.clear();
    hMap.clear();
    dMap.clear();
    sMap.clear();
}

void MessageParse::ExternSensorListBack(DataList dataList)
{
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        dMap[dataName] = (QString)(subList.value(3));
        subList.clear();
    }
    _number_out_sensror = dMap["Sum"].toInt();// 外部传感器的个数
    _m_out_sMap.clear();// 开始新的接受任务，清空缓存
    headDataList.clear();
    dMap.clear();
}

void MessageParse::ExternSensorInfo(DataList dataList)
{
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    QString messNum;
    messNum = (QString)(headDataList.value(3));
    messNum.remove(0,16);
    dMap["ID"] = (QString)(headDataList.value(4));
    dMap["location"] = (QString)(headDataList.value(5));
    DataList subList;
    for(int i = 2;i < dataList.length();i++){
        subList = (dataList.value(i)).split(char(0x7c));
        dMap[(QString)(subList.value(0))] = (QString)(subList.value(3));
        subList.clear();
    }
    _m_out_sMap[tr("%1").arg(messNum)] = dMap;
    qDebug()<<"externSensor list length:"<<messNum;
    if(messNum.toInt() >= _number_out_sensror)
    {
        emit ExternSensorInfoListSignale(_m_out_sMap);
        _number_out_sensror = -1;
        _m_out_sMap.clear();
    }
    headDataList.clear();
    dMap.clear();
}

void MessageParse::windstatusParse(DataList dataList)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["windVersion"] = (QString)(headDataList.value(0));
    hMap["windUnixTime"] = (QString)(headDataList.value(2));
    hMap["WindID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":"
                    + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");//test used
    sMap["windHead"] = hMap;
    sMap["windData"] = dMap;
    emit windStatusSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::humiTempstatusParse(DataList dataList)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["humAndTempVersion"] = (QString)(headDataList.value(0));
    hMap["humAndTempUnixTime"] = (QString)(headDataList.value(2));
    hMap["humAndTempID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":"
                    + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");
    sMap["humAndTempHead"] = hMap;
    sMap["humAndTempData"] = dMap;
    emit humiTempStatusSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::rvrstatusParse(DataList dataList)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["VISVersion"] = (QString)(headDataList.value(0));
    hMap["VISUnixTime"] = (QString)(headDataList.value(2));
    hMap["VISID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":"
                    + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");
    sMap["VISHead"] = hMap;
    sMap["VISData"] = dMap;
    emit rvrStatusSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::cloudstatusParse(DataList /*dataList*/)
{

}

void MessageParse::atmospherePressstatusParse(DataList /*dataList*/)
{

}

void MessageParse::rainstatusParse(DataList /*dataList*/)
{

}

void MessageParse::allSensorsInfo(DataList dataList)
{
    SensorMap sMap;
    DataMap hMap;
    DataMap dMap;
    DataList headDataList = (dataList.value(0)).split(char(0x7c));
    hMap["DUSVersion"] = (QString)(headDataList.value(0));
    hMap["DUSUnixTime"] = (QString)(headDataList.value(2));
    hMap["DUSID"] = (QString)(headDataList.value(4));
    dMap["DUSID"] = (QString)(headDataList.value(4));
    for(int i = 1;i < dataList.length();i++){
        DataList subList = (dataList.value(i)).split(char(0x7c));
        QString dataName = (QString)(subList.value(0));
        if((QString)(subList.value(4)) == ""){
            dMap[dataName] = (QString)(subList.value(3));
        }
        else{
            dMap[dataName] = (QString)(subList.value(3)) + ":"
                    + (QString)(subList.value(4));
        }
        subList.clear();
    }
    dMap["TIME"] = QDateTime::currentDateTimeUtc().toString("yyyy/MM/dd/hh/mm/ss");
    sMap["sensorsHead"] = hMap;
    sMap["sensorsData"] = dMap;
    emit allSensorsInformationSignal(sMap);

    sMap.clear();
    hMap.clear();
    dMap.clear();
    headDataList.clear();
}

void MessageParse::intUserType()
{
    userType = "Not User";
}

void MessageParse::init_out_sensor_value()
{
    _number_out_sensror = -1;
}
