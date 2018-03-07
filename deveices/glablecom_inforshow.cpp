#include "glablecom_inforshow.h"

GlableCom_InforShow::GlableCom_InforShow(QWidget *parent) :
    QWidget(parent)
{
    initValues();
    initNumValue();
    initIndexValue();
}

void GlableCom_InforShow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2,height() / 2);
    int left = - width() / 2;
    int top = - height() / 2;
    painter.save();
    painter.setBrush(Qt::gray);
    painter.drawRect(left,top,width(),height());
    painter.restore();

//     显示数据内容
    painter.save();
    painter.setBrush(Qt::black/*QColor("#CDC1C5")*/);
    painter.setPen(Qt::NoPen);
    for(int i = 0;i < m_num;i++){
        if(i == (m_index - 1)){
            painter.setBrush(QColor("#CDAF95"));
            painter.drawRect(left,top + 30 * i,width(),28);
            painter.setBrush(Qt::black/*QColor("#CDC1C5")*/);
        }
        else{
            painter.drawRect(left,top + 30 * i,width(),28);
        }
    }
     painter.setPen(QPen(Qt::white,3));
     QFont font = painter.font();
     font.setBold(true);
     font.setPixelSize(13);
     painter.setFont(font);
     for(int i = 0;i < m_num;i++){
         painter.drawText(left + 10,top + 30 * i,width(),28,
                          Qt::AlignVCenter | Qt::AlignLeft,m_DataMap[i + 1]);
     }
    painter.restore();
}

void GlableCom_InforShow::mousePressEvent(QMouseEvent *e)
{
    bool flag = false;
    if(e->button() == Qt::LeftButton){
        int PosY = e->pos().y();
        for(int n = 0;n < m_num;n++){
            if(PosY > (30 * n) && PosY < (30 * (n + 1) - 2)){
                 flag = true;
                 m_index = n + 1;
            }
        }
    }
    qDebug()<<"index is:"<<m_index;
    if(flag){
        update();
    }
}

void GlableCom_InforShow::initValues()
{
    m_width = 20;
    m_height = 20;
}

void GlableCom_InforShow::initNumValue()
{
    m_num = 0;
}

void GlableCom_InforShow::initIndexValue()
{
    m_index = -1;
}
