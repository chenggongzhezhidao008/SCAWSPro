#include "installcom_testportcfg.h"
/***********************
 *
 *
 *    安装配置界面 - 测试端口
 *
 *
 * **********************/
TestPortCFGCom::TestPortCFGCom(QWidget *parent) :
    QWidget(parent)
{
    initRowsValue();
    initInforCom();
    initCustomMenus();
    initMenuDealsConnection();
    initScrollArea();
    initButton();
    addSubWidget();
    initsizeValue();
}

QString TestPortCFGCom::idAirportId() const
{
    return m_idAairportId;
}

void TestPortCFGCom::paintEvent(QPaintEvent *e)
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
//    int tiltefour[4][2] = {{cLeft,cTop + cHeight*3/4},{cLeft+120,cTop + cHeight*3/4},{cLeft + 140,cTop + cHeight *25 / 32},{cLeft,cTop + cHeight  *25 / 32}};

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
//    painter.drawPolygon(QPolygon(4,&tiltefour[0][0]));
    painter.restore();

    painter.save();
    painter.setPen(QPen(Qt::white,3));
    int csHeight = height() / 32;
    painter.drawText(cLeft + 20,cTop,80,csHeight,Qt::AlignCenter,"测试机场");
    painter.drawText(cLeft + 20,cTop + height()*3/16,80,csHeight,Qt::AlignCenter,"测试跑道");
    painter.drawText(cLeft + 20,cTop + height()/2,80,csHeight,Qt::AlignCenter,"测试传感器");
//    painter.drawText(cLeft + 20,cTop + height()*3/4,80,csHeight,Qt::AlignCenter,"测试链接状态");
    painter.restore();
}

void TestPortCFGCom::setIdAirportId(QString value)
{
    m_idAairportId = value;
}

void TestPortCFGCom::backAirInfoSlot(SensorMap map)
{
    DataMap data = map["AirportData"];
    int num = m_airpotMap.count();
    if(num == 0){
        m_airpotMap[1] =  "名称:"+ data["AirPortName"]
                + "  ID编号:"+ data["AirPortID"]
                + "  代码:"+ data["AirPortCode"]
                + "  标高:"+ data["AirPortHeight"]
                + "  跑道入口标高:"+ data["RunWayInHeight"];
    }
    else{
        QString id;
        for(int i = 1;i <= num;i++){
            id.clear();
            id = (m_airpotMap[1].split(":")).value(2);
            id = id.split(" ",QString::SkipEmptyParts).value(0);
            if(id.trimmed() == data["AirPortID"]){
                return ;
            }
        }
        m_airpotMap[num+1] = "名称:"+ data["AirPortName"]
                + "  ID编号:"+ data["AirPortID"]
                + "  代码:"+ data["AirPortCode"]
                + "  标高:"+ data["AirPortHeight"]
                + "  跑道入口标高:%1"+ data["RunWayInHeight"];
    }
    qDebug()<<"Test airport data"<<data;
    inforAirportRows = m_airpotMap.count();
    setHandInforGeomerty();
    inforAirport->setDataMap(m_airpotMap);
}

void TestPortCFGCom::backRunwayInfoSlot(SensorMap map)
{
    DataMap data = map["runWayData"];  // 可能出buge
    int num = data.count() - 2;
    m_runwayMap.clear();
    for(int i = 1; i <= num;i++){
        m_runwayMap[i] =
                "跑道Id编号: "+data[QString("RunWay%1InfoUnit").arg(i)].split("/").value(1)
                +"    所属机场编号: "+data[QString("RunWay%1InfoUnit").arg(i)].split("/").value(0)
                +"    跑道头编号: "+data[QString("RunWay%1InfoUnit").arg(i)].split("/").value(2)
                +"    跑道中编号: "+data[QString("RunWay%1InfoUnit").arg(i)].split("/").value(3)
                +"    跑道尾编号: "+data[QString("RunWay%1InfoUnit").arg(i)].split("/").value(4);
    }
    inforRunWayRows = num;
    setHandInforGeomerty();
    qDebug()<<"Test RunWay dataTTTTTT"<<data;
    inforRunWay->setDataMap(m_runwayMap);
}

void TestPortCFGCom::backMatchInfoSlot(SensorMap map)
{
    DataMap data = map["MatchData"];
    qDebug()<<"MAtch Sensors:"<<data;
    int num = data.count() - 2; // 可能在改动消息时出buge
    m_MatchMap.clear();
    QString subStr;
    for(int s = 1 ; s <= num;s++){
        subStr = data[QString("SensorMatch%1").arg(s)];
        m_MatchMap[s] ="传感器ID编号:  " + subStr.split("/").value(0) +
                "  传感器类型:  " + subStr.split("/").value(1) +
                "  所属跑道ID编号:  " + subStr.split("/").value(2) +
                "  传感器物理位置:  " + subStr.split("/").value(3)/*+
                        "  传感器界面显示位置:  " + subStr.split("/").value(4)*/;
    }
    sensorRows = num;
    setHandInforGeomerty();
    qDebug()<<"Test Sensor dataTTTTTT"<<data;
    inforSensor->setDataMap(m_MatchMap);
}

void TestPortCFGCom::initIdAairportId()
{
    m_idAairportId = "22:33";
}

void TestPortCFGCom::initRowsValue()
{
    inforAirportRows = 1;
    inforRunWayRows = 1;
    sensorRows = 1;
//    sensorStatueRows = 1;
}

void TestPortCFGCom::initInforCom()
{
    InforMap dataList;
    dataList[1] = "";
    dataList[2] = "";
    dataList[3] = "";
    dataList[4] = "";
    dataList[5] = "";
    dataList[6] = "";

    inforAirport = new glableHandInfor(this);
    inforAirport->setDataMap(dataList);
    inforRunWay = new glableHandInfor(this);
    inforRunWay->setDataMap(dataList);
    inforSensor = new glableHandInfor(this);
    inforSensor->setDataMap(dataList);
//    sensorConnet = new glableHandInfor(this);
//    sensorConnet->setDataMap(dataList);
}

void TestPortCFGCom::setHandInforGeomerty()
{
    inforAirport->setSubWidth(width()- 20);
    inforRunWay->setSubWidth(width()- 20);
    inforSensor->setSubWidth(width()- 20);
//    sensorConnet->setSubWidth(width()- 20);

    inforAirport->setSubHeight(((18*inforAirportRows)>(height()/8))? 18*inforAirportRows : height()/8);
//    sensorConnet->setSubHeight(((18*sensorStatueRows)>(height()*3/16))? 18*sensorStatueRows : height()*3/16);
    inforSensor->setSubHeight( ((18*sensorRows)>(height()*3/16))? 18*sensorRows : height()*3/16);
    inforRunWay->setSubHeight(((18*inforRunWayRows)>(height()/4))? 18*inforRunWayRows : height()/4);
}

void TestPortCFGCom::initCustomMenus()
{
    if(inforAirport && inforRunWay && inforSensor /*&& sensorConnet*/){
      connect(inforAirport,SIGNAL(menuOption(QString)),SIGNAL(MenuOptionSlot(QString)));
      connect(inforRunWay,SIGNAL(menuOption(QString)),SIGNAL(MenuOptionSlot(QString)));
      connect(inforSensor,SIGNAL(menuOption(QString)),SIGNAL(MenuOptionSlot(QString)));
//      connect(sensorConnet,SIGNAL(menuOption(QString)),SIGNAL(MenuOptionSlot(QString)));
    }
}

void TestPortCFGCom::initMenuDealsConnection()
{
    QStringList menuList;
    if(inforAirport && inforRunWay && inforSensor /*&& sensorConnet*/){
        menuList<<"testAirport:刷新"<<"testAirport:增加"<<"testAirport:修改"<<"testAirport:删除";
        inforAirport->setActionName(menuList);
        menuList.clear();
        menuList<<"testRunWay:刷新"<<"testRunWay:增加"<<"testRunWay:修改"<<"testRunWay:删除";
        inforRunWay->setActionName(menuList);
        menuList.clear();
        menuList<<"testSensor:刷新"<<"testSensor:增加"<<"testSensor:修改"<<"testSensor:删除";
        inforSensor->setActionName(menuList);
    }
}

void TestPortCFGCom::initScrollArea()
{
    ScrollAreaTestAirport = new QScrollArea(this);
    ScrollAreaTestRunWay = new QScrollArea(this);
    ScrollAreaTestSensor = new QScrollArea(this);
//    ScrollAreaTestSensorStatue = new QScrollArea(this);
}

void TestPortCFGCom::addSubWidget()
{
    if(ScrollAreaTestAirport && /*ScrollAreaTestSensorStatue &&*/
            ScrollAreaTestSensor && ScrollAreaTestRunWay) {
        ScrollAreaTestAirport->setWidget(inforAirport);
        ScrollAreaTestRunWay->setWidget(inforRunWay);
        ScrollAreaTestSensor->setWidget(inforSensor);
//        ScrollAreaTestSensorStatue->setWidget(sensorConnet);
    }
}

void TestPortCFGCom::setInforComGeometry()
{
    int sWidth = width();
    int sHeight = height();
    if(ScrollAreaTestAirport && /*ScrollAreaTestSensorStatue &&*/
        ScrollAreaTestSensor && ScrollAreaTestRunWay) {
        ScrollAreaTestAirport->setGeometry(0,sHeight/32,sWidth,sHeight/8);
        ScrollAreaTestRunWay->setGeometry(0,sHeight*7/32,sWidth,sHeight/4);
        ScrollAreaTestSensor->setGeometry(0,sHeight*17/32,sWidth,sHeight*3/16);
//        ScrollAreaTestSensorStatue->setGeometry(0,sHeight*25/32,sWidth,sHeight*3/16);
    }
}

void TestPortCFGCom::initButton()
{
    UpAirport = new GlableSelectButton(this);
    UpAirport->setNameStr("testAirport:刷新");
    connect(UpAirport,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
    UpRunWay = new GlableSelectButton(this);
    UpRunWay->setNameStr("testRunWay:刷新");
    connect(UpRunWay,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
    UpSensors = new GlableSelectButton(this);
    UpSensors->setNameStr("testSensor:刷新");
    connect(UpSensors,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
}

void TestPortCFGCom::setButtonGeometry()
{
    int right = width();
    int buttonHeight = height()/32;

    UpAirport->setGeometry(right - 80,0,60,buttonHeight);
    UpRunWay->setGeometry(right - 80,height()*3/16,60,buttonHeight);
    UpSensors->setGeometry(right - 80,height()*8/16,60,buttonHeight);
//    UpSensorStatue->setGeometry(right - 80,height()*12/16,60,buttonHeight);
}

void TestPortCFGCom::initsizeValue()
{
    comWidth = 0;
    comHeight = 0;
}
