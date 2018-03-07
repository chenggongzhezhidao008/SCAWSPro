#include "subtestcfg.h"
#include <QDebug>

subTestCfg::subTestCfg(QWidget *parent) :
    QWidget(parent)
{
    initContrlBool();
    initReleaseBool();
    initInputCom();
    initMemerySizeParent();

    initairportList();
    initNumValue();
    initScrollAreaOBject();
    setScrollPolicy();

    initsubWidgets();
    setsubWidgetsSize(); // test
}

void subTestCfg::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    int left = - width() / 2;
    int top = - height() / 2;
    int uiwidth = width();
    int uiheight = height();
    if(parentWidth != uiwidth || parentHeight != uiheight ){
        parentWidth = uiwidth ;
        parentHeight = uiheight;
        initMemerySizeParent();
        setInputValueComGeometry();
        setScrollGeometry();
    }
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2,height() / 2);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRect(left,top,uiwidth,uiheight);
    int formwidth = uiwidth * 2 / 3;
    painter.setBrush(Qt::white);
    painter.setPen(QPen(QColor("#FFFFFF"),2));

    //添加标题
    painter.save();
    painter.setPen(QPen(QColor("#4A708B"),3));
    painter.drawText(left + 6,top,60,20,Qt::AlignLeft,"机场");
    painter.drawText(left + 6,top + uiheight / 10,60,20,Qt::AlignLeft ,"跑道");
    painter.drawText(left + 6,top + uiheight * 3 / 10,60,20,Qt::AlignLeft,"传感器");
    painter.restore();

    //添加、删除、修改机场跑道传感器按钮
    int buttonleft = left + 6 + formwidth,
            buttonwidth = uiwidth / 9 - 2,
            buttoTop1 = top + 20,
            buttoTop2 = top + 70,
            buttoTop3 = top + 120;
    painter.save();
    painter.setBrush(QColor("#4A708B"));

    QPoint Point11(0,buttoTop1);
    QPoint Point12(0,buttoTop1 + 40);
    QLinearGradient gradMet11(Point11,Point12);
    QLinearGradient gradMet12(Point11,Point12);
    gradMet11.setColorAt(0,QColor("#4A708B"));
    gradMet11.setColorAt(1,QColor("#00688B"));
    gradMet12.setColorAt(0,QColor("#CAE1FF"));
    gradMet12.setColorAt(1,QColor("#B0E0E6"));

    if(!addAirpot){
        painter.setBrush(gradMet11);
    }
    else{
        painter.setBrush(gradMet12);
    }
    painter.drawRect(buttonleft,buttoTop1,buttonwidth,40);
    if(!deleAirpot){
        painter.setBrush(gradMet11);
    }
    else{
        painter.setBrush(gradMet12);
    }
    painter.drawRect(buttonleft + buttonwidth,buttoTop1,buttonwidth,40);
    if(!modiAirpot){
        painter.setBrush(gradMet11);
    }
    else{
        painter.setBrush(gradMet12);
    }
    painter.drawRect(buttonleft + 2 * buttonwidth,buttoTop1,buttonwidth,40);

    QPoint Point21(0,buttoTop2);
    QPoint Point22(0,buttoTop2 + 40);
    QLinearGradient gradMet21(Point21,Point22);
    QLinearGradient gradMet22(Point21,Point22);
    gradMet21.setColorAt(0,QColor("#4A708B"));
    gradMet21.setColorAt(1,QColor("#00688B"));
    gradMet22.setColorAt(0,QColor("#CAE1FF"));
    gradMet22.setColorAt(1,QColor("#B0E0E6"));

    if(!addRunWay){
        painter.setBrush(gradMet21);
    }
    else{
        painter.setBrush(gradMet22);
    }
    painter.drawRect(buttonleft,buttoTop2,buttonwidth,40);
    if(!deleRunWay){
        painter.setBrush(gradMet21);
    }
    else{
        painter.setBrush(gradMet22);
    }
    painter.drawRect(buttonleft + buttonwidth,buttoTop2,buttonwidth,40);
    if(!modRunWay){
        painter.setBrush(gradMet21);
    }
    else{
        painter.setBrush(gradMet22);
    }
    painter.drawRect(buttonleft + 2 * buttonwidth,buttoTop2,buttonwidth,40);

    QPoint Point31(0,buttoTop3);
    QPoint Point32(0,buttoTop3 + 40);
    QLinearGradient gradMet31(Point31,Point32);
    QLinearGradient gradMet32(Point31,Point32);
    gradMet31.setColorAt(0,QColor("#4A708B"));
    gradMet31.setColorAt(1,QColor("#00688B"));
    gradMet32.setColorAt(0,QColor("#CAE1FF"));
    gradMet32.setColorAt(1,QColor("#B0E0E6"));

    if(!addSensor){
        painter.setBrush(gradMet31);
    }
    else{
        painter.setBrush(gradMet32);
    }
    painter.drawRect(buttonleft,buttoTop3,buttonwidth,40);
    if(!deleSensor){
        painter.setBrush(gradMet31);
    }
    else{
        painter.setBrush(gradMet32);
    }
    painter.drawRect(buttonleft + buttonwidth,buttoTop3,buttonwidth,40);
    if(!modSeneor){
        painter.setBrush(gradMet31);
    }
    else{
        painter.setBrush(gradMet32);
    }
    painter.drawRect(buttonleft + 2 * buttonwidth,buttoTop3,buttonwidth,40);
    painter.restore();

    //添加、删除、修改机场跑道传感器标题
    painter.save();
    painter.setPen(QPen(Qt::white,3));

    painter.drawText(buttonleft,buttoTop1,buttonwidth,40,Qt::AlignCenter,"新增机场");
    painter.drawText(buttonleft + buttonwidth,buttoTop1,buttonwidth,40,Qt::AlignCenter,"删除机场");
    painter.drawText(buttonleft + 2 * buttonwidth,buttoTop1,buttonwidth,40,Qt::AlignCenter,"修改机场");

    painter.drawText(buttonleft,buttoTop2,buttonwidth,40,Qt::AlignCenter,"新增跑道");
    painter.drawText(buttonleft + buttonwidth,buttoTop2,buttonwidth,40,Qt::AlignCenter,"删除跑道");
    painter.drawText(buttonleft + 2 * buttonwidth,buttoTop2,buttonwidth,40,Qt::AlignCenter,"修改跑道");

    painter.drawText(buttonleft,buttoTop3,buttonwidth,40,Qt::AlignCenter,"新增传感器");
    painter.drawText(buttonleft + buttonwidth,buttoTop3,buttonwidth,40,Qt::AlignCenter,"删除传感器");
    painter.drawText(buttonleft + 2 * buttonwidth,buttoTop3,buttonwidth,40,Qt::AlignCenter,"修改传感器");
    painter.restore();
}

void subTestCfg::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    bool updateFlag = false;
    if(e->button() == Qt::LeftButton){
        int posX = e->pos().x();
        int posY = e->pos().y();

        // airport
        if(posX > (width() * 2 / 3 + 6) && posX < (width() * 7 / 9 + 4)&&
                posY > 20 && posY < 60){
            addAirpot = true;
            updateFlag = true;
            releaseBool = true;
            selectShowInformation(1);
        }

        else if(posX > (width() * 7 / 9 + 4) && posX < (width() * 8 / 9 + 2) &&
                posY > 20 && posY < 60){
            deleAirpot = true;
            updateFlag = true;
            releaseBool = true;
            //  ++++信息
            selectShowInformation(1);
        }

        else if(posX > (width() * 8 / 9 + 2) && posX < width() &&
                posY > 20 && posY < 60){
            modiAirpot = true;
            updateFlag = true;
            releaseBool = true;
            //  ++++信息
            selectShowInformation(1);
        }

        // run way
        else if(posX > (width() * 2 / 3 + 6) && posX < (width() * 7 / 9 + 4)&&
                posY > 70 && posY < 110){
            addRunWay = true;
            updateFlag = true;
            releaseBool = true;
            selectShowInformation(2);
        }
        else if(posX > (width() * 7 / 9 + 4) && posX < (width() * 8 / 9 + 2) &&
                posY > 70 && posY < 110){
            deleRunWay = true;
            updateFlag = true;
            releaseBool = true;
            //  ++++信息
            selectShowInformation(2);
        }
        else if(posX > (width() * 8 / 9 + 2) && posX < width()&&
                posY > 70 && posY < 110){
            modRunWay = true;
            updateFlag = true;
            releaseBool = true;
            //  ++++信息
            selectShowInformation(2);
        }

        // sensor
        else if(posX > (width() * 2 / 3 + 6) && posX < (width() * 7 / 9 + 4)&&
                posY > 120 && posY < 160){
            addSensor = true;
            updateFlag = true;
            releaseBool = true;
            selectShowInformation(3);
        }

        else if(posX > (width() * 7 / 9 + 4) && posX < (width() * 8 / 9 + 2) &&
                posY > 120 && posY < 160){
            deleSensor = true;
            updateFlag = true;
            releaseBool = true;
            //  ++++信息
            selectShowInformation(3);
        }

        else if(posX > (width() * 8 / 9 + 2) && posX < width() &&
                posY > 120 && posY < 160){
            modSeneor = true;
            updateFlag = true;
            releaseBool = true;
            //  ++++信息
            selectShowInformation(3);
        }
    }

    if(updateFlag){
        update();
    }
}

void subTestCfg::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    if(addAirpot){
        addAirpot = false;
    }
    else if(deleAirpot){
        deleAirpot = false;
    }
    else if(modiAirpot){
        modiAirpot  = false;
    }
    else if(addRunWay){
        addRunWay  = false;
    }
    else if(deleRunWay){
        deleRunWay = false;
    }
    else if(modRunWay){
        modRunWay = false;
    }
    else if(modRunWay){
        modRunWay = false;
    }
    else if(addSensor){
        addSensor = false;
    }
    else if(deleSensor){
        deleSensor = false;
    }
    else if(modSeneor){
        modSeneor = false;
    }
    if(releaseBool){
        releaseBool = false;
        update();
    }
}

void subTestCfg::backAirInfoSlot(SensorMap map)
{
    DataMap airData = map["AirportData"];
    m_airInfor.clear();
    qDebug()<<"airport data"<<map;
    int num = m_airportList.length();
    for(int i = 0;i < num ;i++){

        if(i ==( num - 1)){
            m_airInfor = m_airInfor + m_airportList.value(i)+ ":" + airData [m_airportList.value(i)];
        }
        else{
            m_airInfor = m_airInfor + m_airportList.value(i)+ ":" + airData [m_airportList.value(i)] + "   ";
        }
    }
    InforMap data;
    data[1] = m_airInfor;
    if(airWidget){
        airWidget->setDataMap(data);
    }
}

void subTestCfg::backRunwayInfoSlot(SensorMap map)
{
    qDebug()<<"runWay data"<<map;
    DataMap runWayData = map["runWayData"];
    m_runwayInfor.clear();
    runWayNum = runWayData.count() - 2;
    QString indextStr;
    QStringList CtxStr;
    for(int i = 1 ;i <= runWayNum;i++){
        indextStr.clear();
        CtxStr.clear();
        indextStr = QString("RunWay%1InfoUnit").arg(i);
        CtxStr = runWayData[indextStr].trimmed().split("/");
        m_runwayInfor[i] = "跑道序号："+CtxStr.value(0) +"  "+
                "机场号:"+CtxStr.value(1) +"  "+
                "跑道号:"+CtxStr.value(2) +"  "+
                "头编号:"+CtxStr.value(3) +"  "+
                "中编号:"+CtxStr.value(4) +"  "+
                "尾编号:"+CtxStr.value(5);
    }
    if(runwayWidget){
        runwayWidget->setDataMap(m_runwayInfor);
    }
}

void subTestCfg::backMatchInfoSlot(SensorMap map)// 以后处理自动识别匹配条数
{
    qDebug()<<"Match data"<<map;
    DataMap matchData = map["MatchData"];
    m_matchInfor.clear();

    matchNum = matchData.count() - 2;
    QString indextStr;
    QStringList CtxStr;
    for(int i = 1 ;i <= matchNum;i++){
        indextStr.clear();
        CtxStr.clear();
        indextStr = QString("SensorMatch%1").arg(i);
        CtxStr = matchData[indextStr].trimmed().split("/");
        m_matchInfor[i] = "传感器编号:"+CtxStr.value(0) + "  "+
                "类型:"+CtxStr.value(1) +"  "+
                "跑道号:"+CtxStr.value(2) +"  "+
                "自定义位置:"+CtxStr.value(3);
    }
    if(matchWidget){
        matchWidget->setDataMap(m_matchInfor);
    }
}

void subTestCfg::initContrlBool()
{
    addAirpot  = false;
    deleAirpot = false;
    modiAirpot = false;
    addRunWay  = false;
    deleRunWay = false;
    modRunWay  = false;
    addSensor  = false;
    deleSensor = false;
    modSeneor  = false;
}

void subTestCfg::initReleaseBool()
{
    releaseBool = false;
}

void subTestCfg::initInputCom()
{
    input = new InputValueCom(this);
    input->hide();
}

void subTestCfg::setInputValueComGeometry()
{
    input->setGeometry(width() * 2 / 3 + 6,160,width() / 3 - 8,height() - 170);
    input->show();
}

void subTestCfg::selectShowInformation(int classIndex)
{
    input->setClassIndex(classIndex);
}

void subTestCfg::initMemerySizeParent()
{
    parentWidth = 0;
    parentHeight = 0;
}

void subTestCfg::initairportList()
{
    m_airportList.push_back("AirPortName");
    m_airportList.push_back("AirPortID");
    m_airportList.push_back("AirPortCode");
    m_airportList.push_back("AirPortHeight");
    m_airportList.push_back("RunWayInHeight");
}

void subTestCfg::initNumValue()
{
    runWayNum = 0;
    matchNum = 0;
}

void subTestCfg::initScrollAreaOBject()
{
    m_AirArea = new QScrollArea(this);
    m_RunWayArea = new QScrollArea(this);
    m_MatchArea = new QScrollArea(this);
}

void subTestCfg::setScrollGeometry()
{
    if(m_AirArea&&m_RunWayArea&&m_MatchArea){
        int scrollWidth = width()* 2 / 3;
        int scrollHeight = height() / 10;
        m_AirArea->setGeometry(0,20,scrollWidth,scrollHeight - 20);
        m_RunWayArea->setGeometry(0,scrollHeight + 20,scrollWidth,height()  * 2 / 10 - 20);
        m_MatchArea->setGeometry(0,height() * 3 / 10 + 20,scrollWidth,height() * 7 / 10 - 20);
        setScrollMInHeightSize();
        setsubWidgetsSize();
    }
}

void subTestCfg::setScrollMInHeightSize()
{
    if(m_AirArea&&m_RunWayArea&&m_MatchArea){
        m_AirArea->setMinimumHeight(height() / 10 - 20);
        m_RunWayArea->setMinimumHeight(height()  * 2 / 10 - 20);
        m_MatchArea->setMinimumHeight(height() * 7 / 10 - 20);
    }
}

void subTestCfg::setScrollPolicy()
{
    if(m_AirArea&&m_RunWayArea&&m_MatchArea){
        m_AirArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        m_RunWayArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        m_MatchArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    }
}

void subTestCfg::initsubWidgets()
{
    airWidget = new GlableCom_InforShow(this);
    runwayWidget = new GlableCom_InforShow(this);
    matchWidget = new GlableCom_InforShow(this);
    if(m_AirArea&&m_RunWayArea&&m_MatchArea){
        m_AirArea->setWidget(airWidget);
        m_RunWayArea->setWidget(runwayWidget);
        m_MatchArea->setWidget(matchWidget);
    }
}

void subTestCfg::setsubWidgetsSize()
{
    airWidget->setSubWidth(width()* 2 / 3 - 20);
    airWidget->setSubHeight(height() / 10 - 20);

    runwayWidget->setSubWidth(width()* 2 / 3 - 20);
    runwayWidget->setSubHeight(height() * 2 / 10 - 20);

    matchWidget->setSubWidth(width()* 2 / 3 - 20);
    matchWidget->setSubHeight(height() * 7 / 10 - 20);
}
