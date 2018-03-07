#include "telegram/telesubdatamod.h"

teleSubDataModCtl::teleSubDataModCtl(QWidget *parent) :
    QWidget(parent)
{
    m_telegramName = "电报名称";
    initTelegramnLable();
    initManualEdit();
    initTeleStartCtx();

    newAllSubContrls();
    setAllContrlsOnliyRead();
    setAllContrlsGeometry();
    initAllEditLineValue();

    newAllComboxContrl();
    setAllComboxContrlsGeometry();
    initComboxConnections();

    initTelegramSubOptions();
    setAllComboxContrlsValue();

    m_encodTelegramStyle = true;
    initItemsValue();
    initTeleCodecDeal();
    initWeather();
    initCavokChieck();
    _init_user_grade_type();
}

void teleSubDataModCtl::initTelegramnLable()
{
    telegramLabelName[1]  = "报头 [CCCC YYGGggZ]";
    telegramLabelName[2]  = "风             [WIND]";
    telegramLabelName[3]  = "机场能见度值      [VVVV]";
    telegramLabelName[4]  = "跑道视程                RVR]";
    telegramLabelName[5]  = "现在天气             [W`W`]";
    telegramLabelName[6]  = "云量云高         [CLOUD]";
    telegramLabelName[7]  = "温度/露点              [T/Td]";
    telegramLabelName[8]  = "修正海压              [QNH]";
    telegramLabelName[9]  = "近时天气         [REw`w`]";
    telegramLabelName[10] = "道面状况         [MOTNE]";
    telegramLabelName[11] = "趋势报             [TREND]";
    telegramLabelName[12] = "备注                 [REMAK]";
}
void teleSubDataModCtl::setTelegramName(QString telegramName)
{
    this->m_telegramName = telegramName;
    update();
}

void teleSubDataModCtl::setUpdateTime(QTime updateTime)
{
    this->m_updateTime = updateTime;
    update();
}

void teleSubDataModCtl::setToSendTelegramHaveTime(QString toSendTelegramHaveTime)
{
    this->m_haveTime = toSendTelegramHaveTime;
    update();
}

void teleSubDataModCtl::setEncodeTelegramStyle(bool encodcStyle)
{
    this->m_encodTelegramStyle = encodcStyle;
}

void teleSubDataModCtl::headMetarSlot(QString str)
{
    metarOptionSelet("head",str);
    //qDebug()<<"ssss ddddd ffff";
}

void teleSubDataModCtl::windMetarSlot(QString str)
{
    metarOptionSelet("wind",str);
}

void teleSubDataModCtl::visMetarSlot(QString str)
{
    metarOptionSelet("vis",str);
}

void teleSubDataModCtl::RVRMetarSlot(QString str)
{
    metarOptionSelet("rvr",str);
}

void teleSubDataModCtl::weatherMetarSlot(QString str)
{
    metarOptionSelet("weath",str);
}

void teleSubDataModCtl::cloudHightMetarSlot(QString str)
{
    metarOptionSelet("cloud",str);
}

void teleSubDataModCtl::tempHumMetarSlot(QString str)
{
    metarOptionSelet("tempHum",str);
}

void teleSubDataModCtl::pressMetarSlot(QString str)
{
    metarOptionSelet("press",str);
}

void teleSubDataModCtl::closWeatherMetarSlot(QString str)
{
    metarOptionSelet("closeWeather",str);
}

void teleSubDataModCtl::wsMetarSlot(QString str)
{
    metarOptionSelet("ws",str);
}

void teleSubDataModCtl::motneMetarSlot(QString str)
{
    metarOptionSelet("motne",str);
}

void teleSubDataModCtl::trendMetarSlot(QString str)
{
    metarOptionSelet("trend",str);
}

void teleSubDataModCtl::metarOptionSelet(QString nameStr, QString optionStr)
{
    bool openManual;
    if(optionStr == "AUTOMATIC"){
        //qDebug()<<"automatic";
        openManual = false;
    }
    else if(optionStr == "MANUAL"){
        openManual = true;
    }
    else if(true){
        openManual = false;
        //qDebug()<<"unknown one";
    }
    else{
        openManual = false;
        //qDebug()<<"unknown";
    }

    // 操作具体输入控件读取人工输入数据
    if(nameStr == "head"){
        headEdit->setReadOnly(!openManual);
        headManulEditBool = openManual;
    }
    else if(nameStr == "wind"){
        windEdit->setReadOnly(!openManual);
        windManulEditBool = openManual;
    }
    else if(nameStr == "vis"){
        visEdit->setReadOnly(!openManual);
        visManulEditBool = openManual;
    }
    else if(nameStr == "rvr"){
        RVREdit->setReadOnly(!openManual);
        RVRManulEditBool = openManual;
    }
    else if(nameStr == "weath"){
        weatherEdit->setReadOnly(!openManual);
        weatherManulEditBool = openManual;
    }
    else if(nameStr == "cloud" ){
        cloudHightEdit->setReadOnly(!openManual);
        cloudHightManulEditBool = openManual;
    }
    else if(nameStr == "tempHum"){
        tempHumEdit->setReadOnly(!openManual);
        tempHumManulEditBool = openManual;
    }
    else if(nameStr == "press"){
        pressEdit->setReadOnly(!openManual);
        pressManulEditBool = openManual;
    }
    else if(nameStr == "closeWeather"){
        closeWeatherEdit->setReadOnly(!openManual);
        closeWeatherManulEditBool = openManual;
    }
    else if(nameStr == "ws"){
        RemarkEdit->setReadOnly(!openManual);
        RemarManulEditBool = openManual;
    }
    else if(nameStr == "motne"){
        MOTNEEdit->setReadOnly(!openManual);
        MOTNEManulEditBool = openManual;
    }
    else if(nameStr == "trend"){
        TRENDEdit->setReadOnly(!openManual);
        TRENDManulEditBool = openManual;
    }
    else{
        qDebug()<<"other commbox waring";
    }

    // 传输选项配置情况
    QString cfg;
    if(nameStr == "head"){
        cfg.clear();
        cfg = headBox->currentText();
        if(comBoxCFG["head"] == cfg) return;
        comBoxCFG["head"] = cfg;
    }
    else if(nameStr == "wind"){
        cfg.clear();
        cfg = windBox->currentText();
        if(comBoxCFG["wind"] == cfg) return;
        comBoxCFG["wind"] = cfg;
    }
    else if(nameStr == "vis"){
        cfg.clear();
        cfg = visBox->currentText();
        if(comBoxCFG["vis"] == cfg) return;
        comBoxCFG["vis"] = cfg;
    }
    else if(nameStr == "rvr"){
        cfg.clear();
        cfg = RVRBox->currentText();
        if(comBoxCFG["rvr"] == cfg) return;
        comBoxCFG["rvr"] = cfg;
    }
    else if(nameStr == "weath"){
        cfg.clear();
        cfg = weatherBox->currentText();
        if(comBoxCFG["weath"] == cfg) return;
        comBoxCFG["weath"] = cfg;
    }
    else if(nameStr == "cloud" ){
        cfg.clear();
        cfg = cloudHightBox->currentText();
        if(comBoxCFG["cloud"] == cfg) return;
        comBoxCFG["cloud"] = cfg;
    }
    else if(nameStr == "tempHum"){
        cfg.clear();
        cfg = tempHumBox->currentText();
        if(comBoxCFG["tempHum"] == cfg) return;
        comBoxCFG["tempHum"] = cfg;
    }
    else if(nameStr == "press"){
        cfg.clear();
        cfg = pressBox->currentText();
        if(comBoxCFG["press"] == cfg) return;
        comBoxCFG["press"] = cfg;
    }
    else if(nameStr == "closeWeather"){
        cfg.clear();
        cfg = closeWeatherBox->currentText();
        if(comBoxCFG["closeWeather"] == cfg) return;
        comBoxCFG["closeWeather"] = cfg;
    }
    else if(nameStr == "ws"){
        cfg.clear();
        cfg = WsBox->currentText();
        if(comBoxCFG["ws"] == cfg) return;
        comBoxCFG["ws"] = cfg;
    }
    else if(nameStr == "motne"){
        cfg.clear();
        cfg = MOTNEBox->currentText();
        if(comBoxCFG["motne"] == cfg) return;
        comBoxCFG["motne"] = cfg;
    }
    else if(nameStr == "trend"){
        cfg.clear();
        cfg = TRENDBox->currentText();
        if(comBoxCFG["trend"] == cfg) return;
        comBoxCFG["trend"] = cfg;
    }
    else{
        qDebug()<<"other commbox waring";
    }
    // 发送配置控制取数 待做
}

void teleSubDataModCtl::ComboxCtlsSelecetSlot(QString affixstr)
{
    QStringList affixList;
    affixList = affixstr.split(":",QString::SkipEmptyParts);
    QString boxkind ,itemName;
    boxkind = affixList.value(0);
    itemName = affixList.value(1);
    if(boxkind == "updateWindSelect"){
        int num = windItemList.length();
        for(int i = 0;i < num;i++){
            if(windItemList.value(i) == itemName)
                return;
        }
        windItemList.push_back(itemName);
        windBox->clear();
        windBox->addItems(windItemList);
    }
    else if(boxkind == "updateHumiTempselect"){
        int num2 = tempHumItemList.length();
        for(int i = 0;i < num2;i++){
            if(tempHumItemList.value(i) == itemName)
                return;
        }
        tempHumItemList << itemName;
        tempHumBox->clear();
        tempHumBox->addItems(tempHumItemList);
    }
    else if(boxkind == "updateRVRSelect"){

        int num3 = visItemList.length();
        for(int i = 0;i < num3;i++){
            if(visItemList.value(i) == itemName)
                return;
        }
        visItemList << itemName;
        visBox->clear();
        visBox->addItems(visItemList);

        num3 = RVRItemList.length();
        for(int i = 0;i < num3;i++){
            if(RVRItemList.value(i) == itemName)
                return;
        }
        RVRItemList << itemName;
        RVRBox->clear();
        RVRBox->addItems(RVRItemList);
    }
    else if(boxkind == "updateCloudSelect"){
        int num4 = cloudHightItemList.length();
        for(int i = 0;i < num4;i++){
            if(cloudHightItemList.value(i) == itemName)
                return;
        }
        cloudHightItemList.push_back(itemName);
        cloudHightBox->clear();
        cloudHightBox->addItems(cloudHightItemList);
    }
    else if(boxkind == "updatePressSelect")
    {
        int num5 = pressItemList.length();
        for(int i = 0;i < num5;i++)
        {
            if(pressItemList.value(i) == itemName)
                return;
        }
        pressItemList << itemName;
        pressBox->clear();
        pressBox->addItems(pressItemList);
    }
    else if(boxkind == "updateWeatherSelect") //"updateWeatherSelect:%1"
    {
        int num6 = weatherItemList.length();
        for(int i = 0;i < num6;i++)
        {
            if(weatherItemList.value(i) == itemName)
                return;
        }
        weatherItemList << itemName;
        weatherBox->clear();
        weatherBox->addItems(weatherItemList);


        num6 = closeWeatherItemList.length();
        for(int i = 0;i < num6;i++){
            if(closeWeatherItemList.value(i) == itemName)
                return;
        }
        closeWeatherItemList << itemName;
        closeWeatherBox->clear();
        closeWeatherBox->addItems(closeWeatherItemList);
        //近时天气
    }
}

/* ------------------------------------------
 * function descrept
 *  输入实时系统数据 realDataMap
 *  经过条件分析和出里生成Metar报数据内容
 *  保存于界面的各个子METAR报数据子控件中待初次人工修改
 * ----------------------------------------------
 */
void teleSubDataModCtl::updateSubTelegramCtx(realDataMap sysMetarRealData)
{
    QString valueStr,selectStr;
    if(m_encodTelegramStyle){
        // 电报报头............................
        if(headManulEditBool){
            headEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
            //            headEdit->clear();
        }
        else{
            valueStr.clear();
            valueStr = "ZSOF " + QDateTime::currentDateTimeUtc().toString("ddhhmm") + "Z";
            if(!valueStr.isEmpty()){
                headEdit->setText(valueStr);
                headEdit->setStyleSheet("QLineEdit{}");
            }
        }
        // 电报风内容.........................
        if(windManulEditBool){
            windEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
            //            windEdit->clear();
        }
        else{
            valueStr.clear();
            selectStr.clear();
            selectStr = comBoxCFG["wind"];
            QString tenAvgAngle,tenAvgSpeed
                    ,tenMinAngle,tenMaxAngle
                    ,shSpeed;
            if(selectStr.split("-").length() > 1){
                tenAvgAngle = sysMetarRealData["groupMIDIAngle"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                tenAvgSpeed = sysMetarRealData["groupMIDISpeed1"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                tenMinAngle = sysMetarRealData["groupMIDIAngleMin"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                tenMaxAngle = sysMetarRealData["groupMIDIAngleMax"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                shSpeed = sysMetarRealData["groupMIDISHSpeed"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                valueStr = teleCodecDeal->getWindCodec(tenAvgAngle,tenAvgSpeed
                                                       ,tenMinAngle,tenMaxAngle
                                                       ,shSpeed);
            }
            else if(selectStr.toInt() < 18){
                tenAvgAngle = sysMetarRealData["groupLeftAngle"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                tenAvgSpeed = sysMetarRealData["groupLeftSpeed1"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                tenMinAngle = sysMetarRealData["groupLeftAngleMin"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                tenMaxAngle = sysMetarRealData["groupLeftAngleMax"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                shSpeed = sysMetarRealData["groupLeftSHSpeed"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                valueStr = teleCodecDeal->getWindCodec(tenAvgAngle,tenAvgSpeed
                                                       ,tenMinAngle,tenMaxAngle
                                                       ,shSpeed);
            }
            else if(selectStr.toInt() >17){
                tenAvgAngle = sysMetarRealData["groupRightAngle"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                tenAvgSpeed = sysMetarRealData["groupRightSpeed1"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                tenMinAngle = sysMetarRealData["groupRightAngleMin"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                tenMaxAngle = sysMetarRealData["groupRightAngleMax"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                shSpeed = sysMetarRealData["groupRightSHSpeed"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
                valueStr = teleCodecDeal->getWindCodec(tenAvgAngle,tenAvgSpeed
                                                       ,tenMinAngle,tenMaxAngle
                                                       ,shSpeed);
            }
            if(!valueStr.isEmpty()){
                windEdit->setText(valueStr);
                windEdit->setStyleSheet("QLineEdit{}");
            }
        }
        //电报能见度内容............................
        if(visManulEditBool){
            visEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
            //            visEdit->clear();
        }
        else{
            QString rvr1,rvr2,rvr3,maxRvr,tenVisMin,rowVis;
            int Vrvr1,Vrvr2,Vrvr3,VmaxRvr;
            rowVis = sysMetarRealData["groupVisRowVis"].split(".",QString::SkipEmptyParts).value(0);
            tenVisMin = sysMetarRealData["groupVisSensor_vis10m"].split(".",QString::SkipEmptyParts).value(0);
            rvr1 = sysMetarRealData["groupLeftRVRTenAvgValue"].split(".",QString::SkipEmptyParts).value(0);
            rvr2 = sysMetarRealData["groupMIDIRVRTenAvgValue"].split(".",QString::SkipEmptyParts).value(0);
            rvr3 = sysMetarRealData["groupRightRVRTenAvgValue"].split(".",QString::SkipEmptyParts).value(0);
            Vrvr1 =  rvr1.toInt();
            Vrvr2 =  rvr2.toInt();
            Vrvr3 =  rvr3.toInt();
            VmaxRvr = qMax(qMax(Vrvr1,Vrvr2),Vrvr3);
            maxRvr = QString("%1").arg(VmaxRvr);
            valueStr.clear();
            valueStr = teleCodecDeal->getMorCodes(rowVis,maxRvr,tenVisMin);
            if(!valueStr.isEmpty()){
                visEdit->setText(valueStr);
                visEdit->setStyleSheet("QLineEdit{}");
            }
        }
        //电报跑道视程内容............................
        if(RVRManulEditBool){
            RVREdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
            //            RVREdit->clear();
        }
        else{
            valueStr.clear();
            selectStr.clear();
            QString tenAvgRvr,tenMinRvr,tenMaxRvr,tenAvgVis,runWayNUmber,rvrTrend;
            selectStr = comBoxCFG["rvr"];
            if(selectStr.split("-").length() > 1){
                ;// 跑道视程中间区域不用报
            }
            else if(selectStr.toInt() < 18){
                tenAvgRvr = sysMetarRealData["groupLeftRVRTenAvgValue"].trimmed()// 正在使用的跑道的接触地带RVR
                        .split(" ",QString::SkipEmptyParts).value(0);
                tenMinRvr = sysMetarRealData["groupLeftRVRTenMinValue"].trimmed()// 正在使用的跑道10分钟最小RVR
                        .split(" ",QString::SkipEmptyParts).value(0);
                tenMaxRvr = sysMetarRealData["groupLeftRVRTenMaxValue"].trimmed()// 正在使用的跑道10分钟最大RVR
                        .split(" ",QString::SkipEmptyParts).value(0);
                tenAvgVis = sysMetarRealData["groupVisRowVis"].trimmed()// 主导能见度值（合肥取法直接取电报中的能见度报的数据rowVis）
                        .split(" ",QString::SkipEmptyParts).value(0);
                runWayNUmber = selectStr;                                           // 注：必须带上R/L ，在平行跑道时
                rvrTrend = sysMetarRealData["groupLeftRVRTendency"].trimmed() // 跑道视程变化趋势
                        .split(" ",QString::SkipEmptyParts).value(0);
                valueStr = teleCodecDeal->getRvrCodes(tenAvgRvr,tenMinRvr,tenMaxRvr
                                                      ,tenAvgVis,runWayNUmber,rvrTrend);
            }
            else if(selectStr.toInt() >17){
                tenAvgRvr = sysMetarRealData["groupRightRVRTenAvgValue"].trimmed()// 正在使用的跑道的接触地带RVR
                        .split(" ",QString::SkipEmptyParts).value(0);
                tenMinRvr = sysMetarRealData["groupRightRVRTenMinValue"].trimmed()// 正在使用的跑道10分钟最小RVR
                        .split(" ",QString::SkipEmptyParts).value(0);
                tenMaxRvr = sysMetarRealData["groupRightRVRTenMaxValue"].trimmed()// 正在使用的跑道10分钟最大RVR
                        .split(" ",QString::SkipEmptyParts).value(0);
                tenAvgVis = sysMetarRealData["groupVisRowVis"].trimmed()// 主导能见度值（合肥取法直接取电报中的能见度报的数据rowVis）
                        .split(" ",QString::SkipEmptyParts).value(0);
                runWayNUmber = selectStr;                                           // 注：必须带上R/L ，在平行跑道时
                rvrTrend = sysMetarRealData["groupRightRVRTendency"].trimmed() // 跑道视程变化趋势
                        .split(" ",QString::SkipEmptyParts).value(0);
                valueStr = teleCodecDeal->getRvrCodes(tenAvgRvr,tenMinRvr,tenMaxRvr
                                                      ,tenAvgVis,runWayNUmber,rvrTrend);
            }
            if(!valueStr.isEmpty()){
                RVREdit->setText(valueStr);
                RVREdit->setStyleSheet("QLineEdit{}");
            }
        }
        //天气现象内容............................
        if(weatherManulEditBool){
            weatherEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
            //            weatherEdit->clear();
        }
        else{
            valueStr.clear();
            QString PW;
            PW =  sysMetarRealData["groupCurrentWeather"].trimmed()
                    .split(" ",QString::SkipEmptyParts).value(0);
            valueStr = teleCodecDeal->getWeatherCodes(PW);
            m_weatherStr = valueStr;
            if(valueStr == "DataLost"){
                valueStr = "";
            }
            else if(valueStr == "NotWeather"){
                valueStr = "";
            }
            else{
                ;
            }
            //            if(!valueStr.isEmpty()){
            weatherEdit->setText(valueStr);
            weatherEdit->setStyleSheet("QLineEdit{}");
            //            }
        }
        //电报云高内容............................
        if(cloudHightManulEditBool){
            cloudHightEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
            //            cloudHightEdit->clear();
        }
        else{
            valueStr.clear();
            selectStr.clear();
            selectStr = comBoxCFG["cloud"];
            QString isSkyClear;  //   是否为晴空
            QString isVerVis;    //   是否能测量垂直能见度
            //            QString /*verVisE5*/;    //   5分钟垂直能见度值
            QString cloudBase;   //   云底高度值
            //            QString /*cloudBaseE5*/ ;//   5分钟最低云快高度(维萨拉不提供这数据)
            QString ch1Ins30;   //   30分钟第一层云高
            QString ch2Ins30;    //   30分钟第二层云高
            QString ch3Ins30;    //   30分钟第三层云高
            QString amount1_30; //   30分钟第一层云量
            QString amount2_30; //   30分钟第二层云量
            QString amount3_30;  //   30分钟第三层云量


            if(selectStr.split("-").length() > 1){
                ;
            }
            else if(selectStr.toInt() < 18){
                isSkyClear = sysMetarRealData["groupLeftIsSkyClear"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                isVerVis= sysMetarRealData["groupLeftIsVerVis"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                cloudBase= sysMetarRealData["groupLeftCloudBase"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                ch1Ins30 = sysMetarRealData["groupLeft1CloudHight"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                ch2Ins30 = sysMetarRealData["groupLeft2CloudHight"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                ch3Ins30 = sysMetarRealData["groupLeft3CloudHight"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                amount1_30 = sysMetarRealData["groupLeft1CloudCount"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                amount2_30 = sysMetarRealData["groupLeft2CloudCount"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                amount3_30 = sysMetarRealData["groupLeft3CloudCount"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                qDebug()<<"isSkyClear:"<<isSkyClear
                       <<"isVerVis:"<<isVerVis
                      <<"cloudBase:"<<cloudBase
                     <<"ch1Ins30:"<<ch1Ins30
                    <<"ch2Ins30:"<<ch2Ins30
                   <<"ch3Ins30:"<<ch3Ins30
                  <<"amount1_30:"<<amount1_30
                 <<"amount2_30:"<<amount2_30
                <<"amount3_30:"<<amount3_30;
                valueStr = teleCodecDeal->getCloudCodes(isSkyClear,isVerVis,cloudBase
                                                        ,ch1Ins30,ch2Ins30,ch3Ins30
                                                        ,amount1_30,amount2_30,amount3_30);
            }
            else if(selectStr.toInt() >17){
                isSkyClear = sysMetarRealData["groupRightIsSkyClear"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                isVerVis= sysMetarRealData["groupRightIsVerVis"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                cloudBase= sysMetarRealData["groupRightCloudBase"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);

                ch1Ins30 = sysMetarRealData["groupRight1CloudHight"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                ch2Ins30 = sysMetarRealData["groupRight2CloudHight"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                ch3Ins30 = sysMetarRealData["groupRight3CloudHight"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);

                amount1_30 = sysMetarRealData["groupRight1CloudCount"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                amount2_30 = sysMetarRealData["groupRight2CloudCount"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                amount3_30 = sysMetarRealData["groupRight3CloudCount"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                valueStr = teleCodecDeal->getCloudCodes(isSkyClear,isVerVis,cloudBase
                                                        ,ch1Ins30,ch2Ins30,ch3Ins30
                                                        ,amount1_30,amount2_30,amount3_30);
                qDebug()<<"isSkyClear:"<<isSkyClear
                       <<"isVerVis:"<<isVerVis
                      <<"cloudBase:"<<cloudBase
                     <<"ch1Ins30:"<<ch1Ins30
                    <<"ch2Ins30:"<<ch2Ins30
                   <<"ch3Ins30:"<<ch3Ins30
                  <<"amount1_30:"<<amount1_30
                 <<"amount2_30:"<<amount2_30
                <<"amount3_30:"<<amount3_30;
            }
            if(!valueStr.isEmpty()){
                cloudHightEdit->setText(valueStr);
                cloudHightEdit->setStyleSheet("QLineEdit{}");
            }
        }
        //电报温度露点度内容............................
        if(tempHumManulEditBool){
            tempHumEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
            //            tempHumEdit->clear();
        }
        else{
            valueStr.clear();
            selectStr.clear();
            selectStr = comBoxCFG["tempHum"];
            QString temp,dew;
            if(selectStr.split("-").length() > 1){
                ;
            }
            else if(selectStr.toInt() < 18){
                temp = sysMetarRealData["groupLeftTem"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                dew = sysMetarRealData["groupLeftDew"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                valueStr = teleCodecDeal->getTempretrueDewCodes(temp,dew);
            }
            else if(selectStr.toInt() >17){
                temp = sysMetarRealData["groupRightTem"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                dew = sysMetarRealData["groupRightDew"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                valueStr = teleCodecDeal->getTempretrueDewCodes(temp,dew);
            }
            if(!valueStr.isEmpty()){
                tempHumEdit->setText(valueStr);
                tempHumEdit->setStyleSheet("QLineEdit{}");
            }
        }
        //电报气压数据内容............................
        if(pressManulEditBool){
            pressEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
            //            pressEdit->clear();
        }
        else{
            valueStr.clear();
            selectStr.clear();
            selectStr = comBoxCFG["press"];
            QString press;
            if(selectStr.split("-").length() > 1){
                ;
            }
            else if(selectStr.toInt() < 18){
                press = sysMetarRealData["groupPress"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                valueStr = teleCodecDeal->getPressCodes(press);
            }
            else if(selectStr.toInt() >17){
                press = sysMetarRealData["groupPress"].trimmed()
                        .split(" ",QString::SkipEmptyParts).value(0);
                valueStr = teleCodecDeal->getPressCodes(press);
            }
            if(!valueStr.isEmpty()){
                pressEdit->setText(valueStr);
                pressEdit->setStyleSheet("QLineEdit{}");
            }
        }
        //电报近时天气现象内容............................
        if(closeWeatherManulEditBool){
            closeWeatherEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
            //            closeWeatherEdit->clear();
        }
        else{
            valueStr.clear();
            QString RW;
            RW = sysMetarRealData["groupCloseTimeWeather"].trimmed()
                    .split(" ",QString::SkipEmptyParts).value(0);
            valueStr = teleCodecDeal->getWeatherCodes(RW);
            if(valueStr == "DataLost"){
                valueStr = "";
            }
            else if(valueStr == "NotWeather"){
                valueStr = "";
            }
            else{
                ;
            }
            //            if(!valueStr.isEmpty()){
            closeWeatherEdit->setText(valueStr);
            closeWeatherEdit->setStyleSheet("QLineEdit{}");
            //            }
        }
        //电报道面状况内容............................
        if(MOTNEManulEditBool){
            MOTNEEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
            //            MOTNEEdit->clear();
        }
        else{
            //  只能人工输入数据
            //  MOTNEEdit->setText();
            MOTNEEdit->setStyleSheet("QLineEdit{}");
        }
        //电报趋势内容............................
        if(TRENDManulEditBool){
            TRENDEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
            //            TRENDEdit->clear();
        }
        else{
            valueStr.clear();
            selectStr.clear();
            selectStr = comBoxCFG["trend"];
            if(selectStr == "AUTOMATIC"){
                TRENDEdit->setText("NOSIG");
            }
            else{
                TRENDEdit->setText(selectStr);
            }
            TRENDEdit->setStyleSheet("QLineEdit{}");
        }
        //电报备注内容............................
        if(RemarManulEditBool){
            RemarkEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
            //            RemarkEdit->clear();
        }
        else{
            //   只能人工输入备注
            //   RemarkEdit->setText();
            RemarkEdit->setStyleSheet("QLineEdit{}");
        }
    }
    else{
        QMessageBox::warning(this,"信息提示！","请手动编辑METAR报内容并送发一份Metar报。");
    }
}

void teleSubDataModCtl::updateSubTelegramTrendCtx(QString trendCtx)
{
    TRENDEdit->setText(trendCtx);
    TRENDEdit->setStyleSheet("QLineEdit{background-color:#00ff00;color:balck;border-width:1;border-color:red;border-style:outset}");
}

void teleSubDataModCtl::_update_Forcaster_Sub_Telegram_Ctx(QString _Metar_Ctx)
{
    QMap<QString,QString> metarMap;
    metarMap.clear();
    QString metarStr;
    QStringList metarlist;
    metarStr = _Metar_Ctx.trimmed();
    metarlist = metarStr.split("/");
    QString _subCtx,_m_Name,_m_Ctx;
    int len = metarlist.length();
    for(int i = 0;i < len;i++){
        _m_Name.clear();
        _m_Ctx.clear();
        _subCtx = metarlist.value(i);
        _m_Name = _subCtx.split("=").value(0);
        _m_Ctx = _subCtx.split("=").value(1);
        metarMap[_m_Name] = _m_Ctx;
    }
    headEdit->setText(metarMap["head"]);
    windEdit->setText(metarMap["wind"]);
    visEdit->setText(metarMap["vis"]);
    RVREdit->setText(metarMap["rvr"]);
    weatherEdit->setText(metarMap["pw"]);
    cloudHightEdit->setText(metarMap["cloud"]);
    tempHumEdit->setText(metarMap["tempdew"]);
    pressEdit->setText(metarMap["press"]);
    closeWeatherEdit->setText(metarMap["closedpw"]);
    MOTNEEdit->setText(metarMap["daomian"]);
    TRENDEdit->setText(metarMap["trend"]);
    RemarkEdit->setText(metarMap["remak"]);
    qDebug()<<"aaaaaaaaaa"<<_Metar_Ctx;
}

void teleSubDataModCtl::setEnableCavokSlot(bool flag)
{
    m_cavokCheick = flag;
}


/* ---------------------------------------
 *  function description
 *  从界面获取生成报的数据
 *  并做是否满足CAVOK 条件编报
 *  最后把编写出METAR报内容返回
 * ---------------------------------------
 */

SerialWarMap teleSubDataModCtl::getTelegramCtx()
{
    SerialWarMap  subMap;
    // 2 . 从界面的各个控件中取值更新，并判断Cavok情况。
    bool cavok;
    cavok = false;
    if(m_cavokCheick){
        QString visStr,cloudStr,weatherStr;
        visStr = visEdit->text().trimmed();
        cloudStr = cloudHightEdit->text().trimmed();
        weatherStr = weatherEdit->text().trimmed();
        if(visStr == "9999"
                && (cloudStr == "NSC"
                    || cloudStr == "SKC")
                && weatherStr.isEmpty())
        {
            cavok = true;
        }
    }

    if(cavok){
        subMap[1]  = headEdit->text();
        subMap[2]  = windEdit->text();
        subMap[3]  = "CAVOK";
        subMap[4]  = tempHumEdit->text();
        subMap[5]  = pressEdit->text();
        subMap[6] = MOTNEEdit->text();
        subMap[7] = TRENDEdit->text();
        subMap[8] = RemarkEdit->text();
    }
    else{
        subMap[1] = headEdit->text();
        subMap[2] = windEdit->text();
        subMap[3] = visEdit->text();
        subMap[4] = RVREdit->text();
        subMap[5] = weatherEdit->text();
        subMap[6] = cloudHightEdit->text();
        subMap[7] = tempHumEdit->text();
        subMap[8] = pressEdit->text();
        subMap[9] = closeWeatherEdit->text();
        subMap[10] = MOTNEEdit->text();
        subMap[11] = TRENDEdit->text();
        subMap[12] = RemarkEdit->text();
    }
    return  subMap;
}

TrendMetar teleSubDataModCtl::getTrendRequestMetarCtx()
{
    TrendMetar trendMetar;
    trendMetar["head"] = headEdit->text();
    trendMetar["wind"] = windEdit->text();
    trendMetar["vis"] = visEdit->text();
    trendMetar["rvr"] = RVREdit->text();
    trendMetar["pw"] = weatherEdit->text();
    trendMetar["cloud"] = cloudHightEdit->text();
    trendMetar["tempdew"] = tempHumEdit->text();
    trendMetar["press"] = pressEdit->text();
    trendMetar["closedpw"] = closeWeatherEdit->text();
    trendMetar["daomian"] = MOTNEEdit->text();
    trendMetar["trend"] = TRENDEdit->text();
    trendMetar["remak"] = RemarkEdit->text();
    return  trendMetar;
}

void teleSubDataModCtl::_set_user_type(QString _user_type_Str)
{
    _user_type.clear();
    _user_type = _user_type_Str;
}

void teleSubDataModCtl::newAllSubContrls()
{
    headEdit         = new QLineEdit(this);
    windEdit         = new QLineEdit(this);
    visEdit          = new QLineEdit(this);
    RVREdit          = new QLineEdit(this);
    weatherEdit      = new QLineEdit(this);
    cloudHightEdit   = new QLineEdit(this);
    tempHumEdit      = new QLineEdit(this);
    pressEdit        = new QLineEdit(this);
    closeWeatherEdit = new QLineEdit(this);
    RemarkEdit           = new QLineEdit(this);
    MOTNEEdit        = new QLineEdit(this);
    TRENDEdit        = new QLineEdit(this);
}

void teleSubDataModCtl::setAllContrlsOnliyRead()
{
    headEdit->setReadOnly(true);
    windEdit->setReadOnly(true);
    visEdit->setReadOnly(true);
    RVREdit->setReadOnly(true);
    weatherEdit->setReadOnly(true);
    cloudHightEdit->setReadOnly(true);
    tempHumEdit->setReadOnly(true);
    pressEdit->setReadOnly(true);
    closeWeatherEdit->setReadOnly(true);
    RemarkEdit->setReadOnly(true);
    MOTNEEdit->setReadOnly(true);
    TRENDEdit->setReadOnly(true);
}

void teleSubDataModCtl::setAllContrlsGeometry()
{
    int sHeight = height();
    int subHeight = sHeight / 13 - 8;
    int Swidth2 = width()- 138 - 120;
    int xPos = 134;
    headEdit->setGeometry(xPos,sHeight * 1 / 13  + 4 ,Swidth2,subHeight );
    windEdit->setGeometry(xPos,sHeight * 2 / 13  + 4 ,Swidth2,subHeight );
    visEdit->setGeometry(xPos,sHeight * 3 / 13  + 4 ,Swidth2,subHeight );
    RVREdit->setGeometry(xPos,sHeight * 4 / 13  + 4 ,Swidth2,subHeight );
    weatherEdit->setGeometry(xPos,sHeight * 5 / 13  + 4 ,Swidth2,subHeight );
    cloudHightEdit->setGeometry(xPos,sHeight * 6 / 13  + 4 ,Swidth2,subHeight );
    tempHumEdit->setGeometry(xPos,sHeight * 7 / 13  + 4 ,Swidth2,subHeight );
    pressEdit->setGeometry(xPos,sHeight * 8 / 13  + 4 ,Swidth2,subHeight );
    closeWeatherEdit->setGeometry(xPos,sHeight * 9 / 13  + 4 ,Swidth2,subHeight );
    MOTNEEdit->setGeometry(xPos,sHeight * 10 / 13  + 4 ,Swidth2,subHeight );
    TRENDEdit->setGeometry(xPos,sHeight * 11 / 13  + 4 ,Swidth2,subHeight );
    RemarkEdit->setGeometry(xPos,sHeight * 12 / 13  + 4 ,Swidth2,subHeight );
}

void teleSubDataModCtl::initAllEditLineValue()
{
    headEdit->setText(removeFeild(m_MStartVlaue[1]));
    windEdit->setText(removeFeild(m_MStartVlaue[2]));
    visEdit->setText(removeFeild(m_MStartVlaue[3]));
    RVREdit->setText(removeFeild(m_MStartVlaue[4]));
    weatherEdit->setText(removeFeild(m_MStartVlaue[5]));
    cloudHightEdit->setText(removeFeild(m_MStartVlaue[6]));
    tempHumEdit->setText(removeFeild(m_MStartVlaue[7]));
    pressEdit->setText(removeFeild(m_MStartVlaue[8]));
    closeWeatherEdit->setText(removeFeild(m_MStartVlaue[9]));
    MOTNEEdit->setText(removeFeild(m_MStartVlaue[10]));
    TRENDEdit->setText(removeFeild(m_MStartVlaue[11]));
    RemarkEdit->setText(removeFeild(m_MStartVlaue[12]));
}

void teleSubDataModCtl::newAllComboxContrl()
{
    headBox           = new QComboBox(this);
    windBox           = new QComboBox(this);
    visBox            = new QComboBox(this);
    RVRBox            = new QComboBox(this);
    weatherBox        = new QComboBox(this);
    cloudHightBox     = new QComboBox(this);
    tempHumBox        = new QComboBox(this);
    pressBox          = new QComboBox(this);
    closeWeatherBox  = new QComboBox(this);
    WsBox             = new QComboBox(this);
    MOTNEBox          = new QComboBox(this);
    TRENDBox          = new QComboBox(this);
}

void teleSubDataModCtl::setAllComboxContrlsGeometry()
{
    int sHeight = height();
    int subHeight = sHeight / 13 - 8;
    int xPos = width()- 138 - 120 + 134 + 4;
    headBox->setGeometry(xPos,sHeight * 1 / 13+ 4 ,112,subHeight );
    windBox->setGeometry(xPos,sHeight * 2 / 13+ 4 ,112,subHeight );
    visBox->setGeometry(xPos,sHeight * 3 / 13+ 4 ,112,subHeight );
    RVRBox->setGeometry(xPos,sHeight * 4 / 13+ 4 ,112,subHeight );
    weatherBox->setGeometry(xPos,sHeight * 5 / 13+ 4 ,112,subHeight );
    cloudHightBox->setGeometry(xPos,sHeight * 6 / 13+ 4 ,112,subHeight );
    tempHumBox->setGeometry(xPos,sHeight * 7 / 13+ 4 ,112,subHeight );
    pressBox->setGeometry(xPos,sHeight * 8 / 13+ 4 ,112,subHeight );
    closeWeatherBox->setGeometry(xPos,sHeight * 9 / 13+ 4 ,112,subHeight );
    MOTNEBox->setGeometry(xPos,sHeight * 10 / 13+ 4 ,112,subHeight );
    TRENDBox->setGeometry(xPos,sHeight * 11 / 13+ 4 ,112,subHeight );
    WsBox->setGeometry(xPos,sHeight * 12 / 13+ 4 ,112,subHeight );
}

void teleSubDataModCtl::setAllComboxContrlsValue()
{
    for(int i = 1;i < 6;i++){
        if(i < 3){
            headBox->addItem(telegramSubOptions[i]);
            windBox->addItem(telegramSubOptions[i]);
            visBox->addItem(telegramSubOptions[i]);
            RVRBox->addItem(telegramSubOptions[i]);
            weatherBox->addItem(telegramSubOptions[i]);
            cloudHightBox->addItem(telegramSubOptions[i]);
            tempHumBox->addItem(telegramSubOptions[i]);
            pressBox->addItem(telegramSubOptions[i]);
            closeWeatherBox->addItem(telegramSubOptions[i]);
            MOTNEBox->addItem(telegramSubOptions[i]);
            WsBox->addItem(telegramSubOptions[i]);
        }
        TRENDBox->addItem(telegramSubOptions[i]);
    }
}

void teleSubDataModCtl::initComboxConnections()
{
    connect(headBox,SIGNAL(currentTextChanged(QString)),         SLOT(headMetarSlot(QString)));
    connect(windBox,SIGNAL(currentTextChanged(QString)),         SLOT(windMetarSlot(QString)));
    connect(visBox ,SIGNAL(currentTextChanged(QString)),         SLOT(visMetarSlot(QString)));
    connect(RVRBox ,SIGNAL(currentTextChanged(QString)),         SLOT(RVRMetarSlot(QString)));
    connect(weatherBox,SIGNAL(currentTextChanged(QString)),      SLOT(weatherMetarSlot(QString)));
    connect(cloudHightBox,SIGNAL(currentTextChanged(QString)) ,  SLOT(cloudHightMetarSlot(QString)));
    connect(tempHumBox,SIGNAL(currentTextChanged(QString)),      SLOT(tempHumMetarSlot(QString)));
    connect(pressBox,SIGNAL(currentTextChanged(QString)),        SLOT(pressMetarSlot(QString)));
    connect(closeWeatherBox,SIGNAL(currentTextChanged(QString)), SLOT(closWeatherMetarSlot(QString)));
    connect(WsBox,SIGNAL(currentTextChanged(QString)),           SLOT(wsMetarSlot(QString)));
    connect(MOTNEBox,SIGNAL(currentTextChanged(QString)),        SLOT(motneMetarSlot(QString)));
    connect(TRENDBox,SIGNAL(currentTextChanged(QString)),        SLOT(trendMetarSlot(QString)));
}

void teleSubDataModCtl::initItemsValue()
{
    windItemList<<"AUTOMATIC"<<"MANUAL";
    visItemList<<"AUTOMATIC"<<"MANUAL"; ;
    RVRItemList<<"AUTOMATIC"<<"MANUAL"; ;
    weatherItemList<<"AUTOMATIC"<<"MANUAL"; ;
    cloudHightItemList<<"AUTOMATIC"<<"MANUAL"; ;
    tempHumItemList<<"AUTOMATIC"<<"MANUAL"; ;
    pressItemList<<"AUTOMATIC"<<"MANUAL"; ;
    closeWeatherItemList<<"AUTOMATIC"<<"MANUAL"; ;
}

void teleSubDataModCtl::initTelegramSubOptions()
{
    telegramSubOptions[1] = "AUTOMATIC";
    telegramSubOptions[2] = "MANUAL";
    telegramSubOptions[3] = "NOSIG";
    telegramSubOptions[4] = "BECMG";
    telegramSubOptions[5] = "TEMPO";
}

void teleSubDataModCtl::initManualEdit()
{
    headManulEditBool = false;
    windManulEditBool = false;
    visManulEditBool = false;
    RVRManulEditBool = false;
    weatherManulEditBool = false;
    cloudHightManulEditBool = false;
    tempHumManulEditBool = false;
    pressManulEditBool = false;
    closeWeatherManulEditBool = false;
    RemarManulEditBool = false;
    MOTNEManulEditBool = false;
    TRENDManulEditBool = false;
}

QString teleSubDataModCtl::removeFeild(QString str)
{
    QString tempStr = str;
    tempStr = tempStr.replace(":"," ");
    tempStr = tempStr.replace(";","");
    return tempStr;
}

void teleSubDataModCtl::initTeleStartCtx()
{
    m_MStartVlaue[1]  = "ZSOF:140000;Z";
    m_MStartVlaue[2]  = "170;03;MPS:100;V;210";
    m_MStartVlaue[3]  = "9000";//机场能见度值
    m_MStartVlaue[4]  = "2100";//跑道视程
    m_MStartVlaue[5]  = "-RA";
    m_MStartVlaue[6]  = "BKN050";
    m_MStartVlaue[7]  = "24;/;20";
    m_MStartVlaue[8]  = "Q;1007";
    m_MStartVlaue[9]  = "BR";//近时天气
    m_MStartVlaue[10] = "";//道面状况
    m_MStartVlaue[11] = "NOSIG";
    m_MStartVlaue[12] = "";//备注
}

void teleSubDataModCtl::initTeleCodecDeal()
{
    teleCodecDeal = new TelegramCodes(this);
}

void teleSubDataModCtl::initWeather()
{
    m_weatherStr = "NOTData";
}

void teleSubDataModCtl::initCavokChieck()
{
    m_cavokCheick =  false;
}

void teleSubDataModCtl::_init_user_grade_type()
{
    _user_type = "Not User";
}
