#include "awosmainfram.h"
#include "ui_awosmainfram.h"

AwosMainFram::AwosMainFram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AwosMainFram)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background:#4F4F4F");/*#FFFFFF*//*#404040*/ /*#68838B*/ /*#8B795E*/ /*#BDB76B*/ /*#C5C1AA*/

    //初始化界面配置隐藏按钮
    initUpdateUIButton();

    //测试空间
    {
        ui->widget_updateConfig->installEventFilter(this);
        ui->widget_updateSub->installEventFilter(this);
    }
    //状态控件
    {
        ui->widget_Hum_state->setComName("Hum");
        ui->widget_temp_state->setComName("Temp");
        ui->widget_wind_state->setComName("Wind");
        ui->widget_RVR_state->setComName("RVR");
    }
    //标签
    {
        ui->widget_State->setText("State");
        ui->widget_State->setFontSize(16);
        ui->widget_State->setBorder(true);

        ui->widget_Humidity->setText("Humidity");
        ui->widget_Humidity->setFontSize(16);

        ui->widget_temperature->setText("Temperature");
        ui->widget_temperature->setFontSize(16);
        ui->widget_dewPoint->setText("DewPonit");
        ui->widget_dewPoint->setFontSize(16);
    }
    //Value Widget
    {
        ui->widget_TempValue->setText("///");
        ui->widget_TempValue->setUnitStr("oc");
        ui->widget_TempValue->setFontSize(23);
        ui->widget_dewPointValue->setText("///");
        ui->widget_dewPointValue->setUnitStr("oc");
        ui->widget_dewPointValue->setFontSize(23);
        ui->widget_HumValue->setUnitStr("%");
        ui->widget_HumValue->setText("///");
        ui->widget_HumValue->setFontSize(23);
    }
    setAwosSize(1024,716);
}

AwosMainFram::~AwosMainFram()
{
    delete ui;
}

void AwosMainFram::setAwosSize(int width, int height)
{
    this->setGeometry(160,6,width,height);
}

void AwosMainFram::initUpdateUIButton()
{
    // test used.
    ui->widget_updateSub->setSignalFlag(true);
    ui->widget_updateConfig->setSignalFlag(false);
    // codec
    connect(ui->widget_updateSub,SIGNAL(removeFilter(bool)),this,SIGNAL(editSubUi(bool)));
    connect(ui->widget_updateConfig,SIGNAL(removeFilter(bool)),this,SIGNAL(editSubUi(bool)));
}

void AwosMainFram::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){//判断鼠标事件的按钮名称
        point = e->globalPos() - this->pos();//计算全局做表与局部坐标差向量
        mousePressed = true;
    }
    e->accept();//接收事件
}

void AwosMainFram::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton && this->mousePressed){//判断鼠标事件的所有按钮被按下状态的按钮
        this->move(e->globalPos() - this->point);//以界面左上角坐标为基点移动Awos界面
    }
    e->accept();
}

void AwosMainFram::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){//判断鼠标事件的按钮名称
        this->mousePressed = false;
    }
    e->accept();
}

bool AwosMainFram::eventFilter(QObject *obj, QEvent *event)
{
    //    qDebug()<<"SC sub object:"<<obj->objectName();
    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove) {
        event->accept();
        return true;
    }
    else{
        return QWidget::eventFilter(obj, event);
    }
}

void AwosMainFram::on_pushButton_clicked()
{
    emit yes(true);
}
