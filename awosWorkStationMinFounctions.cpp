#include "awosworkstationmin.h"
#include "ui_workstation.h"

// affixOption 组成 分类字符串：combox显示名称 / 具体对应于系统的实时控件或者值名称
void WorkStation::setTelegramReportValuesSlot(realDataMap datamap,QString affixOption)
{
    //updateWeatherSelect:33
    QString comboxAffixStr,realDataAffStr;
    realDataAffStr = affixOption.split(":",QString::SkipEmptyParts).value(1);
    comboxAffixStr = affixOption.split("/",QString::SkipEmptyParts).value(0);
    //系统数据控件
    if(realDataAffStr != ""){
        _metar_Realdata_contrl->updateSubName(realDataAffStr);
        _spaci_Realdata_contrl->updateSubName(realDataAffStr);
        _metar_Report_Realdata_contrl->updateSubName(realDataAffStr);
        _spacial_Report_Realdata_contrl->updateSubName(realDataAffStr);
    }
    _metar_Realdata_contrl->setRealData(datamap);
    _spaci_Realdata_contrl->setRealData(datamap);
    _metar_Report_Realdata_contrl->setRealData(datamap);
    _spacial_Report_Realdata_contrl->setRealData(datamap);
    //编报控件
    if(comboxAffixStr != ""){
        MetarEcodecContrl->ComboxCtlsSelecetSlot(comboxAffixStr);
        MetarReportEcodecContrl->ComboxCtlsSelecetSlot(comboxAffixStr);
        SpaciEcodecContrl->ComboxCtlsSelecetSlot(comboxAffixStr);
        SpaciReportEcodecContrl->ComboxCtlsSelecetSlot(comboxAffixStr);
        teleCFG->_m_update_ctrl_item(comboxAffixStr);
    }
}

void WorkStation::telegramAskSubSlot(SensorMap /*telegramData*/)
{
    if(!popVec.isEmpty()){
        int len = popVec.length();
        for(int n = 0;n < len; n++){
            popVec.value(n)->close();
            disconnect(popVec.value(n),SIGNAL(popTelegramSendSignal(TelegramCtx)),this,
                       SLOT(popTelegramSendSlot(TelegramCtx)));
            delete popVec.value(n);
        }
        popVec.clear();
    }

    // 更新界面子报数据
    automaticMetarTelegramData();

    // 设置弹出窗口数据
    TelegramPop *pop = new TelegramPop();
    connect(pop,SIGNAL(popTelegramSendSignal(TelegramCtx)),this,
            SLOT(popTelegramSendSlot(TelegramCtx)));
    pop->setGeometry(200,300,800,200);
    pop->show();
    pop->setCtxMap(MetarEcodecContrl->getTelegramCtx());    //设置电报内容
    popVec.push_back(pop);
    qDebug()<<"请求电报";
}

/* -----------------------
 * function descriptions
 * 用于弹出窗口的发送METAR报的趋势请求报。
 * -----------------------
 */
void WorkStation::popTelegramSendSlot(TelegramCtx Ctx)
{
    metarContextMap.clear();
    metarContextMap = Ctx;
    metCodeShow();
    //   if(metarSenAddresses->text().trimmed() == ""){
    //       QMessageBox::warning(this,"告警提示","电报发送地址不能为空！");
    //       return;
    //   }
    sendMetar(); // 需要改正
    return ;
}

void WorkStation::telegramShowSubSlot(SensorMap /*telegramData*/)
{
    qDebug()<<"显示收报";
}

/*  -----------------------------
 *  function description
 *  获取实时数据生成各条Metar报内容。
 *
 *  -----------------------------
 */
void WorkStation::automaticMetarTelegramData()
{
    realDataMap metarRealdata;
    metarRealdata = _metar_Realdata_contrl->getrealData();
    MetarEcodecContrl->updateSubTelegramCtx(metarRealdata);
}


/*  -----------------------------
 *  function description
 *  获取实时数据生成各条Speci报内容。
 *
 *  -----------------------------
 */
void WorkStation::automaticSpaciTelegramData()
{
    realDataMap speciRealdata;
    speciRealdata = _spaci_Realdata_contrl->getrealData();
    SpaciEcodecContrl->updateSubTelegramCtx(speciRealdata);
}


/*  -----------------------------
 *  function description
 *  获取实时数据生成各条Metar Report报内容。
 *
 *  -----------------------------
 */
void WorkStation::snedReportMetarTelegramData()
{
    realDataMap metarReportRealData;
    metarReportRealData = _metar_Realdata_contrl->getrealData();
    MetarReportEcodecContrl->updateSubTelegramCtx(metarReportRealData);
}

/*  -----------------------------
 *  function description
 *  获取实时数据生成各条Speci Report报内容。
 *
 *  -----------------------------
 */
void WorkStation::snedReportSpaciTelegramData()
{
    realDataMap speciReportRealData;
    speciReportRealData = _metar_Realdata_contrl->getrealData();
    SpaciReportEcodecContrl->updateSubTelegramCtx(speciReportRealData);
}

/*  -----------------------------
 *  function description
 *  获取实时数据生成各条Metar Report报内容。
 *
 *  -----------------------------
 */
void WorkStation::updateMetarReport()
{
    QString telegramCtx = MetarReportTranslateContext(getMetarReportControlsText());
    MetarReportTelegramContextUI->setTelegramContextStr(telegramCtx);
}

void WorkStation::updateSpaciReport()
{
    QString telegramCtx = SpaciReportTranslateContext(getMetarReportControlsText());
    SpaciReportTelegramContextUI->setTelegramContextStr(telegramCtx);
}

void WorkStation::metarReportsender(QString ctx)
{
    qDebug()<<"Metar Report Context:"<<ctx;
}

void WorkStation::spaciReportsender(QString ctx)
{
    qDebug()<<"Spaci Report Context:"<<ctx;
}

void WorkStation::dusSupplyModlesSlot(SensorMap dataMap)
{
    DataMap data;
    SerialMap modulesMap;
    data = dataMap["DUSData"];
    statue->setDeveice3616ID(data["DUSID"].trimmed().toInt());
    int len = data.count();
    modulesMap[1] = "VRAOS";
    for(int n = 2;n <= len;n++){
        modulesMap[n] = data["Libname"+QString("%1").arg(n - 1)];
    }
    statue->setModleNameList(modulesMap);
    //qDebug()<<"MODULE cccccccc:"<<dataMap;
}

void WorkStation::allSensorsInformationSlot(SensorMap dataMap)
{
    DataMap data;
    SerialMap sensorMap;
    data = dataMap["sensorsData"];
    statue->setDeveice3616ID(data["DUSID"].trimmed().toInt());
    int len = data.count();
    QString str ;
    for(int n = 1;n <= len;n++){
        str = data["CARD"+QString("%1").arg(n)];
        if(str != "NULL"){
            sensorMap[n] = str;
        }
        else{
            sensorMap[n] = "";
        }
    }
    statue->setSensorsNameMap(sensorMap);
    //qDebug()<<"SENSORS cccccccc:"<<sensorMap;
}

void WorkStation::setQNFValue(QString value)
{
    QString tempValue;
    tempValue = value.split(".").value(0).trimmed();
    int len;
    len = tempValue.length();
    if(len == 1){
        tempValue = QString("000%1").arg(tempValue);
    }
    if(len == 2){
        tempValue = QString("00%1").arg(tempValue);
    }
    if(len == 3){
        tempValue = QString("0%1").arg(tempValue);
    }
    this->m_qnf = tempValue;
    update();
}

void WorkStation::setTreandMetar(QString trend)
{
    MetarEcodecContrl->updateSubTelegramTrendCtx(trend);
    updateMetar();
    qDebug()<<"收到预报员编写得趋势报内容:"<<trend;
}

void WorkStation::_set_user_typeStr(QString type)
{
    _m_user_type.clear();
    _m_user_type = type;
    MetarEcodecContrl->_set_user_type(type);
}


// 设置跑道数据
void WorkStation::set_runWays_setting(QSettings *&runwayInfor)
{
    m_runwayInfor = runwayInfor;
    qDebug()<<"list settings1:"<<m_runwayInfor->allKeys();
    locaCFG->runWays_setting_config(m_runwayInfor);
}

// 设置再用跑道传感器数据
void WorkStation::set_usedWay_setting(QSettings *&usedRunWay)
{
    m_usedRunWay = usedRunWay;
    qDebug()<<"list settings2:"<<m_usedRunWay->allKeys();
    locaCFG->usedWay_setting_config(m_usedRunWay);
}

// 设能用的传感器
void WorkStation::set_sensors_setting(QSettings *&sensor)
{
    m_sensor = sensor;
    qDebug()<<"list settings3:"<<m_sensor->allKeys();
}

// 设置电报使用的传感器的数据
void WorkStation::set_telegram_setting(QSettings *&telegramSensor)
{
    m_telegramSensor = telegramSensor;
    qDebug()<<"list settings4:"<<m_telegramSensor->allKeys();
    teleCFG->telegram_setting_config(m_telegramSensor);
}

void WorkStation::functionSelectDo(int count, int index)
{
    for(int i = 1; i<= count;i++){
        if(i == index){
            funcMap[i] = true;
        }
        else{
            funcMap[i] = false;
        }
    }

    // 外部传感器开关控件
    if(index == 1){
        emit openOrClosedContrls(true);
    }
    else{
        emit openOrClosedContrls(false);
    }
    //qDebug()<<"function do:"<<funcMap;
}

void WorkStation::metarSelectDo(int count, int index)
{
    for(int i = 1; i<= count;i++){
        if(i == index){
            m_metar[i] = true;
        }
        else{
            m_metar[i] = false;
        }
    }
    //qDebug()<<"metar do:"<<m_metar;
}

void WorkStation::configSelectDo(int count, int index)
{
    for(int i = 1; i<= count;i++){
        if(i == index){
            m_configPage[i] = true;
        }
        else{
            m_configPage[i] = false;
        }
    }
    //qDebug()<<"metar do:"<<m_metar;
}

void WorkStation::oneSecondUpdate()
{
    update();
}


