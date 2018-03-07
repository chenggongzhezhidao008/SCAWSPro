#include "affix9addsensor.h"

AFFIX9AddSensor::AFFIX9AddSensor(QWidget *parent) :
    QWidget(parent)
{
    initComboxcontrl();
    setComboxItems();
    setComboxStyleSheet();
    initUIsize();
    this->setWindowFlags(Qt::FramelessWindowHint);
    initleftClickValue();
    initClickBoolValue();
    initTitleStr();
    initCommunicateValue();
    init36Id();
    qDebug()<<"object name:"<<objectName();
}

QStringList AFFIX9AddSensor::getU36Id() const{
    return this->m_36ID;
}

void AFFIX9AddSensor::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2,height() / 2);
    int xleft = - width() / 2;
    int xright = width() / 2;
    int ytop = -height() / 2;
    int yuttom = height() /2;

    if(s_width != width() ||s_height != height()){
        setComboxGeometry();
        s_width = width();
        s_height = height();
    }

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
    painter.drawText(tRect,Qt::AlignCenter,"添加传感器所需参数设置");
    painter.restore();

    painter.save();
    font.setBold(false);
    font.setPixelSize(13);
    painter.setFont(font);
    painter.setPen(QPen(Qt::black,3));
    for(int j = 1;j <= 6;j++ ){
        QRectF tRectip(xleft + width() * (j - 1)/6,ytop + height()* 2 /6
                       ,width()/6,height()/6);
        painter.drawText(tRectip,Qt::AlignHCenter,title[j]);
    }
    for(int n = 1;n <= 2;n++ ){
        QRectF tRectip(xleft + width() * (n - 1)/6,ytop + height()* 7 /12
                       ,width()/6,height()/6);
        painter.drawText(tRectip,Qt::AlignHCenter,title2[n]);
    }
    painter.setPen(Qt::NoPen);
    if(cancle){
        painter.setBrush(Qt::green);
    }
    else{
        painter.setBrush(Qt::gray);
    }

    painter.drawRoundedRect(xright-width() *3/6
                            ,yuttom - height()*2/6
                            ,width()/6,height()/6,6,6);
    if(confirm){
        painter.setBrush(Qt::green);
    }
    else{
        painter.setBrush(Qt::gray);
    }
    painter.drawRoundedRect(xright-width() *2/6 + 10
                            ,yuttom - height()*2/6
                            ,width()/6,height()/6,6,6);
    painter.setPen(QPen(Qt::white,1));
    font.setPixelSize(13);
    painter.setFont(font);
    painter.drawText(xright-width() *3/6,yuttom - height()*2/6
                     ,width()/6,height()/6,Qt::AlignCenter,"返回");

    painter.drawText(xright-width() *2/6 + 10,yuttom - height()*2/6
                     ,width()/6,height()/6,Qt::AlignCenter,"确定");

    painter.restore();
}

void AFFIX9AddSensor::mousePressEvent(QMouseEvent *e)
{
    bool updateFlag = false;
    if(e->button() == Qt::LeftButton){
        int posX = e->pos().x();
        int posY = e->pos().y();
        // 原点在中间 ：xleft,ytop/* 0 - height()/ 4 / 2*/,width(),height()/6
        // 原点在左上角 ：0,0,width(),height()/6
        if(posX > 0 && posX < width() &&
                posY > 0 && posY <(height()/6)){
            leftClick = true;
            leftPos = e->globalPos() - this->pos();
        }
        // xright-width() *3/6,yuttom - height()*2/6,width()/6,height()/6,
        // 转化换坐标：width() -width() *3/6， height() - height()*2/6 ，width()/6,height()/6
        else if(posX > (width()/2) && posX < (width() *4/6) &&
                posY > (height()*4/6) && posY <(height()*5/6)){
            cancle = true;
            release = true;
            updateFlag = true;
            emit closeCommuSet(QString("sensor:添加关闭>framName|%1").arg(objectName()));
            //            this->close();
        }
        //xright-width() *2/6 + 10,yuttom - height()*2/6,width()/6,height()/6,
        // 转化换坐标：width() -width() *2/6， height() - height()*2/6 ，width()/6,height()/6
        else if(posX > (width()*4/6) && posX < (width()*5/6) &&
                posY > (height()*4/6) && posY <(height()*5/6)){
            confirm = true;
            release = true;
            updateFlag = true;
            //待处理
            QString command = "sensor:add>"+getCommunicate();
            emit closeCommuSet(command);
        }
    }
    if(updateFlag){
        update();
    }
    e->accept();
}

void AFFIX9AddSensor::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton && leftClick){
        this->move(e->globalPos() - leftPos);
    }
    e->accept();
}

void AFFIX9AddSensor::mouseReleaseEvent(QMouseEvent *e)
{
    leftClick = false;
    if(cancle){
        cancle = !cancle;
    }
    if(confirm){
        confirm = !confirm;
    }
    if(release){
        update();
    }

    e->accept();
}

void AFFIX9AddSensor::setU36Id(QStringList id){
    m_36ID.clear();
    m_36ID = id;
    B_Unit36->clear();
    B_Unit36->addItems(this->m_36ID);
}

void AFFIX9AddSensor::setSensorModel(QStringList model)
{
    int n = model.length();
    for(int i= 0;i < n;i++){
        B_Model->addItem(model.value(i).split("=").value(0));
    }
}

void AFFIX9AddSensor::setCommData(InforData data,QString index){
    m_CommuData.clear();
    m_CommuData = data;
    showDefultValue(index);
}

void AFFIX9AddSensor::showDefultValue(QString str){
    qDebug()<<"index is:"+str;
    //    qDebug()<<"data0000000000"<<m_CommuData;
    QStringList defultValue = m_CommuData[QString("index%1").arg(str)].split(",");
    qDebug()<<"index ccccccccc"<<m_CommuData<<"aaaaaaa"<<defultValue;
    if(
            B_Bate&&
            B_Bits&&
            B_CRC&&
            B_StopBit)
    {
        B_cards->setCurrentText(str);
        B_Bate->setCurrentText(m_Bate[defultValue.value(1).split("=").value(1)]);
        B_Bits->setCurrentText(m_Bits[defultValue.value(2).split("=").value(1)]);
        B_CRC->setCurrentText(m_CRC[defultValue.value(3).split("=").value(1)]);
        B_StopBit->setCurrentText(m_StopBit[defultValue.value(4).split("=").value(1)]);
    }
}

void AFFIX9AddSensor::initComboxcontrl()
{
    B_Unit36 = new QComboBox(this);
    B_cards = new QComboBox(this);
    connect(B_cards,SIGNAL(currentIndexChanged(QString))
            ,SLOT(showDefultValue(QString)));
    B_Bate = new QComboBox(this);
    B_Bits = new QComboBox(this);
    B_CRC = new QComboBox(this);
    B_StopBit = new QComboBox(this);
    B_Model = new QComboBox(this);
    B_Eable = new QComboBox(this);
}

void AFFIX9AddSensor::setComboxItems()
{
    QStringList list;
    //    B_Unit36->addItems();
    list<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"
       <<"9"<<"10"<<"11"<<"12"<<"13"<<"14"<<"15"<<"16";
    B_cards->addItems(list);
    list.clear();
    list<<"4800"<<"9600"<<"19200"<<"57600"
       <<"115200";
    B_Bate->addItems(list);
    list.clear();
    list<<"5"<<"6"<<"7"<<"8";
    B_Bits->addItems(list);
    list.clear();
    list<<"无校验"<<"偶校验"<<"奇校验";
    B_CRC->addItems(list);
    list.clear();
    list<<"一位"<<"两位";
    B_StopBit->addItems(list);
    list.clear();
    list<<"Enable"<<"Disable";
    B_Eable->addItems(list);
}

void AFFIX9AddSensor::setComboxGeometry()
{
    if(B_Unit36 &&
            B_cards &&
            B_Bate &&
            B_Bits &&
            B_CRC &&
            B_StopBit &&
            B_Model &&
            B_Eable){
        int w=width() -20,sh = 20,h = height()*3/7,h2 = height()*5/7,sw = w / 6 -8;
        B_Unit36->setGeometry(10,h,sw,sh);
        B_cards->setGeometry(10+w *1/6,h,sw,sh);
        B_Bate->setGeometry(10+w *2/6,h,sw,sh);
        B_Bits->setGeometry(10+w *3/6,h,sw,sh);
        B_CRC->setGeometry(10+w *4/6,h,sw,sh);
        B_StopBit->setGeometry(10+w *5/6,h,sw,sh);
        B_Model->setGeometry(10,h2,sw,sh);
        B_Eable->setGeometry(10+w/6,h2,sw,sh);
    }
}

void AFFIX9AddSensor::setComboxStyleSheet()
{
    if(B_Unit36 &&
            B_cards &&
            B_Bate &&
            B_Bits &&
            B_CRC &&
            B_StopBit &&
            B_Model &&
            B_Eable){
        QString styleStr = "QComboBox{border:0px solid #636363;border-radius:5px;}";
        B_Unit36->setStyleSheet(styleStr);
        B_cards->setStyleSheet(styleStr);
        B_Bate->setStyleSheet(styleStr);
        B_Bits->setStyleSheet(styleStr);
        B_CRC->setStyleSheet(styleStr);
        B_StopBit->setStyleSheet(styleStr);
        B_Model->setStyleSheet(styleStr);
        B_Eable->setStyleSheet(styleStr);
    }
}

void AFFIX9AddSensor::initUIsize()
{
    s_width = 0;
    s_height = 0;
}

void AFFIX9AddSensor::initleftClickValue()
{
    leftClick = false;
}

void AFFIX9AddSensor::initClickBoolValue()
{
    cancle = false;
    confirm = false;
    release = false;
}

void AFFIX9AddSensor::initTitleStr()
{
    title[1] = "3616";
    title[2] = "卡号";
    title[3] = "波特率";
    title[4] = "数据";
    title[5] = "校验";
    title[6] = "停止";
    title2[1] = "传感器";
    title2[2] = "使能数据";
}

void AFFIX9AddSensor::initCommunicateValue()
{
    //波特率
    Bate["4800"] = "1";
    Bate["9600"] = "2";
    Bate["19200"] = "3";
    Bate["57600"] = "4";
    Bate["115200"] = "5";

    //数据位
    Bits["5"] = "1";
    Bits["6"] = "2";
    Bits["7"] = "3";
    Bits["8"] = "4";

    //校验
    CRC["无校验"] = "1";
    CRC["偶校验"] = "2";
    CRC["奇校验"] = "3";

    //停止位
    StopBit["一位"] = "1";
    StopBit["两位"] = "2";

    //使能sensor
    Enable["Enable"] = "1";
    Enable["Disable"] = "0";
    //波特率
    m_Bate["1"] = "4800";
    m_Bate["2"] = "9600";
    m_Bate["3"] = "19200";
    m_Bate["4"] = "57600";
    m_Bate["5"] = "115200";

    //数据位
    m_Bits["1"] = "5";
    m_Bits["2"] = "6";
    m_Bits["3"] = "7";
    m_Bits["4"] = "8";

    //校验
    m_CRC["1"] = "无校验";
    m_CRC["2"] = "偶校验";
    m_CRC["3"] = "奇校验";

    //停止位
    m_StopBit["1"] = "一位";
    m_StopBit["2"] = "两位";
}

void AFFIX9AddSensor::init36Id()
{
    m_36ID<<"111";
}

QString AFFIX9AddSensor::getCommunicate()
{
    QString data;
    if(B_Unit36&&
            B_cards&&
            B_Bate&&
            B_Bits&&
            B_CRC&&
            B_StopBit){
        data = "id36|" + B_Unit36->currentText() + "/";
        data = data + "card|" + B_cards->currentText() + "/";
        data = data + "bate|" + Bate[B_Bate->currentText()] + "/";
        data = data + "bits|" + Bits[B_Bits->currentText()] + "/";
        data = data + "crc|" + CRC[B_CRC->currentText()] + "/";
        data = data + "stop|" + StopBit[B_StopBit->currentText()] + "/";
        data = data + "model|" + B_Model->currentText() + "/";
        data = data + "enable|" + Enable[B_Eable->currentText()] + "/";
    }
    return data;
}
