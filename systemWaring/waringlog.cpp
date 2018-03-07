#include "waringlog.h"

WaringLogShow::WaringLogShow(QWidget *parent) :
    QWidget(parent)
{
    _init_infor_show();
    _init_size();
    _init_log_number();
    _init_show_kind();
    _init_logIndex();
}

void WaringLogShow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    if(width() != _m_width ||height() != _m_height){
        _m_width = width();
        _m_height = height();
        _m_setGeomerty();
    }
    painter.translate(width()/2,height()/2);
    int m_x = - width() / 2;
    int m_y = - height() / 2 ;
    int m_width = width();
    int m_height = 16;
    // title draw.
    painter.save();
    QLinearGradient gradwaring(0,m_y,0,m_y + m_height);
    gradwaring.setColorAt(0,Qt::gray);
    gradwaring.setColorAt(0.5,QColor("#D9D9D9"));
    painter.setBrush(gradwaring);
    painter.drawRoundedRect(m_x,m_y + 0.5,m_width,m_height,4,4);
    painter.setBrush(QColor("#F0F8FF"));
    painter.setPen(QPen(QColor("#4A708B"),4));
    painter.drawText(m_x,m_y,m_width * 1 / 20,m_height
                     ,Qt::AlignBottom | Qt::AlignHCenter,"序号");
    painter.drawText(m_x + m_width / 20,m_y,m_width * 3 / 20,m_height
                     ,Qt::AlignBottom | Qt::AlignHCenter,"时间");
    painter.drawText(m_x + m_width / 5,m_y,m_width * 14 / 20,m_height
                     ,Qt::AlignBottom | Qt::AlignLeft,"告警内容");
    painter.drawText(m_x + m_width * 9 / 10,m_y,m_width * 2 / 20,m_height
                     ,Qt::AlignBottom | Qt::AlignHCenter,"用户");
    painter.restore();

    //向前翻页
    painter.save();
    painter.drawText(width()/2 - 200,height()/2 - 40,60,10
                     ,Qt::AlignBottom | Qt::AlignHCenter,"前一页");
    painter.restore();

    //向后翻页
    painter.save();
    painter.drawText(width()/2 - 130,height()/2 - 40,60,10
                     ,Qt::AlignBottom | Qt::AlignHCenter,"后一页");
    painter.restore();
}

/*  ----------------------------
 *  function description
 *  日志数据确认处理
 * -----------------------------
 */
void WaringLogShow::_m_log_information_update_page(int index)
{
    if(_m_showConfirm){
        return;
    }
    if(index == _m_log_number || _m_warData.count() == 1){
    }
    else{
        for(int i = index;i < _m_log_number;i++){
            _m_warData[i] =  _m_warData[i + 1];
        }
    }
    _m_warData.remove(_m_log_number);
    _m_log_number--;
    if(_m_log_number * 18 == 0){
        infor->setSubHeight(1);
    }
    else{
        infor->setSubHeight(_m_log_number * 18);
    }
    infor->setDataMap(_m_warData);
}

void WaringLogShow::_m_add_log_Slot(QString logCtx,QString optioner)
{
    QString logMess,time;
    logMess  = tr("sequence:%1|").arg(_m_log_index);
    _m_log_index ++;
    logMess  = logMess + tr("context:%1|").arg(logCtx);
    time = QDateTime::currentDateTime().toString("yyyy/MM/dd hh-mm-ss");
    logMess  = logMess + tr("time:%1|optioner:%2").arg(time).arg(optioner);
    _m_add_logInformation(logMess);
    emit store_log_to_database(logMess);
    if(_m_log_index > 9999){
        _m_log_index = 1;
    }
}

void WaringLogShow::_init_infor_show()
{
    infor = new  WaringLogInforCtx();
    areaBar = new QScrollArea(this);
    areaBar->setWidget(infor);
    areaBar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void WaringLogShow::_m_setGeomerty()
{
    areaBar->setGeometry(0,17,width(),height()-18);
    infor->setSubWidth(width()-4);
    _m_log_number = _m_warData.count();
    infor->setSubHeight(_m_log_number * 18);
    infor->setDataMap(_m_warData);
}

void WaringLogShow::_m_add_logInformation(QString data)
{
    if(!data.isEmpty()){
        if(_m_log_number != 0){
            for(int n = _m_log_number; n >=1;n--){
                _m_warData[n + 1] = _m_warData[n];
            }
        }
        _m_warData[1] = data;
        _m_log_number = _m_warData.count();
    }
    if(_m_log_number > 30){
        _m_warData.remove(31);
        _m_log_number = 30;
    }
    if(!_m_showConfirm){
        // show confirm wars
        infor->setSubHeight(_m_log_number * 18);
        infor->setDataMap(_m_warData);
    }
}

void WaringLogShow::_init_size()
{
    _m_width = 0;
    _m_height = 0;
}

void WaringLogShow::_init_log_number()
{
    _m_log_number = 0;
}

void WaringLogShow::_init_show_kind()
{
    _m_showConfirm = false;
}

void WaringLogShow::_init_logIndex()
{
    _m_log_index = 0;
}

