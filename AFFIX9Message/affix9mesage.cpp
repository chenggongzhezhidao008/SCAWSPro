#include "affix9mesage.h"
#include <QDateTime>
#include <QTime>
#include <QDate>

AFFIX9Mesage::AFFIX9Mesage(QObject *parent) :
    QObject(parent)
{
    init3616IpEdit();
    initSensorClassData();
    initNumberValue();
    initAFFIX9LocaDataDueConn();
    _init_Deceive_3616_infor();
    _init_update_sensor_type_value();
    init_local_connection();
}

/*   数据传输规定：
 *   1.附件9消息指定命令名称=命令头
 *   2.命令内容分隔符 ":" = 命令头与命令操作值的分隔符
 *   3.命令数据分隔符 ">" = 命令部分与数据部分的分隔符
 *   4.数据分隔符 "/" = 每个数据之间的分隔符
 *   5.数据内容分隔符 "|" = 数据名称与数据值之间的分隔符
 *   格式：
 *   command:optionValue>dtataName1|dataValue1/dtataName2|dataValue2/.......
 *   样例：
 *   Airport_Data:Store>airportName|合肥机场/airportId|1/.......
 *   6.数据值中的分隔符","
 */

void AFFIX9Mesage::AFFIX9CommandOptions(QString optionStr)
{
    SC_COMMD commd;
    // UTC time translate
    //QDateTime utcStr;
    //utcStr = QDateTime::currentDateTimeUtc();        //qDebug()<<"UTC Time:"<<utcStr;
    QDateTime now = QDateTime::currentDateTime();    //currentDateTimeUtc();
    QDateTime xmas(QDate(1970, 1, 1),QTime(8, 0));   //1970年1月1日
    quint64 utcSecs = xmas.secsTo(now);              //qDebug()<<"qDebug time :"<<utcSecs;
    QString headCtx = optionStr.split(">").value(0);
    QString dataCtx = optionStr.split(">").value(1);
    //qDebug()<<"============ AFFIX 9 Message Options"<<headCtx
    //<<"=============all Data"<<optionStr;
    if(headCtx == "infor36:刷新")
    {
        commd.clear();          // 3616 deceive infor query
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue("SC_3616Configure_Get:I:M:1:NULL");
        emit AFFIX9Message("SC_3616Configure_Get",commd);
    }
    if(headCtx == "infor36:编辑IP")
    {
        _3616_ipEdit->show();  //open ip edit UI
    }
    if(headCtx == "infor36:ipconfig")
    {
        if(_3616_AirId == "-1" || _3616_Id == "-1")
        {
            return ;            //qDebug()<<"waring: deceive paramater lost.please update 3616 deceive information.";
        }
        commd.clear();
        QStringList list = dataCtx.split(".");
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue("SC_3616Configure_Set:I:M:1:NULL");
        commd.enqueue(QString("AirPortID:I:M:%1:NULL").arg(_3616_AirId));
        commd.enqueue(QString("ID3616:I:M:%1:NULL").arg(_3616_Id));
        commd.enqueue(QString("Addr1:I:M:%1:NULL").arg(list.value(0)));
        commd.enqueue(QString("Addr2:I:M:%1:NULL").arg(list.value(1)));
        commd.enqueue(QString("Addr3:I:M:%1:NULL").arg(list.value(2)));
        commd.enqueue(QString("Addr4:I:M:%1:NULL").arg(list.value(3)));              //commd.enqueue("AirPortName:S:M:ZOSF:NULL");     //temporary set ZOSF as He Feint Airpot
        commd.enqueue(QString("AirPortName:S:M:%1:NULL").arg(_airport_name));
        emit AFFIX9Message("_3616_IP_set",commd);
    }
    else if(headCtx == "wind:位置设置"          //* 设置各大传感器位置 WMT52 VR800 HMP155
            ||headCtx == "Vis:位置设置"
            ||headCtx == "HumiTemp:位置设置")
    {
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue("SC_SensorLocation_Set:S:M:WMT52:NULL");//WMT52
        commd.enqueue("AIRportID:I:M:1:NULL");
        commd.enqueue("ID3616:I:M:1:NULL");
        commd.enqueue("CARDID:I:M:15:NULL");//15
        commd.enqueue("Location:S:M:06-24Mid:NULL");//02R
        commd.enqueue("RunwayName:S:M:02R:NULL");
        commd.enqueue("RunwayID:I:M:4:NULL");
        emit AFFIX9Message("SC_SensorLocation_Set",commd);
    }
    else if(headCtx == "4")      //* 查询各大传感器的位置 WMT52 VR800 HMP155
    {
        //    commd.clear();
        //    commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        //    commd.enqueue("SC_SensorLocation_Get:S:M:WMT52:NULL");
        //    commd.enqueue("AIRportID:I:M:0:NULL");
        //    commd.enqueue("ID3616:I:M:0:NULL");
        //    commd.enqueue("CARDID:I:M:14:NULL");
        //    emit AFFIX9Message("SC_SensorLocation_Get",commd);
    }
    else if(headCtx == "5"){                          // * 设置各大传感器的id号(无反应 此功能3616设备还没放到模块里)
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue("SC_SensorID_Set:S:M:WMT52:NULL");
        commd.enqueue("AIRportID:I:M:1:NULL");
        commd.enqueue("ID3616:I:M:1:NULL");
        commd.enqueue("CardID:I:M:15:NULL");          //确定定指定的传感器
        commd.enqueue("SetValue:I:M:2:NULL");
        emit AFFIX9Message("SC_SensorID_Set",commd);
    }
    else if(headCtx == "sensorWind_id") // * 查询风传感器的id号
    {
        for(int i = 1;i <= 16;i++){
            commd.clear();
            commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
            commd.enqueue(QString("SC_WIND_IDAsk:I:M:%1:NULL").arg(i));
            emit AFFIX9Message("SC_WIND_IDAsk",commd);
        }
    }
    else if(headCtx == "7")            // * 查询温湿度传感器的id号(无反应)
    {
        //    commd.clear();
        //    commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        //    commd.enqueue(":I:M:15:NULL");
        //    emit AFFIX9Message("",commd);
    }
    // * 新增的传感器模块的开启
    else if(headCtx == "lib36:打开" || headCtx == "lib36:关闭")  //1.打开VR800 模块
    {
        QString enable;
        if(headCtx == "lib36:打开"){
            enable = "1";
        }
        else if(headCtx == "lib36:关闭"){
            enable = "0";
        }
        else{
        }
        QString index = findAppointKeyValue(dataCtx,"index");
        if(index == "ERROR"){
            qDebug()<<"find the key error!";
            return ;
        }
        qDebug()<<"key value is:"<<index;
        if(m_libary.isEmpty()){
            qDebug()<<"lib is empty!";
            return ;
        }
        qDebug()<<"libs"<<m_libary;
        QString libNme = m_libary[QString("index%1").arg(index)];
        qDebug()<<"libNme"<<libNme;
        if(libNme.isEmpty()){
            qDebug()<<"lib is Not exisit!";
            return ;
        }
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue(QString("SC_Sensor_Open:S:M:%1:NULL").arg(libNme.split("=").value(1)));
        commd.enqueue(QString("AirPortID:I:M:1:NULL").arg(" "));
        commd.enqueue(QString("ID3616:I:M:1:NULL").arg(" "));
        commd.enqueue(QString("SC_Sensor_En:I:M:%1:NULL").arg(enable));
        emit AFFIX9Message("SC_Sensor_Open",commd);
    }
    // *新增传感器
    else if(headCtx == "sensor:add")                       // 1.新增一个传感器风wind sensor
    {
        qDebug()<<"添加传感器操作！"<<dataCtx;             // qDebug()<<"通讯卡设置:"<<dataCtx;
        QString id36 = findAppointKeyValue(dataCtx,"id36")
                ,idcar = findAppointKeyValue(dataCtx,"card")
                ,bate = findAppointKeyValue(dataCtx,"bate")
                ,bit = findAppointKeyValue(dataCtx,"bits")
                ,crc = findAppointKeyValue(dataCtx,"crc")
                ,stop = findAppointKeyValue(dataCtx,"stop")
                ,model = findAppointKeyValue(dataCtx,"model")
                ,enable = findAppointKeyValue(dataCtx,"enable");
        if(id36 == "ERROR"
                ||idcar == "ERROR"
                ||bate == "ERROR"
                ||bit == "ERROR"
                ||crc == "ERROR"
                ||stop == "ERROR"
                ||model == "ERROR"
                ||enable == "ERROR")
        {
            qDebug()<<"通讯卡设置参数丢失！";
            return ;
        }
        commd.clear();   //qDebug()<<"commd data>>>>>>:"<<id36 + idcar + bate + bit + crc + stop + model + enable;
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue(QString("SC_Sensor_Add:S:M:%1:NULL").arg(model));
        commd.enqueue(QString("AirPortID:I:M:%1:NULL").arg("1"));
        commd.enqueue(QString("ID3616:I:M:%1:NULL").arg(id36));
        commd.enqueue(QString("CardID:I:M:%1:NULL").arg(idcar));
        commd.enqueue(QString("En:I:M:%1:NULL").arg(enable));
        commd.enqueue(QString("Bate:I:M:%1:NULL").arg(bate));
        commd.enqueue(QString("Bit:I:M:%1:NULL").arg(bit));
        commd.enqueue(QString("Crc:I:M:%1:NULL").arg(crc));
        commd.enqueue(QString("StopBit:I:M:%1:NULL").arg(stop));
        emit AFFIX9Message("SC_Sensor_Add",commd);
    }

    // 通讯部分
    else if(headCtx == "cardParameter36:刷新"){           //   1.查询某一块卡的通讯参数
        for(int i = 1;i <= 16; i++){
            commd.clear();
            commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
            commd.enqueue(QString("SC_Serial_Get:I:M:%1:NULL").arg(i));
            commd.enqueue("AirPortID:I:M:0:NULL");
            commd.enqueue("ID3616:I:M:1:NULL");
            emit AFFIX9Message("SC_Serial_Get",commd);
        }
    }
    else if(headCtx == "cardParameter36:通讯设置2"){       //    设置某一块卡的通讯参数
        QString id36 = findAppointKeyValue(dataCtx,"id36")   //    qDebug()<<"通讯卡设置:"<<dataCtx;
                ,idcar = findAppointKeyValue(dataCtx,"card")
                ,bate = findAppointKeyValue(dataCtx,"bate")
                ,bit = findAppointKeyValue(dataCtx,"bits")
                ,crc = findAppointKeyValue(dataCtx,"crc")
                ,stop = findAppointKeyValue(dataCtx,"stop");
        if(id36 == "ERROR"
                ||idcar == "ERROR"
                ||bate == "ERROR"
                ||bit == "ERROR"
                ||crc == "ERROR"
                ||stop == "ERROR"){
            qDebug()<<"通讯卡设置参数丢失！";
            return ;
        }
        commd.clear();     //qDebug()<<"commd data>>>>>>:"<<id36 + idcar + bate + bit + crc + stop;
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue(QString("SC_Serial_Set:I:M:%1:NULL").arg(idcar));
        commd.enqueue("AirPortID:I:M:1:NULL");
        commd.enqueue(QString("ID3616:I:M:%1:NULL").arg(id36));
        commd.enqueue(QString("Bate:I:M:%1:NULL").arg(bate));
        commd.enqueue(QString("Bit:I:M:%1:NULL").arg(bit));
        commd.enqueue(QString("Crc:I:M:%1:NULL").arg(crc));
        commd.enqueue(QString("StopBit:I:M:%1:NULL").arg(stop));
        emit AFFIX9Message("SC_Serial_Set",commd);
    }
    else if(headCtx == "statue36:刷新"){   // 刷新当前3616卡连接状态
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue("SC_DUSSENSORLIST_Get:I:N:14:NULL");
        commd.enqueue("AIRPORTID:I:M:10:NULL");
        emit AFFIX9Message("SC_DUSSENSORLIST_Get",commd);
    }

    //  预报员下发Metar报趋势消息
    else if(headCtx == "forCaster:SendTrend"){
        QString trendStr = dataCtx;
        qDebug()<<"forCasterSendTrend:"<<trendStr;
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue(QString("SC_MetarForecasterTo3616:S:N:%1:NULL").arg(trendStr));
        commd.enqueue("ID3616:I:N:15:NULL");
        commd.enqueue("AirPortName:S:N:06:NULL");
        commd.enqueue("AirPortID:I:N:15:NULL");     //commd.enqueue(QString("Metar:S:N:%1:NULL").arg(trendStr));
        emit AFFIX9Message("SC_MetarForecasterTo3616",commd);
    }
    //  观测员发完整的Metar给3616设备
    else if(headCtx == "Metar:sendOkMetar"){
        QStringList metar_list = dataCtx.split("+");
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue("SC_MetarOKToSendOut:S:N:NULL:NULL");
        commd.enqueue("ID3616:I:N:15:NULL");
        commd.enqueue("AirPortName:S:N:06:NULL");
        commd.enqueue("AirPortID:I:N:15:NULL");
        commd.enqueue("MessageID:I:N:12:NULL");
        commd.enqueue(QString("Metar:S:N:%1:NULL").arg(metar_list.value(0)));
        commd.enqueue(QString("Rank:S:N:GG:NULL").arg(metar_list.value(1)));
        commd.enqueue(QString("ReciveAddr:S:N:%1:NULL").arg(metar_list.value(2)));
        emit AFFIX9Message("SC_MetarOKToSendOut",commd);
    }
    else if(headCtx == "19"){              // 2. humtemp 传感器
        //    commd.clear();
        //    commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        //    commd.enqueue("SC_HUMITEMP_Alive_Get:I:M:1:NULL");
        //    emit AFFIX9Message("SC_HUMITEMP_Alive_Get",commd);
    }
    else if(headCtx == "20"){              //3. wind 传感器
        //    commd.clear();
        //    commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        //    commd.enqueue("SC_WIND_Alive_Get:I:M:15:NULL");
        //    emit AFFIX9Message("SC_WIND_Alive_Get",commd);
    }
    else if(headCtx == "lib36:刷新"){     //查询3616支持的传感器驱动(调试通过)
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue("SC_DUSLIBLIST_Get:I:M:10:NULL");
        commd.enqueue("AirPortID:I:M:10:NULL");
        emit AFFIX9Message("SC_DUSLIBLIST_Get",commd);
    }
    else if(headCtx == "lib36:open"){             //获取3616已经开启的模块
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue("SC_OpenModuleList_Get:I:M:10:NULL");
        commd.enqueue("AirPort:I:M:10:NULL");
        commd.enqueue("ID3616:I:M:10:NULL");
        emit AFFIX9Message("SC_OpenModuleList_Get",commd);
    }
    else if(headCtx == "23")                     //声光告警测试
    {
        //    QApplication::beep();//电脑声音。
        //    QSound *voide = new QSound("./waring.wav",this);
        //    voide->setLoops(3);
        //    voide->play();
    }

    //**** test Messgae
    else if(headCtx == "24")                      //    test 1 机场信息参数配置(能回)
    {
        //    commd.clear();
        //    commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        //    commd.enqueue("ID3616:I:M:1:NULL");
        //    commd.enqueue("AirPortName:S:M:hefeijichang:NULL");
        //    commd.enqueue("AirPortID:I:M:ZGHA:NULL");
        //    commd.enqueue("AirPortCode:S:M:ZGHA:NULL");
        //    commd.enqueue("AirPortHeight:I:M:115:NULL");
        //    commd.enqueue("RunWayInHeight:I:M:115:NULL");
        //    emit AFFIX9Message("AirPortInfoSet",commd);
    }
    else if((headCtx == "airport:刷新")            // test 2 机场信息参数查询
            ||(headCtx == "testAirport:刷新"))
    {
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        emit AFFIX9Message("AirPortInfoGet",commd);
    }
    else if(headCtx == "26") // test 3 跑道信息设置
    {
        //    commd.clear();
        //    commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        //    commd.enqueue("ID3616:I:N:1:NULL");
        //    commd.enqueue("AirPortInfoID:I:N:0:NULL");
        //    commd.enqueue("RunWayInfoID:I:N:2:NULL");
        //    commd.enqueue("Head:S:N:R-15:NULL");
        //    commd.enqueue("Mid:S:N:15-33MID:NULL");
        //    commd.enqueue("Rear:S:N:L-33:NULL");
        //    emit AFFIX9Message("RunWayInfoSet",commd);
    }
    else if((headCtx == "runWay:刷新")             // test 4 跑道信息查询（没回）
            || (headCtx == "testRunWay:刷新"))
    {
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue("ID3616:I:N:1:NULL");
        emit AFFIX9Message("RunWayInfoGet",commd);
    }
    else if(headCtx == "28")                 // test 5 传感器匹配跑道设置
    {
        //    commd.clear();
        //    commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        //    commd.enqueue("ID3616:I:N:1:NULL");
        //    commd.enqueue("SensorID:I:N:1:NULL");
        //    commd.enqueue("SensorType:S:N:Cloud:NULL");
        //    commd.enqueue("RunWayInfoID:I:N:2:NULL");
        //    commd.enqueue("sensorLocation:s:N:1:NULL");
        //    emit AFFIX9Message("SensorRunWayMatchSet",commd);
        return ;
    }
    else if(headCtx == "testSensor:刷新")     // test 6 传感器匹配跑道查询
    {
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue("ID3616:I:N:1:NULL");
        emit AFFIX9Message("SensorRunWayMatchGet",commd);
        return ;
    }
    // 取传感器信息部分
    else if(headCtx == "wind:刷新")
    {
        upadte_sensor_type_str = "wind";
        emit send_self_signal("statue36:刷新");
        emit send_self_signal("ExternSensor:query");
        return;
    }
    else if(headCtx == "wind:find"){
        emit backRequeryAFFIX9menberSignal("wind_query",findSensorInfoByClass("WIND"));
        //emit backRequeryAffix9_out_sensor_menber_Signal();
        return ;
    }
    else if(headCtx == "RVR:刷新")
    {
        upadte_sensor_type_str = "RVR";
        emit send_self_signal("statue36:刷新");
        emit send_self_signal("ExternSensor:query");
        return ;
    }
    else if(headCtx == "RVR:find"){
        emit backRequeryAFFIX9menberSignal("rvr_query",findSensorInfoByClass("VIS"));
        //emit backRequeryAffix9_out_sensor_menber_Signal();
        return ;
    }
    else if(headCtx == "tempHumi:刷新")
    {
        upadte_sensor_type_str = "tempHumi";
        emit send_self_signal("statue36:刷新");
        emit send_self_signal("ExternSensor:query");
        return ;
    }
    else if(headCtx == "tempHumi:find"){
        emit backRequeryAFFIX9menberSignal("tempHumi_query",findSensorInfoByClass("HUMITEMP"));
        //emit backRequeryAffix9_out_sensor_menber_Signal();
        return ;
    }
    else if(headCtx == "custom:刷新")
    {
        upadte_sensor_type_str = "custom";
        emit send_self_signal("statue36:刷新");
        emit send_self_signal("ExternSensor:query");
        return ;
    }
    else if(headCtx == "custom:find"){
        emit backRequeryAFFIX9menberSignal("custom_query",findSensorInfoByClass("CUSTOM"));
        //emit backRequeryAffix9_out_sensor_menber_Signal();
        return ;
    }
    // 配置vis传感器
    // 污染和温度共同补偿设置
    else if(headCtx == "SC_RVR:MakeUpSetPollute&Temp") // 暂时不用此方法做补偿
    {
        QString pvalue,tvalue;
        pvalue = findAppointKeyValue(dataCtx,"vmor");
        tvalue = findAppointKeyValue(dataCtx,"able");
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue(QString("SC_RVR_MakeUpSet:I:N:%1:NULL").arg(pvalue));
        commd.enqueue(QString("TemMakeUpEn:I:N:%1:NULL").arg(tvalue));
        emit AFFIX9Message("SC_RVR_MakeUpSet",commd);
        return ;
    }
    //测污补偿设置
    else if(headCtx == "SC_RVR:MakeUpSetPollute")
    {
        QString pVa,pVb;
        pVa = findAppointKeyValue(dataCtx,"pollute_a");
        pVb = findAppointKeyValue(dataCtx,"pollute_b");
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue(QString("PolluteAD_a:R:N:%1:NULL").arg(pVa));
        commd.enqueue(QString("PolluteAD_b:R:N:%1:NULL").arg(pVb));
        emit AFFIX9Message("PolluteAD_a",commd);
        return ;
    }
    //晴天下最大AD设置
    else if(headCtx == "SC_RVR:SpotADMax")
    {
        QString spotAD;
        spotAD = findAppointKeyValue(dataCtx,"spotMax");
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue(QString("SpotADMax:I:N:%1:NULL").arg(spotAD));
        emit AFFIX9Message("SpotADMax",commd);
        return ;
    }
    //昌平系统测试最大值
    else if(headCtx == "SC_RVR:StandardADMax")
    {
        QString maxValue;
        maxValue = findAppointKeyValue(dataCtx,"stdMax");
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue(QString("StandardADMax:I:N:%1:NULL").arg(maxValue));
        emit AFFIX9Message("StandardADMax",commd);
        return ;
    }
    //mor计算参数设置
    else if(headCtx == "SC_RVR:MorCalculate")
    {
        QString Va,Vb;
        Va = findAppointKeyValue(dataCtx,"calc_a");
        Vb = findAppointKeyValue(dataCtx,"calc_b");
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue(QString("MorCalculate_a:R:N:%1:NULL").arg(Va));
        commd.enqueue(QString("MorCalculate_b:R:N:%1:NULL").arg(Vb));
        emit AFFIX9Message("MorCalculate_a",commd);
        return ;
    }
    // 查询所有用于修正RVR的参数数据
    else if(headCtx == "SC_RVR:VR800CorrectAsk"){
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue("VR800CorrectAsk:I:N:0:NULL");
        emit AFFIX9Message("VR800CorrectAsk",commd);
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue("SC_RVR_MakeUpAsk:I:N:1:NULL");
        emit AFFIX9Message("SC_RVR_MakeUpAsk",commd);
        return ;
    }
    // 添加传感器
    else if(headCtx == "wind:本地添加"
            || headCtx == "wind:设置"
            || headCtx == "wind:关闭")
    {
        qDebug()<<"wind ADD:"<< headCtx<<" Data:"<<dataCtx;
        openSensorAdd("wind");
        return ;
    }
    else if(headCtx == "wind:外部添加")
    {
        openVirtualSenorAdd("wind");
    }
    else if(headCtx == "RVR:本地添加"
            || headCtx == "RVR:设置"
            || headCtx == "RVR:关闭")
    {
        qDebug()<<"RVR ADD:"<< headCtx<<" Data:"<<dataCtx;
        openSensorAdd("vis");
        return ;
    }
    else if(headCtx == "RVR:外部添加")
    {
        openVirtualSenorAdd("VIS");
    }
    else if(headCtx == "tempHumi:本地添加"
            || headCtx == "tempHumi:设置"
            || headCtx == "tempHumi:关闭")
    {
        qDebug()<<"tempHumi ADD:"<< headCtx<<" Data:"<<dataCtx;
        openSensorAdd("humiTemp");
        return ;
    }
    else if(headCtx == "tempHumi:外部添加")
    {
        openVirtualSenorAdd("tempHumi");
    }
    else if(headCtx == "custom:本地添加"
            || headCtx == "custom:设置"
            || headCtx == "custom:关闭")
    {
        qDebug()<<"custom ADD:"<< headCtx<<" Data:"<<dataCtx;
        openSensorAdd("custom");
        return ;
    }
    else if(headCtx == "custom:外部添加")
    {
        openVirtualSenorAdd("custom");
    }
    else if(headCtx == "sensor:添加关闭")
    {
        closeFram(findAppointKeyValue(dataCtx,"framName"));
        return;
    }
    else if(headCtx == "cardParameter36:设置")
    {
        openCommunicateSet(findAppointKeyValue(dataCtx,"index"));
        return ;
    }
    else if(headCtx == "cardParameter36:关闭卡设置")
    {
        closeCommunicateSet();
        return ;
    }
    else if(headCtx == "Data_Airport:Store")
    {
        addInfor(dataCtx,&m_airPort);
        qDebug()<<"airport信息数据:"<<m_airPort;
        return ;
    }
    else if(headCtx == "Data_RunWay:Store")
    {
        addInfor(dataCtx,&m_runWay);
        qDebug()<<"runway信息数据:"<<m_runWay;
        return ;
    }
    else if(headCtx == "Data_3616:Store")
    {
        addInfor(dataCtx,&m_3616);
        qDebug()<<"3616信息据:"<<m_3616;
        return ;
    }
    else if(headCtx == "Data_36heartBeat:Store")
    {
        addInfor(dataCtx,&m_state36);
        emit AFFIX9NewMessageSendUp("36state",m_state36);
    }
    else if(headCtx == "Data_lib:Store")
    {
        addInfor(dataCtx,&m_libary);
        qDebug()<<"Libs库数据:"<<m_libary;
        classfiySensors();
        qDebug()<<"归类Libs库数据:"<<m_realExistSensor;
        emit AFFIX9LocationDataDueSignal("lib36:open");
        return ;
    }
    else if(headCtx == "Data_openlib:Store")
    {
        addInfor(dataCtx,&m_openModels);
        qDebug()<<"open libs  Datas:"<<m_openModels;
        emit AFFIX9NewMessageSendUp("openModel",m_openModels);
        emit update_all_sensor_devices("initSensorInfoShow");
        return ;
    }
    else if(headCtx == "Data_carCommunicate:Store")
    {
        addInfor(dataCtx,&m_cardCommunicate);
        qDebug()<<"cardCommunicate通讯卡数据:"<<m_cardCommunicate;
        return ;
    }
    else if(headCtx == "Data_sensor:Store")
    {
        addInfor(dataCtx,&m_sensor);
        qDebug()<<"检查各卡链接的传感器后生成sensor信息数据表:"<<m_sensor;
        emit update_all_sensor_devices(upadte_sensor_type_str);
    }
    else if(headCtx == "ExternSensor:add")
    {
        QString name = findAppointKeyValue(dataCtx,"name")
                ,id = findAppointKeyValue(dataCtx,"id")
                ,loca = findAppointKeyValue(dataCtx,"loca")
                ,source = findAppointKeyValue(dataCtx,"source")
                ,kind = findAppointKeyValue(dataCtx,"kind");
        if(name == "ERROR"
                ||id == "ERROR"
                ||loca == "ERROR"
                ||source == "ERROR"
                ||kind == "ERROR")
        {
            qDebug()<<"添加外部传感器所需参数丢失。";
            return ;
        }
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue(QString("Name:S:N:%1:NULL").arg(name));
        commd.enqueue(QString("Type:S:N:%1:NULL").arg(kind));
        commd.enqueue(QString("ID:I:N:%1:NULL").arg(id));
        commd.enqueue(QString("Location:S:N:%1:NULL").arg(loca));
        commd.enqueue(QString("Source:S:N:%1:NULL").arg(source));
        emit AFFIX9Message("ExternSensorAdd",commd);
    }
    else if(headCtx == "ExternSensor:delete")
    {
        QString delname = findAppointKeyValue(dataCtx,"name")
                ,delid = findAppointKeyValue(dataCtx,"id")
                ,delloca = findAppointKeyValue(dataCtx,"loca")
                ,delsource = findAppointKeyValue(dataCtx,"source")
                ,delkind = findAppointKeyValue(dataCtx,"kind");
        if(delname == "ERROR"
                ||delid == "ERROR"
                ||delloca == "ERROR"
                ||delsource == "ERROR"
                ||delkind == "ERROR")
        {
            qDebug()<<"删除外部传感器所需参数丢失。";
            return ;
        }
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        commd.enqueue(QString("Name:S:N:%1:NULL").arg(delname));
        commd.enqueue(QString("Type:S:N:%1:NULL").arg(delid));
        commd.enqueue(QString("ID:I:N:%1:NULL").arg(delloca));
        commd.enqueue(QString("Location:S:N:%1:NULL").arg(delsource));
        commd.enqueue(QString("Source:S:N:%1:NULL").arg(delkind));
        emit AFFIX9Message("ExternSensorDelete",commd);
    }
    else if(headCtx == "ExternSensor:query")
    {
        commd.clear();
        commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
        emit AFFIX9Message("ExternSensorListAsk",commd);
    }
    else if(headCtx == "Data_BIASLIGHT:Store")
    {
        QString idStr = findAppointKeyValue(dataCtx,"BIASLIGHTid");qDebug()<<"id is:"<<idStr;
        QString command = dataCtx.replace("/",",");
        command = command.replace("|","=");
        QStringList idlist = findAppointKeyValues(m_basiLight,"BIASLIGHTid");
        bool flag = false;
        for(int i = 0;i < idlist.length();i++)
        {
            if(idStr == idlist.value(i))
            {
                m_basiLight[QString("index%1").arg(i)] = command;
                flag = true;
            }
        }
        if(!flag)
        {
            int n = m_basiLight.count();
            m_basiLight[QString("index%1").arg(n + 1)] = command;
        }
        qDebug()<<"basiLight data:"<<m_basiLight;
        emit AFFIX9NewMessageSendUp("basiLight",m_basiLight);
    }
    else
    {
        return ;
    }
}

/***
 *   findAppointKeyValue(QString dataPart, QString key)
 *   查找dataPart中第一个键值等于 key 值并返回
 */

QString AFFIX9Mesage::findAppointKeyValue(QString dataPart, QString key)
{
    QStringList unit;
    QString tempKey,value;
    QStringList Units = dataPart.split("/",QString::SkipEmptyParts);
    int unitNum = Units.length();
    for(int n = 0;n < unitNum;n++){
        unit.clear();
        tempKey.clear();
        value.clear();
        unit = (Units.value(n)).split("|",QString::SkipEmptyParts);
        tempKey = unit.value(0);
        value = unit.value(1);
        if(tempKey == key){
            if(!value.isEmpty()){
                return value;
            }
            else{
                return "ERROR"; //"DataLost";
            }
        }
    }
    return "ERROR"; //"NotTheKey";
}

/*   ---------------------------
 *   function description
 *   findAppointKeyValues(InforData dataPart, QString key)
 *   查找dataPart中所有项中值部分中的键等于 key 的所有值并返回
 *   ---------------------------
 */
QStringList AFFIX9Mesage::findAppointKeyValues(InforData dataPart, QString key)
{
    int num = dataPart.count(),subNum;
    QString itemStr;
    QStringList itemStrList,sub,result;
    for(int item = 1;item <= num;item++){
        itemStr.clear();
        itemStrList.clear();
        itemStr = dataPart[QString("index%1").arg(item)];
        itemStrList = itemStr.split(",");
        subNum = itemStrList.length();
        for(int subItem = 0;subItem < subNum;subItem++){
            sub.clear();
            sub = itemStrList.value(subItem).split("=");
            if(sub.value(0) == key){
                result.push_back(sub.value(1));
            }
        }
    }
    return result;
}

/*  -----------------------------
 *  function description
 *  store loca 36 device information
 *  -----------------------------
 */
void AFFIX9Mesage::_Store_3616_Deceive_Infor(SensorMap data)
{
    DataMap _3616_data = data["CFG36Data"];
    _3616_AirId.clear();
    _3616_Id.clear();
    _3616_AirId = _3616_data["AirPortID"];
    _3616_Id = _3616_data["ID3616"];
    _airport_name = _3616_data["AirPortName"];
}
/* ---------------------------
 * function description
 * add outside sensor data to database
 * ---------------------------
 */
void AFFIX9Mesage::storeAffix9ToDatabaseSolt(QString storeData)
{
    QString datacommand;
    datacommand = tr("ExternSensor:add>%1").arg(storeData);
    qDebug()<<"out side sensor"<<storeData;
    emit AFFIX9LocationDataDueSignal(datacommand);

    // not used to store out sensors to data base
    //emit storeAffix9ToDatabaseSignal("outSensorUser",storeData);
}

/*  -----------------------
 *  description function
 *  add informations
 *  -----------------------
 */
void AFFIX9Mesage::addInfor(QString ctxStr,InforData *m_data,bool clearFlage)
{
    if(clearFlage){
        m_data->clear();
    }
    QStringList subData;
    QString subNameStr,subCtxStr;
    QStringList dataList = ctxStr.split("/",QString::SkipEmptyParts);
    int dataCount = dataList.length();
    for(int n = 0;n < dataCount;n++){
        subData.clear();
        subData = (dataList.value(n)).split("|");
        subNameStr.clear();
        subCtxStr.clear();
        subNameStr = subData.value(0);
        subCtxStr = subData.value(1);
        (*m_data)[subNameStr] = subCtxStr;
    }
}

/* --------------------------
 * description function
 * edit 36 device information
 * --------------------------
 */
void AFFIX9Mesage::init3616IpEdit()
{
    _3616_ipEdit = new Ip36Edit();
    _3616_ipEdit->setGeometry(100,300,600,300);
    _3616_ipEdit->_set_Option_Signal("infor36:ipconfig>");
    connect(_3616_ipEdit,SIGNAL(updateIpAddress(QString))
            ,SLOT(AFFIX9CommandOptions(QString)));
    _3616_ipEdit->hide();
}

/* ---------------------------
 * function description
 * by sensor kind to find its informations
 * ---------------------------
 */
InforData AFFIX9Mesage::findSensorInfoByClass(QString sClass)
{
    //qDebug()<<"card connestion state:"<<m_sensor;
    //qDebug()<<"sup sensor:"<<m_realExistSensor[sClass];
    QStringList supSensor = m_realExistSensor[sClass].split("/");
    InforData data;
    int n = m_sensor.count();
    int remenber;
    remenber = 1;
    QString sub,dataCtx;
    for(int s = 1; s <= n;s++){
        sub.clear();
        dataCtx.clear();
        dataCtx = m_sensor[QString("index%1").arg(s)];
        sub = dataCtx.split(",").value(1);
        for(int c = 0;c < supSensor.length();c++){
            if((sub.split("=").value(1)) == (supSensor.value(c).split("=").value(0))){
                data[QString("data%1").arg(remenber)]
                        = QString("cardId=%1,sensorName=%2,制造厂商=%3")
                        .arg(s)
                        .arg(sub.split("=").value(1))
                        .arg(supSensor.value(c).split("=").value(1));
                remenber++;
                break;
            }
        }
    }
    return data;
}
/*  ---------------------
 *  function description
 *  ---------------------
 */
void AFFIX9Mesage::openCommunicateSet(QString index)
{
    AFFIX9ConfirmWind * comm = new AFFIX9ConfirmWind();
    connect(comm,SIGNAL(closeCommuSet(QString)),
            SLOT(AFFIX9CommandOptions(QString)));
    comm->setGeometry(100.0,100.0,600,300);
    qDebug()<<"36 data +===="<<m_3616;
    comm->setU36Id(findAppointKeyValues(m_3616,"ID3616"));
    comm->setCommData(m_cardCommunicate,index);
    comm->show();
    cardVec.push_back(comm);
}

void AFFIX9Mesage::closeCommunicateSet()
{
    int n = cardVec.length();
    for (int i = (n - 1); i >= 0; i--) {
        cardVec.value(i)->close();
        disconnect(cardVec.value(i),SIGNAL(closeCommuSet(QString))
                   ,this,SLOT(AFFIX9CommandOptions(QString)));
        delete cardVec.value(i);
        cardVec.remove(i);
    }
}

void AFFIX9Mesage::initSensorClassData()
{
    m_ClassStore["CLOUD"] = "";
    m_ClassStore["HUMITEMP"] = "HMP155=维萨拉";
    m_ClassStore["RAIN"] = "RAINSC=视程科技";
    m_ClassStore["VIS"] = "VR800=视程科技/VS2K101=LUFFT前散";
    m_ClassStore["WIND"] = "WMT52=维萨拉/VENTUS=LUFFT";
    m_ClassStore["PW"] = "";
    m_ClassStore["PV"] = "";
    m_ClassStore["CUSTOM"] = "INPUTDATA=视程科技/AFTN=视程科技/BIASLIGHT=视程科技";
}

void AFFIX9Mesage::classfiySensors()
{
    m_realExistSensor.clear();
    if(!m_libary.isEmpty()){
        int count = m_libary.count();
        QString libCtx,sensorName;
        QStringList classKeys = m_ClassStore.keys();
        int keyNum = classKeys.length();
        QStringList sensorNames;
        int sensorNum;
        QString tempSensorStr;
        for(int l = 1;l <= count;l++){
            libCtx.clear();
            sensorName.clear();
            libCtx = m_libary[QString("index%1").arg(l)];
            sensorName = libCtx.split("=").value(1);
            for(int key = 0;key < keyNum;key++){
                sensorNames.clear();
                sensorNames = m_ClassStore[classKeys.value(key)].split("/");
                sensorNum = 0;
                sensorNum = sensorNames.length();
                for(int sub = 0;sub <sensorNum;sub++){
                    tempSensorStr.clear();
                    if(sensorName == sensorNames.value(sub).split("=").value(0)){
                        tempSensorStr = m_realExistSensor[classKeys.value(key)];
                        if(tempSensorStr.isEmpty()){
                            tempSensorStr = sensorNames.value(sub);
                        }else{
                            tempSensorStr = tempSensorStr + "/" +sensorNames.value(sub);
                        }
                        m_realExistSensor[classKeys.value(key)] = tempSensorStr;
                    }
                }
            }
        }
        qDebug()<<"36真实支持的传感器:"<<m_realExistSensor;
    }
    else{
        qDebug()<<"传感器库查询失败！";
    }
}

void AFFIX9Mesage::openSensorAdd(QString sClass)
{
    if(sClass == "wind"){
        initLib("WIND");
        openFram(QString("wind_%1").arg(n_wind));
        n_wind++;
    }
    else if(sClass == "vis"){
        initLib("VIS");
        openFram(QString("vis_%1").arg(n_vis));
        n_vis++;
    }
    else if(sClass == "humiTemp"){
        initLib("HUMITEMP");
        openFram(QString("humiTemp_%1").arg(n_humitemp));
        n_humitemp++;
    }
    else if(sClass == "custom"){
        initLib("CUSTOM");
        openFram(QString("custom_%1").arg(n_custom));
        n_custom++;
    }
    else{
        return ;
    }
}

void AFFIX9Mesage::openFram(QString name)
{
    AFFIX9AddSensor *sensor = new AFFIX9AddSensor();
    sensor->setObjectName(name);
    connect(sensor,SIGNAL(closeCommuSet(QString)),
            SLOT(AFFIX9CommandOptions(QString)));
    sensor->setU36Id(findAppointKeyValues(m_3616,"ID3616"));
    sensor->setSensorModel(libList);
    sensor->setCommData(m_cardCommunicate,"1");
    sensor->setGeometry(100.0,100.0,600,300);
    sensor->show();
    sensorVec.push_back(sensor);
}

void AFFIX9Mesage::closeFram(QString deleteName)
{
    if(!sensorVec.isEmpty()){
        int n = sensorVec.length();
        QString name;
        for(int i = 0;i < n;i++){
            name.clear();
            name = sensorVec.value(i)->objectName();
            qDebug()<<"object name:"<<sensorVec.value(i)->objectName();
            if(name == deleteName){
                sensorVec.value(i)->close();
                disconnect(sensorVec.value(i),SIGNAL(closeCommuSet(QString)),
                           this,SLOT(AFFIX9CommandOptions(QString)));
                delete sensorVec.value(i);
                sensorVec.remove(i);
                return ;
            }
        }
    }
}

void AFFIX9Mesage::openVirtualSenorAdd(QString sClass)
{
    int len;
    len = outSensorVec.length();
    QString subClass;
    for(int n = 0;n < len;n++){
        subClass.clear();
        subClass = outSensorVec.value(n)->objectName();
        if(subClass == sClass){
            outSensorVec.value(n)->show();
            return ;
        }
    }
    Affix9AddOutSensor *outSensor = new Affix9AddOutSensor();
    connect(outSensor,SIGNAL(store_sensor_data(QString))
            ,this,SLOT(storeAffix9ToDatabaseSolt(QString)));
    outSensor->setObjectName(sClass);
    outSensor->_set_out_sensor_title(sClass);
    if(sClass == "custom"){
        outSensor->_set_out_sensor_kind("");
    }
    else{
        outSensor->_set_out_sensor_kind(sClass);
    }
    outSensor->setGeometry(100,300,600,200);
    outSensor->show();
    outSensorVec.push_back(outSensor);
}

void AFFIX9Mesage::initNumberValue()
{
    n_wind = 1;
    n_vis = 1;
    n_humitemp = 1;
    n_custom = 1;
    //   n_wind = 0;
    //   n_wind = 0;
}

void AFFIX9Mesage::initLib(QString libClass)
{
    libList.clear();
    if(m_realExistSensor.isEmpty()){
        qDebug()<<"没有可用的库传感器！";
        return;
    }
    libList = m_realExistSensor[libClass].split("/");
    return ;
}

void AFFIX9Mesage::initAFFIX9LocaDataDueConn()
{
    connect(this,SIGNAL(AFFIX9LocationDataDueSignal(QString))
            ,SLOT(AFFIX9CommandOptions(QString)));
}

void AFFIX9Mesage::_init_Deceive_3616_infor()
{
    _3616_Id = "-1";
    _3616_AirId = "-1";
    _airport_name = "NULL";
}

void AFFIX9Mesage::_init_update_sensor_type_value()
{
    upadte_sensor_type_str = "all";
}

void AFFIX9Mesage::init_local_connection()
{
    connect(this,SIGNAL(send_self_signal(QString)),
            this,SLOT(AFFIX9CommandOptions(QString)));
}



