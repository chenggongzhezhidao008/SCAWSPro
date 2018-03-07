#include "telegramsubdatamodifitycontrl.h"

telegramSubDataModifityContrl::telegramSubDataModifityContrl(QWidget *parent) :
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
}

void telegramSubDataModifityContrl::initTelegramnLable()
{
    telegramLabelName[1]  = "报头 [CCCC YYGGggZ]";
    telegramLabelName[2]  = "风             [WIND]";
    telegramLabelName[3]  = "机场能见度值      [VVVV]";
    telegramLabelName[4]  = "跑道视程                RVR]";
    telegramLabelName[5]  = "现在天气             [W`W`]";
    telegramLabelName[6]  = "云量云高         [CLOUD]";
    telegramLabelName[7]  = "温度湿度               [T/Td]";
    telegramLabelName[8]  = "修正海压              [QNH]";
    telegramLabelName[9]  = "近时天气         [REw`w`]";
    telegramLabelName[10] = "道面状况         [MOTNE]";
    telegramLabelName[11] = "趋势报             [TREND]";
    telegramLabelName[12] = "备注                 [REMAK]";
}
void telegramSubDataModifityContrl::setTelegramName(QString telegramName)
{
    this->m_telegramName = telegramName;
    update();
}

void telegramSubDataModifityContrl::setUpdateTime(QTime updateTime)
{
    this->m_updateTime = updateTime;
    update();
}

void telegramSubDataModifityContrl::setToSendTelegramHaveTime(QString toSendTelegramHaveTime)
{
    this->m_haveTime = toSendTelegramHaveTime;
    update();
}

void telegramSubDataModifityContrl::setEncodeTelegramStyle(bool encodcStyle)
{
    this->m_encodTelegramStyle = encodcStyle;
}

void telegramSubDataModifityContrl::headMetarSlot(QString str)
{
    metarOptionSelet("head",str);
    qDebug()<<"ssss ddddd ffff";
}

void telegramSubDataModifityContrl::windMetarSlot(QString str)
{
    metarOptionSelet("wind",str);
}

void telegramSubDataModifityContrl::visMetarSlot(QString str)
{
    metarOptionSelet("vis",str);
}

void telegramSubDataModifityContrl::RVRMetarSlot(QString str)
{
    metarOptionSelet("rvr",str);
}

void telegramSubDataModifityContrl::weatherMetarSlot(QString str)
{
    metarOptionSelet("weath",str);
}

void telegramSubDataModifityContrl::cloudHightMetarSlot(QString str)
{
    metarOptionSelet("cloud",str);
}

void telegramSubDataModifityContrl::tempHumMetarSlot(QString str)
{
    metarOptionSelet("tempHum",str);
}

void telegramSubDataModifityContrl::pressMetarSlot(QString str)
{
    metarOptionSelet("press",str);
}

void telegramSubDataModifityContrl::closWeatherMetarSlot(QString str)
{
    metarOptionSelet("closeWeather",str);
}

void telegramSubDataModifityContrl::wsMetarSlot(QString str)
{
    metarOptionSelet("ws",str);
}

void telegramSubDataModifityContrl::motneMetarSlot(QString str)
{
    metarOptionSelet("motne",str);
}

void telegramSubDataModifityContrl::trendMetarSlot(QString str)
{
    metarOptionSelet("trend",str);
}

void telegramSubDataModifityContrl::metarOptionSelet(QString nameStr, QString optionStr)
{
    bool openManual;
    if(optionStr == "AUTOMATIC"){
        qDebug()<<"automatic";
        openManual = false;
    }
    else if(optionStr == "MANUAL"){
        openManual = true;
    }
    else if(true){
        openManual = false;
        qDebug()<<"unknown one";
    }
    else{
        openManual = false;
        qDebug()<<"unknown";
    }

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
        WsManulEditBool = openManual;
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

    // call many one second please check codec

    //    qDebug()<<"Manul edit:"<<
    //              "headManulEditBool"<<            headManulEditBool<<
    //              "windManulEditBool"<<            windManulEditBool<<
    //              "visManulEditBool"<<             visManulEditBool<<
    //              "RVRManulEditBool"<<             RVRManulEditBool<<
    //              "weatherManulEditBool"<<         weatherManulEditBool<<
    //              "cloudHightManulEditBool"<<      cloudHightManulEditBool<<
    //              "tempHumManulEditBool"<<         tempHumManulEditBool<<
    //              "pressManulEditBool"<<           pressManulEditBool<<
    //              "closeWeatherManulEditBool"<<    closeWeatherManulEditBool<<
    //              "WsManulEditBool"<<              WsManulEditBool<<
    //              "MOTNEManulEditBool"<<           MOTNEManulEditBool<<
    //              "TRENDManulEditBool"<<            TRENDManulEditBool;
}

void telegramSubDataModifityContrl::updateSubTelegramCtx(realDataMap systemTelegramTtx)
{
    QString valueStr;
    if(m_encodTelegramStyle){
        if(headManulEditBool){
            headEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");
        }
        else{
            valueStr.clear();
            valueStr = "ZGHA " + QDateTime::currentDateTimeUtc().toString("ddhhmm") + "Z";
            if(!valueStr.isEmpty()){
                headEdit->setText(valueStr);
            }
        }
        if(windManulEditBool){
            windEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");

        }
        else{
            valueStr.clear();
            valueStr = systemTelegramTtx["groupLeftAngle"].trimmed().split(" ").value(0);/*groupLeftAngle->text()*/
            valueStr = valueStr + systemTelegramTtx["groupLeftSpeed1"].trimmed().split(" ").value(0) + "MPS";/*groupLeftSpeed1->text()*/
            //            valueStr = valueStr + groupLeftSpeed2 //待处理此处
            valueStr = valueStr + " " + systemTelegramTtx["groupLeftAngleMin"].trimmed().split(" ").value(0);/*groupLeftAngleMin->text()*/
            valueStr = valueStr + "V" + systemTelegramTtx["groupLeftAngleMax"].trimmed().split(" ").value(0);/*groupLeftAngleMax->text()*/
            if(!valueStr.isEmpty()){
                windEdit->setText(valueStr);
            }
        }
        if(visManulEditBool){
            visEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");

        }
        else{
            //     visEdit->setText();
        }
        if(RVRManulEditBool){
            RVREdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");

        }
        else{
            valueStr.clear();/*groupLeftRVRTenAvgValue->text()*/
            valueStr = systemTelegramTtx["groupLeftRVRTenAvgValue"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
            if(!valueStr.isEmpty()){
                RVREdit->setText(valueStr);
            }
        }
        if(weatherManulEditBool){
            weatherEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");

        }
        else{
            //            weatherEdit->setText();
        }
        if(cloudHightManulEditBool){
            cloudHightEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");

        }
        else{
            //            cloudHightEdit->setText();
        }
        if(tempHumManulEditBool){
            tempHumEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");

        }
        else{
            valueStr.clear();/*groupLeftTem->text()*//*groupLeftHum->text()*/
            valueStr = systemTelegramTtx["groupLeftTem"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
            valueStr = valueStr + "/" + systemTelegramTtx["groupLeftHum"].trimmed().split(" ",QString::SkipEmptyParts).value(0);
            if(!valueStr.isEmpty()){
                tempHumEdit->setText(valueStr);
            }
        }
        if(pressManulEditBool){
            pressEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");

        }
        else{
            //            pressEdit->setText();
        }
        if(closeWeatherManulEditBool){
            closeWeatherEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");

        }
        else{
            //            closeWeatherEdit->setText();
        }
        if(MOTNEManulEditBool){
            MOTNEEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");

        }
        else{
            //            MOTNEEdit->setText();
        }
        if(TRENDManulEditBool){
            TRENDEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");

        }
        else{
            //            TRENDEdit->setText();
        }
        if(WsManulEditBool){
            RemarkEdit->setStyleSheet("QLineEdit{background-color:#F0F8FF;color:balck;border-width:1;border-color:red;border-style:outset}");

        }
        else{
            //            RemarkEdit->setText();
        }
    }
    else{
        QMessageBox::warning(this,"信息提示！","请手动编发一份METAR报并发送");
    }
}

SerialWarMap telegramSubDataModifityContrl::getTelegramCtx()
{
    SerialWarMap  subMap;

    // 2 . 从界面的各个控件中取值更新
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

    return  subMap;
}

void telegramSubDataModifityContrl::newAllSubContrls()
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

void telegramSubDataModifityContrl::setAllContrlsOnliyRead()
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

void telegramSubDataModifityContrl::setAllContrlsGeometry()
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

void telegramSubDataModifityContrl::initAllEditLineValue()
{
    headEdit->setText(removeFeild(m_telegramStartContextValue[1]));
    windEdit->setText(removeFeild(m_telegramStartContextValue[2]));
    visEdit->setText(removeFeild(m_telegramStartContextValue[3]));
    RVREdit->setText(removeFeild(m_telegramStartContextValue[4]));
    weatherEdit->setText(removeFeild(m_telegramStartContextValue[5]));
    cloudHightEdit->setText(removeFeild(m_telegramStartContextValue[6]));
    tempHumEdit->setText(removeFeild(m_telegramStartContextValue[7]));
    pressEdit->setText(removeFeild(m_telegramStartContextValue[8]));
    closeWeatherEdit->setText(removeFeild(m_telegramStartContextValue[9]));
    MOTNEEdit->setText(removeFeild(m_telegramStartContextValue[10]));
    TRENDEdit->setText(removeFeild(m_telegramStartContextValue[11]));
    RemarkEdit->setText(removeFeild(m_telegramStartContextValue[12]));
}

void telegramSubDataModifityContrl::newAllComboxContrl()
{
    headBox         = new QComboBox(this);
    windBox         = new QComboBox(this);
    visBox          = new QComboBox(this);
    RVRBox          = new QComboBox(this);
    weatherBox      = new QComboBox(this);
    cloudHightBox   = new QComboBox(this);
    tempHumBox      = new QComboBox(this);
    pressBox        = new QComboBox(this);
    closeWeatherBox = new QComboBox(this);
    WsBox           = new QComboBox(this);
    MOTNEBox        = new QComboBox(this);
    TRENDBox        = new QComboBox(this);
}

//void telegramSubDataModifityContrl::installAllComboxContrls()
//{

//}

void telegramSubDataModifityContrl::setAllComboxContrlsGeometry()
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

void telegramSubDataModifityContrl::setAllComboxContrlsValue()
{
    for(int i = 1;i < 6;i++){
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
        TRENDBox->addItem(telegramSubOptions[i]);
    }
    WsBox->addItem("MANUAL"/*telegramSubOptions[i]*/);
}

void telegramSubDataModifityContrl::initComboxConnections()
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

void telegramSubDataModifityContrl::initTelegramSubOptions()
{
    telegramSubOptions[1] = "AUTOMATIC";
    telegramSubOptions[2] = "MANUAL";
    telegramSubOptions[3] = "NOSIG";
    telegramSubOptions[4] = "BECMG";
    telegramSubOptions[5] = "TEMPO";
}

void telegramSubDataModifityContrl::initManualEdit()
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
    WsManulEditBool = false;
    MOTNEManulEditBool = false;
    TRENDManulEditBool = false;
}

QString telegramSubDataModifityContrl::removeFeild(QString str)
{
    QString tempStr = str;
    tempStr = tempStr.replace(":"," ");
    tempStr = tempStr.replace(";","");
    return tempStr;
}

void telegramSubDataModifityContrl::initTeleStartCtx()
{
    m_telegramStartContextValue[1]  = "ZGHA:140000;Z";
    m_telegramStartContextValue[2]  = "170;03;MPS:100;V;210";
    m_telegramStartContextValue[3]  = "9000";//机场能见度值
    m_telegramStartContextValue[4]  = "";//跑道视程
    m_telegramStartContextValue[5]  = "-RA";
    m_telegramStartContextValue[6]  = "BKN050";
    m_telegramStartContextValue[7]  = "24;/;20";
    m_telegramStartContextValue[8]  = "Q;1007";
    m_telegramStartContextValue[9]  = "";//近时天气
    m_telegramStartContextValue[10] = "";//道面状况
    m_telegramStartContextValue[11] = "NOSIG";
    m_telegramStartContextValue[12] = "";//备注
}
