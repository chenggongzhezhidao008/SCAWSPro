#include "waringloginforCtx.h"

WaringLogInforCtx::WaringLogInforCtx(QWidget *parent) :
    QWidget(parent)
{
    initValues();
    initNumValue();
    initIndexValue();
    _init_cell_width();
}

void WaringLogInforCtx::_set_data_cell_width(int w)
{
    m_cell_w = w;
}

void WaringLogInforCtx::paintEvent(QPaintEvent *e)
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
    painter.setBrush(QColor("#FFFAF0"));
    painter.setPen(Qt::NoPen);
    for(int i = 0;i < m_num;i++){
        if(i == (m_index - 1)){
            painter.setBrush(QColor("#CDAF95"));
            painter.drawRect(left,top + 18 * i,width(),16);
            painter.setBrush(QColor("#FFFAF0"));
        }
        else{
            painter.drawRect(left,top + 18 * i,width(),16);
        }
    }
    painter.setPen(QPen(Qt::black,3));
    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(13);
    painter.setFont(font);
    QStringList list;
    int len;
    int m_y;
    QString subStr,valueStr;
    for(int i = 0;i < m_num;i++)
    {
        list.clear();
        list = m_DataMap[i + 1].split("|",QString::SkipEmptyParts);
        len = list.length();
        m_y = - height() / 2 + 18 * i;
        for(int n = 0;n < len;n++){
            subStr.clear();
            valueStr.clear();
            subStr = list.value(n).split(":").value(0);
            valueStr = list.value(n).split(":",QString::SkipEmptyParts).value(1);
            if(subStr == "sequence"){
                painter.drawText(left,m_y,width() * 1 / 20,16
                                 ,Qt::AlignBottom | Qt::AlignHCenter,valueStr);
            }
            else if(subStr == "time"){
                painter.drawText(left + width() * 1 / 20,m_y,width() * 3 / 20,16
                                 ,Qt::AlignBottom | Qt::AlignHCenter,valueStr);
            }
            else if(subStr == "context"){
                painter.drawText(left + width() * 4 / 20,m_y,width() * 14 / 20,16
                                 ,Qt::AlignBottom | Qt::AlignLeft,valueStr);

            }
            else if(subStr == "optioner"){
                painter.drawText(left + width() * 18 / 20,m_y,width() * 2 / 20,16
                                 ,Qt::AlignBottom | Qt::AlignHCenter,valueStr);
            }
        }
    }
    painter.restore();
}

void WaringLogInforCtx::mousePressEvent(QMouseEvent *e)
{
    bool flag = false;
    if(e->button() == Qt::LeftButton){
        int PosY = e->pos().y();
        for(int n = 0;n < m_num;n++){
            if(PosY > (18 * n) && PosY < (18 * (n + 1))){
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

void WaringLogInforCtx::mouseDoubleClickEvent(QMouseEvent *e)
{
    bool flag = false;
    if(e->button() == Qt::LeftButton){
        int PosY = e->pos().y();
        for(int n = 0;n < m_num;n++){
            if(PosY > (18 * n) && PosY < (18 * (n + 1))){
                flag = true;
                m_index = n + 1;
                emit doubleClickSignal(m_index);
            }
        }
    }
    qDebug()<<"double click index is:"<<m_index;
    if(flag){
        update();
    }
}

void WaringLogInforCtx::setSubWidth(int value)
{
    if( m_width != value){
        m_width = value;
        this->setGeometry(0,0,m_width,m_height);
        update();
    }
}

void WaringLogInforCtx::setSubHeight(int value)
{
    if(m_height != value){
        m_height = value;
        this->setGeometry(0,0,m_width,m_height);
        update();
    }
}
void WaringLogInforCtx::setDataMap(InforMap data)
{
    m_DataMap.clear();
    m_DataMap = data;
    m_num = m_DataMap.count();
    update();
}

void WaringLogInforCtx::initValues()
{
    m_width = 20;
    m_height = 20;
}

void WaringLogInforCtx::initNumValue()
{
    m_num = 0;
}

void WaringLogInforCtx::initIndexValue()
{
    m_index = -1;
}

void WaringLogInforCtx::_init_cell_width()
{
    m_cell_w = 180;
}
