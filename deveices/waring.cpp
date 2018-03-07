#include "waring.h"

WaringShow::WaringShow(QWidget *parent) :
    QWidget(parent)
{
    initValue();
    m_init_waring_show();
    m_init_size();
}

void WaringShow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    if(width() != m_width || height() != m_height){
        m_width = width();
        m_height = height();
        m_init_waring_geomerty();
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
    painter.drawRoundedRect(left + 2,top + 2,subWidth - 2,subHeight - 2,3,3);
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRoundedRect(left + 2,top + 2,subWidth - 4,subHeight - 4,3,3);
    painter.restore();

    //背景光选项
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::gray);
    painter.drawRect(left + 10,top + 10,100,20);
    painter.drawRect(left + 220,top + 10,100,20);
    painter.setPen(QPen(Qt::black,12));
    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(12);
    painter.setFont(font);
    painter.drawText(left + 10,top + 10,100,20,Qt::AlignCenter,"背景光等级");
    painter.drawText(left + 110,top + 10,100,20,Qt::AlignCenter,m_grade);
    painter.drawText(left + 220,top + 10,100,20,Qt::AlignCenter,"实时数值");
    painter.drawText(left + 330,top + 10,100,20,Qt::AlignCenter,m_adValue);
    painter.restore();
}

void WaringShow::AFFIX9NewMessageSendUp(QString dCtx, InforData data)
{
   if(dCtx == "basiLight"){
       m_basiLight.clear();
       m_basiLight = data;
       m_grade = findAppointKeyValues(m_basiLight,"Grade").value(0);
       m_adValue = findAppointKeyValues(m_basiLight,"Value").value(0);
       update();
   }
   return ;
}

void WaringShow::initValue()
{
    m_grade = "///";
    m_adValue = "///";
}
QStringList WaringShow::findAppointKeyValues(InforData dataPart, QString key)
{
    int num = dataPart.count(),subNum;
    QString itemStr;
    QStringList itemStrList,sub,result;
    for(int item = 1;item <= num;item++){
        itemStr.clear();
        itemStrList.clear();
        itemStr = dataPart[QString("index%1").arg(item)];
        itemStrList = itemStr.split(",");
        subNum = itemStrList.length();
        for(int subItem = 0;subItem < subNum;subItem++){
            sub.clear();
            sub = itemStrList.value(subItem).split("=");
            if(sub.value(0) == key){
                result.push_back(sub.value(1));
            }
        }
    }
    return result;
}

void WaringShow::m_init_waring_show()
{
    warShow = new WaringLogShow(this);
}

void WaringShow::m_init_waring_geomerty()
{
    warShow->setGeometry(2,32,width() - 2,height() - 32);
}

void WaringShow::m_init_size()
{
    m_width = 0;
    m_height = 0;
}
