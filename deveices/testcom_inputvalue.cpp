#include "testcom_inputvalue.h"

InputValueCom::InputValueCom(QWidget *parent) :
    QWidget(parent)
{
    initAddValue();
    initConfirmValue();
}

void InputValueCom::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    int left = -width()/2;
    int top = -height()/2;
    int right = width()/2;
    int bottm = height()/2;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width()/2,height()/2);

    painter.save();
    painter.setPen(QPen(Qt::gray,2));
    painter.drawRect(-width()/2,-height()/2,width(),height());
    painter.restore();

    painter.save();
    QPoint configStartPoint(0,bottm - 60);
    QPoint configEndPoint(0,bottm - 30);
    QLinearGradient gradMet1(configStartPoint,configEndPoint);
    QLinearGradient gradMet2(configStartPoint,configEndPoint);
    gradMet1.setColorAt(0,QColor("#4A708B"));
    gradMet1.setColorAt(1,QColor("#00688B"));
    gradMet2.setColorAt(0,QColor("#CAE1FF"));
    gradMet2.setColorAt(1,QColor("#B0E0E6"));
    if(!confirm){
        painter.setBrush(gradMet1);
    }
    else {
        painter.setBrush(gradMet2);
    }
    painter.drawRect(right - 120,bottm - 60,100,30);
    painter.setPen(QPen(Qt::white,4));
    painter.drawText(right - 120,bottm - 60,100,30,Qt::AlignCenter,"确定");
    painter.restore();

}

void InputValueCom::mousePressEvent(QMouseEvent *e)
{
    bool falge = false;
    if(e->button() == Qt::LeftButton){
        int posX = e->pos().x();
        int posY = e->pos().y();
        if(posX > (width() - 120) && posX < (width() - 20)&&
                posY > (height() - 60) && posY < (height() - 30)){
            falge = true;
            confirm = true;
            release = true;
        }
    }
    if(falge){
        update();
    }
}

void InputValueCom::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    if(confirm){
        confirm = false;
    }
    if(release){
        update();
    }
}

void InputValueCom::clearVEC()
{
    if(labelVEC.count() > 0){
        for(int i = 0;i < labelVEC.count();i++){
            /// 注意检查此处
            labelVEC.at(i)->close();
            delete labelVEC.at(i);
        }
        labelVEC.clear();
    }

    if (lineVEC.count() > 0) {
        for(int i = 0;i < lineVEC.count();i++){
            /// 注意检查此处
            lineVEC.at(i)->close();
            delete lineVEC.at(i);
        }
        lineVEC.clear();
    }
}

void InputValueCom::addLabelComs(QString infor, int index, int comWidth, int comheight)
{
    QLabel *label = new QLabel(this);
    label->setText(infor.split(":").value(0));
    label->setObjectName(QString("%1").arg(index));
    label->setGeometry(10,10 + 40 *(index - 1),comWidth,comheight);
    label->show();
    labelVEC.push_back(label);
}

void InputValueCom::addEditComs(QString infor, int index, int comWidth, int comheight)
{
    QLineEdit *edit = new QLineEdit(this);
    edit->setText(infor.split(":").value(1));
    edit->setObjectName(QString("%1:%1").arg(index).arg(infor.split(":").value(0)));
    edit->setGeometry( width() / 3 + 10,10 + 40 *(index - 1),comWidth,comheight);
    edit->show();
    lineVEC.push_back(edit);
}

void InputValueCom::initSubContrls(int Index)
{
    clearVEC();
    int len;
    QString str;
    int labelWidth = width() / 3 - 20;
    int editWidth = width() * 2 / 3 - 20;
    //    int labelHeight = height() - 10;
    //初始化机场配置界面
    if(Index == 1){
        len = airportAdd.count();
        for(int i = 1;i <= len; i++){
            str = airportAdd[i];
            addLabelComs(str,i,labelWidth,30);
            addEditComs(str,i,editWidth,30);
        }
    }

    //初始跑道场配置界面
    if(Index == 2){
        len = runWayAdd.count();
        for(int i = 1;i <= len; i++){
            str = runWayAdd[i];
            addLabelComs(str,i,labelWidth,30);
            addEditComs(str,i,editWidth,30);
        }
    }

    //初始化传感器配置界面
    if(Index == 3){
        len = sensorAdd.count();
        for(int i = 1;i <= len; i++){
            str = sensorAdd[i];
            addLabelComs(str,i,labelWidth,30);
            addEditComs(str,i,editWidth,30);
        }
    }
}

void InputValueCom::initAddValue()
{
    {
        airportAdd[1] = "3616主机:NULL";
        airportAdd[2] = "机场名称:NULL";
        airportAdd[3] = "机场ID:NULL";
        airportAdd[4] = "机场代码:NULL";
        airportAdd[5] = "机场标高:NULL";
        airportAdd[6] = "跑道入口标高:NULL";
    }

    {
        runWayAdd[1] = "3616主机:NULL";
        runWayAdd[2] = "机场ID:NULL";
        runWayAdd[3] = "跑道ID:NULL";
        runWayAdd[4] = "头编号:NULL";
        runWayAdd[5] = "中编号:NULL";
        runWayAdd[6] = "尾编号:NULL";
    }

    {
        sensorAdd[1] = "3616主机:NULL";
        sensorAdd[2] = "传感器ID:NULL";
        sensorAdd[3] = "传感器类型:NULL";
        sensorAdd[4] = "跑道ID:NULL";
    }
}

void InputValueCom::initConfirmValue()
{
    confirm = false;
    release = false;
}

