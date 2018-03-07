#include "telegramcfg.h"

void TelegramCFG::mousePressEvent(QMouseEvent *e)
{
    bool flag = false;
    if(e->button() == Qt::LeftButton)// 标题栏按钮
    {
        int posY = e->pos().y();
        int posX = e->pos().x();
        int sWidth =  width()/ 2 + 10;
        int sHeight = height()* 2/3 - 12;
        if(posX > sWidth
                && posX < (sWidth+120)    // 1 . 更新AFTN配置内容
                && posY > sHeight
                && posY < (sHeight+35))
        {
            updateAFTNValues();
            m_metarSetConfirm = true;
            flag = true;
            releaseDo = true;
        }
        else if(posX > (sWidth+130)      // 2 . 发送AFTN配置
                && posX < (sWidth+250)
                && posY > sHeight
                && posY < (sHeight+35))
        {
            setAFTNParavmeter();
            m_metarSetCancel = true;
            flag = true;
            releaseDo = true;
        }
    }
    e->accept();
    if(flag){
        update();
    }
}

void TelegramCFG::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_metarSetConfirm){
        m_metarSetConfirm = false;
    }
    if(m_metarSetCancel){
        m_metarSetCancel = false;
    }
    if(releaseDo){
        update();
        releaseDo = false;
    }
    e->accept();
}

void TelegramCFG::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    int left = -width() / 2;
    int top = -height() / 2;
    int sWidth = width();
    int sHeight = height();
    int subSHeight = 30;
    int fram1Start = top + 4;
    int fram2Start = top + 8 + sHeight * 4 / 11;
    int fram3Start = top + 12 + sHeight * 9 / 11;
    if(wSize != sWidth || hSize != sHeight){
        wSize = sWidth;
        hSize = sHeight;
        setGeometryEditContrls();
        setComBoxGeometry();
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2,height() / 2);
    painter.setPen(Qt::NoPen);

    //画区域背景
    painter.save();
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(left,top,sWidth - 2,sHeight - 2,3,3);
    painter.setBrush(Qt::gray);
    painter.drawRoundedRect(left + 2,top + 2,sWidth - 2,sHeight - 2,3,3);
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRoundedRect(left + 2,top + 2,sWidth - 4,sHeight - 4,3,3);
    painter.restore();

    //qDebug()<<"draw five";
    painter.save();
    painter.setPen(Qt::gray);
    painter.drawRect(left + 4,fram1Start,sWidth / 2,sHeight * 4 / 11);
    painter.drawRect(left + 4,fram2Start,sWidth / 2,sHeight * 5 / 11);
    painter.drawRect(left + 4,fram3Start,sWidth / 2,sHeight * 2/ 11);
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::black);

    painter.drawText(left + 20,fram1Start,300,30,Qt::AlignVCenter | Qt::AlignLeft,"报文设置");
    painter.drawText(left + 20,fram2Start,300,30,Qt::AlignVCenter | Qt::AlignLeft,"报头报尾设置");
    painter.drawText(left + 20,fram3Start,300,30,Qt::AlignVCenter | Qt::AlignLeft,"换行回车符设置");

    painter.setPen(Qt::black);
    painter.drawText(left + 4 + sWidth / 4,fram1Start + 90 ,100,subSHeight,Qt::AlignCenter,"报文冠子");
    painter.drawText(left + 4 + sWidth / 4,fram1Start + 130 ,100,subSHeight,Qt::AlignCenter,"流水长度");

    painter.drawText(left + 4,fram1Start + 50 ,100,subSHeight,Qt::AlignCenter,"AFTN地址");
    painter.drawText(left + 4,fram1Start + 90 ,100,subSHeight,Qt::AlignCenter,"信道名");
    painter.drawText(left + 4,fram1Start + 130 ,100,subSHeight,Qt::AlignCenter,"分隔符");

    painter.drawText(left + 4,fram2Start + 50 ,100,subSHeight,Qt::AlignCenter,"发送报头");
    painter.drawText(left + 4,fram2Start + 90 ,100,subSHeight,Qt::AlignCenter,"发送报尾");
    painter.drawText(left + 4,fram2Start + 130 ,100,subSHeight,Qt::AlignCenter,"接收报头");
    painter.drawText(left + 4,fram2Start + 170,100,subSHeight,Qt::AlignCenter,"接收报尾");

    painter.drawText(left + 4,fram3Start + 40,100,subSHeight,Qt::AlignCenter,"AFTN电报");
    painter.drawText(left + 4 + sWidth / 4,fram3Start + 40,120,subSHeight,Qt::AlignCenter,"远端发送地址");
    painter.restore();

    //metar message show

    painter.save();
    painter.setPen(Qt::gray);
    painter.drawRect(left + 4 + sWidth / 2 + 4,top + 4,sWidth / 2 - 4,sHeight + 8);
    painter.setPen(QPen(Qt::black,12));
    painter.drawText(left + 4 + sWidth / 2 + 20,top,300,30,
                     Qt::AlignVCenter | Qt::AlignLeft,"AFTN 配置参数");

    //button show
    painter.setPen(Qt::NoPen);
    QLinearGradient gradStart(0,top + 4 + (sHeight - 8) * 2 / 3
                              ,0,top + 34 + (sHeight - 8) * 2 / 3);
    QLinearGradient gradEnd(0,top + 4 + (sHeight - 8) * 2 / 3
                            ,0,top + 34 + (sHeight - 8) * 2 / 3);
    gradStart.setColorAt(0,QColor("#4A708B"));
    gradStart.setColorAt(1,QColor("#00688B"));
    gradEnd.setColorAt(0,QColor("#CAE1FF"));
    gradEnd.setColorAt(1,QColor("#B0E0E6"));
    if(!m_metarSetConfirm){
        painter.setBrush(gradStart);
    }
    else{
        painter.setBrush(gradEnd);
    }
    painter.drawRoundedRect(left + sWidth / 2 + 10
                            ,top + 8 + (sHeight - 8) * 12 / 18
                            ,120,30,8,8);
    if(!m_metarSetCancel){
        painter.setBrush(gradStart);
    }
    else{
        painter.setBrush(gradEnd);
    }
    painter.drawRoundedRect(left + sWidth / 2 + 140
                            ,top + 8 + (sHeight - 8) * 2 / 3
                            ,120,30,8,8);
    painter.setPen(Qt::white);
    painter.drawText(left + sWidth / 2 + 10
                     ,top + 4 + (sHeight - 8) * 2 / 3
                     ,120,30,Qt::AlignCenter,"更新");
    painter.drawText(left + sWidth / 2 + 140
                     ,top + 4 + (sHeight - 8) * 2 / 3
                     ,120,30,Qt::AlignCenter,"设置");
    painter.restore();

    //set metar context show
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::gray);
    for(int met = 1; met < 12;met++){
        painter.drawRoundedRect(left + 4 + sWidth / 2 + 8,top + 4 + 34 * met
                                ,sWidth / 4 - 9,26,8,8);
    }
    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPixelSize(14);
    painter.setFont(font);
    for(int met = 1; met < 12;met++){
        painter.drawText(left + sWidth / 2 + 60,top + 4 + 34 * met
                         ,sWidth / 2 - 96,26,
                         Qt::AlignVCenter | Qt::AlignLeft,AFTNInitValues[met]);
    }
    painter.restore();
}

