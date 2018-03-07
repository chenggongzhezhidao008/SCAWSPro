#include "rvrcfg.h"
#include <QDebug>

RVRCFG::RVRCFG(QWidget *parent) :
    QWidget(parent)
{
    m_initValue();
    m_init_Contrls();
    m_init_Connections();
    m_setGeometry();
}

void RVRCFG::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    if(width() != m_width || height() != m_height)
    {
        m_width = width();
        m_height = height();
        m_setGeometry();
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.save();
    painter.setPen(QPen(Qt::gray,4));
    painter.drawText(0,0,100,40,Qt::AlignCenter | Qt::AlignLeft,"大透仪调整");
    painter.setPen(QPen(Qt::white,1));
    painter.drawLine(0,30,100,30);
    painter.drawLine(0,130,360,130);
    painter.drawLine(0,210,360,210);
    painter.drawLine(0,290,360,290);
    painter.drawLine(0,390,360,390);
    painter.drawLine(380,30,380,height());
    painter.restore();
}

void RVRCFG::show_cfg()
{
    this->show();
}
// 所有对RVR配置的数据结果处理都在此处做处理。
void RVRCFG::m_config_message(QString info)
{
    if(!doAction) return;
    doAction = false;//清除操作标志
    // 传值格式 ">" 分隔命令与数据
    // "/" 分隔每个数据单元,"="分隔键与值
    // QString value;
    // value = "SC_RVR_MakeUpBack=" +dMap[SC_RVR_MakeUpBack]
    //        +"/TemMakeUpEn=" +dMap[TemMakeUpEn];
    // emit VR800CFGBack(QString("SC_RVR_MakeUpSet>").arg(value));
    QString headStr = info.split(">").value(0);
    if(headStr == "SC_RVR_MakeUpSet" && askall){
        QString v1,v2;
        v1 = info.split(">").value(1).split("/").value(0).split("=").value(1);
        v2 = info.split(">").value(1).split("/").value(1).split("=").value(1);
        V_morMakeUp_v->setText(v1);
        V_morMakeUp_enable->setText(v2);
        askall = false;
    }
    else{
        QMessageBox::warning(this,"提示！",QString("%1设置成功！").arg(headStr));
    }
}

void RVRCFG::m_set_all_values(DataMap data)
{
    V_PolluteAD_a->setText(data["VR800CorrectBack"]);
    V_PolluteAD_b->setText(data["PolluteAD_b"]);
    V_SpotADMax->setText(data["SpotADmax"]);
    V_StdADMax->setText(data["StandardADmax"]);
    V_morCaLc_a->setText(data["MorCalculate_a"]);
    V_morCaLc_b->setText(data["MorCalculate_b"]);
}

void RVRCFG::PolluteAD_set()
{
    doAction = true;
    QString commd;
    QString pollute_a,pollute_b;
    pollute_a = E_PolluteAD_a->text().trimmed();
    pollute_b = E_PolluteAD_b->text().trimmed();
    if(pollute_a.isEmpty() || pollute_b.isEmpty()) return;
    commd = QString("SC_RVR:MakeUpSetPollute>pollute_a|%1/pollute_b|%2").arg(pollute_a).arg(pollute_b);
    emit dataCommandOptions(commd);
}

void RVRCFG::SpotADMax_set()
{
    doAction = true;
    QString commd;
    QString spotMax;
    spotMax = E_SpotADMax->text().trimmed();
    if(spotMax.isEmpty()) return;
    commd = QString("SC_RVR:SpotADMax>spotMax|%1").arg(spotMax);
    emit dataCommandOptions(commd);
}

void RVRCFG::StandardADMax_set()
{
    doAction = true;
    QString commd;
    QString stdMax;
    stdMax = E_StdADMax->text().trimmed();
    if(stdMax.isEmpty()) return;
    commd = QString("SC_RVR:StandardADMax>stdMax|%1").arg(stdMax);
    emit dataCommandOptions(commd);
}

void RVRCFG::MorCalculate_set()
{
    doAction = true;
    QString commd;
    QString calc_a,calc_b;
    calc_a = E_morCaLc_a->text().trimmed();
    calc_b = E_morCaLc_b->text().trimmed();
    if(calc_a.isEmpty() || calc_b.isEmpty()) return;
    commd = QString("SC_RVR:MorCalculate>calc_a|%1/calc_b|%2").arg(calc_a).arg(calc_b);
    emit dataCommandOptions(commd);
}

void RVRCFG::VR800Correct_ask()
{
    doAction = true;
    emit dataCommandOptions("SC_RVR:VR800CorrectAsk");
    askall = true;
}

void RVRCFG::MakeUpMor_set()
{
    doAction = true;
    QString morV,enableV;
    morV = E_morMakeUp_v->text().trimmed();
    enableV = E_morMakeUp_enable->currentText().trimmed();
    emit dataCommandOptions(QString("SC_RVR:MakeUpSetPollute&Temp>vmor|%1/able|%2")
                            .arg(morV).arg(enableV));
}


void RVRCFG::m_init_Contrls()
{
    L_PolluteAD_a = new QLabel(this);
    L_PolluteAD_a->setText("污染补偿系数a");
    L_PolluteAD_a->show();
    E_PolluteAD_a = new QLineEdit(this);
    E_PolluteAD_a->show();
    V_PolluteAD_a = new QLineEdit(this);
    V_PolluteAD_a->show();
    V_PolluteAD_a->setText("///");
    V_PolluteAD_a->setAlignment(Qt::AlignCenter);
    V_PolluteAD_a->setReadOnly(true);
    L_PolluteAD_b = new QLabel(this);
    L_PolluteAD_b->setText("污染补偿系数b");
    L_PolluteAD_b->show();
    E_PolluteAD_b = new QLineEdit(this);
    E_PolluteAD_b->show();
    V_PolluteAD_b = new QLineEdit(this);
    V_PolluteAD_b->show();
    V_PolluteAD_b->setText("///");
    V_PolluteAD_b->setAlignment(Qt::AlignCenter);
    V_PolluteAD_b->setReadOnly(true);
    B_PolluteAD_b = new QPushButton(this);
    B_PolluteAD_b->setText("补偿");
    B_PolluteAD_b->show();
    update_AllData = new QPushButton(this);
    update_AllData->setText("刷新所有参数");
    update_AllData->show();

    L_SpotADMax = new QLabel(this);
    L_SpotADMax->setText("现场测试最大AD");
    L_SpotADMax->show();
    E_SpotADMax = new QLineEdit(this);
    E_SpotADMax->show();
    V_SpotADMax = new QLineEdit(this);
    V_SpotADMax->show();
    V_SpotADMax->setText("///");
    V_SpotADMax->setAlignment(Qt::AlignCenter);
    V_SpotADMax->setReadOnly(true);
    B_SpotADMax = new QPushButton(this);
    B_SpotADMax->setText("确认");
    B_SpotADMax->show();

    L_StdADMax = new QLabel(this);
    L_StdADMax->setText("昌平测试最大AD");
    L_StdADMax->show();
    E_StdADMax = new QLineEdit(this);
    E_StdADMax->show();
    V_StdADMax = new QLineEdit(this);
    V_StdADMax->show();
    V_StdADMax->setText("///");
    V_StdADMax->setAlignment(Qt::AlignCenter);
    V_StdADMax->setReadOnly(true);
    B_StdADMax = new QPushButton(this);
    B_StdADMax->setText("确认");
    B_StdADMax->show();

    L_morCaLc_a = new QLabel(this);
    L_morCaLc_a->setText("MOR计算参数a");
    L_morCaLc_a->show();
    E_morCaLc_a = new QLineEdit(this);
    E_morCaLc_a->show();
    V_morCaLc_a = new QLineEdit(this);
    V_morCaLc_a->show();
    V_morCaLc_a->setText("///");
    V_morCaLc_a->setAlignment(Qt::AlignCenter);
    V_morCaLc_a->setReadOnly(true);
    L_morCaLc_b = new QLabel(this);
    L_morCaLc_b->setText("MOR计算参数b");
    L_morCaLc_b->show();
    E_morCaLc_b = new QLineEdit(this);
    E_morCaLc_b->show();
    V_morCaLc_b = new QLineEdit(this);
    V_morCaLc_b->show();
    V_morCaLc_b->setText("///");
    V_morCaLc_b->setAlignment(Qt::AlignCenter);
    V_morCaLc_b->setReadOnly(true);
    B_morCaLc_b = new QPushButton(this);
    B_morCaLc_b->setText("设定");
    B_morCaLc_b->show();

    L_morMakeUp_v = new QLabel(this);
    L_morMakeUp_v->setText("MOR输入参数");
    L_morMakeUp_v->show();
    E_morMakeUp_v = new QLineEdit(this);
    E_morMakeUp_v->show();
    V_morMakeUp_v = new QLineEdit(this);
    V_morMakeUp_v->setText("///");
    V_morMakeUp_v->setAlignment(Qt::AlignCenter);
    V_morMakeUp_v->setReadOnly(true);
    V_morMakeUp_v->show();
    L_morMakeUp_enable = new QLabel(this);
    L_morMakeUp_enable->setText("补偿使能");
    L_morMakeUp_enable->show();
    E_morMakeUp_enable = new QComboBox(this);
    QStringList list;
    list<<"1"<<"0";
    E_morMakeUp_enable->addItems(list);
    E_morMakeUp_enable->show();
    V_morMakeUp_enable = new QLineEdit(this);
    V_morMakeUp_enable->setText("///");
    V_morMakeUp_enable->setAlignment(Qt::AlignCenter);
    V_morMakeUp_enable->setReadOnly(true);
    V_morMakeUp_enable->show();
    B_morMakeUp = new QPushButton(this);
    B_morMakeUp->setText("修改Mor");
    B_morMakeUp->show();
}

void RVRCFG::m_setGeometry()
{
    int t_width = 0;
    int t_height = 0;

    update_AllData->setGeometry(t_width + 400,20,140,25);

    L_PolluteAD_a->setGeometry(t_width + 20,t_height + 50,100,20);
    E_PolluteAD_a->setGeometry(t_width + 120,t_height + 50,140,20);
    V_PolluteAD_a->setGeometry(t_width + 400,t_height + 50,140,20);

    L_PolluteAD_b->setGeometry(t_width + 20,t_height + 80,100,20);
    E_PolluteAD_b->setGeometry(t_width + 120,t_height + 80,140,20);
    B_PolluteAD_b->setGeometry(t_width + 280,t_height + 80,80,25);
    V_PolluteAD_b->setGeometry(t_width + 400,t_height + 80,140,20);

    // 150 画线
    L_SpotADMax->setGeometry(t_width + 20,t_height + 160,100,20);
    E_SpotADMax->setGeometry(t_width + 120,t_height + 160,140,20);
    B_SpotADMax->setGeometry(t_width + 280,t_height + 160,80,25);
    V_SpotADMax->setGeometry(t_width + 400,t_height + 160,140,20);

    // 230 画线
    L_StdADMax->setGeometry(t_width + 20,t_height + 240,100,20);
    E_StdADMax->setGeometry(t_width + 120,t_height + 240,140,20);
    B_StdADMax->setGeometry(t_width + 280,t_height + 240,80,25);
    V_StdADMax->setGeometry(t_width + 400,t_height + 240,140,20);

    // 310 画线
    L_morCaLc_a->setGeometry(t_width + 20,t_height + 320,100,20);
    E_morCaLc_a->setGeometry(t_width + 120,t_height + 320,140,20);
    V_morCaLc_a->setGeometry(t_width + 400,t_height + 320,140,20);
    L_morCaLc_b->setGeometry(t_width + 20,t_height + 350,100,20);
    E_morCaLc_b->setGeometry(t_width + 120,t_height + 350,140,20);
    B_morCaLc_b->setGeometry(t_width + 280,t_height + 350,80,25);
    V_morCaLc_b->setGeometry(t_width + 400,t_height + 350,140,20);

    // 410
    L_morMakeUp_v->setGeometry(t_width + 20,t_height + 420,100,20);
    E_morMakeUp_v->setGeometry(t_width + 120,t_height + 420,140,20);
    V_morMakeUp_v->setGeometry(t_width + 400,t_height + 420,140,20);
    L_morMakeUp_enable->setGeometry(t_width + 20,t_height + 450,100,20);
    E_morMakeUp_enable->setGeometry(t_width + 120,t_height + 450,140,20);
    V_morMakeUp_enable->setGeometry(t_width + 400,t_height + 450,140,20);
    B_morMakeUp->setGeometry(t_width + 280,t_height + 450,80,25);
}

void RVRCFG::m_init_Connections()
{
    connect(B_PolluteAD_b,SIGNAL(clicked()),this,SLOT(PolluteAD_set()));
    connect(B_SpotADMax,SIGNAL(clicked()),this,SLOT(SpotADMax_set()));
    connect(B_StdADMax,SIGNAL(clicked()),this,SLOT(StandardADMax_set()));
    connect(B_morCaLc_b,SIGNAL(clicked()),this,SLOT(MorCalculate_set()));
    connect(B_morMakeUp,SIGNAL(clicked()),this,SLOT(MakeUpMor_set()));
    connect(update_AllData,SIGNAL(clicked()),this,SLOT(VR800Correct_ask()));
}

void RVRCFG::m_initValue()
{
    m_width = 0;
    m_height = 0;
    askall = false;
    doAction = false;
}



