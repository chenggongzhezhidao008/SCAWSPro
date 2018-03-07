#include "waveline.h"
#include <QDebug>
#include <QVector>
#include <QLineF>

void WaveLine::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(this->width() / 2,this->height() / 2);
    drawBackground(&painter);
    drawName(&painter);
    drawLineNames(&painter);
    drawScaleLines(&painter);
    drawTimeLines(&painter);
    drawPushButton(&painter);
    drawWaves(&painter);
}

void WaveLine::drawName(QPainter *painter)
{
    painter->save();
    QFont font = painter->font();
    font.setPixelSize(23);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(Qt::gray);
    painter->drawText(- this->width() / 2 + 2,- this->height() / 2,//+ 2偏右 +4 名称稍偏下
                      200,30,Qt::AlignVCenter | Qt::AlignLeft,this->m_graphname);
    painter->restore();
}

void WaveLine::drawLineNames(QPainter *painter)
{
    painter->save();
    QLinearGradient gradientName;
    QStringList existWaveLineList = this->showWaves.keys();
    int existNum = existWaveLineList.length();
    int num = this->m_lineNames.count();
    for (int nameNum = 0; nameNum < num; nameNum++) {
        gradientName.setStart(- this->width() / 2 + 100 * nameNum + 2,//+ 2 右移一点
                              - this->height() / 2 + 30 );
        gradientName.setFinalStop(- this->width() / 2 + 100 * nameNum + 27/*25 + 2*/,//+ 2 右移一点
                                  - this->height() / 2 + 55/*25 + 30*/ );
        gradientName.setColorAt(0,Qt::white);
        gradientName.setColorAt(0.5,Qt::green);
        painter->setBrush(gradientName);
        painter->drawRect(QRect(- this->width() / 2 + 100 * nameNum + 2,//+ 2 右移一点
                                - this->height() / 2 + 30 ,25,25));
    }

    //text......
    QFont font = painter->font();
    font.setPixelSize(16);
    painter->setFont(font);
    QString lineNameStr;
    for (int nameNum = 0; nameNum < num; nameNum++) {
        painter->setPen(Qt::gray);
        lineNameStr = m_lineNames[nameNum + 1];
        painter->drawText(QRect(- this->width() / 2 + 100 * nameNum +30 + 4,//+ 4 右移一点
                                - this->height() / 2 + 30 ,70,25),Qt::AlignVCenter | Qt::AlignLeft,lineNameStr);
        for(int j = 0; j < existNum; j++){
            if(existWaveLineList.value(j) == lineNameStr){
                if(showWaves[lineNameStr]){
                    painter->setPen(Qt::black);
                    QVector<QLine> VLines;
                    VLines.push_back(QLine(- this->width() / 2 + 100 * nameNum + 2,
                                           - this->height() / 2 + 42 ,
                                           - this->width() / 2 + 100 * nameNum + 14,
                                           - this->height() / 2 + 55));
                    VLines.push_back(QLine(- this->width() / 2 + 100 * nameNum + 14,
                                           - this->height() / 2 + 55 ,
                                           - this->width() / 2 + 100 * nameNum + 27,
                                           - this->height() / 2 + 30));
                    painter->drawLines(VLines);
                }
            }
        }
    }
    painter->restore();
}

void WaveLine::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#4F4F4F"));
    painter->drawRect(- this->width() / 2,- this->height() / 2,
                      this->width(),this->height());
    painter->restore();

    //绘制图形背景
    painter->save();
    painter->setBrush(QColor("#F0F8FF"));
    painter->drawRect(- this->width() / 2 + 90,- this->height() / 2 + 60,//+ 60 留住页眉高度
                      this->width() - 90 - 2 - 70,// - 70 留出按钮区域
                      this->height() - 90);
    painter->restore();
}

void WaveLine::drawScaleLines(QPainter *painter)
{
    QVector<QLine> vectorHLines;
    painter->save();
    painter->setPen(Qt::gray);
    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);
    int linesNum = 9;
    for(int i = linesNum;i > 0 ;i--){
        painter->drawText(- this->width() / 2 + 25,
                          - this->height() / 2 + 60 -10 + (this->height() - 90) * i / (linesNum + 1),
                          30,20,Qt::AlignCenter,QString("%1").arg(((linesNum + 1) - i) * 10 ));//字体相对水平线垂直居中，右靠线左端，宽高比为30 * 20
        vectorHLines.push_back(QLine(- this->width() / 2 + 70,
                                     - this->height() / 2 + 60 + (this->height() - 90) * i / (linesNum + 1),
                                     this->width() / 2 - 2 - 70,// - 70 留出按钮区域
                                     - this->height() / 2 + 60 + (this->height() - 90) * i / (linesNum + 1)));
    }
    painter->restore();
    painter->save();
    painter->drawLines(vectorHLines);
    painter->restore();
}

void WaveLine::drawTimeLines(QPainter *painter)
{
    QVector<QLine> linesNamesRect;
    painter->save();

    for (int timesSacel = 1; timesSacel < 7; timesSacel++) {
        linesNamesRect.push_back(QLine(- this->width() / 2 + 90     //                                     -(this->width() - 90 - 72) / 14  //- (this->width() - 90 - 72) / 14  每条竖线往左移动半个步进
                                       +(this->width() - 90 - 72) * timesSacel / 7  ,  //+ 90 左侧留出的宽度 - 72右侧留出的宽度
                                       - this->height() / 2 + 60,   //+ 60 上测留出的高度
                                       - this->width() / 2 + 90     //                                     -(this->width() - 90 - 72) / 14
                                       +(this->width() - 90 - 72) * timesSacel / 7 ,
                                       this->height() / 2 - 30 + 10));//- 30 下测预留出的高度 + 10竖线向下伸出长度
    }
    painter->drawLines(linesNamesRect);
    painter->setPen(Qt::gray);
    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);
    QTime sTime,time = QTime::currentTime();
    for (int timesSacel = 1; timesSacel < 7; timesSacel++) {
        sTime = time.addSecs(10 * 60 * (timesSacel - 6));
        painter->drawText(- this->width() / 2 + 90 + (this->width() - 90 - 72) * timesSacel / 7 - 40,//- 40 让时间的文本字体往左移20使其垂直评分线与时间竖线同线
                          this->height() / 2 - 20,80,20,Qt::AlignCenter,sTime.toString("hh:mm"));//80*20 时间文本的宽高比
    }
    painter->restore();
}

void WaveLine::drawPushButton(QPainter *painter)
{
    //track  mouse
    painter->save();

    painter->setPen(Qt::gray);
    QFont font = painter->font();
    font.setPixelSize(16);
    painter->setFont(font);
    painter->drawText(this->width() / 2 - 40 ,- this->height() / 2 + 10,30,20,Qt::AlignCenter,"跟踪");
    painter->setBrush(QColor("#F0F8FF"));/*Qt::red*/
    painter->drawRect(this->width() / 2 - 65 ,- this->height() / 2 + 13,16,16);
    if(this->m_track){
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::black);
        painter->translate(this->width() / 2 - 65 + 8,- this->height() / 2 + 13 + 8);
        painter->rotate(45);
        painter->drawRoundRect(-8,-3,16,6,8,3);
        painter->drawRoundRect(-3,-8,6,16,3,8);
    }
    painter->restore();

    //time selected
    painter->save();
    QLinearGradient gradient,gradient2;
    for(int i = 0; i < 8;i++){
        if(this->m_slectTimeList[this->m_timeList[i + 1]]){
            gradient.setStart(this->width() / 2 - 65,-this->height() / 2 + 40 + (this->height() - 40) * i / 8);
            gradient.setFinalStop(this->width() / 2 - 65,-this->height() / 2 + 70 + (this->height() - 40) * i / 8);
            gradient.setColorAt(0,Qt::white);
            painter->setBrush(gradient);
        }
        else{
            gradient2.setStart(this->width() / 2 - 65,-this->height() / 2 + 40 + (this->height() - 40) * i / 8);
            gradient2.setFinalStop(this->width() / 2 - 65,-this->height() / 2 + 70 + (this->height() - 40) * i / 8);
            gradient2.setColorAt(0,Qt::white);
            gradient2.setColorAt(0.5,Qt::gray);
            gradient2.setColorAt(1,Qt::white);
            painter->setBrush(gradient2);
        }
        painter->drawRect(this->width() / 2 - 65,
                          -this->height() / 2 + 40 + (this->height() - 40 -10) * i / 8 //-10 按钮与底线预留的高度
                          ,60,30);
    }
    painter->setPen(Qt::black);
    QFont fonth = painter->font();
    fonth.setPixelSize(16);
    painter->setFont(fonth);
    for(int i = 0; i < 8;i++){
        painter->drawText(this->width() / 2 - 65,
                          -this->height() / 2 + 40 + (this->height() - 40 -10) * i / 8
                          ,60,30,Qt::AlignCenter,this->m_timeList[ i + 1 ]);
    }
    painter->restore();
}

void WaveLine::drawWaves(QPainter *painter)
{
    int timeIndex = this->hourSelected;
    int timeLength = this->hourSelected * 3600;
    //qDebug()<<"time selected:"<<timeIndex;
    if(timeIndex == 1){
        drawLine(painter,timeLength);
    }
    else if(timeIndex == 2){
        drawLine(painter,timeLength);
    }
    else if(timeIndex == 3){
        drawLine(painter,timeLength);
    }
    else if(timeIndex == 6){
        drawLine(painter,timeLength);
    }
    else if(timeIndex == 12){
        drawLine(painter,timeLength);
    }
    else if(timeIndex == 24){
        drawLine(painter,timeLength);
    }
    else if(timeIndex == 48){
        drawLine(painter,timeLength);
    }
    else if(timeIndex == 72){
        drawLine(painter,timeLength);
    }

}

void WaveLine::drawLine(QPainter *&painter,int timeLength)
{
    painter->save();
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(3);
    painter->setPen(pen);
    QStringList keys = m_waveData1Hour.keys();
    QStringList pointList;
    for(int line = 0;line < keys.length();line++){
        if(showWaves["湿度"+ keys.value(line)]){
            pointList.clear();
            qDebug()<<"show:"<<"湿度"+ keys.value(line) + "曲线";
            pointList = m_waveData1Hour[keys.value(line)];
            //qDebug()<<"points are:"<<pointList;
            QDateTime pointDatetime,drawDatetime;
            drawDatetime = newDateTime.addSecs( -timeLength );
            int pointNum = pointList.length();
            for(int p = 0;p < pointNum;p++){
                //时间计算
                pointDatetime = QDateTime::fromString(pointList.value(p).split(":").value(0),"yyyy'/'MM'/'dd'/'hh'/'mm'/'ss");
                qreal x = - this->width() / 2 + 90 + (drawDatetime.secsTo(pointDatetime)  * (this->width() - 162))/ timeLength;
                //qDebug()<<"drawDatetime:"<<drawDatetime<<"pointDatetime:"<<pointDatetime;
                //数值计算
                qreal dataValue = pointList.value(p).split(":").value(1).toDouble();
                qreal y = this->height() / 2 - 30 - (dataValue  * (this->height() - 90))/ 100;
                if(p == 0){
                    m_x = x;
                    m_y = y;
                    continue;
                }
                painter->drawLine(m_x,m_y,x,y);
                m_x = x;
                m_y = y;
                qDebug()<<"x==>:"<<x<<" y==>"<<y;
            }
        }
    }
    painter->restore();
}




















