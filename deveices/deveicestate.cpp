#include "deveicestate.h"

void deveiceStateControl::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    if(width() != m_width || height() != m_height){
        m_width = width() ;
        m_height = height();
        m_set_rvr_geomerty();
        m_init_setGeomerty();
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    int subWidth = width();
    int subHeight = height();
    int left = - subWidth / 2;
    int top = - subHeight / 2;
    int righ = subWidth / 2;
    int buttom = subHeight / 2;
    painter.translate(righ, buttom);
    painter.setPen(Qt::NoPen);

    //画区域背景
    painter.save();
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(left,top,subWidth - 2,subHeight - 2,3,3);
    painter.setBrush(Qt::gray);
    painter.drawRoundedRect(left + 2,top + 2,subWidth - 2,
                            subHeight - 2,3,3);
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRoundedRect(left + 2,top + 2,subWidth - 4,
                            subHeight - 4,3,3);
    painter.restore();

    //绘制切换操作
    painter.save();
    if(m_select){
        painter.setBrush(QColor("#4A708B"));
        painter.drawRoundedRect(left+width()/2-20,top+10,20,20,10,10);
        painter.setBrush(Qt::white);
        painter.drawRoundedRect(left+width()/2 ,top+10,20,20,10,10);
    }
    else{
        painter.setBrush(QColor("#4A708B"));
        painter.drawRoundedRect(left+width()/2 ,top+10,20,20,10,10);
        painter.setBrush(Qt::white);
        painter.drawRoundedRect(left+width()/2-20,top+10,20,20,10,10);
    }
    QFont font;
    font.setBold(true);
    font.setPixelSize(12);
    painter.setFont(font);
    painter.setPen(QPen(QColor("#4A708B"),3));
    painter.drawText(left+width()/2 - 100,top+10,80,20,Qt::AlignCenter,"实物状态");
    painter.drawText(left+width()/2 + 20,top+10,80,20,Qt::AlignCenter,"参数展示");
    painter.restore();

    if(m_select){
        //        m_init_setGeomerty();
        center3616UI->show();

    }
    else{
        center3616UI->hide();
        //绘制表格
        painter.save();
        // draw tables height max : 500
        if(subHeight > 500){
            subHeight = 500;
        }
        painter.setBrush(Qt::gray);
        int TLE36[4][2] = {{left + 4,top + 20},
                           {left - 36 + (subWidth - 2) / 6,top + 20},
                           {left + 4 + (subWidth - 2) / 6,
                            top + 10 +(subHeight - 18) / 12},
                           {left + 4,top + 10+(subHeight - 18) / 12}};
        painter.drawConvexPolygon(QPolygon(4,&TLE36[0][0]));
        painter.setPen(QPen(QColor("#4A708B"),2));
        QFont fontOne = painter.font();
        fontOne.setBold(true);
        fontOne.setPixelSize(21);
        painter.setFont(fontOne);
        painter.drawText(left + 4,top + 20,(subWidth - 2) / 6 - 40,
                         (subHeight - 18) / 12  - 10,Qt::AlignCenter,"3616");

        // 3616 设备状态
        fontOne.setBold(true);
        fontOne.setPixelSize(12);
        painter.setFont(fontOne);
        painter.setPen(QPen(QColor("#4A708B"),4));
        painter.drawText(left + 2 ,top + 16 + (subHeight - 18) / 12,
                         (subWidth - 2) * 5 / 96,
                         (subHeight - 18) / 12,
                         Qt::AlignCenter,"模块");
        painter.drawText(left + 2 ,top + 16 + (subHeight - 18) * 2 / 12,
                         (subWidth - 2) * 5 / 96,
                         (subHeight - 18) / 12,
                         Qt::AlignCenter,"状态");
        painter.setPen(QPen(QColor("#4A708B"),2));
        int tempy,x1,x2;
        x1 = left + 6;
        x2 = left + 2 + (subWidth - 2) * 35 / 48;
        for(int row = 1;row < 4;row++){
            tempy = top + 16 + (subHeight - 18) * row / 12;
            painter.drawLine(x1,tempy,x2,tempy);
        }

        int tempx,y1,y2,tabley1,tabley2,tableW,tableH;
        y1 = top + 16 + (subHeight - 18) / 12;
        y2 = top + 16 + (subHeight - 18) / 4;
        tabley1 = top + 16 + (subHeight - 18) / 12;
        tabley2 = top + 16 + (subHeight - 18) / 6;
        tableW = ((subWidth - 2) * 5 / 6)  * 7 / 72;
        tableH = (subHeight - 18) / 12;
        QString str;
        for(int cloum = 0;cloum <= 10;cloum++){
            str.clear();
            tempx = left + 2
                    + ((subWidth - 2) * 35 / 48) * cloum / 10;
            if(cloum == 0) tempx = tempx + 4;
            if(cloum == 10) {
                painter.drawLine(tempx+2,y1,tempx+2,y2);
                continue;
            }
            else{
                painter.drawLine(tempx,y1,tempx,y2);
            }
            if(cloum == 0) continue;
            painter.drawText(tempx,tabley1,tableW,tableH,
                             Qt::AlignCenter,
                             m_modelMap[cloum]);
            str = m_openModel[m_modelMap[cloum]];
            str = (str == "open")? "open" :"closed";
            if(str == "open"){
                painter.setBrush(Qt::green);
                painter.drawRect(tempx,tabley2,tableW - 7,tableH);
            }
            else{
                painter.setBrush(Qt::lightGray);
                painter.drawRect(tempx,tabley2,tableW - 7,tableH);
            }
            painter.drawText(tempx,tabley2,tableW,tableH,Qt::AlignCenter,str);
        }

        // 传感器状态
        painter.setBrush(Qt::gray);
        painter.setPen(Qt::NoPen);
        int TLEsensor[4][2] = {{left + 5,top + 20 + (subHeight - 18) / 4},
                               {left -35 + (subWidth - 2) / 6,
                                top + 20 + (subHeight - 18) / 4},
                               {left + 5 + (subWidth - 2) / 6,
                                top + 10 + (subHeight - 18) / 4 + (subHeight - 20) / 12},
                               {left + 5 ,top + 10 + (subHeight - 18) / 4 + (subHeight - 20) / 12}};
        painter.drawConvexPolygon(QPolygon(4,&TLEsensor[0][0]));
        painter.setPen(QPen(QColor("#4A708B"),2));
        fontOne.setBold(true);
        fontOne.setPixelSize(20);
        painter.setFont(fontOne);
        painter.drawText(left + 5,top + 20 + (subHeight - 18) / 4,
                         (subWidth - 2) / 6 - 40,
                         (subHeight - 20) / 12 - 10,
                         Qt::AlignCenter,"SENSORS");
        fontOne.setBold(true);
        fontOne.setPixelSize(12);
        painter.setFont(fontOne);

        //画传感器制表横线
        int rowx;
        for(int rowNum = 0;rowNum <= 5;rowNum++){
            rowx = top + 40 +  subHeight * ( rowNum + 3 ) / 12;
            if(rowNum == 0){
                painter.drawLine(left + 6,rowx + 10,
                                 left + subWidth - 4 - (subWidth - 2) / 6,rowx + 10);
            }
            else{
                painter.drawLine(left + 6,rowx,
                                 left + subWidth - 4 - (subWidth - 2) / 6,rowx);
            }
        }

        //画传感器制表竖线
        int cloumy;
        for(int rowNum = 0;rowNum < 17;rowNum++){
            cloumy = left + 6 + ((subWidth - 2) * 5 / 6) * rowNum / 16;
            if(rowNum == 16){
                painter.drawLine(cloumy - 6,top + 50 +  subHeight * ( 3 ) / 12,
                                 cloumy - 6,top + 40 +  subHeight * ( 5 + 3 ) / 12);
            }
            else{
                painter.drawLine(cloumy,top + 50 +  subHeight * ( 3 ) / 12,
                                 cloumy,top + 40 +  subHeight * ( 5 + 3 ) / 12);
            }
        }
        for(int addcolor = 0;addcolor < 16;addcolor++){

        }
        int rowx1 = top + subHeight / 4 + 50;
        int rowx2 = top  +  subHeight / 3 + 40;
        int rowx3 = top  +  subHeight * 5 / 12 + 40;
        int rowx4 = top  +  subHeight / 2 + 40;
        int rowx5 = top  +  subHeight * 7 / 12 + 40;
        int cycH =  subHeight / 12;
        int cycW = (subWidth - 2) * 5 / 96;
        for(int addName = 0;addName < 17;addName++){
            cloumy = left + 6 +((subWidth - 2) * 5 / 6) * addName / 16;
            if(addName == 16){
                painter.drawText(cloumy - 6,rowx1,cycW,cycH - 10,
                                 Qt::AlignCenter,cardMap[addName + 1]);
                painter.drawText(cloumy - 6,rowx2,cycW,cycH ,
                                 Qt::AlignCenter,sensorStateMap[addName + 1]);
                painter.drawText(cloumy - 6,rowx3,cycW,cycH ,
                                 Qt::AlignCenter,m_sensorNameMap[addName + 1]);
                painter.drawText(cloumy - 6,rowx4,cycW,cycH ,
                                 Qt::AlignCenter,sensorIdMap[addName + 1]);
                painter.drawText(cloumy - 6,rowx5,cycW,cycH ,
                                 Qt::AlignCenter,beyonRunWayMap[addName + 1]);
            }
            else{
                painter.drawText(cloumy,rowx1,cycW,cycH - 10,
                                 Qt::AlignCenter,cardMap[addName + 1]);
                painter.drawText(cloumy,rowx2,cycW,cycH ,
                                 Qt::AlignCenter,sensorStateMap[addName + 1]);
                painter.drawText(cloumy,rowx3,cycW,cycH ,
                                 Qt::AlignCenter,m_sensorNameMap[addName + 1]);
                painter.drawText(cloumy,rowx4,cycW,cycH ,
                                 Qt::AlignCenter,sensorIdMap[addName + 1]);
                painter.drawText(cloumy,rowx5,cycW,cycH ,
                                 Qt::AlignCenter,beyonRunWayMap[addName + 1]);
            }
        }
        painter.restore();
    }
}

void deveiceStateControl::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton){
        int px = e->pos().x();
        int py = e->pos().y();
        if(px > (width() - 100) && px < width()
                && py > (height() - 100)&& py < height())
        {
            do_rvr_config();
        }
    }
    if(e->buttons() == Qt::LeftButton){
        int px2 = e->pos().x();
        int py2 = e->pos().y();
        // 实物状态
        if(px2 > (width()/2-20) && px2 < width()/2
                && py2 > 10&& py2 < 30)
        {
            m_select = true;
            update();
        }
        // 参数展示
        else if(px2 > width()/2 && px2 < width()/2+20
                && py2 > 10&& py2 < 30){
            m_select = false;
            update();
        }
    }
}

void deveiceStateControl::setDeveice3616ID(int id)
{
    this->m_3616Id = id;
}

void deveiceStateControl::setModleNameList(SerialMap modleNameMap)
{
    this->m_modelMap.clear();
    this->m_modelMap = modleNameMap;
    update();
}

void deveiceStateControl::setSensorsNameMap(SerialMap nameMap)
{
    this->m_sensorNameMap.clear();
    this->m_sensorNameMap = nameMap;
    update();
}

void deveiceStateControl::AFFIX9NewMessageSendUp(QString dCtx, InforData data)
{
    if(dCtx == "openModel"){
        qDebug()<<"data ctx:"<<dCtx<<"data:"<<data;
        m_openModel.clear();
        m_openModel = data;
        updateSate();
    }
    else if(dCtx =="basiLight"){
        qDebug()<<"basiLight"<<data;
    }
    return ;
}

void deveiceStateControl::updateSate()
{
    update();
}

void deveiceStateControl::m_init_push_button()
{
    m_time = new QTimer(this);
    connect(m_time,SIGNAL(timeout()),SLOT(remberTime()));
    m_time->start(2000);
    m_number = 0;
    //m_rvr_set = new QPushButton(this);
    //connect(m_rvr_set,SIGNAL(clicked()),SLOT(do_rvr_config()));
}

void deveiceStateControl::m_set_rvr_geomerty()
{
    //m_rvr_set->setGeometry(width()-100,height()-100,100,100);
    //m_rvr_set->setFlat(true);
}

void deveiceStateControl::m_init_size()
{
    m_width = 0;
    m_height = 0;
}

void deveiceStateControl::m_init_instance()
{
    center3616UI = new DealCenter3616(this);
    m_select = true;
}

void deveiceStateControl::m_init_setGeomerty()
{
    if (center3616UI){
        center3616UI->setGeometry(2,40,width()-4,height()-30);
    }
}

void deveiceStateControl::remberTime()
{
    m_number = 0;
}

void deveiceStateControl::do_rvr_config()
{
    m_number ++;
    if(m_number > 5){
        emit cofg_rvr_values();
        qDebug()<<"配置RVR大透仪参数！";
    }
}

