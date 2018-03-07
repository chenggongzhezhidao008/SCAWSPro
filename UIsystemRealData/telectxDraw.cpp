#include "telectx.h"

void TelegramContextDealUI::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    if(!sizeFirstUpdate){
        setAllContrlGeometry();
        sizeFirstUpdate = true;
    }
    QPainter painter(this);
    int left = -width() / 2;
    int top = -height() / 2;
    int right = width() / 2;
    int buttom = height() / 2;

    int sHeight = height(); // V drection 4 * 4 - 100
    int sWidth = width(); // H drection 3 * 4

    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(right,buttom);
    painter.setPen(Qt::NoPen);

    painter.save();

    //qDebug()<<"draw one";
    painter.setPen(Qt::gray);

    // metar context show controls
    painter.setPen(QPen(Qt::gray,2));
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRoundedRect(left + 2,top + 4,sWidth - 4,sHeight / 2 - 6,6,6);
    painter.drawRoundedRect(left + 2,top + sHeight / 2 + 2,sWidth - 4,sHeight / 2 - 6,6,6);

    // metar send buttons controls
    //1 . update 更新
    QLinearGradient gradMetSend1(3,top + 75,3,top + 115);
    if(!m_Update){
        gradMetSend1.setColorAt(0,QColor("#4A708B"));
        gradMetSend1.setColorAt(1,QColor("#00688B"));

    }
    else{
        gradMetSend1.setColorAt(0,QColor("#CAE1FF"));
        gradMetSend1.setColorAt(1,QColor("#B0E0E6"));
    }
    painter.setBrush(gradMetSend1);
    painter.drawRoundRect(left + sWidth * 4 / 5 ,top + 9,sWidth / 5 - 6,(sHeight / 2 - 11) / 3 - 5,6,6);

    //2 . modify 修改
    QLinearGradient gradMetSend2(3,top + 75,3,top + 115);
    if(!m_Comfirm){
        gradMetSend2.setColorAt(0,QColor("#4A708B"));
        gradMetSend2.setColorAt(1,QColor("#00688B"));

    }
    else{
        gradMetSend2.setColorAt(0,QColor("#CAE1FF"));
        gradMetSend2.setColorAt(1,QColor("#B0E0E6"));
    }
    painter.setBrush(gradMetSend2);
    painter.drawRoundRect(left + sWidth * 4 / 5 ,top + 9 + (sHeight / 2 - 11) / 3 ,sWidth / 5 - 6,(sHeight / 2 - 11) / 3 - 5,6,6);

    //3 . send 发送
    QLinearGradient gradMetSend3(3,top + 75,3,top + 115);
    if(!m_send){
        gradMetSend3.setColorAt(0,QColor("#4A708B"));
        gradMetSend3.setColorAt(1,QColor("#00688B"));

    }
    else{
        gradMetSend3.setColorAt(0,QColor("#CAE1FF"));
        gradMetSend3.setColorAt(1,QColor("#B0E0E6"));
    }
    painter.setBrush(gradMetSend3);
    painter.drawRoundRect(left + sWidth * 4 / 5 ,top + 9 + (sHeight / 2 - 11) * 2 / 3,sWidth / 5 - 6,(sHeight / 2 - 11) / 3 - 5,3,3);

    //4 metar 报确认
    QLinearGradient gradMetSend4(0,buttom - 102,0,buttom - 8);
    if(!m_metComfirm){
        gradMetSend4.setColorAt(0,QColor("#4A708B"));
        gradMetSend4.setColorAt(1,QColor("#00688B"));

    }
    else{
        gradMetSend4.setColorAt(0,QColor("#CAE1FF"));
        gradMetSend4.setColorAt(1,QColor("#B0E0E6"));
    }
    painter.setBrush(gradMetSend4);
    painter.drawRoundRect(left  + width() / 2 - (width() / 2) / 5,top + sHeight / 2 + 5,(width() / 2) / 5 - 6,sHeight / 2 - 12,6,6);

    // spacial 报确认
    QLinearGradient gradMetSend5(0,buttom - 102,0,buttom - 8);
    if(!m_spacComfirm){
        gradMetSend5.setColorAt(0,QColor("#4A708B"));
        gradMetSend5.setColorAt(1,QColor("#00688B"));
    }
    else{
        gradMetSend5.setColorAt(0,QColor("#CAE1FF"));
        gradMetSend5.setColorAt(1,QColor("#B0E0E6"));
    }
    painter.setBrush(gradMetSend5);
    painter.drawRoundRect(left  + width() - (width() / 2) / 5,top + sHeight / 2 + 5,(width() / 2) / 5 - 6,sHeight / 2 - 12,6,6);

    //metar show control titles
    painter.setPen(Qt::black);
    painter.drawText(left ,top,80,sHeight / 2,Qt::AlignCenter,m_contextNameStr);

    painter.setPen(Qt::white);
    painter.drawText(left  + width() / 2 - (width() / 2) / 5,top + sHeight / 2 + 5,(width() / 2) / 5 - 6,sHeight / 2 - 12,Qt::AlignCenter,"METAR确认");
    painter.drawText(left  + width() - (width() / 2) / 5,top + sHeight / 2 + 5,(width() / 2) / 5 - 6,sHeight / 2 - 12,Qt::AlignCenter,"SPACIL确认");

    painter.drawText(left + sWidth * 4 / 5 ,top + 9,sWidth / 5 - 6,(sHeight / 2 - 11) / 3 - 5,Qt::AlignCenter,"更新");
    if(met_modifytTelegramFlag){
        painter.drawText(left + sWidth * 4 / 5 ,top + 9 + (sHeight / 2 - 11) / 3 ,sWidth / 5 - 6,(sHeight / 2 - 11) / 3 - 5,
                         Qt::AlignCenter,"确认修改");
    }
    else{
        painter.drawText(left + sWidth * 4 / 5 ,top + 9 + (sHeight / 2 - 11) / 3 ,sWidth / 5 - 6,(sHeight / 2 - 11) / 3 - 5,
                         Qt::AlignCenter,"修改");
    }
    painter.drawText(left + sWidth * 4 / 5 ,top + 9 + (sHeight / 2 - 11) * 2 / 3,sWidth / 5 - 6,(sHeight / 2 - 11) / 3 - 5,
                     Qt::AlignCenter,"发送");
    painter.restore();
}

void TelegramContextDealUI::setTelegramName(QString telegramName)
{
    m_contextNameStr.clear();
    m_contextNameStr = telegramName;
    update();
}
