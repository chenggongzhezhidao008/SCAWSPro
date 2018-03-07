#include "affix9addoutsensor.h"

Affix9AddOutSensor::Affix9AddOutSensor(QWidget *parent) :
    QWidget(parent)
{
    open_kind = false;
    _init_Size_Sub_UI();
    _init_label_name();
    _init_Input_name();
    _init_button_Value();
    _init_move_bool_Value();
    _init_kind_value();
}

void Affix9AddOutSensor::_set_out_sensor_title(QString title)
{
    _m_title_.clear();
    _m_title_ = title;
    update();
}

void Affix9AddOutSensor::_set_out_sensor_kind(QString kind)
{
    _m_kind.clear();
    _m_kind = kind;
    if(_m_kind != ""){
        _leabel_kin_ctx = new QLabel(this);
        _leabel_kin_ctx->setText(kind);
    }
    else{
        _combox_Kind = new QComboBox(this);
        QStringList list;
        list<<"CLOUD"<<"PRESS"<<"RAIN"
           <<"PW"<<"PV"<<"ROSE"
          <<"RWYLIGHTS";
        _combox_Kind->addItems(list);
    }
    open_kind = true;
}

void Affix9AddOutSensor::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    if(width() != _width_s || height() != _height_s){
        _width_s = width();
        _height_s = height();
        _set_lable_geometry();
        _set_input_geometry();
    }

    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2,height() / 2);
    int xleft = - width() / 2;
    int xright = width() / 2;
    int ytop = -height() / 2;
    int ybuttom = height() /2;

    painter.save();
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::NoPen);
    painter.drawRect(xleft,ytop,width(),height()/6);

    QFont font = painter.font();
    font.setBold(true);
    font.setPixelSize(13);
    painter.setFont(font);
    painter.setPen(QPen(Qt::white,3));
    QRectF tRect(xleft,ytop,width(),height()/6);
    painter.drawText(tRect,Qt::AlignCenter
                     ,QString("添加外部%1传感器").arg(_m_title_));
    painter.restore();

    painter.save();
    font.setBold(false);
    font.setPixelSize(13);
    painter.setFont(font);
    painter.setPen(Qt::NoPen);
    if(_cancle_b){
        painter.setBrush(Qt::green);
    }
    else{
        painter.setBrush(Qt::gray);
    }

    painter.drawRoundedRect(xright-width() *3/6
                            ,ybuttom - height()*2/6
                            ,width()/6,height()/6,6,6);
    if(_confirm_b){
        painter.setBrush(Qt::green);
    }
    else{
        painter.setBrush(Qt::gray);
    }
    painter.drawRoundedRect(xright-width() *2/6 + 10
                            ,ybuttom - height()*2/6
                            ,width()/6,height()/6,6,6);

    painter.setPen(QPen(Qt::white,1));
    font.setPixelSize(13);
    painter.setFont(font);
    painter.drawText(xright-width() *3/6,ybuttom - height()*2/6
                     ,width()/6,height()/6,Qt::AlignCenter,"返回");

    painter.drawText(xright-width() *2/6 + 10,ybuttom - height()*2/6
                     ,width()/6,height()/6,Qt::AlignCenter,"确定");

    painter.restore();
}

void Affix9AddOutSensor::mousePressEvent(QMouseEvent *e)
{
    bool _t_press;
    _t_press = false;
    if(e->button() == Qt::LeftButton){
        int _pos_x;
        int _pos_y;
        _t_press = true;
        _pos_x = e->pos().x();
        _pos_y = e->pos().y();
        if(_pos_y > 0 && _pos_y < height()/6)
        {
            m_left_b = true;
            m_pos = e->globalPos() - this->pos();
        }
        else if(_pos_x > (width()/2)
                && _pos_x <(width()*2/3)
                && _pos_y > (height()*2/3)
                && _pos_y <(height()*5/6))
        {
            _release_b = true;
            _cancle_b = true;
        }
        else if(_pos_x > (width()*2/3)
                && _pos_x <(width()*5/6)
                && _pos_y > (height()*2/3)
                && _pos_y <(height()*5/6))
        {
            _release_b = true;
            _confirm_b = true;
            // add virtual sensor
        }
    }
    if(_t_press){
        update();
    }
}

void Affix9AddOutSensor::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    if(_cancle_b){
        _cancle_b = false;
        this->close();
    }
    if(_confirm_b){
        _out_sensor_data_deal();
        _confirm_b = false;
    }
    if(_release_b){
        _release_b = false;
        update();
    }
}

void Affix9AddOutSensor::mouseMoveEvent(QMouseEvent */*e*/)
{
    //  if(m_left_b){
    //      move(this->pos());
    //  }
}

void Affix9AddOutSensor::_out_sensor_data_deal()
{
    QString _sensor_data;
    _sensor_data = _sensor_data + tr("name|%1").arg(_edit_name->text());
    _sensor_data = _sensor_data + tr("/id|%1").arg(_edit_Id->text());
    _sensor_data = _sensor_data + tr("/loca|%1").arg(_edit_loca->text());
    _sensor_data = _sensor_data + tr("/source|%1").arg(_edit_source->text());
    if(_m_kind == ""){
        _sensor_data = _sensor_data + tr("/kind|%1").arg(_combox_Kind->currentText());
    }
    else {
       _sensor_data = _sensor_data + tr("/kind|%1").arg(_leabel_kin_ctx->text());
    }
    emit store_sensor_data(_sensor_data);
}

void Affix9AddOutSensor::_init_Size_Sub_UI()
{
    _width_s = 0;
    _height_s = 0;
}

void Affix9AddOutSensor::_init_label_name()
{
    _leabel_name = new QLabel(this);
    _leabel_ID = new QLabel(this);
    _leabel_Loca = new QLabel(this);
    _leabel_Kind = new QLabel(this);
    _leabel_source = new QLabel(this);
    _leabel_name->setText("名称");
    _leabel_ID->setText("Id编号");
    _leabel_Loca->setText("位置");
    _leabel_Kind->setText("类型");
    _leabel_source->setText("数据源");
}

void Affix9AddOutSensor::_init_Input_name()
{
    _edit_name = new QLineEdit(this);
    _edit_Id = new QLineEdit(this);
    _edit_loca = new QLineEdit(this);
    _edit_source = new QLineEdit(this);
}

void Affix9AddOutSensor::_set_input_geometry()
{
    _edit_name->setGeometry(40,height()/3+5,80,20);
    _edit_Id->setGeometry(170,height()/3+5,40,20);
    _edit_loca->setGeometry(250,height()/3+5,40,20);
    _edit_source->setGeometry(340,height()/3+5,80,20);
    if(open_kind){
        if(_m_kind == ""){
            _combox_Kind->setGeometry(470,height()/3+5,100,20);
        }
        else{
            _leabel_kin_ctx->setGeometry(470,height()/3+5,100,20);
        }
    }
}

void Affix9AddOutSensor::_set_lable_geometry()
{
    _leabel_name->setGeometry(5,height()/3,30,30); // 5,30
    _leabel_ID->setGeometry(125,height()/3,40,30); //
    _leabel_Loca->setGeometry(215,height()/3,30,30);
    _leabel_source->setGeometry(295,height()/3,40,30);
    _leabel_Kind->setGeometry(435,height()/3,30,30);
}

void Affix9AddOutSensor::_init_button_Value()
{
    _cancle_b = false;
    _confirm_b = false;
    _release_b = false;
}

void Affix9AddOutSensor::_init_move_bool_Value()
{
    m_left_b = false;
}

void Affix9AddOutSensor::_init_out_Sensor_title()
{
    _m_title_ = "外部传感器";
}

void Affix9AddOutSensor::_init_kind_value()
{
    _m_kind = "";
}
