#include "waringshow.h"

WarShow::WarShow(QWidget *parent) :
    QWidget(parent)
{
    _init_infor_show();
    _init_size();
    _init_war_number();
    _init_war_confirm();
    _init_show_kind();
    _m_init_Custom_Menus();
    _init_warIndex();
}

void WarShow::paintEvent(QPaintEvent *e)
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
                     ,Qt::AlignBottom | Qt::AlignLeft,"内容");
    painter.drawText(m_x + m_width * 9 / 10,m_y,m_width * 2 / 20,m_height
                     ,Qt::AlignBottom | Qt::AlignHCenter,"状态");
    painter.restore();
}

void WarShow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton){
        _m_menu->exec(QCursor::pos());
    }
}

/*  ----------------------------
 *  function description
 *  告警数据确认处理
 *  将已确认的数据取出放到已确认的map中
 *  或放到数据库中，待后期查询或检查
 * -----------------------------
 */
void WarShow::_m_warinfor_confirm(int index)
{
    if(_m_showConfirm){
        return;
    }
    QString confirmStr;
    confirmStr = _m_warData[index] + tr("true");
    if(index == _m_war_number || _m_warData.count() == 1){
    }
    else{
        for(int i = index;i < _m_war_number;i++){
            _m_warData[i] =  _m_warData[i + 1];
        }
    }
    _m_warData.remove(_m_war_number);
    _m_war_number--;
    qDebug()<<"war number:"<<_m_war_number
           <<"map length:"<<_m_warData.count();
    if(_m_war_number * 18 == 0){
        infor->setSubHeight(1);
    }
    else{
        infor->setSubHeight(_m_war_number * 18);
    }
    infor->setDataMap(_m_warData);

    // 保存到告警确认map
    _add_confirm_waring(confirmStr);

    // 保存到数据库
    emit store_waring_to_database(confirmStr);
}

void WarShow::menuOptionSlot()
{
    QAction *act=qobject_cast<QAction*>(sender());
    QString DataStr = act->objectName();
    _m_menu_option_Slot(DataStr);
}

void WarShow::_m_menu_option_Slot(QString option)
{
    qDebug()<<"======"<<option;
    if(option == "已确认"){
        _m_select_waring(true);
        _m_showConfirm = true;
    }
    if(option == "未确认"){
        _m_select_waring(false);
        _m_showConfirm = false;
    }
}

void WarShow::_m_add_waring_Slot(QString warCtx)
{
    QString war,time;
    war  = tr("sequence:%1|").arg(_m_war_index);
    _m_war_index ++;
    war  = war + tr("context:%1|").arg(warCtx);
    time = QDateTime::currentDateTime().toString("yyyy/MM/dd hh-mm-ss");
    war  = war + tr("time:%1|deal:").arg(time);
    _m_add_NoConfirm_waring(war);
    if(_m_war_index > 9999){
        _m_war_index = 1;
    }
}

void WarShow::_init_infor_show()
{
    infor = new  InforCtx();
    QStringList m_namelist;
    m_namelist<<"已确认"<<"未确认";
    infor->setActionName(m_namelist);
    connect(infor,SIGNAL(doubleClickSignal(int))
            ,SLOT(_m_warinfor_confirm(int)));
    connect(infor,SIGNAL(menuOption(QString))
            ,this,SLOT(_m_menu_option_Slot(QString)));
    // signal is sequence or breaklink
    areaBar = new QScrollArea(this);
    areaBar->setWidget(infor);
    areaBar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void WarShow::_m_setGeomerty()
{
    areaBar->setGeometry(0,17,width(),height()-18);
    infor->setSubWidth(width()-4);
    _m_war_number = _m_warData.count();     // test
    infor->setSubHeight(_m_war_number * 18); // test
    infor->setDataMap(_m_warData);           // test
}

void WarShow::_m_add_NoConfirm_waring(QString data)
{
    if(!data.isEmpty()){
        if(_m_war_number != 0){
            for(int n = _m_war_number; n >=1;n--){
                _m_warData[n + 1] = _m_warData[n];
            }
        }
        _m_warData[1] = data;
        _m_war_number = _m_warData.count();
    }
    if(_m_war_number > 30){
        _m_warData.remove(31);
        _m_war_number = 30;
    }
    if(!_m_showConfirm){
        // show confirm wars
        infor->setSubHeight(_m_war_number * 18);
        infor->setDataMap(_m_warData);
    }
}
/*  -------------------------
 *  function description
 *  comfirm = false : not confirm data message
 *  confirm = true : confirmed data message
 *  -------------------------
 */
void WarShow::_m_select_waring(bool comfirm)
{
    if(!comfirm){
        infor->setSubHeight(_m_war_number * 18);
        infor->setDataMap(_m_warData);
    }
    else{
        // show confirm wars
        infor->setSubHeight(_m_war_confirm_number * 18);
        infor->setDataMap(_m_war_confirmData);
    }
}

void WarShow::_init_size()
{
    _m_width = 0;
    _m_height = 0;
}

void WarShow::_init_war_number()
{
    _m_war_number = 0;
}

void WarShow::_init_war_confirm()
{
    _m_war_confirm_number = 0;
}

void WarShow::_add_confirm_waring(QString war)
{
    if(_m_war_confirm_number > 30){     //max confirm warings len = 300.over 300
        _m_war_confirmData.remove(31);  //will delete key gt 300 part waring message
        _m_war_confirm_number = 30;
    }
    if(_m_war_confirm_number != 0){
        for(int n = _m_war_confirm_number; n >=1;n--){
            _m_war_confirmData[n + 1] = _m_war_confirmData[n];
        }
    }
    _m_war_confirmData[1] = war;
    _m_war_confirm_number = _m_war_confirmData.count();

    // show confirm wars
    if(_m_showConfirm){
        infor->setSubHeight(_m_war_confirm_number * 18);
        infor->setDataMap(_m_war_confirmData);
    }
}

void WarShow::_init_show_kind()
{
    _m_showConfirm = false;
}

void WarShow::_m_init_Custom_Menus()
{
    _m_menu = new QMenu(this);
    _m_namelist<<"已确认"<<"未确认";
    _m_create_Action_Contrls();
}

void WarShow::_m_create_Action_Contrls()
{
    QString nameStr;
    for(int i = 0;i < _m_namelist.length();i++){
        nameStr = _m_namelist.value(i).trimmed();
        QAction *action = _m_menu->addAction(nameStr);
        connect(action,SIGNAL(triggered()),this,SLOT(menuOptionSlot()));
        action->setObjectName(nameStr);
        _m_action_List.push_back(action);
    }
}

void WarShow::_init_warIndex()
{
    _m_war_index = 0;
}

