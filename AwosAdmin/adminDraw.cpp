#include "awosadmin.h"
#include <QDebug>

void AwosAdmin::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    //绘图
    m_wdith =  width();
    m_heigh =  height();
    QPainter painter(this);
    painter.setBrush(QColor("#4F4F4F"));
    painter.translate(m_wdith / 2,m_heigh / 2);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.save();
    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(14);
    font.setPointSize(12);
    painter.setFont(font);
    //背景颜色
    painter.drawRect(- m_wdith / 2, - m_heigh / 2,m_wdith,m_heigh);

    //标签
    painter.setPen(Qt::white);
    painter.drawText(- m_wdith * 2 / 5 + 40,- m_heigh * 2 / 5,m_wdith * 3/ 10,m_heigh / 5,Qt::AlignHCenter | Qt::AlignBottom,"用户");
    painter.drawText(- m_wdith * 2 / 5 + 40,- m_heigh / 5,m_wdith * 3/ 10,m_heigh / 5,Qt::AlignHCenter | Qt::AlignBottom,"口令");

    //输入行编辑
    painter.drawLine(- m_wdith / 10,- m_heigh / 5, m_wdith * 2 / 5,- m_heigh / 5);
    painter.drawLine(- m_wdith / 10, 0 ,m_wdith * 2 / 5,0);

    //登录分类
    QPoint configStartPoint(0,m_heigh / 5 );
    QPoint configEndPoint(0,m_heigh * 2 / 5 );
    QLinearGradient gradMet1(configStartPoint,configEndPoint);
    QLinearGradient gradMet2(configStartPoint,configEndPoint);
    gradMet1.setColorAt(0,QColor("#4A708B"));
    gradMet1.setColorAt(1,QColor("#00688B"));
    gradMet2.setColorAt(0,QColor("#CAE1FF"));
    gradMet2.setColorAt(1,QColor("#B0E0E6"));

    if(!_m_forcaster){
        painter.setBrush(gradMet1);
    }
    else{
        painter.setBrush(gradMet2);
    }
    painter.drawRoundRect(- m_wdith * 17 / 36,m_heigh / 5
                          ,m_wdith / 6,m_heigh / 5,m_heigh / 10,m_heigh / 10);
    if(!_m_obsever){
        painter.setBrush(gradMet1);
    }
    else{
        painter.setBrush(gradMet2);
    }
    painter.drawRoundRect(- m_wdith * 10 / 36,m_heigh / 5
                          ,m_wdith / 6,m_heigh / 5,m_heigh / 10,m_heigh / 10);
    if(!_m_machine){
        painter.setBrush(gradMet1);
    }
    else{
        painter.setBrush(gradMet2);
    }
    painter.drawRoundRect(- m_wdith * 3 / 36,m_heigh / 5
                          ,m_wdith / 6,m_heigh / 5,m_heigh / 10,m_heigh / 10);
    if(!_m_tower){
        painter.setBrush(gradMet1);
    }
    else{
        painter.setBrush(gradMet2);
    }
    painter.drawRoundRect(+ m_wdith * 4 / 36,m_heigh / 5
                          ,m_wdith / 6,m_heigh / 5,m_heigh / 10,m_heigh / 10);
    if(!_m_manager){
        painter.setBrush(gradMet1);
    }
    else{
        painter.setBrush(gradMet2);
    }
    painter.drawRoundRect(+ m_wdith * 11 / 36,m_heigh / 5
                          ,m_wdith / 6,m_heigh / 5,m_heigh / 10,m_heigh / 10);

    //绘制字符
    painter.drawText(- m_wdith * 17 / 36,m_heigh / 5 - 3 ,m_wdith / 6,m_heigh / 5,
                     Qt::AlignCenter,"预报");
    painter.drawText(- m_wdith * 10 / 36,m_heigh / 5 - 3,m_wdith / 6,m_heigh / 5,
                     Qt::AlignCenter,"观测");
    painter.drawText(- m_wdith * 3 / 36,m_heigh / 5 - 3,m_wdith / 6,m_heigh / 5,
                     Qt::AlignCenter,"机务");
    painter.drawText(+ m_wdith * 4 / 36,m_heigh / 5 - 3,m_wdith / 6,m_heigh / 5,
                     Qt::AlignCenter,"塔台");
    painter.drawText(+ m_wdith * 11 / 36,m_heigh / 5 - 3,m_wdith / 6,m_heigh / 5,
                     Qt::AlignCenter,"管理");
    painter.restore();

    painter.save();
    painter.setPen(Qt::NoPen);
    QLinearGradient gradT(0,-height()/2,0,30);
    gradT.setColorAt(0,QColor("#4F4F4F"));
    gradT.setColorAt(0.2,QColor("#4F94CD"));
    painter.setBrush(gradT);
    painter.drawRect(-width()/2,-height()/2,width(),30);
    painter.restore();

    //画界面控制按钮
    painter.save();

    //4画按钮形状
    QPen drawPen;
    drawPen.setWidth(3);
    drawPen.setColor(Qt::white);
    painter.setPen(drawPen);

    //关闭
    if(!_m_closed)
    {
        painter.drawLine(width()/2 - 24,-height()/2 + 9
                         ,width()/2 - 12,-height()/2 + 21);
        painter.drawLine(width()/2 - 24,-height()/2 + 21
                         ,width()/2 - 12,-height()/2 + 9);
    }
    else{
        painter.drawLine(width()/2 - 20,-height()/2 + 11
                         ,width()/2 - 12,-height()/2 + 19);
        painter.drawLine(width()/2 - 20,-height()/2 + 19
                         ,width()/2 - 12,-height()/2 + 11);
    }
    painter.restore();
    if(!txtStr.isEmpty())
    {
        painter.save();
        painter.setPen(QPen(Qt::white,3));
        painter.drawText(-width()/2 + 10,-height()/2
                         ,width() - 30,30
                         ,Qt::AlignLeft|Qt::AlignVCenter
                         ,txtStr);
        painter.restore();
    }
}

void AwosAdmin::mousePressEvent(QMouseEvent *event)
{
    bool _v_flag;
    _v_flag = false;                                                                          //_m_manager
    if(event->button() == Qt::LeftButton)
    {
        //qDebug()<<"the mouse coordinate:"<<event->pos();
        int posY = event->pos().y();
        int posX = event->pos().x();

        //打开跟踪
        if(posY > (this->height() * 7 / 10) && posY < (this->height() * 9 / 10))
        {
            if(posX >(width() / 36) && posX < (width() * 7 / 36))
            {
                _v_flag = true;
                _m_forcaster = true;
                _m_release = true;
                setLoginClass("预报");
            }
            else if(posX >(width() / 9) && posX < (width() * 7 / 18))
            {
                _v_flag = true;
                _m_obsever = true;
                _m_release = true;
                setLoginClass("观测");
            }
            else if(posX >(width() * 5 / 12) && posX < (width() * 7 / 12))
            {
                _v_flag = true;
                _m_machine = true;
                _m_release = true;
                setLoginClass("机务");
            }
            else if(posX >(width() * 11 / 18) && posX < (width() * 7 / 9))
            {
                _v_flag = true;
                _m_tower = true;
                _m_release = true;
                setLoginClass("塔台");
            }
            else if(posX >(width() * 29 / 36) && posX < (width() * 35 / 36))
            {
                _v_flag = true;
                _m_manager = true;
                _m_release = true;
                setLoginClass("管理");
            }
            logining();
            event->accept();
            return ;
        }
        else if(posY > 9 && posY < 21
                && posX > (width() -24)
                && posX <(width() -12))
        {
            _v_flag = true;
            _m_closed = true;
            _m_release = true;
        }
        else{
            moveWidget = true;
            StartPoint = event->globalPos() - this->pos();
        }
        event->accept();
    }
    if(_v_flag){
        update();
    }
}

void AwosAdmin::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    bool close = false;
    if(moveWidget){
        moveWidget = false;
    }
    if(_m_obsever){
        _m_obsever = false;
    }
    if(_m_forcaster){
        _m_forcaster = false;
    }
    if(_m_machine){
        _m_machine = false;
    }
    if(_m_tower){
        _m_tower = false;
    }
    if(_m_manager){
        _m_manager = false;
    }
    if(_m_closed){
        _m_closed = false;
        close = true;
    }
    if( _m_release){
        _m_release = false;
        update();
        if(close)
        {
            this->close();
        }
    }
}

void AwosAdmin::mouseMoveEvent(QMouseEvent *event)
{
    if(moveWidget){
        move(event->globalPos() - StartPoint);
    }
}



