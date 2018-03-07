#include "aftnhurdle.h"

AFTNHurdle::AFTNHurdle(QWidget *parent) :
    QWidget(parent)
{
    initShowContrl();
    initShowContrlOnliyRead();
    initShowcontrlSetstyle();

    initContrlSize();
    initMinButtonBoolValue();
    initReleaseBool();
}

void AFTNHurdle::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width() / 2,height() / 2);
    if(contrlHeight != height() || contrlWidth != width()){
        contrlHeight = height();
        contrlWidth = width();
        setShowContrlGeomerty();
    }

    // init values
    int left = -width() / 2;
    int top = -height() / 2;
    int Hsize =  height()- 4;
    int Wsize =  width() - 4;
    int BHsize = height()- 2;

    // paint background
    painter.save();
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRect(left + 2,top + 2,Wsize,Hsize);
    painter.restore();

    //paint button comfire
    painter.save();
    if(ackClickBool){
        painter.setBrush(QColor("#E8E8E8"));
    }
    else{
        painter.setBrush(QColor("#E0FFFF"));
    }
    painter.drawRoundedRect(left + 2,top + 2,Wsize / 10,Hsize,3,3);
    QFont font = painter.font();
    font.setPixelSize(13);
    painter.setFont(font);
    painter.drawText(left + 2,top + 2,Wsize / 10,Hsize,Qt::AlignCenter,"确认");
    painter.restore();

    //paint send again button
    painter.save();
    if(sendClickAgainBool){
        painter.setBrush(QColor("#E8E8E8"));
    }
    else{
        painter.setBrush(QColor("#E0FFFF"));
    }
    painter.drawRoundedRect(left + 2 + Wsize / 2,top + 2,Wsize / 10,Hsize,3,3);
    QFont fontTow = painter.font();
    fontTow.setPixelSize(13);
    painter.setFont(fontTow);
    painter.drawText(left + 2 + Wsize / 2,top + 2,Wsize / 10,Hsize,Qt::AlignCenter,"重新发送");
    painter.restore();

    //paint code telegram hint
    painter.save();
    painter.setBrush(Qt::gray);
    painter.drawRect(left + 2 + Wsize / 10,top + 2,Wsize * 3 / 10,Hsize);
    painter.restore();

    //paint AFTN Information show
    painter.save();
    painter.setBrush(Qt::gray);
    painter.drawRect(left + 2 + Wsize * 3 / 5,top + 2,Wsize * 4 / 10,Hsize);
    painter.setPen(QPen(Qt::black,2));
    painter.drawText(left + 8 + Wsize * 3 / 5,top + 2,Wsize * 4 / 10,Hsize,Qt::AlignVCenter | Qt::AlignLeft,"AFTN");
    painter.restore();

    // sended
    painter.save();
    if(sendedBool){
        painter.setBrush(QColor("#E8E8E8"));
    }
    else{
        painter.setBrush(QColor("#E0FFFF"));
    }
    painter.drawRoundedRect(left + 2 + Wsize * 2 / 5,top + 2,Wsize / 10,BHsize / 3 - 2,3,3);
    QFont four = painter.font();
    four.setPixelSize(13);
    painter.setFont(four);
    painter.drawText(left + 2 + Wsize * 2 / 5,top + 2,Wsize / 10,BHsize / 3 - 2,Qt::AlignCenter,"发送了");
    painter.restore();

    //comfired
    painter.save();
    if(comfiredBool){
        painter.setBrush(QColor("#E8E8E8"));
    }
    else{
        painter.setBrush(QColor("#E0FFFF"));
    }
    painter.drawRoundedRect(left + 2 + Wsize * 2 / 5,top + 2 + BHsize / 3,Wsize / 10,BHsize / 3 - 2,3,3);
    QFont fontThree = painter.font();
    fontThree.setPixelSize(13);
    painter.setFont(fontThree);
    painter.drawText(left + 2 + Wsize * 2 / 5,top + 2 + BHsize / 3,Wsize / 10,BHsize / 3 - 2,Qt::AlignCenter,"确认了");
    painter.restore();

    //steup second send
    painter.save();
    if(setupSendFunctionBool){
        painter.setBrush(QColor("#E8E8E8"));
    }
    else{
        painter.setBrush(QColor("#E0FFFF"));
    }
    painter.drawRoundedRect(left + 2 + Wsize * 2 / 5,top + 2 + BHsize * 2 / 3,Wsize / 10,BHsize / 3 - 2,3,3);
    QFont ffive = painter.font();
    ffive.setPixelSize(13);
    painter.setFont(ffive);
    painter.drawText(left + 2 + Wsize * 2 / 5,top + 2 + BHsize * 2 / 3,Wsize / 10,BHsize / 3 - 2,Qt::AlignCenter,"重发功能");
    painter.restore();
}

void AFTNHurdle::mousePressEvent(QMouseEvent *e)
{
    bool falg = false;
    if(e->button() == Qt::LeftButton){
        int posX = e->pos().x();
        int posY = e->pos().y();
        int Wsize =  width() - 4;
        int BHsize = height()- 2;

        if(posX > 2 && posX < (2 + Wsize / 10) &&
                posY > 2 && posY < (2 + BHsize)){
            falg = true;
            releaseBool = true;
            ackClickBool = true;
        }
        else if(posX > (2 + Wsize / 2) && posX < (2 + Wsize * 3 / 5)
                && posY > 2 && posY < (2 + BHsize)){
            falg = true;
            releaseBool = true;
            sendClickAgainBool = true;
        }
        else if(posX > (2 + Wsize * 2 / 5)&& posX < (2 + Wsize / 2) &&
                posY > (2 + BHsize / 3) && posY < (BHsize * 2 / 3)){
            falg = true;
            releaseBool = true;
            comfiredBool = true;
        }
        else if(posX > (2 + Wsize * 2 / 5)&& posX < (2 + Wsize / 2) &&
                posY > 2 && posY < (BHsize / 3)){
            falg = true;
            releaseBool = true;
            sendedBool = true;
        }
        else if(posX > (2 + Wsize * 2 / 5)&& posX < (2 + Wsize / 2) &&
                posY > (2 + BHsize * 2 / 3) && posY < BHsize){
            falg = true;
            releaseBool = true;
            setupSendFunctionBool = true;
        }
    }
    if(falg){
        update();
    }
}

void AFTNHurdle::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    if(ackClickBool){
        ackClickBool = false;
    }
    if(sendClickAgainBool){
        sendClickAgainBool = false;
    }
    if(comfiredBool){
        comfiredBool = false;
    }
    if(sendedBool){
        sendedBool = false;
    }
    if(setupSendFunctionBool){
        setupSendFunctionBool = false;
    }

    if (releaseBool) {
        update();
    }
}

void AFTNHurdle::initShowContrl()
{
    telegramOptionHint = new QTextEdit(this);
    AFTNInformation = new QTextEdit(this);
}

void AFTNHurdle::initShowContrlOnliyRead()
{
    telegramOptionHint->setReadOnly(true);
    AFTNInformation->setReadOnly(true);
}

void AFTNHurdle::initShowcontrlSetstyle()
{
    telegramOptionHint->setStyleSheet("QTextEdit{background: white}");
    AFTNInformation->setStyleSheet("QTextEdit{background:white}");
}

void AFTNHurdle::setShowContrlGeomerty()
{
    if(telegramOptionHint && AFTNInformation){
        int Hsize =  height()- 4;
        int Wsize =  width() - 4;
        telegramOptionHint->setGeometry( 2 + Wsize / 10 + 10,2+2,Wsize * 3 / 10 - 20,Hsize -4);
        AFTNInformation->setGeometry(2 + Wsize * 3 / 5 + 40,2+2,Wsize * 4 / 10 - 50,Hsize -4);
    }
}

void AFTNHurdle::initContrlSize()
{
    contrlWidth = 0;
    contrlHeight = 0;
}

void AFTNHurdle::initMinButtonBoolValue()
{
    ackClickBool = false;
    sendClickAgainBool = false;
    comfiredBool = false;
    sendedBool = false;
    setupSendFunctionBool = false;
}

void AFTNHurdle::initReleaseBool()
{
    releaseBool = false;
}
