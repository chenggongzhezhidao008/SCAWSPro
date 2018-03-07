#include "realtimedata.h"
RealTimeData::RealTimeData(QWidget *parent) :
    QWidget(parent)
{
    initSubTitles();
    initAllDataContrls();
    updateAllContrlsSize();
    initRealNameDataList();
    setAllContrlsReadOnly();
    assignment("initDataMap");
    initLocation("Left");
}
void RealTimeData::setTitleName(QString titleName)
{
    this->m_titleName = titleName;
    update();
}
void RealTimeData::setUpdateTime(QTime updateTime)
{
    this->m_updateTime = updateTime;
    update();
}
void RealTimeData::setRealData(realDataMap realData)
{
    if(assignment("updateValue",realData)){
        setAllContrlsValue();
    }
}
void RealTimeData::setSubNameMap(SerialWarMap subNameList)
{
    this->m_subDataNameList.clear();
    this->m_subDataNameList = subNameList;
    update();
}

void RealTimeData::updateSubName(QString affixstr)
{
   //qDebug()<<"affix:"<<affixstr;
   QStringList affixList;
   QString ctlNamestr,titleStr,completeStr;
   affixList = affixstr.split("/",QString::SkipEmptyParts);
   ctlNamestr = affixList.value(1);
   if(ctlNamestr == ""){
       //qDebug()<<QString("xxx option:%1 return。").arg(affixstr);
       return ;// 第三个字段刻为空字符
   }
   titleStr = affixList.value(0);
   if(ctlNamestr == "windleft"){
       completeStr = m_subDataNameList[1];
       completeStr = completeStr.split(" ",QString::SkipEmptyParts).value(1);
       if(completeStr == titleStr) return;
       m_subDataNameList[1]  = QString("风            %1").arg(titleStr);
       update();
   }
   else if(ctlNamestr == "windmid"){
       return ;
       //暂时不处理
   }
   else if(ctlNamestr == "windright"){
       completeStr = m_subDataNameList[3];
       completeStr = completeStr.split(" ",QString::SkipEmptyParts).value(1);
       if(completeStr == titleStr) return;
       m_subDataNameList[3]  = QString("风            %1").arg(titleStr);
       update();
   }
   else if(ctlNamestr == "HumiTempleft"){
       completeStr = m_subDataNameList[9];
       completeStr = completeStr.split(" ",QString::SkipEmptyParts).value(1);
       if(completeStr == titleStr) return;
       m_subDataNameList[9]  = QString("温度/露点/湿度 %1").arg(titleStr);
       update();
   }
   else if(ctlNamestr == "HumiTempright"){
       completeStr = m_subDataNameList[10];
       completeStr = completeStr.split(" ",QString::SkipEmptyParts).value(1);
       if(completeStr == titleStr) return;
       m_subDataNameList[10]  = QString("温度/露点/湿度 %1").arg(titleStr);
       update();
   }
   else if(ctlNamestr == "rvrleft"){
       completeStr = m_subDataNameList[5];
       completeStr = completeStr.split(" ",QString::SkipEmptyParts).value(1);
       if(completeStr == titleStr) return;
       m_subDataNameList[5]  = QString("跑道视程           %1").arg(titleStr);
       update();
   }
   else if(ctlNamestr == "rvrmid"){
       return;
       //暂时不处理
   }
   else if(ctlNamestr == "rvrright"){
       completeStr = m_subDataNameList[7];
       completeStr = completeStr.split(" ",QString::SkipEmptyParts).value(1);
       if(completeStr == titleStr) return;
       m_subDataNameList[7]  = QString("跑道视程           %1").arg(titleStr);
       update();
   }
   return ;
}
void RealTimeData::updateAllContrlsSize()
{
    int sHeight = height();
    int sWidth = width();
    int left = 100;
    int top = sHeight / 13;
    int subWidth = sWidth - 127;
    int lenWidthOne = subWidth / 5;
    int widthOne = sWidth - 100;
    int lenWidthTwo = subWidth / 6;
    groupLeftAngle->setGeometry(left,top,lenWidthOne - 20,sHeight / 13 - 8);
    groupLeftSpeed1->setGeometry(left + 4 + subWidth  / 5,top,lenWidthOne - 20,sHeight / 13 - 8);
    groupLeftSpeed2->setGeometry(left + 8 + subWidth  * 2 / 5,top,lenWidthOne - 20,sHeight / 13 - 8);
    groupLeftAngleMin->setGeometry(left + 12 + subWidth  * 3 / 5,top,lenWidthOne - 20,sHeight / 13 - 8);
    groupLeftAngleMax->setGeometry(left + 16 + subWidth  * 4 / 5,top,lenWidthOne - 20,sHeight / 13 - 8);

    groupMIDIAngle->setGeometry(left,top + sHeight / 13,lenWidthOne - 20,sHeight / 13 - 8);
    groupMIDISpeed1->setGeometry(left + 4 + subWidth  / 5, top + sHeight / 13,lenWidthOne - 20,sHeight / 13 - 8);
    groupMIDISpeed2->setGeometry(left + 8 + subWidth  * 2 / 5, top + sHeight / 13,lenWidthOne - 20,sHeight / 13 - 8);
    groupMIDIAngleMin->setGeometry(left + 12 + subWidth  * 3 / 5, top + sHeight / 13,lenWidthOne - 20,sHeight / 13 - 8);
    groupMIDIAngleMax->setGeometry(left + 16 + subWidth  * 4 / 5, top + sHeight / 13,lenWidthOne - 20,sHeight / 13 - 8);

    groupRightAngle->setGeometry(left,top +  sHeight * 2 / 13,lenWidthOne - 20,sHeight / 13 - 8);
    groupRightSpeed1->setGeometry(left + 4 + subWidth  / 5, top + sHeight * 2 / 13,lenWidthOne - 20,sHeight / 13 - 8);
    groupRightSpeed2->setGeometry(left + 8 + subWidth  * 2 / 5, top + sHeight * 2 / 13,lenWidthOne - 20,sHeight / 13 - 8);
    groupRightAngleMin->setGeometry(left + 12 + subWidth  * 3 / 5, top + sHeight * 2 / 13,lenWidthOne - 20,sHeight / 13 - 8);
    groupRightAngleMax->setGeometry(left + 16 + subWidth  * 4 / 5, top + sHeight * 2 / 13,lenWidthOne - 20,sHeight / 13 - 8);

    groupVisTenAvg->setGeometry(left + widthOne * 1 / 7 ,top +  sHeight * 3 / 13,widthOne / 7,sHeight / 13 - 8);
    groupVisTenMin->setGeometry(left + widthOne * 3 / 7,top +  sHeight * 3 / 13,widthOne / 7,sHeight / 13 - 8);
    groupVisTenDirection->setGeometry(left + widthOne * 5 / 7,top +  sHeight * 3 / 13,widthOne / 7,sHeight / 13 - 8);

    groupLeftRVRTenAvgValue->setGeometry(left,top +  sHeight * 4 / 13,lenWidthOne,sHeight / 13 - 8);
    groupLeftRVRTendency->setGeometry(left + 4 + subWidth  / 5,top +  sHeight * 4 / 13,lenWidthOne,sHeight / 13 - 8);

    groupMIDIRVRTenAvgValue->setGeometry(left,top +  sHeight * 5 / 13,lenWidthOne,sHeight / 13 - 8);
    groupMIDIRVRTendency->setGeometry(left + 4 + subWidth  / 5,top +  sHeight * 5 / 13,lenWidthOne,sHeight / 13 - 8);

    groupRightRVRTenAvgValue->setGeometry(left,top +  sHeight * 6 / 13,lenWidthOne,sHeight / 13 - 8);
    groupRightRVRTendency->setGeometry(left + 4 + subWidth  / 5,top +  sHeight * 6 / 13,lenWidthOne,sHeight / 13 - 8);

    group1CloudCount->setGeometry(left,top +  sHeight * 7 / 13,lenWidthTwo,sHeight / 13 - 8);
    group1CloudHight->setGeometry(left + 4 + subWidth  / 6,top +  sHeight * 7 / 13,lenWidthTwo,sHeight / 13 - 8);
    group2CloudCount->setGeometry(left + 8 + subWidth  * 2 / 6,top +  sHeight * 7 / 13,lenWidthTwo,sHeight / 13 - 8);
    group2CloudHight->setGeometry(left + 12 + subWidth  * 3 / 6,top +  sHeight * 7 / 13,lenWidthTwo,sHeight / 13 - 8);
    group3CloudCount->setGeometry(left + 16 + subWidth  * 4 / 6,top +  sHeight * 7 / 13,lenWidthTwo,sHeight / 13 - 8);
    group3CloudHight->setGeometry(left + 20 + subWidth  * 5 / 6,top +  sHeight * 7 / 13,lenWidthTwo,sHeight / 13 - 8);

    groupLeftTem->setGeometry(left,top +  sHeight * 8 / 13,lenWidthOne,sHeight / 13 - 8);
    groupLeftDew->setGeometry(left + 4 + subWidth  / 5,top +  sHeight * 8 / 13,lenWidthOne,sHeight / 13 - 8);
    groupLeftHum->setGeometry(left + 8 + subWidth  * 2 / 5,top +  sHeight * 8 / 13,lenWidthOne,sHeight / 13 - 8);
    groupRightTem->setGeometry(left,top +  sHeight * 9 / 13,lenWidthOne,sHeight / 13 - 8);
    groupRightDew->setGeometry(left + 4 + subWidth  / 5,top +  sHeight * 9 / 13,lenWidthOne,sHeight / 13 - 8);
    groupRightHum->setGeometry(left + 8 +  subWidth  * 2 / 5,top +  sHeight * 9 / 13,lenWidthOne,sHeight / 13 - 8);
    groupPress->setGeometry(left,top + sHeight * 10 / 13,lenWidthOne,sHeight / 13 - 8);
    groupCurrentWeather->setGeometry(left + 100 - 10,top +  sHeight * 11 / 13,(sWidth - 100) / 2 - 140,sHeight / 13 - 8);
    groupCloseTimeWeather->setGeometry(left + 100 + (sWidth - 100) / 2 - 60,top +  sHeight * 11 / 13,(sWidth - 100) / 2 - 140,sHeight / 13 - 8);
}
void RealTimeData::initRealNameDataList()
{
    m_dataNameStrList<<"groupLeftAngle"<<
                       "groupLeftSpeed1"<<
                       "groupLeftSpeed2"<<
                       "groupLeftAngleMin"<<
                       "groupLeftAngleMax"<<
                       "groupLeftSHSpeed"<<
                       "groupMIDIAngle"<<
                       "groupMIDISpeed1"<<
                       "groupMIDISpeed2"<<
                       "groupMIDIAngleMin"<<
                       "groupMIDIAngleMax"<<
                       "groupMIDISHSpeed"<<
                       "groupRightAngle"<<
                       "groupRightSpeed1"<<
                       "groupRightSpeed2"<<
                       "groupRightAngleMin"<<
                       "groupRightAngleMax"<<
                       "groupRightSHSpeed"<<
                       "groupVisRowVis"<<
                       "groupVisSensor_vis10m"<<
                       "groupVisTenMin"<<
                       "groupVisTenAvg"<<
                       "groupVisTenDirection"<<
                       "groupLeftRVRTenAvgValue"<<
                       "groupLeftRVRTenMaxValue"<<
                       "groupLeftRVRTenMinValue"<<
                       "groupLeftRVRTendency"<<
                       "groupMIDIRVRTenAvgValue"<<
                       "groupMIDRVRTenMaxValue"<<
                       "groupMIDRVRTenMinValue"<<
                       "groupMIDIRVRTendency"<<
                       "groupRightRVRTenAvgValue"<<
                       "groupRightRVRTenMaxValue"<<
                       "groupRightRVRTenMinValue"<<
                       "groupRightRVRTendency"<<
                       "groupLeft1CloudCount"<<
                       "groupLeft1CloudHight"<<
                       "groupLeft2CloudCount"<<
                       "groupLeft2CloudHight"<<
                       "groupLeft3CloudCount"<<
                       "groupLeft3CloudHight"<<
                       "groupLeftIsSkyClear"<<
                       "groupLeftIsVerVis"<<
                       "groupLeftCloudBase"<<
                       "groupRight1CloudCount"<<
                       "groupRight1CloudHight"<<
                       "groupRight2CloudCount"<<
                       "groupRight2CloudHight"<<
                       "groupRight3CloudCount"<<
                       "groupRight3CloudHight"<<
                       "groupRightIsSkyClear"<<
                       "groupRightIsVerVis"<<
                       "groupRightCloudBase"<<
                       "groupLeftTem"<<
                       "groupLeftDew"<<
                       "groupLeftHum"<<
                       "groupRightTem"<<
                       "groupRightDew"<<
                       "groupRightHum"<<
                       "groupPress"<<
                       "groupCurrentWeather"<<
                       "groupCloseTimeWeather";
    return ;
}
bool RealTimeData::assignment(QString option,realDataMap newDataMap)
{
    bool updateFlag = false;
    int number = m_dataNameStrList.length();
    if(option == "initDataMap"){
        for(int index = 0;index < number;index++){
            m_realDataMap[m_dataNameStrList.value(index)] = "      " ;
        }
        return true;
    }
    else if(option == "updateValue"){
        QString valueName;
        for(int index = 0;index < number;index++){
            valueName = m_dataNameStrList.value(index);
            if(m_realDataMap[valueName] != newDataMap[valueName]){
                m_realDataMap[valueName] = newDataMap[valueName];
                updateFlag = true;
            }
        }
    }
    else{
        ;
    }
    return updateFlag;
}
void RealTimeData::initAllDataContrls()
{
    groupLeftAngle             = new QLineEdit(this);
    groupLeftSpeed1            = new QLineEdit(this);
    groupLeftSpeed2            = new QLineEdit(this);
    groupLeftAngleMin          = new QLineEdit(this);
    groupLeftAngleMax          = new QLineEdit(this);
    groupMIDIAngle             = new QLineEdit(this);
    groupMIDISpeed1            = new QLineEdit(this);
    groupMIDISpeed2            = new QLineEdit(this);
    groupMIDIAngleMin          = new QLineEdit(this);
    groupMIDIAngleMax          = new QLineEdit(this);
    groupRightAngle            = new QLineEdit(this);
    groupRightSpeed1           = new QLineEdit(this);
    groupRightSpeed2           = new QLineEdit(this);
    groupRightAngleMin         = new QLineEdit(this);
    groupRightAngleMax         = new QLineEdit(this);
    groupVisTenAvg             = new QLineEdit(this);
    groupVisTenMin             = new QLineEdit(this);
    groupVisTenDirection       = new QLineEdit(this);
    groupLeftRVRTenAvgValue    = new QLineEdit(this);
    groupLeftRVRTendency       = new QLineEdit(this);
    groupMIDIRVRTenAvgValue    = new QLineEdit(this);
    groupMIDIRVRTendency       = new QLineEdit(this);
    groupRightRVRTenAvgValue   = new QLineEdit(this);
    groupRightRVRTendency      = new QLineEdit(this);
    group1CloudCount           = new QLineEdit(this);
    group1CloudHight           = new QLineEdit(this);
    group2CloudCount           = new QLineEdit(this);
    group2CloudHight           = new QLineEdit(this);
    group3CloudCount           = new QLineEdit(this);
    group3CloudHight           = new QLineEdit(this);
    groupLeftTem               = new QLineEdit(this);
    groupLeftDew               = new QLineEdit(this);
    groupLeftHum               = new QLineEdit(this);
    groupRightTem              = new QLineEdit(this);
    groupRightDew              = new QLineEdit(this);
    groupRightHum              = new QLineEdit(this);
    groupPress                 = new QLineEdit(this);
    groupCurrentWeather       = new QLineEdit(this);
    groupCloseTimeWeather     = new QLineEdit(this);
}
void RealTimeData::setAllContrlsReadOnly()
{
    groupLeftAngle->setReadOnly(true);
    groupLeftSpeed1->setReadOnly(true);
    groupLeftSpeed2->setReadOnly(true);
    groupLeftAngleMin->setReadOnly(true);
    groupLeftAngleMax->setReadOnly(true);
    groupMIDIAngle->setReadOnly(true);
    groupMIDISpeed1->setReadOnly(true);
    groupMIDISpeed2->setReadOnly(true);
    groupMIDIAngleMin->setReadOnly(true);
    groupMIDIAngleMax->setReadOnly(true);
    groupRightAngle->setReadOnly(true);
    groupRightSpeed1->setReadOnly(true);
    groupRightSpeed2->setReadOnly(true);
    groupRightAngleMin->setReadOnly(true);
    groupRightAngleMax->setReadOnly(true);
    groupVisTenAvg->setReadOnly(true);
    groupVisTenMin->setReadOnly(true);
    groupVisTenDirection->setReadOnly(true);
    groupLeftRVRTenAvgValue->setReadOnly(true);
    groupLeftRVRTendency->setReadOnly(true);
    groupMIDIRVRTenAvgValue->setReadOnly(true);
    groupMIDIRVRTendency->setReadOnly(true);
    groupRightRVRTenAvgValue->setReadOnly(true);
    groupRightRVRTendency->setReadOnly(true);
    group1CloudCount->setReadOnly(true);
    group1CloudHight->setReadOnly(true);
    group2CloudCount->setReadOnly(true);
    group2CloudHight->setReadOnly(true);
    group3CloudCount->setReadOnly(true);
    group3CloudHight->setReadOnly(true);
    groupLeftTem->setReadOnly(true);
    groupLeftDew->setReadOnly(true);
    groupLeftHum->setReadOnly(true);
    groupRightTem->setReadOnly(true);
    groupRightDew->setReadOnly(true);
    groupRightHum->setReadOnly(true);
    groupPress->setReadOnly(true);
    groupCurrentWeather->setReadOnly(true);
    groupCloseTimeWeather->setReadOnly(true);
}
void RealTimeData::setAllContrlsValue()
{
    groupLeftAngle->setText(m_realDataMap["groupLeftAngle"]);
    groupLeftSpeed1->setText(m_realDataMap["groupLeftSpeed1"]);
    groupLeftSpeed2->setText(m_realDataMap["groupLeftSpeed2"]);
    groupLeftAngleMin->setText(m_realDataMap["groupLeftAngleMin"]);
    groupLeftAngleMax->setText(m_realDataMap["groupLeftAngleMax"]);

    groupMIDIAngle->setText(m_realDataMap["groupMIDIAngle"]);
    groupMIDISpeed1->setText(m_realDataMap["groupMIDISpeed1"]);
    groupMIDISpeed2->setText(m_realDataMap["groupMIDISpeed2"]);
    groupMIDIAngleMin->setText(m_realDataMap["groupMIDIAngleMin"]);
    groupMIDIAngleMax->setText(m_realDataMap["groupMIDIAngleMax"]);

    groupRightAngle->setText(m_realDataMap["groupRightAngle"]);
    groupRightSpeed1->setText(m_realDataMap["groupRightSpeed1"]);
    groupRightSpeed2->setText(m_realDataMap["groupRightSpeed2"]);
    groupRightAngleMin->setText(m_realDataMap["groupRightAngleMin"]);
    groupRightAngleMax->setText(m_realDataMap["groupRightAngleMax"]);

    groupVisTenAvg->setText(m_realDataMap["groupVisTenAvg"]);
    groupVisTenMin->setText(m_realDataMap["groupVisTenMin"]);
    groupVisTenDirection->setText(m_realDataMap["groupVisTenDirection"]);

    groupLeftRVRTenAvgValue->setText(m_realDataMap["groupLeftRVRTenAvgValue"]);
    groupLeftRVRTendency->setText(m_realDataMap["groupLeftRVRTendency"]);
    groupMIDIRVRTenAvgValue->setText(m_realDataMap["groupMIDIRVRTenAvgValue"]);
    groupMIDIRVRTendency->setText(m_realDataMap["groupMIDIRVRTendency"]);
    groupRightRVRTenAvgValue->setText(m_realDataMap["groupRightRVRTenAvgValue"]);
    groupRightRVRTendency->setText(m_realDataMap["groupRightRVRTendency"]);

    if(cloudLoca == "Left"){
        group1CloudCount->setText(m_realDataMap["groupLeft1CloudCount"]);
        group1CloudHight->setText(m_realDataMap["groupLeft1CloudHight"]);
        group2CloudCount->setText(m_realDataMap["groupLeft2CloudCount"]);
        group2CloudHight->setText(m_realDataMap["groupLeft2CloudHight"]);
        group3CloudCount->setText(m_realDataMap["groupLeft3CloudCount"]);
        group3CloudHight->setText(m_realDataMap["groupLeft3CloudHight"]);

    }
    else if(cloudLoca == "Right"){
        group1CloudCount->setText(m_realDataMap["groupRight1CloudCount"]);
        group1CloudHight->setText(m_realDataMap["groupRight1CloudHight"]);
        group2CloudCount->setText(m_realDataMap["groupRight2CloudCount"]);
        group2CloudHight->setText(m_realDataMap["groupRight2CloudHight"]);
        group3CloudCount->setText(m_realDataMap["groupRight3CloudCount"]);
        group3CloudHight->setText(m_realDataMap["groupRight3CloudHight"]);
    }
    else{
        ;
    }

    groupLeftTem->setText(m_realDataMap["groupLeftTem"]);
    groupLeftDew->setText(m_realDataMap["groupLeftDew"]);
    groupLeftHum->setText(m_realDataMap["groupLeftHum"]);

    groupRightTem->setText(m_realDataMap["groupRightTem"]);
    groupRightDew->setText(m_realDataMap["groupRightDew"]);
    groupRightHum->setText(m_realDataMap["groupRightHum"]);

    groupPress->setText(m_realDataMap["groupPress"]);

    groupCurrentWeather->setText(m_realDataMap["groupCurrentWeather"]);
    groupCloseTimeWeather->setText(m_realDataMap["groupCloseTimeWeather"]);
    _m_init_update_time();
}

void RealTimeData::initSubTitles()
{
    m_subDataNameList[1]  = "风            06";
    m_subDataNameList[2]  = "风          MIDI";
    m_subDataNameList[3]  = "风            24";
    m_subDataNameList[4]  = "能见度              AD";
    m_subDataNameList[5]  = "跑道视程           06";
    m_subDataNameList[6]  = "跑道视程       MIDI";
    m_subDataNameList[7]  = "跑道视程           24";
    m_subDataNameList[8]  = "云量云高           AD";
    m_subDataNameList[9]  = "温度/露点/湿度 06";
    m_subDataNameList[10] = "温度/露点/湿度 24";
    m_subDataNameList[11] = "修正海压           AD";
    m_subDataNameList[12] = "现在天气           AD";
}

void RealTimeData::_m_init_update_time()
{
    m_upd_t = QTime::currentTime().toString("hh:mm:ss");
}

void RealTimeData::initLocation(QString loca)
{
   cloudLoca = loca;
   setAllContrlsValue();
}
