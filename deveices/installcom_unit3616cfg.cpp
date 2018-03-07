#include "installcom_unit3616cfg.h"

/***********************
 *
 *
 *    安装配置界面 - 3616
 *
 *
 * **********************/
Unit3616CFGCom::Unit3616CFGCom(QWidget *parent) :
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
QString Unit3616CFGCom::idAirportId() const
{
    return m_idAairportId;
}

void Unit3616CFGCom::paintEvent(QPaintEvent *e)
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
    painter.drawText(cLeft + 20,cTop,80,csHeight,Qt::AlignCenter,"3616设备");
    painter.drawText(cLeft + 20,cTop + height()*3/16,80,csHeight,Qt::AlignCenter,"卡通讯参数");
    painter.drawText(cLeft + 20,cTop + height()/2,80,csHeight,Qt::AlignCenter,"卡链接状态");
    painter.drawText(cLeft + 20,cTop + height()*3/4,80,csHeight,Qt::AlignCenter,"模块驱动");
    painter.restore();
}

void Unit3616CFGCom::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    e->accept();
}
void Unit3616CFGCom::setIdAirportId(QString value)
{
    m_idAairportId = value;
}

void Unit3616CFGCom::Configure3616Slot(SensorMap senMap)
{
    DataMap data = senMap["CFG36Data"];
    QString AFFIX9commandData = "Data_3616:Store>";
    qDebug()<<"36参数:"<<data;
    int num = m_infor36Map.count();
    if(num == 0){
        m_infor36Map[1] = QString("3616设备序号:%1  Id编号:").arg(num+1)
                +  data["ID3616"]
                + "  所属机场:"
                + data["AirPortName"]
                + "  所属机场编号:"
                + data["AirPortID"];
        AFFIX9commandData = AFFIX9commandData
                +QString("index1|ID3616=%1,beyAirName=%2,beyAirID=%3")
                .arg(data["ID3616"])
                .arg(data["AirPortName"])
                .arg(data["AirPortID"]);
    }
    else{
        QString list36;
        for(int i = 1;i <= num;i++){
            qDebug()<<"36信息--------："<<m_infor36Map;
            list36 = m_infor36Map[i].split(" ",QString::SkipEmptyParts).value(1);
            if(list36.split(":").value(1) == data["ID3616"]){
                qDebug()<<"查到一样的数据：函数返回！";
                return ;
            }
        }
        m_infor36Map[num+1] = QString("  3616设备序号:%1   Id编号:").arg(num+1)
                +  data["ID3616"]
                + "   所属机场:" + data["AirPortName"]
                + "   机场编号:" + data["AirPortID"];
        AFFIX9commandData = AFFIX9commandData
                +QString("index%4|ID3616=%1,beyAirName=%2,beyAirID=%3/")
                .arg(data["ID3616"])
                .arg(data["AirPortName"])
                .arg(data["AirPortID"])
                .arg(num+1);
    }
    qDebug()<<"生成数据："<<m_infor36Map;
    infor36->setDataMap(m_infor36Map);
    emit MenuOptionSlot(AFFIX9commandData);
}

void Unit3616CFGCom::sensorStatusSlot(SensorMap senMap)
{
    QString AFFIX9commandData = "Data_sensor:Store>";
    DataMap data = senMap["CNN36Data"];
    QString sensorNameStr;
    int unm = data.count();
    for(int i = 1;i <= unm;i++){
        sensorNameStr.clear();
        sensorNameStr = ((data[QString("CARD%1").arg(i)] == "NULL")
                ? ("空闲")
                :(data[QString("CARD%1").arg(i)]));
        m_statue36Map[i] = QString("卡号:%1  ").arg(i)
                + "链接状态:"
                + sensorNameStr;
        AFFIX9commandData = AFFIX9commandData
                + QString("index%1|card=%1,sensor=%2/")
                .arg(i).arg(sensorNameStr);
    }
    statue36Rows = m_statue36Map.count();   //qDebug()<<"<< 收取参数:"<<data;
    setHandInforGeomerty();
    statue36->setDataMap(m_statue36Map);
    emit MenuOptionSlot(AFFIX9commandData);   //存下库信息
}

void Unit3616CFGCom::sensorLIBsSlot(SensorMap senMap)
{
    DataMap data = senMap["LibCFGData"];
    qDebug()<<"<< 收取参数: lib"<<data;
    int unm = data.count();
    QString AFFIX9commandData = "Data_lib:Store>";
    QString str;
    for(int i = 1;i <= unm;i++){
        str.clear();
        str = data[QString("Libname%1").arg(i)];
        m_lib36Map[i] = QString("模块序号:%1  ").arg(i) +
                "    模块名称:"+ str;
        AFFIX9commandData = AFFIX9commandData
                + QString("index%1|libName%1=%2/").arg(i).arg(str);
    }
    lib36Rows = m_lib36Map.count();         //qDebug()<<"<< 收取参数:"<<data;
    setHandInforGeomerty();
    emit MenuOptionSlot(AFFIX9commandData);   //存下库信息表
}

void Unit3616CFGCom::serialCardParamersSlot(SensorMap senMap)
{
    DataMap data = senMap["CardParamerData"];
    QString AFFIX9commandData = "Data_carCommunicate:Store>";
    //    qDebug()<<"<< 收取参数:"<<data;
    int num = data["CardId"].toInt();
    m_cardParam36Map[num] = QString("卡号:%1  ").arg(num) +
            QString("波特率:") + communiteDeal("Bate",data["Bate"].toInt()) +"  "+
            QString("数据位:") + communiteDeal("Bit",data["Bit"].toInt()) +"  "+
            QString("停止位:") + communiteDeal("StopBit",data["StopBit"].toInt()) +"  "+
            QString("校验:") + communiteDeal("Crc",data["Crc"].toInt()) +"  ";
    cardParameter36Rows = m_cardParam36Map.count();
    //    qDebug()<<"value:"<<m_cardParam36Map;
    setHandInforGeomerty();
    cardParameter36->setDataMap(m_cardParam36Map);
    AFFIX9commandData = AFFIX9commandData +
            QString("index%1|cardId=%1,Bate=%2,Bit=%3,Crc=%4,StopBit=%5/").arg(num)
            .arg(data["Bate"],data["Bit"],data["Crc"],data["StopBit"]);
    emit MenuOptionSlot(AFFIX9commandData);
}

void Unit3616CFGCom::AFFIX9NewMessageSendUp(QString dCtx, InforData data)
{
    if(dCtx == "openModel"){
        int n = m_lib36Map.count();
        QString str;
        for(int i = 1;i <= n;i++){
            str.clear();
            str = m_lib36Map[i].split(" ",QString::SkipEmptyParts).value(1);
            str = str.split(":").value(1);
            str = (data[str] == "open")? "open":"close";
            m_lib36Map[i] = m_lib36Map[i].split(" ",QString::SkipEmptyParts).value(0)
                    + "     "+m_lib36Map[i].split(" ",QString::SkipEmptyParts).value(1)
                    + "     模块状态:" + str;
        }
        lib36->setDataMap(m_lib36Map);
    }
    else if(dCtx == "36state")
    {
        //qDebug()<<"36state:"<<data <<"info"<<m_infor36Map;
        QString id36 = data["SC_HeartBeat3616"]
                ,str36,subStr,commd;
        int n = m_infor36Map.count();
        QStringList list;
        if(n > 0)
        {
            for(int i = 1;i <= n;i++)
            {
                str36.clear();
                list.clear();
                commd.clear();
                str36 = m_infor36Map[i];
                list = str36.split(" ",QString::SkipEmptyParts);
                subStr = list.value(1);
                subStr = subStr.split(":").value(1);
                if( subStr == id36)
                {
                    int count = list.length();
                    if(count < 5){
                        count++;
                    }
                    for(int m = 0;m < count;m++)
                    {

                        if(m == 4)
                        {
                            commd = commd  + "  状态:在线";
                        }
                        else
                        {
                            commd = commd + "  " + list.value(m);
                        }
                        //qDebug()<<"ssssssssss"<<list.value(m);
                    }
                    m_infor36Map[i] = commd;
                }
            }
            infor36->setDataMap(m_infor36Map);
        }
    }
    return ;
}

void Unit3616CFGCom::initIdAairportId()
{
    m_idAairportId = "22:33";
}

void Unit3616CFGCom::initRowsValue()
{
    infor36Rows = 1;
    lib36Rows = 1;
    statue36Rows = 1;
    cardParameter36Rows = 1;
}

QString Unit3616CFGCom::communiteDeal(QString option, int index)
{
    if(option == "Bate")
    {
        switch (index) {
        case 1:
            return "4800";
        case 2:
            return "9600";
        case 3:
            return "19200";
        case 4:
            return "57600";
        case 5:
            return "115200";
        }
    }
    else if(option == "Bit"){
        switch (index) {
        case 1:
            return "5";
        case 2:
            return "6";
        case 3:
            return "7";
        case 4:
            return "8";
        }
    }
    else if(option == "Crc"){
        switch (index) {
        case 1:
            return "无校验";
        case 2:
            return "偶校验";
        case 3:
            return "奇校验";
        }
    }
    else if(option == "StopBit"){
        switch (index) {
        case 1:
            return "一位";
        case 2:
            return "两位";
        }
    }
    return QString("");
}

void Unit3616CFGCom::initInforCom()
{
    InforMap dataList;
    dataList[1] = "";
    dataList[2] = "";
    dataList[3] = "";
    dataList[4] = "";
    dataList[5] = "";
    dataList[6] = "";

    infor36 = new glableHandInfor(this);
    infor36->setDataMap(dataList);
    infor36->_set_data_cell_width(120);
    lib36 = new glableHandInfor(this);
    lib36->setDataMap(dataList);
    lib36->_set_data_cell_width(150);
    statue36 = new glableHandInfor(this);
    statue36->setDataMap(dataList);
    statue36->_set_data_cell_width(150);
    cardParameter36 = new glableHandInfor(this);
    cardParameter36->setDataMap(dataList);
    cardParameter36->_set_data_cell_width(100);
}

void Unit3616CFGCom::setHandInforGeomerty()
{
    infor36->setSubWidth(width()- 20);
    lib36->setSubWidth(width()- 20);
    statue36->setSubWidth(width()- 20);
    cardParameter36->setSubWidth(width()- 20);

    infor36->setSubHeight(((18*infor36Rows)>(height()/8))? (18*infor36Rows) : (height()/8));
    cardParameter36->setSubHeight(((18*cardParameter36Rows)>(height()/4))? (18*cardParameter36Rows) : (height()/4));
    statue36->setSubHeight( ((18*statue36Rows)>(height()*3/16))? (18*statue36Rows) : (height()*3/16));
    lib36->setSubHeight(((18*lib36Rows)>(height()*3/16))? (18*lib36Rows) : (height()*3/16));
}

void Unit3616CFGCom::initCustomMenus()
{
    if(infor36 && lib36 && statue36 && cardParameter36){
        connect(infor36,SIGNAL(menuOption(QString))
                ,SIGNAL(MenuOptionSlot(QString)));
        connect(lib36,SIGNAL(menuOption(QString))
                ,SIGNAL(MenuOptionSlot(QString)));
        connect(statue36,SIGNAL(menuOption(QString))
                ,SIGNAL(MenuOptionSlot(QString)));
        connect(cardParameter36,SIGNAL(menuOption(QString))
                ,SIGNAL(MenuOptionSlot(QString)));
    }
}

void Unit3616CFGCom::initMenuDealsConnection()
{
    QStringList menuList;
    if(infor36 && lib36 && statue36 && cardParameter36){
        menuList<<"infor36:刷新"<<"infor36:编辑IP"    /*<<"infor36:修改"<<"infor36:删除"*/;
        infor36->setActionName(menuList);
        menuList.clear();
        menuList<<"lib36:刷新"<<"lib36:打开"<<"lib36:关闭";
        lib36->setActionName(menuList);
        menuList.clear();
        menuList<<"statue36:刷新";
        statue36->setActionName(menuList);
        menuList.clear();
        menuList<<"cardParameter36:刷新"<<"cardParameter36:设置";
        cardParameter36->setActionName(menuList);
    }
}

void Unit3616CFGCom::initScrollArea()
{
    ScrollAreaInfor36 = new QScrollArea(this);
    ScrollAreacardParameter36 = new QScrollArea(this);
    ScrollAreastatue36 = new QScrollArea(this);
    ScrollArealib36 = new QScrollArea(this);
}

void Unit3616CFGCom::addSubWidget()
{
    if(ScrollAreaInfor36 && ScrollArealib36 &&
            ScrollAreastatue36 && ScrollAreacardParameter36) {
        ScrollAreaInfor36->setWidget(infor36);
        ScrollAreacardParameter36->setWidget(cardParameter36);
        ScrollAreastatue36->setWidget(statue36);
        ScrollArealib36->setWidget(lib36);
    }
}

void Unit3616CFGCom::setInforComGeometry()
{
    int sWidth = width();
    int sHeight = height();
    if(ScrollAreaInfor36 && ScrollArealib36 &&
            ScrollAreastatue36 && ScrollAreacardParameter36) {
        ScrollAreaInfor36->setGeometry(0,sHeight/32,sWidth,sHeight/8);
        ScrollAreacardParameter36->setGeometry(0,sHeight*7/32,sWidth,sHeight/4);
        ScrollAreastatue36->setGeometry(0,sHeight*17/32,sWidth,sHeight*3/16);
        ScrollArealib36->setGeometry(0,sHeight*25/32,sWidth,sHeight*3/16);
    }
}

void Unit3616CFGCom::initButton()
{
    Up36Infor = new GlableSelectButton(this);
    Up36Infor->setNameStr("infor36:刷新");
    connect(Up36Infor,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
    Up36Lib = new GlableSelectButton(this);
    Up36Lib->setNameStr("lib36:刷新");
    connect(Up36Lib,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
    Up36Statue = new GlableSelectButton(this);
    Up36Statue->setNameStr("statue36:刷新");
    connect(Up36Statue,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
    Up36CardParameter = new GlableSelectButton(this);
    Up36CardParameter->setNameStr("cardParameter36:刷新");
    connect(Up36CardParameter,SIGNAL(buttonClick(QString))
            ,this,SIGNAL(MenuOptionSlot(QString)));
}

void Unit3616CFGCom::setButtonGeometry()
{
    int right = width();
    int buttonHeight = height()/32;

    Up36Infor->setGeometry(right - 80,0,60,buttonHeight);
    Up36CardParameter->setGeometry(right - 80,height()*3/16,60,buttonHeight);
    Up36Statue->setGeometry(right - 80,height()*8/16,60,buttonHeight);
    Up36Lib->setGeometry(right - 80,height()*12/16,60,buttonHeight);
}

void Unit3616CFGCom::initsizeValue()
{
    comWidth = 0;
    comHeight = 0;
}

