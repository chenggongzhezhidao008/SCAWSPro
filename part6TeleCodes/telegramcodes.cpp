#include "telegramcodes.h"

TelegramCodes::TelegramCodes(QObject *parent) :
    QObject(parent){}

QString TelegramCodes::getWindCodec(  QString tenAvgAngle  // 十分钟平均风向
                                     ,QString tenAvgSpeed  //十分钟平均风速
                                     ,QString tenMinAngle  //风向十分钟最小值
                                     ,QString tenMaxAngle  //风向十分钟最大值
                                     ,QString SHwindSpeed)  //阵风数值
{
    QString  teleTenAvgDegStr //十分钟风向平均值电报字符串
            ,teleTenSpeedStr  //风速电报字符串
            ,teleTenMinDegStr //十分钟风向最小值电报字符串
            ,teleTenMaxDegStr //十分钟风向最大值电报字符串
            ,teleSHSpeedStr;  //十分钟风向平均值电报字符串
    //一，编报内容
    //1.角度转换
    teleTenAvgDegStr = windAngleTranslate(tenAvgAngle);
    teleTenMinDegStr = windAngleTranslate(tenMinAngle);
    teleTenMaxDegStr = windAngleTranslate(tenMaxAngle);
    //2.风速转换
    teleTenSpeedStr = windSpeedTranslate(tenAvgSpeed);
    //3.阵风转换
    teleSHSpeedStr = windGustSpeedTranslate(SHwindSpeed);
    qDebug()<<"teleTenAvgDegStr"<<teleTenAvgDegStr
            <<"teleTenMinDegStr"<<teleTenMinDegStr
            <<"teleTenMaxDegStr"<<teleTenMaxDegStr
            <<"teleTenSpeedStr"<<teleTenSpeedStr;

    // 二，编报条件控制
    int wTenAvgAngle,wTenAvgSpeed,TenMinAngle,TenChangAngle,TenMaxAngle;
    wTenAvgAngle = tenAvgAngle.split(".").value(0).toInt();
    wTenAvgSpeed = tenAvgSpeed.split(".").value(0).toInt();
    TenMinAngle  = teleTenMinDegStr.split(".").value(0).toInt();
    TenMaxAngle  = teleTenMaxDegStr.split(".").value(0).toInt();
    qDebug()<<"TenAvgAngle"<<wTenAvgAngle
            <<"TenAvgSpeed"<<wTenAvgSpeed
            <<"TenMinAngle"<<TenMinAngle
            <<"TenMaxAngle"<<TenMaxAngle;
    TenChangAngle = 0;

    // 求出风向角度变化范围
    if(TenMinAngle > TenMaxAngle){
        if(TenMinAngle == 360){;}
        else{
            TenChangAngle = 360 - TenMinAngle;
        }
        TenChangAngle = TenChangAngle + TenMaxAngle;
    }
    else{
        TenChangAngle = TenMaxAngle - TenMinAngle;
    }
    qDebug()<<"tenChangAngle:"<<TenChangAngle
              <<"GustSpeed:"<<teleSHSpeedStr;
    // 编报
    QString windCodcStr = "";
    //1.条件判断
    if(wTenAvgSpeed == 0){
        windCodcStr = "00000MPS";
    }
    else if(TenChangAngle < 60){
        if(wTenAvgSpeed >= 50){
            if(teleSHSpeedStr != "NotData"){
                windCodcStr = QString("%1P49%2MPS").arg(teleTenAvgDegStr).arg(teleSHSpeedStr);
            }
            else{
                windCodcStr = QString("%1P49MPS").arg(teleTenAvgDegStr);
            }
        }
        else
        {
            if(teleSHSpeedStr != "NotData"){
                windCodcStr = QString("%1%2%3MPS").arg(teleTenAvgDegStr).arg(teleTenSpeedStr).arg(teleSHSpeedStr);
            }
            else{
                windCodcStr = QString("%1%2MPS").arg(teleTenAvgDegStr).arg(teleTenSpeedStr);
            }
        }
    }
    else if(TenChangAngle >= 60 && TenChangAngle < 180){
        if(wTenAvgSpeed < 2){
            if(teleSHSpeedStr != "NotData"){
                windCodcStr = QString("VRB%1%2MPS").arg(teleTenSpeedStr).arg(teleSHSpeedStr);
            }
            else{
                windCodcStr = QString("VRB%1MPS").arg(teleTenSpeedStr);
            }
        }
        else if(wTenAvgSpeed >= 2){
            if(wTenAvgSpeed >= 50){
                if(teleSHSpeedStr != "NotData"){
                    windCodcStr = QString("%1P49%2MPS %3V%4").arg(teleTenAvgDegStr)
                            .arg(teleSHSpeedStr).arg(teleTenMinDegStr).arg(teleTenMaxDegStr);
                }
                else{
                    windCodcStr = QString("%1P49MPS %2V%3").arg(teleTenAvgDegStr)
                            .arg(teleTenMinDegStr).arg(teleTenMaxDegStr);
                }
            }
            else
            {
                if(teleSHSpeedStr != "NotData"){
                    windCodcStr = QString("%1%2%3MPS %4V%5")
                            .arg(teleTenAvgDegStr)
                            .arg(teleTenSpeedStr).arg(teleSHSpeedStr)
                            .arg(teleTenMinDegStr).arg(teleTenMaxDegStr);
                }
                else{
                    windCodcStr = QString("%1%2MPS %3V%4").arg(teleTenAvgDegStr)
                            .arg(teleTenSpeedStr).arg(teleTenMinDegStr)
                            .arg(teleTenMaxDegStr);
                }
            }
        }
        else{
            ;
        }
    }
    else if(TenChangAngle >= 180){
        if(wTenAvgSpeed >= 50){
            if(teleSHSpeedStr != "NotData"){
                windCodcStr = QString("VRBP49%1MPS").arg(teleSHSpeedStr);
            }
            else{
                windCodcStr = QString("VRBP49MPS");
            }
        }
        else
        {
            if(teleSHSpeedStr != "NotData"){
                windCodcStr = QString("VRB%1%2MPS").arg(teleTenSpeedStr).arg(teleSHSpeedStr);
            }
            else{
                windCodcStr = QString("VRB%1MPS").arg(teleTenSpeedStr);
            }
        }
    }
    return windCodcStr;
}

QString TelegramCodes::getMorCodes( //QString tenAvgMor    (暂时不用)   //合肥处理方式 求取三个RVR后最为能见度
                                    QString rowVis
                                   ,QString tenAvgRVR   // vis < 2000 取RVR中的最大的一值
                                   ,QString sensor_Vis10m)
{
    QString morCodesStr;
    int v_rowVis,v_tenAvgRVR,v_sensor_Vis10m;
    v_rowVis = rowVis.split(".",QString::SkipEmptyParts).value(0).toInt();
    v_tenAvgRVR = tenAvgRVR.split(".",QString::SkipEmptyParts).value(0).toInt();
    v_sensor_Vis10m = sensor_Vis10m.split(".",QString::SkipEmptyParts).value(0).toInt();
    if(v_rowVis > 10000){
       morCodesStr = "9999";
    }
    else if(v_rowVis > 2000){
       int len;
       len = 0;
       len = QString("%1").arg(v_sensor_Vis10m).length();
       if(len == 0){
           morCodesStr = "0000";
       }
       else if(len == 1){
           morCodesStr = QString("000%1").arg(v_sensor_Vis10m);
       }
       else if(len == 2){
           morCodesStr = QString("00%1").arg(v_sensor_Vis10m);
       }
       else if(len == 3){
           morCodesStr = QString("0%1").arg(v_sensor_Vis10m);
       }
       else if(len == 4){
           morCodesStr = QString("%1").arg(v_sensor_Vis10m);
       }
    }
    else{ // <2000  //邢的理解
        int len;
        len = 0;
        len = QString("%1").arg(v_tenAvgRVR).length();
        if(len == 0){
            morCodesStr = "0000";
        }
        else if(len == 1){
            morCodesStr = QString("000%1").arg(v_tenAvgRVR);
        }
        else if(len == 2){
            morCodesStr = QString("00%1").arg(v_tenAvgRVR);
        }
        else if(len == 3){
            morCodesStr = QString("0%1").arg(v_tenAvgRVR);
        }
        else if(len == 4){
            morCodesStr = QString("%1").arg(v_tenAvgRVR);
        }
    }
    return morCodesStr;

//    QString tempTenAvgMor,teleTenAvgMor;
//    tempTenAvgMor = morTranslate(tenAvgMor);
//    if(tempTenAvgMor != "NotData"){
//        teleTenAvgMor = tempTenAvgMor;
//    }
//    else{
//        teleTenAvgMor = "";
//    }
//    return teleTenAvgMor;

}

QString TelegramCodes::getRvrCodes(   QString tenAvgRvr   // 正在使用的跑道的接触地带RVR
                                      ,QString tenMinRvr   // 正在使用的跑道10分钟最小RVR
                                      ,QString tenMaxRvr    // 正在使用的跑道10分钟最大RVR
                                      ,QString tenAvgVis   // 主导能见度值（合肥取法直接取电报中的能见度报的数据）
                                      ,QString runWayNUmber // 注：必须练R/L 带上，在平行跑道时
                                      ,QString rvrTrend)
// 多条在用跑道 接触地带 生成多组 RXX/XXXX 类型metar报数据时需多次调用此函数。
{
    QString RVRCodeStr;
    RVRCodeStr = "";
    QString  teleTenAvgRvrStr //十分钟跑道视程平均值电报字符串
            ,teleTenMinRvrStr  //十分钟跑道视程最小值电报字符串
            ,teleTenMaxRvrStr ;//十分钟跑道视程最大值电报字符串
    //一，编报内容
    int  ntenAvgRvr,ntenMinRvr,ntenMaxRvr,ntenAvgVis;
    //1.角度转换
    teleTenAvgRvrStr = rvrTranslate(tenAvgRvr);
    teleTenMinRvrStr = rvrTranslate(tenMinRvr);
    teleTenMaxRvrStr = rvrTranslate(tenMaxRvr);

    ntenAvgRvr = rvrValueTranslate(teleTenAvgRvrStr);
    ntenMinRvr = rvrValueTranslate(teleTenMinRvrStr);
    ntenMaxRvr = rvrValueTranslate(teleTenMaxRvrStr);
    ntenAvgVis = tenAvgVis.toInt(); // 如果使用非报内容的能见度，需修改。
    if((ntenAvgVis == -1) || (ntenAvgRvr == -1)){
        qDebug()<<"data is lost ,canot edit mater.";
        return "";
    }
    // 2.极值判断
    if((ntenMinRvr  == -1) || (ntenMaxRvr  == -1)){
        qDebug()<<"not way get extremum calc";
    }
    bool extreFlag;
    extreFlag = false;
    int extreValue,extremum1,extremum2 ,avgPrint20;
    extreValue = 0;
    extremum1 = 0;
    extremum2 = 0;
    avgPrint20 = 0;
    extremum1 = qAbs(ntenAvgRvr - ntenMinRvr);
    extremum2 = qAbs(ntenAvgRvr - ntenMaxRvr);
    avgPrint20 = ntenAvgRvr / 5;
    extreValue = qMax(extremum1,extremum2);
    if((extreValue > 50) || (extreValue > avgPrint20)){
        extreFlag = true;
    }
    //3.趋势判断
    if(rvrTrend == "///") // 无趋势
    {
        rvrTrend = "";
    }
    //2.条件判断
    if((tenAvgVis.toInt() < 1500)) // 能见度小于 1500 时传入的在用跑道端按此条件编报组
    {  //条件是：主导能见度小于1500 ，不管RVR多少 都要编报
        if(extreFlag){
            RVRCodeStr = QString("R%1/%2V%3%4")
                    .arg(runWayNUmber)
                    .arg(teleTenMinRvrStr)
                    .arg(teleTenMaxRvrStr)
                    .arg(rvrTrend);
        }
        else if(teleTenAvgRvrStr == "P2000")// 超过2000时不加 U/N/D;
        {
            RVRCodeStr = QString("R%1/P2000").arg(runWayNUmber);

        }
        else{
            RVRCodeStr = QString("R%1/%2").arg(runWayNUmber).arg(teleTenAvgRvrStr);
        }
    }
    else if(ntenAvgRvr < 1500) // 能见度不小于 1500 且 RVR 值小于 1500时传入的在用跑道端按此条件编报组
    {//条件是：主导能见度不小于1500 ，RVR小于1500 要编报
        if(extreFlag){
            RVRCodeStr = QString("R%1/%2V%3%4")
                    .arg(runWayNUmber)
                    .arg(teleTenMinRvrStr)
                    .arg(teleTenMaxRvrStr)
                    .arg(rvrTrend);
        }
        else{
            if(ntenAvgRvr == 50){
                RVRCodeStr = QString("R%1/%2")
                        .arg(runWayNUmber)
                        .arg(teleTenAvgRvrStr);
            }
            else{
                RVRCodeStr = QString("R%1/%2%3")
                        .arg(runWayNUmber)
                        .arg(teleTenAvgRvrStr)
                        .arg(rvrTrend);
            }
        }
    }
    else{
        return ""; //不满足编报此组报文，编报；
    }
    return RVRCodeStr;
}

QString TelegramCodes::getWeatherCodes(QString weather)   //天气信息数据
{
    QString weatherCodeStr;
    if(weather == "///"){
        weatherCodeStr = "DataLost";
    }
    else if(weather == ""){
        weatherCodeStr = "NotWeather";
    }
    else{
        weatherCodeStr = weather;
    }

    // 注释：天气的METAR数据主要已经由传感器进行判断处理
    //,故此处不再做条件约束方面处理.

    // if(附录a描述){
    //   if(DZ || RA || SN || SG || IC || PL || GR
    //   || GS || SH(描述词类 指：阵型降水)|| SS || DS){
    //   {
    //   }
    //
    //
    //
    // }
    // else{;}

    return weatherCodeStr;
}

QString TelegramCodes::getCloudCodes( QString isSkyClear  //   是否为晴空
                                      ,QString isVerVis    //   是否能测量垂直能见度
//                                      ,QString /*verVisE5*/    //   5分钟垂直能见度值
                                      ,QString cloudBase   //   云底高度值
//                                      ,QString /*cloudBaseE5*/ //   5分钟最低云快高度(维萨拉不提供这数据)
                                      ,QString ch1Ins30    //   30分钟第一层云高
                                      ,QString ch2Ins30    //   30分钟第二层云高
                                      ,QString ch3Ins30    //   30分钟第三层云高
                                      ,QString amount1_30  //   30分钟第一层云量
                                      ,QString amount2_30  //   30分钟第二层云量
                                      ,QString amount3_30  //   30分钟第三层云量
                                      )
{
    QString cloudCodeStr;
    cloudCodeStr = "";

    bool isclear;
    bool isVVis;
    //是否有云判断
    isclear = false;
    if(isSkyClear.isEmpty()){
        qDebug()<<"sky clear data lost.";
    }
    if(isSkyClear == "1"){
        isclear = true;
    }
    else if(isSkyClear == "0"){
        isclear = false;
    }

    // 是否探测到垂直能见度
    isVVis = false;
    if(isVerVis.isEmpty()){
        qDebug()<<"V vis data lost.";
    }
    if(isVerVis == "1"){
        isVVis = true;
    }
    else if(isVerVis == "0"){
        isVVis = false;
    }
    // 判断是否有对飞行存在影响的云;处理后如果effectFly 为false &&
    //isclear 为 false 则可报NSC(非晴空；有云；但对飞行没影响)
    bool effectFly;
    effectFly = false;
    if(!cloudBase.isEmpty()){
        if(cloudBase.toInt() >= 3000){
            effectFly = true;
        }
    }
    //处理云高，编报数据处理
    QString hightOne,hightTwo,hightThreed;
    QString amountOne,amountTwo,amountThreed;
    hightOne = getCloudHight(ch1Ins30);
    hightTwo = getCloudHight(ch2Ins30);
    hightThreed = getCloudHight(ch3Ins30);
    amountOne = threeCodc(amount1_30);
    amountTwo = threeCodc(amount2_30);
    amountThreed = threeCodc(amount3_30);
    qDebug()<<"isclear:"<<isclear
            <<"isVVis:"<<isVVis
            <<"hightOne:"<<hightOne
            <<"hightTwo:"<<hightTwo
            <<"hightThreed:"<<hightThreed
            <<"amountOne:"<<amountOne
            <<"amountTwo:"<<amountTwo
            <<"amountThreed:"<<amountThreed;
    //云编报条件控制     amountThreed
    if(isclear){ // （人工参与的环节）当满足此条件时如果人工发现有云存在且在综合CAVOK条件后没报CAVOK时
        //，则需人工编报为NSC
        if(!isVVis){ //晴空万里且没有垂直能见度
            cloudCodeStr = "SKC";//（此处可能要修改）在SKC的情况下垂直能见度怎么编报待研究
            // 当报上SKC时是云高仪探测到的天空晴空无云
        }
        else{
            //能见度受FG,SS,DS,BR,FU,HZ,DU,IC,SA 限制，不编报垂直能见度。
            cloudCodeStr = "SKC";
        }
    }
    else{ //（人工参与的环节）
        // 1.当满足此条件时如果人工发现有积雨云CB或者浓积云TCU时，
        //则需人工编报在云高数据后加上CB/TCU代表字码
        // 2.当发现两者同时出现时则另加一组编报，内容为 XX XXX CB/TCU,
        // 两者量少时编报，内容为 FEW XX XXX CB/TCU
        // 3.当发现其他少量云时，可人工改为SKC，
        // 注意改为SKC后做CAVOK检查操作（检查是否满足CAVOK编报）
        if(effectFly){ //非晴空，有云但对飞行无影响
            cloudCodeStr = "NSC";
        }
        else{ //非晴空 有对飞行有影响的云 直接编报云族
            //判断云量三字码，报处理好的云高带入，编报内容
            if((!hightOne.isEmpty()) && (!amountOne.isEmpty()))
            {
                cloudCodeStr = QString("%1%2")
                        .arg(amountOne)
                        .arg(hightOne);
            }
            if((!hightTwo.isEmpty()) && (!amountTwo.isEmpty()))
            {
                cloudCodeStr = QString("%1 %2%3")
                        .arg(cloudCodeStr)
                        .arg(amountTwo)
                        .arg(hightTwo);
            }
            if((!hightThreed.isEmpty()) && (!amountThreed.isEmpty()))
            {
                cloudCodeStr = QString("%1 %2%3")
                        .arg(cloudCodeStr)
                        .arg(amountThreed)
                        .arg(hightThreed);
            }
        }
    }
    return cloudCodeStr;
}

QString TelegramCodes::getTempretrueDewCodes(QString tempretrue
                                             ,QString dew)
{
    QString tempDewCodecStr;
    QString teleTempStr,teleDewStr;
    float fTempretrue,fDew,tempMode,dewMode;
    int interTemp,interDew;
    interTemp = tempretrue.split(".").value(0).toInt();
    interDew = dew.split(".").value(0).toInt();
    fTempretrue = tempretrue.toFloat();
    fDew = dew.toFloat();
    tempMode = fmodf(fTempretrue,1.0);
    dewMode = fmodf(fDew,1.0);
    qDebug()<<"temp:"<<tempMode<<"few:"<<dewMode<<"fTempretrue"<<fTempretrue;
    if(qAbs(tempMode) >= 0.50f){
        if(fTempretrue < 0.0f){
            interTemp = interTemp - 1;
        }
        else{
            interTemp = interTemp + 1;
        }
    }
    else{
//        interTemp = tempretrue.toInt();
    }
    if(qAbs(dewMode) >= 0.50){
        if(fDew < 0.0f){
            interDew = interDew - 1;
        }
        else{
            interDew = interDew + 1;
        }
    }
    else{
//        interDew = dew.toInt();
    }
    qDebug()<<QString("temp:%1;dew:%2.").arg(interTemp).arg(interDew);
    teleTempStr = QString("%1").arg(interTemp);
    teleDewStr = QString("%1").arg(interDew);
    int tempNum,dewNum;
    tempNum = teleTempStr.length();
    dewNum = teleDewStr.length();

    // tempretrue data deal
    if(interTemp < 0){
        if(tempNum == 1){
            teleTempStr = "";
            qDebug()<<"temp data is error!";
        }
        else if(tempNum == 2){
            teleTempStr = QString("M0%1").arg(qAbs(interTemp));
        }
        else if(tempNum == 3){
            teleTempStr = QString("M%1").arg(qAbs(interTemp));
        }
    }
    else{
        if(tempNum == 1){
            teleTempStr = QString("0%1").arg(qAbs(interTemp));
        }
        else if(tempNum == 2){
            teleTempStr = QString("%1").arg(qAbs(interTemp));
        }
        else if(tempNum > 2){
            teleTempStr = "";
            qDebug()<<"temp data is error!";
        }
    }

    //dew data deal
    if(interDew < 0){
        if(dewNum == 1){
            teleDewStr = "";
            qDebug()<<"dew data is error!";
        }
        else if(dewNum == 2){
            teleDewStr = QString("M0%1").arg(qAbs(interDew));
        }
        else if(dewNum == 3){
            teleDewStr = QString("M%1").arg(qAbs(interDew));
        }
    }
    else{
        if(dewNum == 1){
            teleDewStr = QString("0%1").arg(qAbs(interDew));
        }
        else if(dewNum == 2){
            teleDewStr = QString("%1").arg(qAbs(interDew));
        }
        else if(dewNum > 2){
            teleDewStr = "";
            qDebug()<<"dew data is error!";
        }
    }

    //最后做数据是否丢失检查。
    if((!teleDewStr.isEmpty()) && (!teleDewStr.isEmpty())){
        tempDewCodecStr = QString("%1/%2").arg(teleTempStr).arg(teleDewStr);
    }
    else{
        qDebug()<<"lost data of temp & dew!";
        tempDewCodecStr = "";
    }
    return tempDewCodecStr;
}

QString TelegramCodes::getPressCodes(QString QNHPress)
{
    QString pressCodecStr;
    int pressNum;
    pressNum = 0;
    if(QNHPress.isEmpty() || QNHPress == "///"){
        pressCodecStr = "";
        qDebug()<<"press data is lost!";
    }
    else{
        pressCodecStr = QNHPress.split(".").value(0);
        pressNum = pressCodecStr.length();
        if(pressNum == 1){
            pressCodecStr = QString("Q000%1").arg(pressCodecStr);
        }
        else if(pressNum == 2){
            pressCodecStr = QString("Q00%1").arg(pressCodecStr);
        }
        else if(pressNum == 3){
            pressCodecStr = QString("Q0%1").arg(pressCodecStr);
        }
        else if(pressNum == 4){
            pressCodecStr = QString("Q%1").arg(pressCodecStr);
        }
        else{
            pressCodecStr = "";
            qDebug()<<"data Lost!";
        }
    }
    return pressCodecStr;
}

//只支持一个机场一个天气现象仪的条件
QString TelegramCodes::getCAVOKCodes( //QString morVlaue   // 这里输入从所有VIS数据中的mor中求得的均值不能判断CAVOK
                                      /*,*/
                                      QString visValue   //暂时用主导能能见度辅助判断（因为每次CAVOK时vis都达到10000）
                                      //                                      ,QString isSkyClear // 是否晴空
                                      ,QString teleCloudCodec // 云数据电报内容
                                      ,QString weather)   // 天气现象
{
    int vis;
    vis = visValue.toInt();

    // 判断是否是晴空万里
    bool effectFly;
    effectFly = true;
    //    int clearValue;
    //    clearValue = -1;
    //    clearValue = isSkyClear.toInt();
    //    if(clearValue == 1){
    //        effectFly = true;
    //    }
    if(teleCloudCodec == "NSC" || teleCloudCodec == "SKC"){
        effectFly = false;
    }
    else{
        effectFly = true;
    }

    //判断是否是满足附录A中所列的重要天气现象
    bool isNotAffixA;
    isNotAffixA = false;
    QString tempWeatherStr;
    tempWeatherStr = weather;
    if(tempWeatherStr == "///"){
        isNotAffixA = true;
    }
    else if(tempWeatherStr.isEmpty()){
        isNotAffixA = true;
    }

    //判断是否满足CAVOK的所有条件
    bool isCavOk;
    isCavOk = false;
    if((vis >= 10000) && !effectFly && isNotAffixA){
        isCavOk = true;
    }
    if(!isCavOk){
        return "NOCAVOK";
    }
    return QString("CAVOK");
}

void TelegramCodes::checkCavok(QString visValue, QString teleCloudCodec, QString weather)
{
    QString codec;
    codec = getCAVOKCodes(visValue,teleCloudCodec,weather);
    emit returnCavokCode(codec);
}

// 风要素编报内容风向角度数据转换
QString TelegramCodes::windAngleTranslate(QString angleStr)
{
    QString teleAngleStr;
    int tempAngle,wModAngle,wAngle;
    // 转换角度(4四舍五入转换)
    // 1.风向角度
    tempAngle = 0;
    wModAngle = 0;
    wAngle = 0;
    tempAngle = angleStr.split(".").value(0).toInt();
    wModAngle = tempAngle % 10;
    if(wModAngle < 5){
        wAngle = (tempAngle / 10)* 10;
    }
    else{
        wAngle = (tempAngle / 10 +1)* 10;
    }
    teleAngleStr = QString("%1").arg(wAngle);
    int charNum = teleAngleStr.length();
    if(charNum == 0){
        teleAngleStr = "ERR";
    }
    else if(charNum == 1){
        teleAngleStr = "360";//出现1~9度，出现取零；
    }
    else if(charNum == 2){
        teleAngleStr = QString("0%1").arg(teleAngleStr);
    }
    else if(charNum == 3){
        ;
    }
    else{
        teleAngleStr = "ERR";
    }
    return teleAngleStr;
}

QString TelegramCodes::windSpeedTranslate(QString speedStr)
{
    QString windSpeedStr;
    int windSpeed;
    windSpeed = 0;
    QStringList speedlist;
    speedlist =  speedStr.split("/",QString::SkipEmptyParts);
    if(speedlist.length() < 1){
        return QString("ER");
    }
    windSpeed = speedStr.split(".").value(0).toInt()/*.toInt()*/;
    float modeV;
    //modeV = speedStr.toFloat() / 1.00; // 需检查是否转换成功
    modeV = fmodf(speedStr.toFloat(),1.00);
    qDebug()<<QString("wind speed translate->modV:%1").arg(modeV);
    //modeV = modeV * 10.0;
    if(modeV >= 0.500){
        windSpeed = windSpeed + 1;
    }
    else {
        ;
    }
    windSpeedStr = QString("%1").arg(windSpeed);
    int speedNum = windSpeedStr.length();
    if(speedNum == 0){
        windSpeedStr = "ER";
    }
    else if(speedNum == 1){
        windSpeedStr = QString("0%1").arg(windSpeed);
    }
    else if(speedNum == 2){
        if(windSpeed >= 50){
            windSpeedStr = QString("P49");
        }
        else{
            ;
        }
    }
    else{
        windSpeedStr = "ER";
    }
    qDebug()<<"Calc value:"<<modeV<<"speed Codec:"<<windSpeedStr;
    return windSpeedStr;
}

QString TelegramCodes::windGustSpeedTranslate(QString speedStr)
{
    QString windGustStr;
    int windGust;
    windGust = 0;
    windGust = speedStr.split(".").value(0).toInt();
    if((speedStr == "///") || (speedStr.isEmpty()) || (windGust == 0)){
        return QString("NotData");
    }
    windGustStr = QString("%1").arg(windGust);
    int gustNum = windGustStr.length();
    if(gustNum == 0){
        windGustStr = "NotData";
    }
    else if(gustNum == 1){
        windGustStr = QString("G0%1").arg(windGust);
    }
    else if(gustNum == 2){
        windGustStr = QString("G%1").arg(windGust);
    }
    else{
        windGustStr = "NotData";
    }
    qDebug()<<"Gust"<<speedStr<<"Gust Codec:"<<windGustStr;
    return windGustStr;
}

QString TelegramCodes::morTranslate(QString morStr)
{
    QString morCodc;
    morCodc = "";
    int tempValue,morValue;
    tempValue = 0;
    morValue = 0;
    if(morStr.isEmpty()){
        return "NotData";
    }
    if(morStr == "///"){
        return "NotData";
    }
    tempValue = morStr.toInt();
    if(tempValue < 800){
        morValue = (tempValue/50) * 50;
    }
    else if((tempValue >= 800) && (tempValue < 5000)){
        morValue = (tempValue / 100) * 100;
    }
    else if((tempValue >= 5000) && (tempValue < 10000)){
        morValue = (tempValue / 1000) * 1000;
    }
    else if(tempValue >= 10000){
        morValue = 9999;
    }
    morCodc = QString("%1").arg(morValue);
    int codcNum = morCodc.length();
    if(codcNum == 0){
        morCodc = "NotData";
    }
    else if(codcNum == 1){
        morCodc = "0000"; //可能此处要处理，能见度低于50时,报4个零
    }
    else if(codcNum == 2){
        morCodc = QString("00%1").arg(morCodc);
    }
    else if(codcNum == 3){
        morCodc = QString("0%1").arg(morCodc);
    }
    else{
        ;
    }
    return morCodc;
}

QString TelegramCodes::rvrTranslate(QString rvr)
{
    QString rvrCodec;
    int tempRvrValue,rvrValue;
    tempRvrValue = 0;
    rvrValue = 0;
    tempRvrValue = rvr.toInt();
    if(tempRvrValue < 50){
        rvrCodec = "M0050";
        return rvrCodec;
    }
    else if((tempRvrValue >= 50) && (tempRvrValue < 400)){
        rvrValue = (tempRvrValue / 25) * 25;
    }
    else if((tempRvrValue >= 400) && (tempRvrValue <= 800)){
        rvrValue = (tempRvrValue / 50) * 50;
    }
    else if((tempRvrValue > 800) && (tempRvrValue <= 2000)){
        rvrValue = (tempRvrValue / 100) * 100;
    }
    else if(tempRvrValue > 2000){
        rvrCodec = "P2000";
        return rvrCodec;
    }
    rvrCodec = QString("%1").arg(rvrValue);
    int rvrNum;
    rvrNum = rvrCodec.length();
    if(rvrNum == 0){
        rvrCodec = "NotData";
    }
    else if(rvrNum == 1){
        rvrCodec = "NotData";
    }
    else if(rvrNum == 2){
        rvrCodec = QString("00%1").arg(rvrCodec);
    }
    if(rvrNum == 3){
        rvrCodec = QString("0%1").arg(rvrCodec);
    }
    if(rvrNum == 4){
        ;
    }
    if(rvrNum == 5){
        rvrCodec = "NotData";
    }
    return rvrCodec;
}

int TelegramCodes::rvrValueTranslate(QString teleDataCtx)
{
    int value;
    if(teleDataCtx == "M0050"){
        value = 50;
    }
    else if(teleDataCtx == "P2000"){
        value = 2000;
    }
    else if(teleDataCtx.isEmpty()){
        qDebug()<<"data is lost";
        return -1;
    }
    else{
        value = teleDataCtx.toInt();
    }
    return value;
}

QString TelegramCodes::threeCodc(QString amount)
{
    QString threedCodecStr;
    if(amount == "///"){
        threedCodecStr = "";
        return threedCodecStr;
    }
    int number = amount.toInt();
    if((number > 0) && (number < 3)){
        threedCodecStr = "FEW";
    }
    else if((number > 2) && (number < 5)){
        threedCodecStr = "SCT";
    }
    else if((number > 4) && (number < 8)){
        threedCodecStr = "BKN";
    }
    else if((number >= 8)){
        threedCodecStr = "OVC";
    }
    else{
        threedCodecStr = "";
    }
    qDebug()<<"amount:"<<amount<<"threedCodecStr"<<threedCodecStr;
    return threedCodecStr;
}

QString TelegramCodes::getCloudHight(QString cloudHight)
{
    QString cloudHCodStr;
    if(cloudHight == "///"){
        cloudHCodStr = "";
        return cloudHCodStr;
    }
    int hightValue;
    hightValue = cloudHight.split(".",QString::SkipEmptyParts).value(0).toInt();
    hightValue = hightValue / 30;
    cloudHCodStr = QString("%1").arg(hightValue);
    int len;
    len = cloudHCodStr.length();
    if(len == 0){
        cloudHCodStr = "000";
    }
    else if(len == 1){
        cloudHCodStr = QString("00%1").arg(hightValue);
    }
    else if(len == 2){
        cloudHCodStr = QString("0%1").arg(hightValue);
    }
    else if(len == 3){
        cloudHCodStr = QString("%1").arg(hightValue);
    }
    else{
        ;
    }
    return cloudHCodStr;
}


