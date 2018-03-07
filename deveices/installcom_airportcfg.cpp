#include "installcom_airportcfg.h"

/*
**********************
*
*    安装配置界面 - 机场
*
* *********************
*/

AirportCFGCom::AirportCFGCom(QWidget *parent) :
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

QString AirportCFGCom::idAirportId() const
{
    return m_idAairportId;
}

void AirportCFGCom::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width()/2,height()/2);

    int cLeft= -width() / 2;
    int cTop = -height() / 2;
    int cWidth = width();
    int cHeight = height();

    int tilteOne[4][2] = {{cLeft,cTop},{cLeft+120,cTop},
                          {cLeft + 140,cTop + cHeight / 32},
                          {cLeft,cTop + cHeight / 32}};
    int tiltetwo[4][2] = {{cLeft,cTop + cHeight * 3 / 16},
                          {cLeft+120,cTop+ cHeight * 3 / 16},
                          {cLeft + 140,cTop + cHeight * 7 / 32},
                          {cLeft,cTop + cHeight  * 7 / 32}};

    if(comWidth != cWidth && comHeight != cHeight){
        setHandInforGeomerty();
        setInforComGeometry();
        setButtonGeometry();
    }

    painter.save();
    painter.setBrush(QColor("#4A708B"));
    painter.drawPolygon(QPolygon(4,&tilteOne[0][0]));
    painter.drawPolygon(QPolygon(4,&tiltetwo[0][0]));
    painter.restore();

    painter.save();
    painter.setPen(QPen(Qt::white,3));
    int csHeight = height() / 32;
    painter.drawText(cLeft + 20,cTop,80,csHeight,Qt::AlignCenter,"机场信息");
    painter.drawText(cLeft + 20,cTop + height()*3/16,80,csHeight,Qt::AlignCenter,"跑道参数");
    painter.restore();
}

void AirportCFGCom::setIdAirportId(QString value)
{
    m_idAairportId = value;
}

void AirportCFGCom::backAirInfoSlot(SensorMap map)
{
    DataMap data = map["AirportData"];
    QString AFFIX9commandData = "Data_Airport:Store>";
    int num = m_airpotMap.count();
    if(num == 0){
        m_airpotMap[1] =  "名称:"+ data["AirPortName"]
                + "  ID编号:"+ data["AirPortID"]
                + "  代码:"+ data["AirPortCode"]
                + "  标高:"+ data["AirPortHeight"]
                + "  跑道入口标高:"+ data["RunWayInHeight"];
        AFFIX9commandData = AFFIX9commandData
                + QString("index1|airId=%1,airName=%2,airCod=%3,airHight=%4,airInHight=%5/")
                .arg(data["AirPortName"],data["AirPortID"],data["AirPortCode"]
                ,data["AirPortHeight"],data["RunWayInHeight"]);
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
                + "  跑道入口标高:"+ data["RunWayInHeight"];
        AFFIX9commandData = AFFIX9commandData
                + QString("index%6|airId=%1,airName=%2,airCod=%3,airHight=%4,airInHight=%5/")
                .arg(data["AirPortName"],data["AirPortID"],data["AirPortCode"]
                ,data["AirPortHeight"],data["RunWayInHeight"]).arg(num+1);
    }

    qDebug()<<"airport data"<<data;
    inforAirportRows = m_airpotMap.count();
    setHandInforGeomerty();
    inforAirport->setDataMap(m_airpotMap);
    emit MenuOptionSlot(AFFIX9commandData);
}

void AirportCFGCom::backRunwayInfoSlot(SensorMap map)
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
    inforAirportRows = num;
    setHandInforGeomerty();
    //qDebug()<<"runway dataffffffffff"<<data;
    inforRunWay->setDataMap(m_runwayMap);
}

void AirportCFGCom::backMatchInfoSlot(SensorMap /*map*/)
{
    // DataMap data = map[]; 不用
}

void AirportCFGCom::initIdAairportId()
{
    m_idAairportId = "22:33";
}

void AirportCFGCom::initRowsValue()
{
    inforAirportRows = 1;
    inforRunWayRows = 1;
}

void AirportCFGCom::initInforCom()
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
    inforAirport->_set_data_cell_width(100);
    inforRunWay->_set_data_cell_width(100);
}

void AirportCFGCom::initCustomMenus()
{
    QStringList menuList;
    if(inforAirport && inforRunWay){
        menuList<<"airport:刷新"<<"airport:添加"<<"airport:配置"<<"airport:删除";
        inforAirport->setActionName(menuList);
        menuList.clear();
        menuList<<"runWay:刷新"<<"runWay:增加"<<"runWay:配置"<<"runWay:删除";
        inforRunWay->setActionName(menuList);
    }
}

void AirportCFGCom::setHandInforGeomerty()
{
    inforAirport->setSubWidth(width()- 20);
    inforAirport->setSubHeight(((18*inforAirportRows)>(height()/8))? 18*inforAirportRows : height()/8);
    inforRunWay->setSubWidth(width()- 20);
    inforRunWay->setSubHeight(((18*inforRunWayRows)>(height()/4))? 18*inforRunWayRows : height()/4);
}

void AirportCFGCom::initMenuDealsConnection()
{
    connect(inforAirport,SIGNAL(menuOption(QString))  // transfer the options of data option
            ,SIGNAL(MenuOptionSlot(QString)));
    connect(inforRunWay,SIGNAL(menuOption(QString))  // transfer the options of data option
            ,SIGNAL(MenuOptionSlot(QString)));
}

void AirportCFGCom::initScrollArea()
{
    ScrollAreaAirport = new QScrollArea(this);
    ScrollAreaRunWay = new QScrollArea(this);
}

void AirportCFGCom::addSubWidget()
{
    if(ScrollAreaAirport && ScrollAreaRunWay) {
        ScrollAreaAirport->setWidget(inforAirport);
        ScrollAreaRunWay->setWidget(inforRunWay);
    }
}

void AirportCFGCom::setInforComGeometry()
{
    int sWidth = width();
    int sHeight = height();
    if(ScrollAreaAirport && ScrollAreaRunWay){
        ScrollAreaAirport->setGeometry(0,sHeight/32,sWidth,sHeight/8);
        ScrollAreaRunWay->setGeometry(0,sHeight*7/32,sWidth,sHeight/4);
    }
}

void AirportCFGCom::initButton()
{
    UpAirportInfor = new GlableSelectButton(this);
    UpAirportInfor->setNameStr("airport:刷新");
    connect(UpAirportInfor,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
    UpRunWayInfor = new GlableSelectButton(this);
    UpRunWayInfor->setNameStr("runWay:刷新");
    connect(UpRunWayInfor,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
}

void AirportCFGCom::setButtonGeometry()
{
    int right = width();
    int buttonHeight = height()/32;

    UpAirportInfor->setGeometry(right - 80,0/*height()*5/32*/,60,buttonHeight);
    UpRunWayInfor->setGeometry(right - 80,height()*3/16/*height()*15/32*/,60,buttonHeight);
}

void AirportCFGCom::initsizeValue()
{
    comWidth = 0;
    comHeight = 0;
}

