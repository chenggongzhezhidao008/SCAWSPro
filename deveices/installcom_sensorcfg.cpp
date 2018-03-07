#include "installcom_sensorcfg.h"

/***********************
 *
 *
 *    安装配置界面 - sensor
 *
 *
 * **********************/
SensorCFGCom::SensorCFGCom(QWidget *parent) :
    QWidget(parent)
{
    initRowsValue();
    ext_setZeroRowsValue();
    initInforCom();
    initCustomMenus();
    initMenuDealsConnection();
    initScrollArea();
    initButton();
    addSubWidget();
    initsizeValue();
    //    initSensorClassData();
}

QString SensorCFGCom::idAirportId() const
{
    return m_idAairportId;
}

void SensorCFGCom::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width()/2,height()/2);

    int cLeft= -width() / 2;
    int cTop = -height() / 2;
    int cWidth = width();
    int cHeight = height();

    int tilteOne[4][2] = {{cLeft,cTop},{cLeft+120,cTop},{cLeft + 140,cTop + cHeight / 32},{cLeft,cTop + cHeight / 32}};
    int tiltetwo[4][2] = {{cLeft,cTop + cHeight * 3 / 16},{cLeft+120,cTop+ cHeight * 3 / 16},{cLeft + 140,cTop + cHeight * 7 / 32},{cLeft,cTop + cHeight  * 7 / 32}};
    int tiltethree[4][2] = {{cLeft,cTop + cHeight/2},{cLeft+120,cTop + cHeight/2},{cLeft + 140,cTop + cHeight *17 / 32},{cLeft,cTop + cHeight  *17 / 32}};
    int tiltefour[4][2] = {{cLeft,cTop + cHeight*3/4},{cLeft+120,cTop + cHeight*3/4},{cLeft + 140,cTop + cHeight *25 / 32},{cLeft,cTop + cHeight  *25 / 32}};

    if(comWidth != cWidth && comHeight != cHeight){
        setHandInforGeomerty();
        setInforComGeometry();
        setButtonGeometry();
    }

    painter.save();
    painter.setBrush(QColor("#4A708B"));
    painter.drawPolygon(QPolygon(4,&tilteOne[0][0]));
    painter.drawPolygon(QPolygon(4,&tiltetwo[0][0]));
    painter.drawPolygon(QPolygon(4,&tiltethree[0][0]));
    painter.drawPolygon(QPolygon(4,&tiltefour[0][0]));
    painter.restore();

    painter.save();
    painter.setPen(QPen(Qt::white,3));
    int csHeight = height() / 32;
    painter.drawText(cLeft + 20,cTop,80,csHeight,Qt::AlignCenter,"WIND");
    painter.drawText(cLeft + 20,cTop + height()*3/16,80,csHeight,Qt::AlignCenter,"VIS");
    painter.drawText(cLeft + 20,cTop + height()/2,80,csHeight,Qt::AlignCenter,"HUMITEMP");
    painter.drawText(cLeft + 20,cTop + height()*3/4,80,csHeight,Qt::AlignCenter,"CUSTOM");
    painter.restore();
}
void SensorCFGCom::setIdAirportId(QString value)
{
    m_idAairportId = value;
}

void SensorCFGCom::backRequeryAFFIX9menberSlot(QString query, InforData menber)
{
    InforMap map;
    int n = menber.count();
    if(n > 0)
    {
        QString str;
        for(int i = 1;i <= n;i++)
        {
            str.clear();
            str = menber[QString("data%1").arg(i)];
            str.replace("=",":");
            str.replace("cardId","链接卡号");
            str.replace("sensorName","传感器名称");
            str.replace(","," ");//"   "
            map[i] = str;
        }
    }
    else
    {
        qDebug()<<"not Data function return.";
        return ;
    }
    qDebug()<<"menber is:"<<menber;
    if(query == "wind_query"){
        qDebug()<<"option is wind_query";
        windRows = n;
        windMap.clear();
        windMap = map;
        addDataToShow("wind");//wind->setDataMap(windMap);
    }
    else if(query == "rvr_query"){
        qDebug()<<"option is rvr_query";
        RVRRows = n;
        RVRMap.clear();
        RVRMap = map;
        addDataToShow("rvr");//RVR->setDataMap(map);
    }
    else if(query == "tempHumi_query"){
        tempHumiRows = n;
        tempHumiMap.clear();
        tempHumiMap = map; qDebug()<<"option is tempHumi_query";
        addDataToShow("tempHumi");   //tempHumi->setDataMap(map);
    }
    else if(query == "custom_query"){
        customRows = n;
        customMap.clear();
        customMap = map;  qDebug()<<"option is custom_query";
        addDataToShow("custom");   //custom->setDataMap(map);
    }
    else{
        return ;
    }
}

void SensorCFGCom::externSensorDealList(SensorMap extenSensor)
{
    ext_setZeroRowsValue(); // 归零所有外部传感器的显示行数
    int len = extenSensor.count();
    DataMap sensorInfo;
    QString typeStr;
    QString extSensorStr;
    qDebug()<<"exten sensorsxxx:"<<extenSensor;
    for(int n = 1;n <= len;n++)
    {
        sensorInfo.clear();
        typeStr.clear();
        extSensorStr.clear();
        sensorInfo = extenSensor[QString("%1").arg(n)];
        extSensorStr = QString("链接数据源:%1 传感器名称:%2 制造厂商:视程科技 编号:%3 地理位置:%4")
                .arg(sensorInfo["Source"]).arg(sensorInfo["Name"])
                .arg(sensorInfo["ID"]).arg(sensorInfo["location"]);
        typeStr =  sensorInfo["Type"];
        qDebug()<<"STR=====:"<<sensorInfo;
        if(typeStr == "wind"){            //在添加外部传感器时添加的类型
            ext_windRows++;
            ext_windMap[ext_windRows] = extSensorStr;
        }
        else if(typeStr == "VIS"){        //在添加外部传感器时添加的类型
            ext_RVRRows++;
            ext_RVRMap[ext_RVRRows] = extSensorStr;
        }
        else if(typeStr == "tempHumi"){   //在添加外部传感器时添加的类型
            ext_tempHumiRows++;
            ext_tempHumiMap[ext_tempHumiRows] = extSensorStr;
        }
        else{                              //在添加外部传感器时添加的类型
            ext_customRows++;
            ext_customMap[ext_customRows] = extSensorStr;
        }
    }
    addDataToShow("all");
}

void SensorCFGCom::addDataToShow(QString kind)
{
    if(kind == "wind")
    {
        wind->setDataMap(sensorDeal(windMap,ext_windMap));
    }
    else if(kind == "rvr")
    {
        RVR->setDataMap(sensorDeal(RVRMap,ext_RVRMap));
    }
    else if(kind == "tempHumi")
    {
        tempHumi->setDataMap(sensorDeal(tempHumiMap,ext_tempHumiMap));
    }
    else if(kind == "custom")
    {
        custom->setDataMap(sensorDeal(customMap,ext_customMap));
    }
    else if(kind == "all")
    {
        wind->setDataMap(sensorDeal(windMap,ext_windMap));
        RVR->setDataMap(sensorDeal(RVRMap,ext_RVRMap));
        tempHumi->setDataMap(sensorDeal(tempHumiMap,ext_tempHumiMap));
        custom->setDataMap(sensorDeal(customMap,ext_customMap));
    }
    setHandInforGeomerty();
    return ;
}

InforMap SensorCFGCom::sensorDeal(InforMap one, InforMap two)
{
    InforMap map;
    map = one;
    for(int n = 1;n <= two.count();n++){
        map[one.count() + n] = two[n];
    }
    return map;
}

void SensorCFGCom::initIdAairportId()
{
    m_idAairportId = "22:33";
}

void SensorCFGCom::initRowsValue()
{
    windRows = 1;
    RVRRows = 1;
    tempHumiRows = 1;
    customRows = 1;
}

void SensorCFGCom::ext_setZeroRowsValue()
{
    ext_windRows = 0;
    ext_RVRRows = 0;
    ext_tempHumiRows = 0;
    ext_customRows = 0;
}

void SensorCFGCom::initInforCom()
{
    InforMap dataList;
    dataList[1] = "";
    dataList[2] = "";
    dataList[3] = "";
    dataList[4] = "";
    dataList[5] = "";
    dataList[6] = "";

    wind = new glableHandInfor(this);
    wind->setDataMap(dataList);
    wind->_set_data_cell_width(150);
    RVR = new glableHandInfor(this);
    RVR->setDataMap(dataList);
    RVR->_set_data_cell_width(150);
    tempHumi = new glableHandInfor(this);
    tempHumi->setDataMap(dataList);
    tempHumi->_set_data_cell_width(150);
    custom = new glableHandInfor(this);
    custom->setDataMap(dataList);
    custom->_set_data_cell_width(150);
}

void SensorCFGCom::setHandInforGeomerty()
{
    wind->setSubWidth(width()- 20);
    RVR->setSubWidth(width()- 20);
    tempHumi->setSubWidth(width()- 20);
    custom->setSubWidth(width()- 20);

    wind->setSubHeight(((18*(windRows + ext_windRows))>(height()/8))? 18*(windRows + ext_windRows) : height()/8);
    RVR->setSubHeight(((18*(RVRRows + ext_RVRRows))>(height()/4))? 18*(RVRRows + ext_RVRRows) : height()/4);
    tempHumi->setSubHeight( ((18*(tempHumiRows + ext_tempHumiRows))>(height()*3/16))? 18*(tempHumiRows + ext_tempHumiRows) : height()*3/16);
    custom->setSubHeight(((18*(customRows + ext_customRows))>(height()*3/16))? 18*(customRows + ext_customRows) : height()*3/16);
}

void SensorCFGCom::initCustomMenus()
{
    QStringList menuList;
    if(wind && RVR && tempHumi && custom){
        menuList<<"wind:刷新"<<"wind:本地添加"
               <<"wind:外部添加"<<"wind:设置"
              <<"wind:关闭";
        wind->setActionName(menuList);
        menuList.clear();
        menuList<<"RVR:刷新"<<"RVR:本地添加"
               <<"RVR:外部添加"<<"RVR:设置"
              <<"RVR:关闭";
        RVR->setActionName(menuList);
        menuList.clear();
        menuList<<"tempHumi:刷新"<<"tempHumi:本地添加"
               <<"tempHumi:外部添加"<<"tempHumi:设置"
              <<"tempHumi:关闭";
        tempHumi->setActionName(menuList);
        menuList.clear();
        menuList<<"custom:刷新"<<"custom:本地添加"
               <<"custom:外部添加"<<"custom:设置"
              <<"custom:关闭";
        custom->setActionName(menuList);
    }
}

void SensorCFGCom::initMenuDealsConnection()
{
    if(wind && RVR && tempHumi && custom){
        connect(wind,SIGNAL(menuOption(QString)),SIGNAL(MenuOptionSlot(QString)));
        connect(RVR,SIGNAL(menuOption(QString)),SIGNAL(MenuOptionSlot(QString)));
        connect(tempHumi,SIGNAL(menuOption(QString)),SIGNAL(MenuOptionSlot(QString)));
        connect(custom,SIGNAL(menuOption(QString)),SIGNAL(MenuOptionSlot(QString)));
    }
}

void SensorCFGCom::initScrollArea()
{
    ScrollAreaWind = new QScrollArea(this);
    ScrollAreaRVR = new QScrollArea(this);
    ScrollAreaTempHumi = new QScrollArea(this);
    ScrollAreaCustom = new QScrollArea(this);
}

void SensorCFGCom::addSubWidget()
{
    if(ScrollAreaWind && ScrollAreaCustom &&
            ScrollAreaTempHumi && ScrollAreaRVR) {
        ScrollAreaWind->setWidget(wind);
        ScrollAreaRVR->setWidget(RVR);
        ScrollAreaTempHumi->setWidget(tempHumi);
        ScrollAreaCustom->setWidget(custom);
    }
}

void SensorCFGCom::setInforComGeometry()
{
    int sWidth = width();
    int sHeight = height();
    if(ScrollAreaWind && ScrollAreaCustom &&
            ScrollAreaTempHumi && ScrollAreaRVR) {
        ScrollAreaWind->setGeometry(0,sHeight/32,sWidth,sHeight/8);
        ScrollAreaRVR->setGeometry(0,sHeight*7/32,sWidth,sHeight/4);
        ScrollAreaTempHumi->setGeometry(0,sHeight*17/32,sWidth,sHeight*3/16);
        ScrollAreaCustom->setGeometry(0,sHeight*25/32,sWidth,sHeight*3/16);
    }
}
// 初始化刷新按钮名称
void SensorCFGCom::initButton()
{
    UpWind = new GlableSelectButton(this);
    UpWind->setNameStr("wind:刷新");
    connect(UpWind,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
    UpRVR = new GlableSelectButton(this);
    UpRVR->setNameStr("RVR:刷新");
    connect(UpRVR,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
    UpTempHumi = new GlableSelectButton(this);
    UpTempHumi->setNameStr("tempHumi:刷新");
    connect(UpTempHumi,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
    UpCustom = new GlableSelectButton(this);
    UpCustom->setNameStr("custom:刷新");
    connect(UpCustom,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
}

void SensorCFGCom::setButtonGeometry()
{
    int right = width();
    int buttonHeight = height()/32;

    UpWind->setGeometry(right - 80,0/*height()*5/32*/,60,buttonHeight);
    UpRVR->setGeometry(right - 80,height()*3/16/*height()*15/32*/,60,buttonHeight);
    UpTempHumi->setGeometry(right - 80,height()*8/16/*height()*23/32*/,60,buttonHeight);
    UpCustom->setGeometry(right - 80,height()*12/16/*height()*31/32*/,60,buttonHeight);
}

void SensorCFGCom::initsizeValue()
{
    comWidth = 0;
    comHeight = 0;
}



