#include "runwaycfg.h"

RunWayCFg::RunWayCFg(QWidget *parent) :
    QWidget(parent)
{
    m_init_size();
    m_init_contrls();
    m_init_runway();
    m_init_connections();
}

void RunWayCFg::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    int _with = width();
    int _heigh = height();
    if(m_with != _with || m_heigh != _heigh){
        m_with = _with;
        m_heigh = _heigh;
        m_set_runway_Geometry();
        m_set_contrls_geometry();
    }
    painter.translate(_with / 2,_heigh / 2);
    painter.setPen(Qt::NoPen);

    //画区域背景
    painter.save();
    painter.setBrush(Qt::gray);
    painter.drawRoundedRect(-_with / 2,-_heigh / 2,_with,_heigh ,3,3);
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRoundedRect(-_with / 2 + 2,-_heigh / 2 + 2,_with - 4,_heigh - 4,3,3);
    painter.restore();

    int v_left = -_with / 2 + 2;
    int v_top = -_heigh / 2 + 2;
    int v_width = _with - 4;
    int v_heigh = _heigh - 4;

    // 画三条竖线，区分左、中、右三个区域
    painter.save();
    painter.setPen(QPen(QColor("#ffffff"),0.5));
    painter.drawLine(v_left + (v_width - 210) / 3,v_top,v_left + (v_width - 210) / 3,v_top + v_heigh);
    painter.drawLine(v_left + (v_width - 210) * 2 / 3,v_top,v_left + (v_width - 210)  * 2 / 3,v_top + v_heigh);
    painter.drawLine(v_left + (v_width - 210),v_top,v_left + (v_width - 210),v_top + v_heigh);
    painter.restore();
}

bool RunWayCFg::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove
            || event->type() == QEvent::HoverMove )
    {
        event->accept();
        return true;
    }
    else{
        return QWidget::eventFilter(obj, event);
    }
}

/*  ============== 界面跑道ui参数设置==============
 *  _set_way_number(QString , QString )
 *  headStr  跑道左端号参数
 *  rearStr  跑道右端号参数
 *  跑道中间的号由左右两端合成
 *  ===============================================
 */
void RunWayCFg::_set_way_number(QString headStr, QString rearStr)
{
    // 界面跑道左端部分
    LwindBox->setObjectName(QString("%1:wind").arg(headStr));
    LcloudBox->setObjectName(QString("%1:cloud").arg(headStr));
    LhumtempBox->setObjectName(QString("%1:humitemp").arg(headStr));
    LvisBox->setObjectName(QString("%1:vis").arg(headStr));
    LrainBox->setObjectName(QString("%1:rain").arg(headStr));

    // 界面跑道中间部分
    MwindBox->setObjectName(QString("%1-%2:wind").arg(headStr).arg(rearStr));
    MhumtempBox->setObjectName(QString("%1-%2:humitemp").arg(headStr).arg(rearStr));
    MvisBox->setObjectName(QString("%1-%2:vis").arg(headStr).arg(rearStr));
    MrainBox->setObjectName(QString("%1-%2:rain").arg(headStr).arg(rearStr));
    MpressBox->setObjectName(QString("%1-%2:press").arg(headStr).arg(rearStr));

    // 界面跑道右端部分
    RwindBox->setObjectName(QString("%1:wind").arg(rearStr));
    RcloudBox->setObjectName(QString("%1:cloud").arg(rearStr));
    RhumtempBox->setObjectName(QString("%1:humitemp").arg(rearStr));
    RvisBox->setObjectName(QString("%1:vis").arg(rearStr));
    RrainBox->setObjectName(QString("%1:rain").arg(rearStr));

    // 设置跑道号字符串
    runwayStr = QString("%1-%2").arg(headStr).arg(rearStr);

    // 设置跑道控件的跑道号
    m_runway->setHeadName(headStr);
    m_runway->setRearName(rearStr);
}

void RunWayCFg::_select_way_slot(bool select)
{
    if(select && !runwayStr.isEmpty()){
        emit _select_runway_signal(runwayStr);
    }
}

void RunWayCFg::_select_sensor_slot(QString str)
{
    QString sensorInfor,loca;
    loca = qobject_cast<QComboBox *>(sender())->objectName();
    sensorInfor = QString("%1>%2").arg(loca).arg(str);
    if(!loca.isEmpty() && !str.isEmpty())
    {
        emit _select_sensor_signal(sensorInfor);
    }
}

void RunWayCFg::m_init_size()
{
    m_with = 0;
    m_heigh = 0;
}

void RunWayCFg::m_init_runway()
{
    m_runway = new RunWay(this);
    m_runway->installEventFilter(this);
}

void RunWayCFg::m_set_runway_Geometry()
{
    m_runway->setGeometry(width()- 200,height()/2 - 25,170,50);
}

void RunWayCFg::m_init_contrls()
{
    m_check = new QCheckBox(this);

    // 气压组
    Mpresslab = new QLabel(this);
    Mpresslab->setText("气压");
    MpressBox = new QComboBox(this);

    // 风组
    Lwindlab = new QLabel(this);
    Lwindlab->setText("风");
    Mwindlab = new QLabel(this);
    Mwindlab->setText("风");
    Rwindlab = new QLabel(this);
    Rwindlab->setText("风");
    LwindBox = new QComboBox(this);
    MwindBox = new QComboBox(this);
    RwindBox = new QComboBox(this);

    // 云组
    Lcloudlab = new QLabel(this);
    Lcloudlab->setText("云");
    //    Mcloudlab = new QLabel(this);
    //    Mcloudlab->setText("云");
    Rcloudlab = new QLabel(this);
    Rcloudlab->setText("云");
    LcloudBox = new QComboBox(this);

    //    McloudBox = new QComboBox(this);
    RcloudBox = new QComboBox(this);

    // 温湿度组
    Lhumtemplab = new QLabel(this);
    Lhumtemplab->setText("温湿度");
    Mhumtemplab = new QLabel(this);
    Mhumtemplab->setText("温湿度");
    Rhumtemplab = new QLabel(this);
    Rhumtemplab->setText("温湿度");
    LhumtempBox = new QComboBox(this);
    MhumtempBox = new QComboBox(this);
    RhumtempBox = new QComboBox(this);

    // 能见度组
    Lvislab = new QLabel(this);
    Lvislab->setText("能见度");
    Mvislab = new QLabel(this);
    Mvislab->setText("能见度");
    Rvislab = new QLabel(this);
    Rvislab->setText("能见度");
    LvisBox = new QComboBox(this);
    MvisBox = new QComboBox(this);
    RvisBox = new QComboBox(this);

    // 雨组
    Lrainlab = new QLabel(this);
    Lrainlab->setText("雨");
    Mrainlab = new QLabel(this);
    Mrainlab->setText("雨");
    Rrainlab = new QLabel(this);
    Rrainlab->setText("雨");
    LrainBox = new QComboBox(this);
    MrainBox = new QComboBox(this);
    RrainBox = new QComboBox(this);
}

void RunWayCFg::m_set_contrls_geometry()
{
    if(m_check){
        m_check->setGeometry(width()- 20 - 3,height()/2 - 7,14,14);
    }
    int left = 2;
    int top = 2;
    int g_width = width() - 4 - 210;

    // 气压组
    Mpresslab->setGeometry(left + g_width / 3 + 5,top + 55,50,20);
    MpressBox->setGeometry(left + g_width / 3 + 60,top + 55,100,20);

    // 风组
    Lwindlab->setGeometry(left + 5,top + 5,50,20);
    Mwindlab->setGeometry(left + g_width / 3 + 5,top + 5,50,20);
    Rwindlab->setGeometry(left + g_width * 2 / 3 + 5,top + 5,50,20);
    LwindBox->setGeometry(left + 60,top + 5,100,20);
    MwindBox->setGeometry(left + g_width / 3 + 60,top + 5,100,20);
    RwindBox->setGeometry(left + g_width * 2 / 3  + 60,top + 5,100,20);

    // 云组
    Lcloudlab->setGeometry(left + 5,top + 55,50,20);
    //    Mcloudlab->setGeometry(left + g_width / 3 + 5,top + 55,50,20);
    Rcloudlab->setGeometry(left + g_width * 2 / 3 + 5,top + 55,50,20);
    LcloudBox->setGeometry(left + 60,top + 55,100,20);
    //    McloudBox->setGeometry(left + g_width / 3 + 60,top + 55,100,20);
    RcloudBox->setGeometry(left + g_width * 2 / 3  + 60,top + 55,100,20);

    // 温湿度组
    Lhumtemplab->setGeometry(left + 165,top + 5,50,20);
    Mhumtemplab->setGeometry(left + g_width / 3 + 165,top + 5,50,20);
    Rhumtemplab->setGeometry(left + g_width * 2 / 3 + 165,top + 5,50,20);
    LhumtempBox->setGeometry(left + 220,top + 5,100,20);
    MhumtempBox->setGeometry(left + g_width / 3 + 220,top + 5,100,20);
    RhumtempBox->setGeometry(left + g_width * 2 / 3  + 220,top + 5,100,20);

    // 能见度组
    Lvislab->setGeometry(left + 5,top + 30,50,20);
    Mvislab->setGeometry(left + g_width / 3 + 5,top + 30,50,20);
    Rvislab->setGeometry(left + g_width * 2 / 3 + 5,top + 30,50,20);
    LvisBox->setGeometry(left + 60,top + 30,100,20);
    MvisBox->setGeometry(left + g_width / 3 + 60,top + 30,100,20);
    RvisBox->setGeometry(left + g_width * 2 / 3  + 60,top + 30,100,20);

    // 雨组
    Lrainlab->setGeometry(left + 165,top + 55,50,20);
    Mrainlab->setGeometry(left + g_width / 3 + 165,top + 55,50,20);
    Rrainlab->setGeometry(left + g_width * 2 / 3 + 165,top + 55,50,20);
    LrainBox->setGeometry(left + 220,top + 55,100,20);
    MrainBox->setGeometry(left + g_width / 3 + 220,top + 55,100,20);
    RrainBox->setGeometry(left + g_width * 2 / 3  + 220,top + 55,100,20);
}

void RunWayCFg::m_init_connections()
{
    connect(m_check,SIGNAL(clicked(bool)),SLOT(_select_way_slot(bool)));
    connect(MpressBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(LwindBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(MwindBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(RwindBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(LcloudBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(RcloudBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(LhumtempBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(MhumtempBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(RhumtempBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(LvisBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(MvisBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(RvisBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(LrainBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(MrainBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
    connect(RrainBox,SIGNAL(currentIndexChanged(QString))
            ,SLOT(_select_sensor_slot(QString)));
}
