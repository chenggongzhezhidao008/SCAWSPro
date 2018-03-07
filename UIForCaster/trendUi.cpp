#include "trendUI.h"

TrendUI::TrendUI(QWidget *parent) :
    QWidget(parent)
{
    initTelegramnLable();
    initTeleStartCtx();
    newAllSubContrls();
    setAllContrlsOnliyRead();
    setAllContrlsGeometry();
    setMetarCodec();
}

void TrendUI::initTelegramnLable()
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

void TrendUI::setUpdateTime(QTime updateTime)
{
    this->m_updateTime = updateTime;
    update();
}

void TrendUI::setToSendTelegramHaveTime(QString toSendTelegramHaveTime)
{
    this->m_haveTime = toSendTelegramHaveTime;
    update();
}
/*   --------------------
 *   function description
 *   （预报员）解析未加趋势的Metar报数据内容
 *   格式：dataName=vlue/dataName2=vlaue2/........
 *   --------------------
 */
void TrendUI::setMetarCtx(QString Str)
{
    QString metarStr;
    QStringList metarlist;
    metarStr = Str.trimmed();
    metarlist = metarStr.split("/");
    m_MetarCodec.clear();
    QString _subCtx,_m_Name,_m_Ctx;
    int len = metarlist.length();
    for(int i = 0;i < len;i++){
        _m_Name.clear();
        _m_Ctx.clear();
        _subCtx = metarlist.value(i);
        _m_Name = _subCtx.split("=").value(0);
        _m_Ctx = _subCtx.split("=").value(1);
        m_MetarCodec[_m_Name] = _m_Ctx;
    }
    setMetarCodec();
}

void TrendUI::setTrendCtx(QString ctx)
{
    TRENDEdit->setText(ctx);
}

/* ---------------------------------------
 *  function description
 *  从界面获取生成报的数据
 *  并做是否满足CAVOK 条件编报
 *  最后把编写出METAR报内容返回
 * ---------------------------------------
 */

telegramCFG TrendUI::getTelegramCtx()
{
    telegramCFG  subMap;
    // 2 . 从界面的各个控件中取值更新，并判断Cavok情况。
    subMap["head"]  = headEdit->text();
    subMap["wind"]  = windEdit->text();
    subMap["vis"]  = visEdit->text();
    subMap["rvr"]  = RVREdit->text();
    subMap["pw"]   = weatherEdit->text();
    subMap["cloud"]  = cloudHightEdit->text();
    subMap["tempdew"] = tempHumEdit->text();
    subMap["press"]    = pressEdit->text();
    subMap["closedpw"] = closeWeatherEdit->text();
    subMap["daomian"]  = MOTNEEdit->text();
    subMap["trend"] = TRENDEdit->text();
    subMap["remak"] = RemarkEdit->text();
    return  subMap;
}

void TrendUI::newAllSubContrls()
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

void TrendUI::setAllContrlsOnliyRead()
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

void TrendUI::setAllContrlsGeometry()
{
    int sHeight = height();
    int subHeight = sHeight / 13 - 8;
    int Swidth2 = width()- 150;
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

void TrendUI::setMetarCodec()
{
    headEdit->setText(m_MetarCodec["head"]);
    windEdit->setText(m_MetarCodec["wind"]);
    visEdit->setText(m_MetarCodec["vis"]);
    RVREdit->setText(m_MetarCodec["rvr"]);
    weatherEdit->setText(m_MetarCodec["pw"]);
    cloudHightEdit->setText(m_MetarCodec["cloud"]);
    tempHumEdit->setText(m_MetarCodec["tempdew"]);
    pressEdit->setText(m_MetarCodec["press"]);
    closeWeatherEdit->setText(m_MetarCodec["closedpw"]);
    MOTNEEdit->setText(m_MetarCodec["daomian"]);
    TRENDEdit->setText(m_MetarCodec["trend"]);
    RemarkEdit->setText(m_MetarCodec["remak"]);
}

void TrendUI::initTeleStartCtx()
{
    m_MetarCodec["head"]   = "ZSOF140000Z";
    m_MetarCodec["wind"]   = "17003MPS100V210";
    m_MetarCodec["vis"]    = "9000";//机场能见度值
    m_MetarCodec["rvr"]    = "2100";//跑道视程
    m_MetarCodec["pw"]     = "-RA";
    m_MetarCodec["cloud"]  = "BKN050";
    m_MetarCodec["tempdew"]  = "24/20";
    m_MetarCodec["press"]  = "Q1007";
    m_MetarCodec["closedpw"]  = "BR";//近时天气
    m_MetarCodec["daomian"] = "";//道面状况
    m_MetarCodec["trend"] = "NOSIG";
    m_MetarCodec["remak"] = "";//备注
}
