#include "awosstartsetup.h"
#include <QPropertyAnimation>
#include <QStringList>
#include <QVariantList>
#include <QMetaObject>
#include <QMetaMethod>
#include <QMetaClassInfo>
#include <QObject>
#include <QApplication>

//test
typedef QString DataName;
typedef QString DataValue;
typedef QMap<DataName,DataValue> DataContext;
//test.....

void AwosStartSetup::awosWindData(SensorMap senMap)
{
    //DataMap headmap = senMap["windHead"];
    //qDebug()<<"SC WindHead:"<<headmap;
    DataMap bodymap = senMap["windData"];
    //qDebug()<<"SC WindBody:"<<bodymap;

    int airportId  = bodymap["AirPortID"].toInt();
    int runwayId = bodymap["RunWayID"].toInt();
    int windId = (bodymap["WindID"]).toInt();

    //  wind rose find
    int controlNum = proData->awosDataModel->inUsedWay
            ->roseAreaList.length();
    bool findResult = false;
    QString namestr,affixStr;
    for(int num = 0; num < controlNum;num++){
        int comAirportId = proData->awosDataModel->inUsedWay
                ->roseAreaList.value(num)->airportId();
        int comRunWayId = proData->awosDataModel->inUsedWay
                ->roseAreaList.value(num)->runWayId();
        int comWindId = proData->awosDataModel->inUsedWay
                ->roseAreaList.value(num)->windId();
        QString locaStr = proData->awosDataModel->inUsedWay
                ->roseAreaList.value(num)->getLocation();
        if((airportId == comAirportId)
                && (runwayId == comRunWayId)
                && (windId == comWindId))
        {
            namestr.clear();
            affixStr.clear();
            namestr = proData->awosDataModel->inUsedWay->roseAreaList.value(num)->runwayName();
            QString Cspeed,GUST,Cangle,maxAngle,minAngle,runwayAngle
                    ,MWD10A,WS10M,WS10X,MWD10M,WD10X;
            Cspeed = bodymap["WS2A"].split(":").value(0);
            Cangle = bodymap["WD2A"].split(":").value(0);
            maxAngle = bodymap["WD2X"].split(":").value(0);
            minAngle = bodymap["WD2M"].split(":").value(0);
            GUST = bodymap["10GUST"].split(":").value(0);
            MWD10A = bodymap["WD10A"].split(":").value(0);//MWD10A 暂换成真北
            WS10M = bodymap["WS10M"].split(":").value(0);
            WS10X = bodymap["WS10X"].split(":").value(0);
            MWD10M = bodymap["WD10M"].split(":").value(0);//MWD10M 暂换成真北
            WD10X = bodymap["WD10X"].split(":").value(0);
            // Main ui Data deal**********
            runwayAngle = proData->awosDataModel->inUsedWay
                    ->roseAreaList.value(num)->runwayName();
            proData->awosDataModel->inUsedWay->roseAreaList.value(num)
                    ->setCurrentWindSpeed(Cspeed);
            proData->awosDataModel->inUsedWay->roseAreaList.value(num)
                    ->setCurrentWindAngle(Cangle.toInt());
            proData->awosDataModel->inUsedWay->roseAreaList.value(num)
                    ->setTenWindMaxAngle(maxAngle.toInt());
            proData->awosDataModel->inUsedWay->roseAreaList.value(num)
                    ->setTenWindMinAngle(minAngle.toInt());
            proData->awosDataModel->inUsedWay->roseAreaList.value(num)
                    ->setWindPointAngle(Cangle.toInt());
            proData->awosDataModel->inUsedWay->roseAreaList.value(num)
                    ->setZfeng10(GUST);
            //qDebug()<<"find the wind  rose comm";
            findResult = true;
            // Atc ui data deal ************
            if(locaStr == "left"){
                emit minAwos->AtcDataSignal("left","currentSpeed:"+ Cspeed);
                emit minAwos->AtcDataSignal("left","currentAngle:"+ Cangle);
                emit minAwos->AtcDataSignal("left","maxAngle:"+ maxAngle);
                emit minAwos->AtcDataSignal("left","minAngle:"+ minAngle);
                emit minAwos->AtcDataSignal("left","runAngle:"+ runwayAngle);
                emit minAwos->AtcDataSignal("left","twoSecAvAngle:"+ Cangle);
                emit minAwos->AtcDataSignal("left","GUST:"+ GUST);
            }
            else if(locaStr == "mid"){
                emit minAwos->AtcDataSignal("mid","currentSpeed:"+ Cspeed);
                emit minAwos->AtcDataSignal("mid","currentAngle:"+ Cangle);
                emit minAwos->AtcDataSignal("mid","maxAngle:"+ maxAngle);
                emit minAwos->AtcDataSignal("mid","minAngle:"+ minAngle);
                emit minAwos->AtcDataSignal("mid","runAngle:"+ runwayAngle);
                emit minAwos->AtcDataSignal("mid","twoSecAvAngle:"+ Cangle);
                emit minAwos->AtcDataSignal("mid","GUST:"+ GUST);
            }
            else if(locaStr == "right"){
                emit minAwos->AtcDataSignal("right","currentSpeed:"+ Cspeed);
                emit minAwos->AtcDataSignal("right","currentAngle:"+ Cangle);
                emit minAwos->AtcDataSignal("right","maxAngle:"+ maxAngle);
                emit minAwos->AtcDataSignal("right","minAngle:"+ minAngle);
                emit minAwos->AtcDataSignal("right","runAngle:"+ runwayAngle);
                emit minAwos->AtcDataSignal("right","twoSecAvAngle:"+ Cangle);
                emit minAwos->AtcDataSignal("right","GUST:"+ GUST);
            }
            // send telegram real time data
            if(locaStr == "left"){
                telegramData["groupLeftAngle"]    = QString("      %1  °").arg(MWD10A);
                telegramData["groupLeftSpeed1"]   = QString("      %1  m/s").arg(WS10M);
                telegramData["groupLeftSpeed2"]   = QString("      %1  m/s").arg(WS10X);
                telegramData["groupLeftAngleMin"] = QString("      %1  °").arg(MWD10M);
                telegramData["groupLeftAngleMax"] = QString("      %1  °").arg(WD10X);
                telegramData["groupLeftSHSpeed"] =  GUST;
                affixStr = QString("updateWindSelect:%1/windleft").arg(namestr);
                emit updateTelegramRealTimeData(telegramData,affixStr);
            }
            else if(locaStr == "mid"){
                telegramData["groupMIDIAngle"]    = QString("      %1  °").arg(MWD10A);
                telegramData["groupMIDISpeed1"]   = QString("      %1  m/s").arg(WS10M);
                telegramData["groupMIDISpeed2"]   = QString("      %1  m/s").arg(WS10X);
                telegramData["groupMIDIAngleMin"] = QString("      %1  °").arg(MWD10M);
                telegramData["groupMIDIAngleMax"] = QString("      %1  °").arg(WD10X);
                telegramData["groupMIDISHSpeed"] =  GUST;
                affixStr = QString("updateWindSelect:%1/windmid").arg(namestr);
                emit updateTelegramRealTimeData(telegramData,affixStr);
            }
            else if(locaStr == "right"){
                telegramData["groupRightAngle"]    = QString("      %1  °").arg(MWD10A);
                telegramData["groupRightSpeed1"]   = QString("      %1  m/s").arg(WS10M);
                telegramData["groupRightSpeed2"]   = QString("      %1  m/s").arg(WS10X);
                telegramData["groupRightAngleMin"] = QString("      %1  °").arg(MWD10M);
                telegramData["groupRightAngleMax"] = QString("      %1  °").arg(WD10X);
                telegramData["groupRightSHSpeed"] =  GUST;
                affixStr = QString("updateWindSelect:%1/windright").arg(namestr);
                emit updateTelegramRealTimeData(telegramData,affixStr);
            }
        }
    }
    if(!findResult){
        qDebug()<<"id 36:"<<airportId<<"runwayId"<<runwayId<<"windId"
               <<windId<<"wind rose not register";
    }

    //runway data find
    controlNum = proData->awosDataModel->inUsedWay->dataAreaList.length();
    findResult = false;
    for(int com = 0; com < controlNum;com++){
        int dataAirportId = proData->awosDataModel->inUsedWay
                ->dataAreaList.value(com)->airportId();
        int dataRunWayId = proData->awosDataModel->inUsedWay
                ->dataAreaList.value(com)->runWayId();
        int dataWindId = proData->awosDataModel->inUsedWay
                ->dataAreaList.value(com)->windId();
        //        QString locaStr2 = proData->awosDataModel->runWay  暂时不用
        //                ->dataAreaList.value(com)->getLocation();
        if((airportId == dataAirportId)
                && (runwayId == dataRunWayId)
                && (windId == dataWindId))
        {
            //真北
            //            proData->awosDataModel->runWay->dataAreaList.value(com)->setZOneSpeed((bodymap["WS1A"].split(":")).value(0));
            //            proData->awosDataModel->runWay->dataAreaList.value(com)->setZOneAngle((bodymap["WD1A"].split(":")).value(0));
            //            proData->awosDataModel->runWay->dataAreaList.value(com)->setZTenSpeed((bodymap["WS10A"].split(":")).value(0));
            //            proData->awosDataModel->runWay->dataAreaList.value(com)->setZTenAngle((bodymap["WD10A"].split(":")).value(0));
            proData->awosDataModel->inUsedWay->dataAreaList.value(com)
                    ->setZOneSpeed((bodymap["WS2A"].split(":")).value(0));
            proData->awosDataModel->inUsedWay->dataAreaList.value(com)
                    ->setZOneAngle((bodymap["WD2A"].split(":")).value(0));
            proData->awosDataModel->inUsedWay->dataAreaList.value(com)
                    ->setZTenSpeed((bodymap["WS10A"].split(":")).value(0));
            proData->awosDataModel->inUsedWay->dataAreaList.value(com)
                    ->setZTenAngle((bodymap["WD10A"].split(":")).value(0));

            //磁北
            proData->awosDataModel->inUsedWay->dataAreaList.value(com)
                    ->setCOneSpeed((bodymap["MWS2A"].split(":")).value(0));
            proData->awosDataModel->inUsedWay->dataAreaList.value(com)
                    ->setCOneAngle((bodymap["MWD2A"].split(":")).value(0));
            proData->awosDataModel->inUsedWay->dataAreaList.value(com)
                    ->setCTenSpeed((bodymap["MWS10A"].split(":")).value(0));
            proData->awosDataModel->inUsedWay->dataAreaList.value(com)
                    ->setCTenAngle((bodymap["MWD10A"].split(":")).value(0));
            //qDebug()<<"find the wind data comm";
            findResult = true;
        }
    }
    if(!findResult){
        qDebug()<<"id 36:"<<airportId<<"runwayId"<<runwayId<<"windId"<<windId
               <<"wind data control not register";
    }
}

void AwosStartSetup::awosHumiTempData(SensorMap senMap)
{
    //    DataMap headmap = senMap["humAndTempHead"];
    //    qDebug()<<"SC WindHead:"<<headmap;
    DataMap bodymap = senMap["humAndTempData"];
    //    qDebug()<<"SC HumiTempBody:"<<bodymap;
    int airportId = bodymap["AirPortID"].toInt();
    int runwayId = bodymap["RunWayID"].toInt();
    int humiTempId = bodymap["humAndTempID"].toInt();

    //  wind rose find
    int controlNum = proData->awosDataModel->inUsedWay->dataAreaList.length();
    bool findResult = false;
    QString namestr,affixStr;
    for(int com = 0; com < controlNum;com++){
        int dataAirportId = proData->awosDataModel->inUsedWay
                ->dataAreaList.value(com)->airportId();
        int dataRunWayId = proData->awosDataModel->inUsedWay
                ->dataAreaList.value(com)->runWayId();
        int datahumitempId = proData->awosDataModel->inUsedWay
                ->dataAreaList.value(com)->humitempId();
        QString locaStr = proData->awosDataModel->inUsedWay
                ->dataAreaList.value(com)->getLocation();
        if((airportId == dataAirportId)
                && (runwayId == dataRunWayId)
                && (humiTempId == datahumitempId))
        {
            namestr.clear();
            affixStr.clear();
            namestr = proData->awosDataModel->inUsedWay->dataAreaList.value(com)->runwayName();
            QString TAINS,RHINS,TDINS;
            TAINS = bodymap["TAINS"].split(":").value(0);
            RHINS = bodymap["RHINS"].split(":").value(0);
            TDINS = bodymap["TDINS"].split(":").value(0);
            proData->awosDataModel->inUsedWay->dataAreaList.value(com)
                    ->setTemp(TAINS);
            proData->awosDataModel->inUsedWay->dataAreaList.value(com)
                    ->setHumi(RHINS);
            proData->awosDataModel->inUsedWay->dataAreaList.value(com)
                    ->setDew(TDINS);
            //qDebug()<<"find the humitemp data comm";
            findResult = true;
            if(locaStr == "left"){
                telegramData["groupLeftTem"] = QString("      %1   ℃").arg(TAINS);
                telegramData["groupLeftDew"] = QString("      %1   ℃").arg(TDINS);
                telegramData["groupLeftHum"] = QString("      %1   ％").arg(RHINS);
                affixStr = QString("updateHumiTempselect:%1/HumiTempleft").arg(namestr);
                emit updateTelegramRealTimeData(telegramData,affixStr);
            }
            else if(locaStr == "right"){
                telegramData["groupRightTem"] = QString("      %1   ℃").arg(TAINS);
                telegramData["groupRightDew"] = QString("      %1   ℃").arg(TDINS);
                telegramData["groupRightHum"] = QString("      %1   ％").arg(RHINS);
                affixStr = QString("updateHumiTempselect:%1/HumiTempright").arg(namestr);
                emit updateTelegramRealTimeData(telegramData,affixStr);
            }
        }
    }
    if(!findResult){
        qDebug()<<"id 36:"<<airportId<<"runwayId"<<runwayId<<"humiTempId"
               <<humiTempId<<"humitemp data control not register";
    }
}

void AwosStartSetup::awosRvrData(SensorMap senMap)
{
    //    DataMap headmap = senMap["VISHead"];
    //    qDebug()<<"SC WindHead:"<<headmap;
    DataMap bodymap = senMap["VISData"];
    //    qDebug()<<"SC VisBody:"<<bodymap;
    int airportId = bodymap["AirPortID"].toInt();
    int runwayId = bodymap["RunWayID"].toInt();
    int visId = bodymap["VISID"].toInt();

    //  wind rose find
    int controlNum = proData->awosDataModel->inUsedWay
            ->roseAreaList.length();
    bool findResult = false;
    QString nameStr,affixstr;
    for(int num = 0; num < controlNum;num++){
        int comAirportId = proData->awosDataModel->inUsedWay
                ->roseAreaList.value(num)->airportId();
        int comRunWayId = proData->awosDataModel->inUsedWay
                ->roseAreaList.value(num)->runWayId();
        int comVisId = proData->awosDataModel->inUsedWay
                ->roseAreaList.value(num)->visId();
        QString locaStr = proData->awosDataModel->inUsedWay
                ->roseAreaList.value(num)->getLocation();
//        qDebug()<<QString("comAir:%1,comrun:%2,comvis:%3,air:%4,run:%5,vis:%6")
//                  .arg(comAirportId).arg(comRunWayId).arg(comVisId)
//                  .arg(airportId).arg(runwayId).arg(visId);
        if((airportId == comAirportId)
                && (runwayId == comRunWayId)
                && (visId == comVisId))
        {
            nameStr.clear();
            affixstr.clear();
            nameStr = proData->awosDataModel->inUsedWay->roseAreaList.value(num)->runwayName();
            WaringTepy warin;
            QString RVR,RVR10X,RVR10M,MOR,TREND,VIS10A,VIS10M;
            RVR = (bodymap["RVR"].split(":")).value(0);
            RVR10X = (bodymap["RVR10X"].split(":")).value(0);
            RVR10M = (bodymap["RVR10M"].split(":")).value(0);
            MOR = (bodymap["MOR"].split(":")).value(0);
            VIS10A = bodymap["VIS10A"].split(":").value(0);
            VIS10M = bodymap["VIS10M"].split(":").value(0);
            int tNum = (bodymap["RVR10T"].split(":")).value(0).toInt();
            if(tNum == 0)TREND = "N";
            else if(tNum == -1)TREND = "D";
            else if(tNum == 1)TREND = "U";
            if(RVR.toInt() < proData->awosDataModel->inUsedWay
                    ->roseAreaList.value(num)->morMin() ||
                    RVR.toInt() > proData->awosDataModel->inUsedWay
                    ->roseAreaList.value(num)->morMax())
            {
                warin.clear();
                warin["rvr"] = true;
                awosWaringVoice(warin);
                emit minAwos->addWaring(QString("rvr not in threshold value rang waring"));
            }
            else{
                warin.clear();
                warin["rvr"] = false;
            }
            proData->awosDataModel->inUsedWay->roseAreaList.value(num)
                    ->setWaringBool(warin);
            proData->awosDataModel->inUsedWay->roseAreaList.value(num)
                    ->setMorValue(RVR);

            if(MOR.toInt() < proData->awosDataModel->inUsedWay
                    ->roseAreaList.value(num)->rvrMin()
                    ||MOR.toInt() > proData->awosDataModel->inUsedWay
                    ->roseAreaList.value(num)->rvrMax())
            {
                warin.clear();
                warin["mor"] = true;
                awosWaringVoice(warin);
                emit minAwos->addWaring(QString("mor not in threshold value rang waring"));
            }
            else{
                warin.clear();
                warin["mor"] = false;
            }
            proData->awosDataModel->inUsedWay->roseAreaList.value(num)
                    ->setWaringBool(warin);
            proData->awosDataModel->inUsedWay->roseAreaList.value(num)
                    ->setRvrValue(MOR);
            //qDebug()<<"find the wind  rose comm";
            findResult = true;

            // Atc ui data deal ************
            if(locaStr == "left"){
                emit minAwos->AtcDataSignal("left","RVR:"+ MOR);
                emit minAwos->AtcDataSignal("left","VIS:"+ RVR);
            }
            else if(locaStr == "mid"){
                emit minAwos->AtcDataSignal("mid","RVR:"+ MOR);
                emit minAwos->AtcDataSignal("mid","VIS:"+ RVR);
            }
            else if(locaStr == "right"){
                emit minAwos->AtcDataSignal("right","RVR:"+ MOR);
                emit minAwos->AtcDataSignal("right","VIS:"+ RVR);
            }
            // telegram real time  data deal
            if(locaStr == "left"){

//                tenMinRvr
//                tenMaxRvr
////                tenAvgVis
//                rvrTrend;

                telegramData["groupLeftRVRTenAvgValue"]  = QString("      %1  m").arg(RVR);
                telegramData["groupLeftRVRTenMaxValue"] = QString("%1").arg(RVR10X);
                telegramData["groupLeftRVRTenMinValue"] = QString("%1").arg(RVR10M);
                telegramData["groupLeftRVRTendency"]     = QString("      %1").arg(TREND);
                //                telegramData["groupVisTenAvg"] = QString("      %1  m").arg(VIS10A);
                //                telegramData["groupVisTenMin"] = QString("      %1  m").arg(VIS10M);
                //                telegramData["groupVisTenDirection"] = "      ND" ;
                affixstr = QString("updateRVRSelect:%1/rvrleft").arg(nameStr);
                emit updateTelegramRealTimeData(telegramData,affixstr);
            }
            else if(locaStr == "mid"){
                telegramData["groupMIDIRVRTenAvgValue"]  = QString("      %1  m").arg(RVR);
                telegramData["groupMIDRVRTenMaxValue"] = QString("%1").arg(RVR10X);
                telegramData["groupMIDRVRTenMinValue"] = QString("%1").arg(RVR10M);
                telegramData["groupMIDIRVRTendency"]     = QString("      %1").arg(TREND);
                //                telegramData["groupVisTenAvg"] = QString("      %1  m").arg(VIS10A);
                //                telegramData["groupVisTenMin"] = QString("      %1  m").arg(VIS10M);
                //                telegramData["groupVisTenDirection"] = "      ND" ;
                affixstr = QString("updateRVRSelect:%1/rvrmid").arg(nameStr);
                emit updateTelegramRealTimeData(telegramData,affixstr);
            }
            else if(locaStr == "right"){
                telegramData["groupRightRVRTenAvgValue"] = QString("      %1  m").arg(RVR);
                telegramData["groupRightRVRTenMaxValue"] = QString("%1").arg(RVR10X);
                telegramData["groupRightRVRTenMinValue"] = QString("%1").arg(RVR10M);
                telegramData["groupRightRVRTendency"]    = QString("      %1").arg(TREND);
                //                telegramData["groupVisTenAvg"] = QString("      %1  m").arg(VIS10A);
                //                telegramData["groupVisTenMin"] = QString("      %1  m").arg(VIS10M);
                //                telegramData["groupVisTenDirection"] = "      ND" ;
                affixstr = QString("updateRVRSelect:%1/rvrright").arg(nameStr);
                emit updateTelegramRealTimeData(telegramData,affixstr);
            }
        }
    }
    if(!findResult){
        qDebug()<<"airportId:"<<airportId<<"runwayId"<<runwayId<<"visId"
               <<visId<<"VIS and RVR data show contrls are not register";
    }
}

void AwosStartSetup::awosCloudData(SensorMap senMap)
{
    //DataMap headmap = senMap["CloudHead"];
    //qDebug()<<"SC CloudHead:"<<headmap;
    DataMap bodymap = senMap["CloudData"];
    //qDebug()<<"SC CloudBody:"<<bodymap;

    int airportId = bodymap["AirPortID"].toInt();
    int runwayId = bodymap["RunWayID"].toInt();
    int CloudId = bodymap["CloudID"].toInt();

    int roseNum = proData->awosDataModel->inUsedWay
            ->roseAreaList.length();
    bool findrose = false;
    int roseAirId,roseRunWayId,roseCloudId;
    QString roseLoca;
    for(int w = 0; w < roseNum;w++){
        roseAirId = -1;
        roseRunWayId = -1;
        roseCloudId = -1;
        roseLoca = "";
        roseAirId = proData->awosDataModel->inUsedWay
                ->roseAreaList.value(w)->airportId();
        roseRunWayId = proData->awosDataModel->inUsedWay
                ->roseAreaList.value(w)->runWayId();
        roseCloudId = proData->awosDataModel->inUsedWay
                ->roseAreaList.value(w)->cloudId();
//        roseLoca = proData->awosDataModel->runWay
//                ->roseAreaList.value(w)->getLocation();
        if((roseAirId == airportId)
           && (roseRunWayId == runwayId)
           && (roseCloudId == CloudId))
        {
            QString baseHight;
            baseHight = bodymap["CLOUDBASE"].split(":").value(0);
            proData->awosDataModel->inUsedWay
                    ->roseAreaList.value(w)->setCLDBaseHight(baseHight);
            findrose = true;
            break;
        }
    }
    if(!findrose){
        qDebug()<<"airportId:"<<airportId<<"runwayId"<<runwayId<<"CloudId"
               <<CloudId<<"roseCloud data control not register";
    }
    //  Cloud Sensor ui find
    int controlNum = proData->awosDataModel->inUsedWay
            ->cloudSensorList.length();
    bool findResult = false;
    QString nameStr,affixStr;
    for(int com = 0; com < controlNum;com++){
        int dataAirportId = proData->awosDataModel->inUsedWay
                ->cloudSensorList.value(com)->airportId();
        int dataRunWayId = proData->awosDataModel->inUsedWay
                ->cloudSensorList.value(com)->runWayId();
        int dataCloudId = proData->awosDataModel->inUsedWay
                ->cloudSensorList.value(com)->getCloudId();
        QString locaStr = proData->awosDataModel->inUsedWay
                ->cloudSensorList.value(com)->getLocation();
//        qDebug()<<QString("comAir:%1,comrun:%2,comcloud:%3,air:%4,run:%5,cloud:%6")
//                  .arg(dataAirportId).arg(dataRunWayId).arg(dataCloudId)
//                  .arg(airportId).arg(runwayId).arg(CloudId);
        if((airportId == dataAirportId)
                && (runwayId == dataRunWayId)
                && (CloudId == dataCloudId))
        {
            nameStr.clear();
            affixStr.clear();
            nameStr = proData->awosDataModel->inUsedWay->cloudSensorList.value(com)->runwayName();
            QString AMOUNT1,AMOUNT2,AMOUNT3,CH1INS,CH2INS,CH3INS,SkyClear,VerVis,Base;
            AMOUNT1 = bodymap["AMOUNT1"].split(":").value(0);
            AMOUNT2 = bodymap["AMOUNT2"].split(":").value(0);
            AMOUNT3 = bodymap["AMOUNT3"].split(":").value(0);
            CH1INS  = bodymap["CH1INS"].split(":").value(0);
            CH2INS  = bodymap["CH2INS"].split(":").value(0);
            CH3INS  = bodymap["CH3INS"].split(":").value(0);
            SkyClear = bodymap["ISSKYCLEAR"].split(":").value(0);  //
            VerVis = bodymap["ISVERTVIS"].split(":").value(0);
            // 注：ISVERTVIS 维萨拉的垂直能见度的监测标志
            // 正常的应该为ISVERVIS为能见度的监测标志

            //qDebug()<<"is var vis:"<<bodymap;
            Base = bodymap["CLOUDBASE"].split(":").value(0);   //
            proData->awosDataModel->inUsedWay->cloudSensorList.value(com)
                    ->setFirstlay(CH1INS);
            proData->awosDataModel->inUsedWay->cloudSensorList.value(com)
                    ->setSecondlay(CH2INS);
            proData->awosDataModel->inUsedWay->cloudSensorList.value(com)
                    ->setThirdlay(CH3INS);
            //qDebug()<<"find the cloud data com";
            findResult = true;

            // Atc ui data deal ************
            if(locaStr == "left"){
                emit minAwos->AtcDataSignal("left","CLD:"+ CH1INS);
            }
            else if(locaStr == "right"){
                emit minAwos->AtcDataSignal("right","CLD:"+ CH1INS);
            }
            // telegram real time data deal
            if(locaStr == "left"){
                telegramData["groupLeft1CloudCount"]  = QString("      %1").arg(AMOUNT1);
                telegramData["groupLeft2CloudCount"]  = QString("      %1").arg(AMOUNT2);
                telegramData["groupLeft3CloudCount"]  = QString("      %1").arg(AMOUNT3);
                telegramData["groupLeft1CloudHight"]  = QString("      %1   m").arg(CH1INS);
                telegramData["groupLeft2CloudHight"]  = QString("      %1   m").arg(CH2INS);
                telegramData["groupLeft3CloudHight"]  = QString("      %1   m").arg(CH3INS);
                telegramData["groupLeftIsSkyClear"] = QString("%1").arg(SkyClear);
                telegramData["groupLeftIsVerVis"] = QString("%1").arg(VerVis);
                telegramData["groupLeftCloudBase"] = QString("%1").arg(Base);
                affixStr = QString("updateCloudSelect:%1").arg(nameStr);
                emit updateTelegramRealTimeData(telegramData,affixStr);
            }
            else if(locaStr == "right"){
                telegramData["groupRight1CloudCount"] = QString("      %1").arg(AMOUNT1);
                telegramData["groupRight2CloudCount"] = QString("      %1").arg(AMOUNT2);
                telegramData["groupRight3CloudCount"] = QString("      %1").arg(AMOUNT3);
                telegramData["groupRight1CloudHight"] = QString("      %1   m").arg(CH1INS);
                telegramData["groupRight2CloudHight"] = QString("      %1   m").arg(CH2INS);
                telegramData["groupRight3CloudHight"] = QString("      %1   m").arg(CH3INS);
                telegramData["groupRightIsSkyClear"] = QString("%1").arg(SkyClear);
                telegramData["groupRightIsVerVis"] = QString("%1").arg(VerVis);
                telegramData["groupRightCloudBase"] = QString("%1").arg(Base);
                affixStr = QString("updateCloudSelect:%1").arg(nameStr);
                emit updateTelegramRealTimeData(telegramData,affixStr);
            }
        }
    }
    if(!findResult){
        qDebug()<<"airportId:"<<airportId<<"runwayId"<<runwayId<<"CloudId"
               <<CloudId<<"Cloud data control not register";
    }
}

void AwosStartSetup::awosAtmospherePressData(SensorMap senMap)
{
    //DataMap headmap = senMap["PressHead"];
    //qDebug()<<"SC PressHead:"<<headmap;
    DataMap bodymap = senMap["PressData"];
    //qDebug()<<"SC PressBody:"<<bodymap;
    minAwos->setQNFValue((bodymap["QNHINS"].split(":")).value(0));
    // 双气压数据实时交替显示主界面（此处需后期处理）

    int airportId = bodymap["AirPortID"].toInt();
    int runwayId = bodymap["RunWayID"].toInt();
    int PressId = bodymap["PressID"].toInt();

    //Press Sensor ui find
    int controlNum = proData->awosDataModel->inUsedWay->pressList.length();
    bool findResult = false;
    QString nameStr,affixStr;
    for(int com = 0; com < controlNum;com++){
        int comAirportId = proData->awosDataModel->inUsedWay->pressList.value(com)->airportId();
        int comRunWayId = proData->awosDataModel->inUsedWay->pressList.value(com)->runWayId();
        int comPress = proData->awosDataModel->inUsedWay->pressList.value(com)->getPressId();
        if((airportId == comAirportId)
                && (runwayId == comRunWayId)
                && (PressId == comPress))
        {
            nameStr.clear();
            affixStr.clear();
            nameStr = proData->awosDataModel->inUsedWay->pressList.value(com)->runwayName();
            QString loca,QNHINS;
            loca = proData->awosDataModel->inUsedWay->pressList.value(com)->getLocation();
            QNHINS = bodymap["QNHINS"].split(":").value(0);
            proData->awosDataModel->inUsedWay->pressList.value(com)->setPressValue(QNHINS);
            if(loca == "left"){
                telegramData["groupPress"]  = QString("      %1  hPa").arg(QNHINS);
                affixStr = QString("updatePressSelect:%1").arg(nameStr);
                emit updateTelegramRealTimeData(telegramData,affixStr);
            }
            else if(loca == "right"){
                telegramData["groupPress"]  = QString("      %1  hPa").arg(QNHINS);
                affixStr = QString("updatePressSelect:%1").arg(nameStr);
                emit updateTelegramRealTimeData(telegramData,affixStr);
            }
            //qDebug()<<"find the cloud data com";
            findResult = true;
        }
    }
    if(!findResult){
        qDebug()<<"airtport Id:"<<airportId<<"runwayId"<<runwayId
               <<"PressId"<<PressId<<"Cloud data control not register";
    }

}

void AwosStartSetup::awosRainData(SensorMap senMap)
{
    //DataMap headmap = senMap["RainHead"];
    //qDebug()<<"SC RainHead:"<<headmap;
    DataMap bodymap = senMap["RainData"];
    //qDebug()<<"SC RainBody:"<<bodymap;

    int airportId = bodymap["AirPortID"].toInt();
    int runwayId = bodymap["RunWayID"].toInt();
    int rainId = (bodymap["RainID"]).toInt();
    bool findResult = false;

    //data Area find
    int controlNum = proData->awosDataModel->inUsedWay
            ->dataAreaList.length();
    for(int com = 0; com < controlNum;com++){
        int dataAirportId = proData->awosDataModel->inUsedWay
                ->dataAreaList.value(com)->airportId();
        int dataRunWayId = proData->awosDataModel->inUsedWay
                ->dataAreaList.value(com)->runWayId();
        int dataRainId = proData->awosDataModel->inUsedWay
                ->dataAreaList.value(com)->windId();
//        qDebug()<<QString("comAir:%1,comrun:%2,comrain:%3,air:%4,run:%5,rain:%6")
//                  .arg(dataAirportId).arg(dataRunWayId).arg(dataRainId)
//                  .arg(airportId).arg(runwayId).arg(rainId);
        if((airportId == dataAirportId)
                && (runwayId == dataRunWayId)
                && (rainId == dataRainId))
        {
            proData->awosDataModel->inUsedWay->dataAreaList.value(com)
                    ->setRain((bodymap["SUM_1H"].split(":")).value(0));
            findResult = true;
        }
    }
    if(!findResult){
        qDebug()<<"id 36:"<<airportId<<"runwayId"<<runwayId
               <<"rainId"<<rainId<<"rain data area control not register";
    }
}

void AwosStartSetup::awosPhenomenaWeatherData(SensorMap senMap)
{
    DataMap headmap,bodymap;
    headmap = senMap["PWHead"];
    bodymap = senMap["PWData"];
    //qDebug()<<"SC Weather:"<<headmap;

    int airportId = bodymap["AirPortID"].toInt();  // 0
    int runwayId = bodymap["RunWayID"].toInt();  // 0
    int weatherId = (bodymap["PWID"]).toInt(); // 0
    bool findResult;
    findResult = false;
    QString PWStr,RWStr;
    QString namestr,affixStr;

    //data Area find
    int controlNum = proData->awosDataModel->inUsedWay
            ->weatherList.length();
    for(int com = 0; com < controlNum;com++){
        int dataAirportId = proData->awosDataModel->inUsedWay
                ->weatherList.value(com)->airportId();
        int dataRunWayId = proData->awosDataModel->inUsedWay
                ->weatherList.value(com)->runWayId();
        int dataWeatherId = proData->awosDataModel->inUsedWay
                ->weatherList.value(com)->getweatherId();
//        qDebug()<<QString("comAir:%1,comrun:%2,comweather:%3,air:%4,run:%5,weather:%6")
//                  .arg(dataAirportId).arg(dataRunWayId).arg(dataWeatherId)
//                  .arg(airportId).arg(runwayId).arg(weatherId);
        if((airportId == dataAirportId)
                && (runwayId == dataRunWayId)
                && (weatherId == dataWeatherId))
        {
            namestr.clear();
            affixStr.clear();
            PWStr = (bodymap["PW"].split(":")).value(0);
            RWStr = (bodymap["RW"].split(":")).value(0);
            //qDebug()<<"++++++++Weather:"<<PWStr
            //       <<"++++Closed Weather:"<<RWStr;
            namestr = proData->awosDataModel->inUsedWay->weatherList.value(com)
                    ->runwayName();
            proData->awosDataModel->inUsedWay->weatherList.value(com)
                    ->setweatherValue(RWStr);
            //处理界面的传感器选项（下行）
            affixStr = QString("updateWeatherSelect:%1").arg(namestr);
            telegramData["groupCurrentWeather"]  = QString("      %1").arg(PWStr);
            telegramData["groupCloseTimeWeather"]  = QString("      %1").arg(RWStr);
            emit updateTelegramRealTimeData(telegramData,affixStr);
            findResult = true;
        }
    }
    if(!findResult){
        qDebug()<<"airport id:"<<airportId<<"runwayId:"<<runwayId
               <<"weather Id:"<<weatherId<<"weather data com control not register";
    }
}

void AwosStartSetup::awosPrevailingVisibilityData(SensorMap senMap)
{
    DataMap bodymap = senMap["PVData"];
    QString rowVis,Sensor_Vis10m,VIS10A,VIS10M;
    QString  affixStr;
    affixStr.clear();
    rowVis = (bodymap["RawVIS"].split(":")).value(0);
    Sensor_Vis10m = (bodymap["SENSOR_VIS10M"].split(":")).value(0);
    VIS10A = (bodymap["VIS10A"].split(":")).value(0);
    VIS10M = (bodymap["VIS10M"].split(":")).value(0);
    affixStr = "";
    telegramData["groupVisTenAvg"] = QString("      %1  m").arg(VIS10A);
    telegramData["groupVisTenMin"] = QString("      %1  m").arg(VIS10M);
    telegramData["groupVisTenDirection"] = "      ND" ;
    telegramData["groupVisRowVis"]  = QString("%1").arg(rowVis);
    telegramData["groupVisSensor_vis10m"]  = QString("%1").arg(Sensor_Vis10m);
    emit updateTelegramRealTimeData(telegramData,affixStr);
}

void AwosStartSetup::awosManualInputDataData(SensorMap /*senMap*/)
{

}

void AwosStartSetup::windDataStore(SensorMap senMap)
{
    DataMap dataMap = senMap["windData"];
    //qDebug()<<"wind data +++:"<<dataMap;
    int tableNum = proData->databaseTables->tablesWind
            ->value("tablesWind/tableNum").toInt();
    QString tableName;
    QString tableField;
    QStringList tableFiledList;
    QString tableFiledStr;
    QString tableDataStr;
    for(int i = 1;i <= tableNum;i++){
        tableName = proData->databaseTables->tablesWind
                ->value(QString("tables/table%1Name").arg(i)).toString().trimmed();
        tableFiledList = proData->databaseTables->tablesWind
                ->value(QString("tables/table%1Field").arg(i)).toString().split(",");
        int dataNum = tableFiledList.length();
        for(int j = 0;j < dataNum;j++){
            tableField = tableFiledList.at(j).split(":").at(0).trimmed();
            if(j == (dataNum - 1))
            {
                tableFiledStr = tableFiledStr + "SC_" + tableField;
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'";
            }
            else
            {
                tableFiledStr = tableFiledStr + "SC_" + tableField + ",";
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'" + ",";
            }
        }
        //qDebug()<<"table name:"<<tableName;
        //qDebug()<<"table tableFielStr:"<<tableFiledStr;
        //qDebug()<<"table tableDataStr:"<<tableDataStr;
        database->addData(tableName,tableFiledStr,tableDataStr);
    }
    dataMap.clear();
}

void AwosStartSetup::humiTempDataStore(SensorMap senMap)
{
    DataMap dataMap = senMap["humAndTempData"];
    //qDebug()<<"hum and temp data store:"<<dataMap;
    int tableNum = proData->databaseTables->tablesHumTemp
            ->value("tablesHumTemp/tableNum").toInt();
    QString tableName;
    QString tableField;
    QStringList tableFiledList;
    QString tableFiledStr;
    QString tableDataStr;
    for(int i = 1;i <= tableNum;i++){
        tableName = proData->databaseTables->tablesHumTemp
                ->value(QString("tables/table%1Name").arg(i)).toString().trimmed();
        tableFiledList = proData->databaseTables->tablesHumTemp
                ->value(QString("tables/table%1Field").arg(i)).toString().split(",");
        int dataNum = tableFiledList.length();
        for(int j = 0;j < dataNum;j++){
            tableField = tableFiledList.at(j).split(":").at(0).trimmed();
            if(j == (dataNum - 1)){
                tableFiledStr = tableFiledStr + "SC_" + tableField;
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'";
            }else{
                tableFiledStr = tableFiledStr + "SC_" + tableField + ",";
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'" + ",";
            }
        }
        //qDebug()<<"table name:"<<tableName;
        //qDebug()<<"table tableFielStr:"<<tableFiledStr;
        //qDebug()<<"table tableDataStr:"<<tableDataStr;
        database->addData(tableName,tableFiledStr,tableDataStr);
    }
    dataMap.clear();
}

void AwosStartSetup::rvrDataStore(SensorMap senMap)
{
    DataMap dataMap = senMap["VISData"];
    //qDebug()<<"Vis data store:"<<dataMap;
    int tableNum = proData->databaseTables->tablesVIS
            ->value("tablesVIS/tableNum").toInt();
    QString tableName;
    QString tableField;
    QStringList tableFiledList;
    QString tableFiledStr;
    QString tableDataStr;
    for(int i = 1;i <= tableNum;i++){
        tableName = proData->databaseTables->tablesVIS
                ->value(QString("tables/table%1Name").arg(i)).toString().trimmed();
        tableFiledList = proData->databaseTables->tablesVIS
                ->value(QString("tables/table%1Field").arg(i)).toString().split(",");
        int dataNum = tableFiledList.length();
        for(int j = 0;j < dataNum;j++){
            tableField = tableFiledList.at(j).split(":").at(0).trimmed();
            if(j == (dataNum - 1)){
                tableFiledStr = tableFiledStr + "SC_" + tableField;
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'";
            }else{
                tableFiledStr = tableFiledStr + "SC_" + tableField + ",";
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'" + ",";
            }
        }
        //qDebug()<<"table name:"<<tableName;
        //qDebug()<<"table tableFielStr:"<<tableFiledStr;
        //qDebug()<<"table tableDataStr:"<<tableDataStr;
        database->addData(tableName,tableFiledStr,tableDataStr);
    }
    dataMap.clear();
}

void AwosStartSetup::cloudDataStore(SensorMap senMap)
{
    DataMap dataMap = senMap["CloudData"];
    //qDebug()<<"Vis data store:"<<dataMap;
    int tableNum = proData->databaseTables->tablesCloud
            ->value("tablesCloud/tableNum").toInt();
    QString tableName;
    QString tableField;
    QStringList tableFiledList;
    QString tableFiledStr;
    QString tableDataStr;
    for(int i = 1;i <= tableNum;i++){
        tableName = proData->databaseTables->tablesCloud
                ->value(QString("tables/table%1Name").arg(i)).toString().trimmed();
        tableFiledList = proData->databaseTables->tablesCloud
                ->value(QString("tables/table%1Field").arg(i)).toString().split(",");
        int dataNum = tableFiledList.length();
        for(int j = 0;j < dataNum;j++){
            tableField = tableFiledList.at(j).split(":").at(0).trimmed();
            if(j == (dataNum - 1)){
                tableFiledStr = tableFiledStr + "SC_" + tableField;
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'";
            }else{
                tableFiledStr = tableFiledStr + "SC_" + tableField + ",";
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'" + ",";
            }
        }
        //qDebug()<<"table name:"<<tableName;
        //qDebug()<<"table tableFielStr:"<<tableFiledStr;
        //qDebug()<<"table tableDataStr:"<<tableDataStr;
        database->addData(tableName,tableFiledStr,tableDataStr);
    }
    dataMap.clear();
}

void AwosStartSetup::atmospherePressDataStore(SensorMap senMap)
{
    DataMap dataMap = senMap["PressData"];
    //qDebug()<<"Vis data store:"<<dataMap;
    int tableNum = proData->databaseTables->tablesPress
            ->value("tablesPress/tableNum").toInt();
    QString tableName;
    QString tableField;
    QStringList tableFiledList;
    QString tableFiledStr;
    QString tableDataStr;
    for(int i = 1;i <= tableNum;i++){
        tableName = proData->databaseTables->tablesPress
                ->value(QString("tables/table%1Name").arg(i)).toString().trimmed();
        tableFiledList = proData->databaseTables->tablesPress
                ->value(QString("tables/table%1Field").arg(i)).toString().split(",");
        int dataNum = tableFiledList.length();
        for(int j = 0;j < dataNum;j++){
            tableField = tableFiledList.at(j).split(":").at(0).trimmed();
            if(j == (dataNum - 1)){
                tableFiledStr = tableFiledStr + "SC_" + tableField;
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'";
            }else{
                tableFiledStr = tableFiledStr + "SC_" + tableField + ",";
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'" + ",";
            }
        }
        //qDebug()<<"table name:"<<tableName;
        //qDebug()<<"table tableFielStr:"<<tableFiledStr;
        //qDebug()<<"table tableDataStr:"<<tableDataStr;
        database->addData(tableName,tableFiledStr,tableDataStr);
    }
    dataMap.clear();
}

void AwosStartSetup::rainDataStore(SensorMap senMap)
{
    DataMap dataMap = senMap["RainData"];
    //qDebug()<<"Vis data store:"<<dataMap;
    int tableNum = proData->databaseTables->tablesRain
            ->value("tablesRain/tableNum").toInt();
    QString tableName;
    QString tableField;
    QStringList tableFiledList;
    QString tableFiledStr;
    QString tableDataStr;
    for(int i = 1;i <= tableNum;i++){
        tableName = proData->databaseTables->tablesRain
                ->value(QString("tables/table%1Name").arg(i)).toString().trimmed();
        tableFiledList = proData->databaseTables->tablesRain
                ->value(QString("tables/table%1Field").arg(i)).toString().split(",");
        int dataNum = tableFiledList.length();
        for(int j = 0;j < dataNum;j++){
            tableField = tableFiledList.at(j).split(":").at(0).trimmed();
            if(j == (dataNum - 1)){
                tableFiledStr = tableFiledStr + "SC_" + tableField;
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'";
            }else{
                tableFiledStr = tableFiledStr + "SC_" + tableField + ",";
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'" + ",";
            }
        }
        //qDebug()<<"table name:"<<tableName;
        //qDebug()<<"table tableFielStr:"<<tableFiledStr;
        //qDebug()<<"table tableDataStr:"<<tableDataStr;
        database->addData(tableName,tableFiledStr,tableDataStr);
    }
    dataMap.clear();
}

void AwosStartSetup::phenomenaWeatherDataStore(SensorMap senMap)
{
    DataMap dataMap = senMap["PWData"];
    //qDebug()<<"Vis data store:"<<dataMap;
    int tableNum = proData->databaseTables->tablesPW
            ->value("tablesPW/tableNum").toInt();
    QString tableName;
    QString tableField;
    QStringList tableFiledList;
    QString tableFiledStr;
    QString tableDataStr;
    for(int i = 1;i <= tableNum;i++){
        tableName = proData->databaseTables->tablesPW
                ->value(QString("tables/table%1Name").arg(i)).toString().trimmed();
        tableFiledList = proData->databaseTables->tablesPW
                ->value(QString("tables/table%1Field").arg(i)).toString().split(",");
        int dataNum = tableFiledList.length();
        for(int j = 0;j < dataNum;j++){
            tableField = tableFiledList.at(j).split(":").at(0).trimmed();
            if(j == (dataNum - 1)){
                tableFiledStr = tableFiledStr + "SC_" + tableField;
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'";
            }else{
                tableFiledStr = tableFiledStr + "SC_" + tableField + ",";
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'" + ",";
            }
        }
        //qDebug()<<"table name:"<<tableName;
        //qDebug()<<"table tableFielStr:"<<tableFiledStr;
        //qDebug()<<"table tableDataStr:"<<tableDataStr;
        database->addData(tableName,tableFiledStr,tableDataStr);
    }
    dataMap.clear();
}

void AwosStartSetup::prevailingVisibilityDataStore(SensorMap senMap)
{
    DataMap dataMap = senMap["PVData"];
    //qDebug()<<"Vis data store:"<<dataMap;
    int tableNum = proData->databaseTables->tablesPV
            ->value("tablesPV/tableNum").toInt();
    QString tableName;
    QString tableField;
    QStringList tableFiledList;
    QString tableFiledStr;
    QString tableDataStr;
    for(int i = 1;i <= tableNum;i++){
        tableName = proData->databaseTables->tablesPV
                ->value(QString("tables/table%1Name").arg(i)).toString().trimmed();
        tableFiledList = proData->databaseTables->tablesPV
                ->value(QString("tables/table%1Field").arg(i)).toString().split(",");
        int dataNum = tableFiledList.length();
        for(int j = 0;j < dataNum;j++){
            tableField = tableFiledList.at(j).split(":").at(0).trimmed();
            if(j == (dataNum - 1)){
                tableFiledStr = tableFiledStr + "SC_" + tableField;
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'";
            }else{
                tableFiledStr = tableFiledStr + "SC_" + tableField + ",";
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'" + ",";
            }
        }
        //qDebug()<<"table name:"<<tableName;
        //qDebug()<<"table tableFielStr:"<<tableFiledStr;
        //qDebug()<<"table tableDataStr:"<<tableDataStr;
        database->addData(tableName,tableFiledStr,tableDataStr);
    }
    dataMap.clear();
}

void AwosStartSetup::BIASLIGHTDataSignalDataStore(SensorMap senMap)
{
    DataMap dataMap = senMap["BIASLIGHTData"];
    //qDebug()<<"BIASLIGHT data store:"<<dataMap;
    int tableNum = proData->databaseTables->tablesBIASLIGHT
            ->value("tablesBIASLIGHT/tableNum").toInt();
    QString tableName;
    QString tableField;
    QStringList tableFiledList;
    QString tableFiledStr;
    QString tableDataStr;
    for(int i = 1;i <= tableNum;i++){
        tableName = proData->databaseTables->tablesBIASLIGHT
                ->value(QString("tables/table%1Name").arg(i)).toString().trimmed();
        tableFiledList = proData->databaseTables->tablesBIASLIGHT
                ->value(QString("tables/table%1Field").arg(i)).toString().split(",");
        int dataNum = tableFiledList.length();
        for(int j = 0;j < dataNum;j++){
            tableField = tableFiledList.at(j).split(":").at(0).trimmed();
            if(j == (dataNum - 1)){
                tableFiledStr = tableFiledStr + "SC_" + tableField;
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'";
            }else{
                tableFiledStr = tableFiledStr + "SC_" + tableField + ",";
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'" + ",";
            }
        }
        database->addData(tableName,tableFiledStr,tableDataStr);
    }
    dataMap.clear();
}

void AwosStartSetup::manualInputDataDataStore(SensorMap /*senMap*/)
{

}

void AwosStartSetup::waringDatastore(SensorMap senMap)
{
    DataMap dataMap = senMap["WARData"];
    //qDebug()<<"Vis data store:"<<dataMap;
    int tableNum = proData->databaseTables->tableWaringIfo
            ->value("tablesWaring/tableNum").toInt();
    QString tableName;
    QString tableField;
    QStringList tableFiledList;
    QString tableFiledStr;
    QString tableDataStr;
    for(int i = 1;i <= tableNum;i++){
        tableName = proData->databaseTables->tableWaringIfo
                ->value(QString("tables/table%1Name").arg(i)).toString().trimmed();
        tableFiledList = proData->databaseTables->tableWaringIfo
                ->value(QString("tables/table%1Field").arg(i)).toString().split(",");
        int dataNum = tableFiledList.length();
        for(int j = 0;j < dataNum;j++){
            tableField = tableFiledList.at(j).split(":").at(0).trimmed();
            if(j == (dataNum - 1)){
                tableFiledStr = tableFiledStr + "SC_" + tableField;
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'";
            }else{
                tableFiledStr = tableFiledStr + "SC_" + tableField + ",";
                tableDataStr = tableDataStr + "'"
                        + dataMap[tableField].split(":").at(0) + "'" + ",";
            }
        }
        //qDebug()<<"table name:"<<tableName;
        //qDebug()<<"table tableFielStr:"<<tableFiledStr;
        //qDebug()<<"table tableDataStr:"<<tableDataStr;
        database->addData(tableName,tableFiledStr,tableDataStr);
    }
    dataMap.clear();
}

void AwosStartSetup::userDataSearch(QString option,LoginQueue info)
{
    qDebug()<<"option:"<<option<<"user data:"<<info;
    if(option == "user_putIn"){
        QString name,password,grade
                ,passwordStr,gradeStr;
        QStringList userList,subList;
        name = info.dequeue();
        userList = database->getUserData(name);
        qDebug()<<"users Data:"<<userList;
        password = info.dequeue();
        grade = info.dequeue();
        int count = userList.length();
        for(int n = 0;n < count;n++){
            subList.clear();
            passwordStr.clear();
            subList = userList.value(n).split("/");
            passwordStr = subList.value(0);
            passwordStr = passwordStr.split(":").value(1);
            if(passwordStr == password){
                //qDebug()<<"find password.";
                gradeStr.clear();
                gradeStr = subList.value(1);
                gradeStr = gradeStr.split(":").value(1);
                if(grade == gradeStr){
                    //qDebug()<<"find Grade";
                    //qDebug()<<"ok pass over!";
                    _set_User_Infromations(name,password,grade);
                    emit loginPassSate("pass");
                    return ;
                }
            }
        }
        qDebug()<<"sorry,not have this user!";
        emit loginPassSate("error");
    }
    else if(option == "user_putout"){
        //从数据库中获取数据
    }
    else{
        return ;
    }
}

void AwosStartSetup::initSetupTimer(bool falg)
{
    if(falg){
        setupTimer = new QTimer(this);
        connect(setupTimer,SIGNAL(timeout())
                ,SLOT(initStartSystem()));
        setupTimer->start(100);
    }
}

void AwosStartSetup::addWaringMap(SensorMap senMap)
{
    QString waringStr;
    DataMap waringMap = senMap["WARData"];
    QStringList keyList = waringMap.keys();
    for(int key = 0;key < keyList.length();key++){
        waringStr = waringStr + keyList.value(key) + ":"
                + waringMap[keyList.value(key)] + ",";
    }
    proData->waring->notDealdList.push_back(waringStr);

    //add to ui
    emit waringMessageList(proData->waring->notDealdList);

    //add to database store
    emit waringMessageStr(senMap);
}

void AwosStartSetup::openOrcloseContrls( bool flag )
{
    //qDebug()<<"Update main UI From Size";
    int num = proData->awosDataModel->inUsedWay->roseAreaList.length();
    for(int i = 0; i < num;i++){
        if(proData->awosDataModel->inUsedWay->roseAreaList.value(i)
                ->runWayId() == currentwindareaFlag){
            if(flag){
                proData->awosDataModel->inUsedWay->roseAreaList.value(i)->show();
            }
            else{
                proData->awosDataModel->inUsedWay->roseAreaList.value(i)->hide();
            }
        }
    }
    num = proData->awosDataModel->inUsedWay->dataAreaList.length();
    for(int i = 0; i < num;i++){
        if(proData->awosDataModel->inUsedWay->dataAreaList.value(i)
                ->runWayId() == currentdataAreaFlag){
            if(flag){
                proData->awosDataModel->inUsedWay->dataAreaList.value(i)->show();
            }
            else{
                proData->awosDataModel->inUsedWay->dataAreaList.value(i)->hide();
            }
        }
    }
    num = proData->awosDataModel->inUsedWay->runwaylist.length();
    for(int i = 0; i < num;i++){
        if(proData->awosDataModel->inUsedWay->runwaylist.value(i)
                ->runWayId() == currentShowRunWayID){
            if(flag){
                proData->awosDataModel->inUsedWay->runwaylist.value(i)->show();
            }
            else{
                proData->awosDataModel->inUsedWay->runwaylist.value(i)->hide();
            }
        }
    }
    num = proData->awosDataModel->inUsedWay->cloudSensorList.length();
    for(int i = 0; i < num;i++){
        int runWayId = proData->awosDataModel->inUsedWay
                ->cloudSensorList.value(i)->runWayId();
        if( runWayId == currentShowRunWayID ){
            if(flag){
                proData->awosDataModel->inUsedWay->cloudSensorList.value(i)->show();
            }
            else{
                proData->awosDataModel->inUsedWay->cloudSensorList.value(i)->hide();
            }
        }
    }
}

void AwosStartSetup::AFTNSetSlot(MeaagseQueue queue)
{
    qDebug()<<"aftn:"<<queue;

    //AFTN 配置设置
    SC_COMMD commd;
    QDateTime now = QDateTime::currentDateTime();
    QDateTime xmas(QDate(1970, 1, 1),QTime(8, 0));
    quint64 utcSecs = xmas.secsTo(now);
    commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
    commd.enqueue("SC_AFTN_Config_Set:I:M:3:NULL");
    commd.enqueue("ID3616:I:N:15:NULL");
    commd.enqueue("AirPortName:S:N:06:NULL");
    commd.enqueue("AirPortID:I:N:15:NULL");
    commd.enqueue("AFTNaddr:S:N:" + queue.dequeue() + ":NULL");
    commd.enqueue("ChannelName:S:N:" + queue.dequeue() + ":NULL");
    commd.enqueue("CrownWord:S:N:" + queue.dequeue() + ":NULL");
    commd.enqueue("NumberLength:I:N:" + queue.dequeue() + ":NULL");
    commd.enqueue("SendHead:I:N:" + queue.dequeue() + ":NULL");
    commd.enqueue("SendTail:I:N:" + queue.dequeue() + ":NULL");
    commd.enqueue("SendSeparator:I:N:" + queue.dequeue() + ":NULL");
    commd.enqueue("SendLineBreak:I:N:" + queue.dequeue() + ":NULL");
    commd.enqueue("ReciveHead:I:N:" + queue.dequeue() + ":NULL");
    commd.enqueue("ReciveTail:I:N:" + queue.dequeue() + ":NULL");
    commd.enqueue("SendAddr:S:N:" + queue.dequeue() + ":NULL");
    dataSend->dataUnit3616MessageDue("SC_AFTN_Config_Set",commd);
}

void AwosStartSetup::sendMetarTrandRequestSlot(MeaagseQueue queue)
{
    SC_COMMD commd;
    QDateTime now = QDateTime::currentDateTime();
    QDateTime xmas(QDate(1970, 1, 1),QTime(8, 0));
    quint64 utcSecs = xmas.secsTo(now);
    commd.enqueue(QString("TIME:I:N:%1:NULL").arg(utcSecs));
    commd.enqueue("SC_AFTN_MessageSend_Set:I:M:2:NULL");
    commd.enqueue("ID3616:I:N:15:NULL");
    commd.enqueue("AirPortID:I:N:15:NULL");
    commd.enqueue("Message:S:N:" + queue.dequeue() + ":NULL");
    commd.enqueue("MessageID:I:N:12:NULL");
    commd.enqueue("Rank:S:N:" + queue.dequeue() + ":NULL");
    commd.enqueue("ReciveAddr:S:N:" + queue.dequeue() + ":NULL");
    dataSend->dataUnit3616MessageDue("SC_AFTN_MessageSend_Set",commd);
}

void AwosStartSetup::showForCasterTrendUI(QString trendStr)
{
    emit noTrendMetarCtxSignal(trendStr);
    trendMetar->show();
}

void AwosStartSetup::initSetpValue()
{
    setp = 0;
    heartbeatNumber = 0;
}

void AwosStartSetup::initVocies()
{
    voideMor = new QSound("./waring.wav",this);
    voideRvr = new QSound("./waring.wav",this);
}

void AwosStartSetup::awosWaringVoice(WaringTepy waring)
{
    QStringList m_key = m_waringBool.keys();
    QStringList key = waring.keys();
    bool finded = false;
    for(int i = 0; i < m_key.length(); i++){
        if(m_key.value(i) == key.value(0)){
            finded = true;
            m_waringBool[m_key.value(i)] = waring[key.value(0)];
        }
    }
    if(!finded){
        m_waringBool[key.value(0)] = waring[key.value(0)];
    }
    m_key.clear();
    m_key = m_waringBool.keys();
    for(int j = 0; j < m_key.length(); j++){
        if(m_key.value(j) == "mor" && m_waringBool[m_key.value(j)] == true){
            voideMor->setLoops(1);
            voideMor->play();
        }
        if(m_key.value(j) == "rvr" && m_waringBool[m_key.value(j)] == true){
            voideRvr->setLoops(1);
            voideRvr->play();
        }
    }
}

void AwosStartSetup::_init_User_Infromations()
{
    _name = "NULL";
    _password = "NULL";
    _grade = "NULL";
}

void AwosStartSetup::_set_User_Infromations(
         QString _nameStr
        ,QString _passwordStr
        ,QString _gradeStr)
{
    _name.clear();
    _password.clear();
    _grade.clear();
    _name = _nameStr;
    _password = _passwordStr;
    _grade = _gradeStr;
}
