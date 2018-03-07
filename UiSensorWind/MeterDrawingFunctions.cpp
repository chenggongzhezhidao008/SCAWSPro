#include "UiSensorWind/windmeter.h"
#include <QLinearGradient>
#include <QDebug>
#include <QTime>
//绘制刻度条
void WindMeter::drawAngleScale(QPainter *painter)
{
    //qDebug()<<QTime::currentTime().toString("ss") + "wind ui 1";
    painter->save();
    QPen thinPen(palette().background(),0.1);
    painter->setPen(thinPen);
    QPainterPath path;
    QRectF rect(-150,-150,300,300);
    path.arcTo(rect,1,8);
    painter->rotate(-5);
    for (int i = 0;i < 37;i++)
    {
        painter->rotate(10);
        if(i == 0){
            continue;
        }
        if(i >= (m_tenWindMinAngle / 10) && i<=(m_tenWindMaxAngle / 10)){
            painter->setBrush(QColor("#36648B")/*Qt::blue*/);
        }
        else{
            painter->setBrush(Qt::gray);
        }
        painter->drawPath(path);
    }
    painter->restore();
}

//绘制当前风向刻度
void WindMeter::drawCurrentWindAngle(QPainter *painter)
{
    //qDebug()<<QTime::currentTime().toString("ss") + "wind ui 2";
    painter->save();
    //画笔
    QPen thinPen(palette().background(),0.1);
    painter->setPen(thinPen);
    //路径编辑
    QPainterPath path;
    QRectF rect(-150,-150,300,300);
    path.arcTo(rect,1,8);
    //旋转绘画
    painter->rotate(-5);
    if((m_twoAvAngle /10) == 36){
        painter->rotate(10);
        painter->setBrush(Qt::green);
        painter->drawPath(path);
        painter->restore();
        return ;
    }
    for (int i = 0;i < 37;i++)
    {
        if(i == (m_twoAvAngle / 10) + 1 ){
            painter->setBrush(Qt::green);
            painter->drawPath(path);
        }
        else{
            ;
        }
        painter->rotate(10);
    }
    painter->restore();
}

//绘制刻度数据
void WindMeter::drawAngleScaleText(QPainter *painter)
{
    //qDebug()<<QTime::currentTime().toString("ss") + "wind ui 9";
    painter->rotate(-90);
    painter->setPen(QColor("#4A708B")/*Qt::white*/);/*Qt::black*//*"#545454"*/
    //2017.5.9 #4A708B修改刻度字体颜色
    QFont font;
    font.setBold(true);
    font.setPointSize(13);
    painter->setFont(font);
    painter->save();
    painter->rotate(180);
    for(int i = 0; i<= 36;i++ )
    {
        if(i % 3 != 0 || i == 0){
            continue;
        }
        QString str = QString::number(i,10);
        if(i < 11){
            str = "0"+str;
        }
        //QFontMetricsF fm( this->font());
        //double w = fm.size(Qt::TextSingleLine,str).width();
        //double h = fm.size(Qt::TextSingleLine,str).height();
        qreal x = 164 * cos((i * 2 * PI) / 36 - PI / 2);
        qreal y = 164 * sin((i * 2 * PI) / 36 - PI / 2);
        painter->drawText(x - 12,y - 14,28,28,Qt::AlignCenter,str);
    }
    painter->restore();
}

void WindMeter::drawInsideEllipse(QPainter *painter)
{
    //qDebug()<<QTime::currentTime().toString("ss") + "wind ui 3";
    painter->save();
    QPen penz(Qt::white,5);
    painter->setPen(penz);
    QPoint center2(0,0);
    painter->setBrush((palette().background()).color());
    painter->drawEllipse(center2,130,130);
    painter->restore();
    if(this->m_name != ""){
        painter->save();
        painter->rotate(90);
        painter->setPen(QColor("#FFF0F5"));
        QFont font = painter->font();
        font.setPixelSize(20);
        font.setBold(true);
        painter->setFont(font);
        QRect nameRect( -40,80,80,20);
        painter->drawText(nameRect,Qt::AlignBottom|Qt::AlignHCenter,this->m_name);
        painter->restore();
    }
}

//跑道角度方向
void WindMeter::drawRunUpRect(QPainter *painter)
{
    //qDebug()<<QTime::currentTime().toString("ss") + "wind ui 4";
    painter->save();
    bool mid = false;
    if(m_runUpAngle.split("-",QString::SkipEmptyParts).length() > 1){
        mid = true;
        painter->rotate(m_runUpAngle.split("-",QString::SkipEmptyParts).value(0).toInt() * 10);
    }
    else{
        painter->rotate(m_runUpAngle.toInt() * 10);
    }
    painter->setPen(Qt::gray);
    painter->setBrush(Qt::gray);
    QRect runUplabel(-126,-12,248,24);
    painter->drawRect(runUplabel);
    if(!mid){
        painter->setPen(Qt::gray);
        painter->setBrush(Qt::white);
        for(int i = 0;i < 4;i++){
            QRect touchSpotRect1(84,(-9 + i*5),35,3);
            painter->drawRect(touchSpotRect1);
        }
    }
    painter->restore();
}

void WindMeter::drawUnitLabelArea(QPainter *painter)
{
    //qDebug()<<QTime::currentTime().toString("ss") + "wind ui 5";
    painter->save();
    painter->rotate(90);
    QPen pen;
    pen.setColor((palette().background()).color());
    pen.setWidth(1);
    pen.setColor(QColor("#F0F8FF"));
    painter->setPen(pen);
    if(m_enable){
        painter->setBrush(QColor("#F0F8FF"));
    }
    else
    {
        painter->setBrush(Qt::gray);
    }
    QRect rectlabel(-60,-50,120,100);
    painter->drawRoundRect(rectlabel);
    painter->restore();
}

//当前风向，风速中心标签
void WindMeter::drawWindAngle(QPainter *painter)
{
    //qDebug()<<QTime::currentTime().toString("ss") + "wind ui 6";
    painter->save();
    painter->rotate(90);
    painter->setPen(Qt::black);
    QFont fontangle = painter->font();
    fontangle.setBold(true);
    fontangle.setPointSize(14);
    painter->setFont(fontangle);
    QRectF angleUnit = QRectF(24,-37,20,30);
    QString angleUnitstr = "o";
    painter->drawText(angleUnit,Qt::AlignVCenter|Qt::AlignLeft, angleUnitstr);

    int pixangle = fontangle.pointSize();
    pixangle += 7;
    fontangle.setPointSize(pixangle);
    painter->setFont(fontangle);

    QRectF angleRect= QRectF(-44,-31,60,30);
    QString anglestr = QString::number(m_windCurrentAngle,10);
    painter->drawText(angleRect,Qt::AlignCenter, anglestr);
    painter->restore();
}

void WindMeter::drawWindSpeed(QPainter *painter)
{
    //qDebug()<<QTime::currentTime().toString("ss") + "wind ui 7";
    painter->save();
    painter->rotate(90);
    painter->setPen(Qt::black);
    QFont fontSpeed = painter->font();
    fontSpeed.setBold(true);
    fontSpeed.setPointSize(14);
    painter->setFont(fontSpeed);
    QRectF SpeedUnit = QRectF(24,4,40,30);
    QString SpeedUnitstr = "m/s";
    painter->drawText(SpeedUnit,Qt::AlignCenter, SpeedUnitstr);

    int pixSpeed = fontSpeed.pointSize();
    pixSpeed += 7;
    fontSpeed.setPointSize(pixSpeed);
    painter->setFont(fontSpeed);
    QRectF SpeedRect= QRectF(-55,4,75,28);
    QString Speedstr = m_windCurrentSpeed;
    painter->drawText(SpeedRect,Qt::AlignCenter, Speedstr);
    painter->restore();
}

//当前风向标
void WindMeter::drawWindPointer(QPainter *painter)
{
    painter->save();
    painter->rotate(m_twoAvAngle);
    QColor color(Qt::yellow);
    painter->setPen(color);
    painter->setBrush(color);
    painter->drawPolygon(QPolygon(3, &triangle[0][0]));
    painter->restore();
}


