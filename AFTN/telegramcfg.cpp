#include "telegramcfg.h"

TelegramCFG::TelegramCFG(QWidget *parent) :
    QWidget(parent)
{
    initAFTNParavmeter();
    initaAllFormValues();

    initLineEditContrls();
    setEditContrlsShow(true);
    setEditContrlsInitValue();
    setEditContrlsBackgroundColor();
    initEditContrlsEditFinishSignalsConnectons();
    installEditsEventFilter();

    initComBoxContrls();
    setComBoxInitValues();
    setComBoxBackGroundColor();
    initComBoxCurrentSignalConnections();
    installComBoxEventFilter();

    initButtonBool();
    initSize();
}

void TelegramCFG::editAFTNValues()
{
    QString str;
    QString tempStr;
    QStringList list;

    str = AFTNAddress->text().trimmed();
    list.clear();
    tempStr = AFTNInitValues[1];
    list = tempStr.split(" ",QString::SkipEmptyParts);
    if(list.value(2) != str){
        AFTNInitValues[1]  = "AFTN 地址  " + str;
    }

    str = signalChannel->text().trimmed();
    list.clear();
    tempStr = AFTNInitValues[2];
    list = tempStr.split(" ",QString::SkipEmptyParts);
    if(list.value(1) != str){
        AFTNInitValues[2]  =  "信道名     " + str;
    }

    str = cresrt->text().trimmed();
    list.clear();
    tempStr = AFTNInitValues[3];
    list = tempStr.split(" ",QString::SkipEmptyParts);
    if(list.value(1) != str){
        AFTNInitValues[3]  =  "报文冠子   " + str;
    }

    str = remoteAddress->text().trimmed();
    list.clear();
    tempStr = AFTNInitValues[11];
    list = tempStr.split(" ",QString::SkipEmptyParts);
    if(list.value(1) != str){
        AFTNInitValues[11]  = "远端发送地址  "+ str;
    }
}

void TelegramCFG::separatorSlot(QString str)
{
    qDebug()<<"fen ge"<<str;
    QString tempStr = AFTNInitValues[7];
    QStringList list = tempStr.split(" ",QString::SkipEmptyParts);
    if(list.value(1) != str){
        AFTNInitValues[7]  = "分隔符     " + str;
    }
}

void TelegramCFG::flowSequenceSlot(QString str)
{
    qDebug()<<"ls"<<str;
    QString tempStr = AFTNInitValues[4];
    QStringList list = tempStr.split(" ",QString::SkipEmptyParts);
    if(list.value(1) != str){
        AFTNInitValues[4]  = "流水长度   " + str;
    }
}

void TelegramCFG::sendHeadSlot(QString str)
{
    qDebug()<<"send HEAD"<<str;
    QString tempStr = AFTNInitValues[5];
    QStringList list = tempStr.split(" ",QString::SkipEmptyParts);
    if(list.value(1) != str){
        AFTNInitValues[5]  = "发送报头   " + str;
    }
}

void TelegramCFG::sendRaerSlot(QString str)
{
    qDebug()<<"send REAR"<<str;
    QString tempStr = AFTNInitValues[6];
    QStringList list = tempStr.split(" ",QString::SkipEmptyParts);
    if(list.value(1) != str){
        AFTNInitValues[6]  = "发送报尾   " + str;
    }
}

void TelegramCFG::receiveHeadSlot(QString str)
{
    qDebug()<<"RECI Head"<<str;
    QString tempStr = AFTNInitValues[9];
    QStringList list = tempStr.split(" ",QString::SkipEmptyParts);
    if(list.value(1) != str){
        AFTNInitValues[9]  =  "接送报头   " + str;
    }
}

void TelegramCFG::receiveRaerSlot(QString str)
{
    qDebug()<<"RECI rear"<<str;
    QString tempStr = AFTNInitValues[10];
    QStringList list = tempStr.split(" ",QString::SkipEmptyParts);
    if(list.value(1) != str){
        AFTNInitValues[10]  = "接收报尾   " + str;
    }
}

void TelegramCFG::AFTNTelegramSlot(QString str)
{
    qDebug()<<"AFTN"<<str;
    QString tempStr = AFTNInitValues[8];
    QStringList list = tempStr.split(" ",QString::SkipEmptyParts);
    if(list.value(2) != str){
        AFTNInitValues[8] = "AFTN 电报  " + str;
    }
}



void TelegramCFG::initAFTNParavmeter()
{
    AFTNInitValues[1]   = "AFTN 地址  AAAAAAAA";
    AFTNInitValues[2]   = "信道名     XXX";
    AFTNInitValues[3]   = "报文冠子   LSP";
    AFTNInitValues[4]   = "流水长度   3";
    AFTNInitValues[5]   = "发送报头   ZCZC→";
    AFTNInitValues[6]   = "发送报尾   <≡≡≡≡≡≡≡≡NNNN";
    AFTNInitValues[7]   = "分隔符     None";
    AFTNInitValues[8]   = "AFTN 电报  0";
    AFTNInitValues[9]   = "接收报头   ZCZC→";
    AFTNInitValues[10]  = "接收报尾   <≡≡≡≡≡≡≡≡NNNN";
    AFTNInitValues[11]  = "远端发送地址";
}

void TelegramCFG::setAFTNParavmeter()
{
    MeaagseQueue setqueue;
    qDebug()<<"metar set";
    QString str;
    for(int i = 1; i < 12;i++){
        if(i == 1 || i == 8 ){
            str = AFTNInitValues[i].split(" ",QString::SkipEmptyParts).value(2);
        }
        else{
            str = AFTNInitValues[i].split(" ",QString::SkipEmptyParts).value(1);
        }
        qDebug()<<"metar message queue:"<< str;
        switch (i) {
        case 1:// AFTN
            setqueue.enqueue(str);
            break;
        case 2:// signal
            setqueue.enqueue(str);
            break;
        case 3:// guanzi
            setqueue.enqueue(str);
            break;
        case 4:// 流水
            for(int num1 = 1;num1 < 7;num1++){
                if(flowSequenceMap[num1] == str){
                    setqueue.enqueue(flowSequenceMap[num1]);
                }
            }
            break;
        case 5:// 发送报头
            for(int num2 = 1;num2 < 13;num2++){
                if(sendHeadMap[num2] == str){
                    setqueue.enqueue(QString("%1").arg(num2));
                }
            }
            break;
        case 6:// 发送报尾
            for(int num3 = 1;num3 < 15;num3++){
                if(sendRaerMap[num3].split(" ",QString::SkipEmptyParts).value(0) == str){
                    setqueue.enqueue(QString("%1").arg(num3));
                }
            }
            break;
        case 7:// 分隔符
            for(int num4 = 1; num4 < 5;num4++){
                if(separatorMap[num4] == str){
                    setqueue.enqueue(QString("%1").arg(num4));
                }
            }
            break;
        case 8:// 回车换行符
            for(int num5 = 1; num5 < 4;num5++){
                if(AFTNTelegramMap[num5] == str){
                    setqueue.enqueue(AFTNTelegramMap[num5]);
                }
            }
            break;
        case 9://接收报头
            for(int num6 = 1;num6 < 13;num6++){
                if(receiveHeadMap[num6] == str){
                    setqueue.enqueue(QString("%1").arg(num6));
                }
            }
            break;
        case 10:// 接收报尾
            for(int num7 = 1;num7 < 15;num7++){
                if(receiveRaerMap[num7].split(" ",QString::SkipEmptyParts).value(0) == str){
                    setqueue.enqueue(QString("%1").arg(num7));
                }
            }
            break;
        case 11:// 远端发送地址
            setqueue.enqueue("NULL"); // 暂时不用
            break;
        default:
            break;
        }
    }
    qDebug()<<"message:"<<setqueue;
    emit AFTNConfigSet(setqueue);
}

bool TelegramCFG::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove || event->type() == QEvent::HoverMove )
    {
        event->accept();
        return true;
    }
    else{
        return QWidget::eventFilter(obj, event);
    }
}

void TelegramCFG::initLineEditContrls()
{
    AFTNAddress = new QLineEdit(this);
    cresrt = new QLineEdit(this);
    signalChannel = new QLineEdit(this);
    remoteAddress = new QLineEdit(this);
    return ;
}

void TelegramCFG::setGeometryEditContrls()
{
    int sWidth = width() - 8;
    int sHeight = height() - 16;
    int fram1Start = 4;
    int fram3Start = 12 + sHeight * 9 / 11;
    AFTNAddress->setGeometry(100,fram1Start + 50,sWidth / 4 - 110,30);
    cresrt->setGeometry(100 + sWidth / 4,fram1Start + 90,sWidth / 4 - 110,30);
    signalChannel->setGeometry(100,fram1Start + 90,sWidth / 4 - 110,30);
    remoteAddress->setGeometry(120 + sWidth / 4,fram3Start + 50,sWidth / 4 - 130,30);
    return ;
}

void TelegramCFG::setEditContrlsShow(bool show)
{
    if(show){
        AFTNAddress->show();
        cresrt->show();
        signalChannel->show();
        remoteAddress->show();
    }
    return ;
}

void TelegramCFG::setEditContrlsInitValue()
{
    AFTNAddress->setText("AAAAAAAA");
    cresrt->setText("LSP");
    signalChannel->setText("XXX");
    remoteAddress->setText("CCCCCCCC");
    return ;
}

void TelegramCFG::setEditContrlsBackgroundColor()
{
    AFTNAddress->setStyleSheet("background:#EEEEE0");
    cresrt->setStyleSheet("background:#EEEEE0");
    signalChannel->setStyleSheet("background:#EEEEE0");
    remoteAddress->setStyleSheet("background:#EEEEE0");
    return ;
}

void TelegramCFG::initEditContrlsEditFinishSignalsConnectons()
{
    if(AFTNAddress && cresrt && signalChannel && remoteAddress)
    {
        connect(AFTNAddress,SIGNAL(editingFinished()),SLOT(editAFTNValues()));
        connect(cresrt,SIGNAL(editingFinished()),SLOT(editAFTNValues()));
        connect(signalChannel,SIGNAL(editingFinished()),SLOT(editAFTNValues()));
        connect(remoteAddress,SIGNAL(editingFinished()),SLOT(editAFTNValues()));
    }
    return ;
}

void TelegramCFG::installEditsEventFilter()
{
    AFTNAddress->installEventFilter(this);
    cresrt->installEventFilter(this);
    signalChannel->installEventFilter(this);
    remoteAddress->installEventFilter(this);
}

void TelegramCFG::initComBoxContrls()
{
    flowSequence = new QComboBox(this);
    separator = new QComboBox(this);
    sendHead = new QComboBox(this);
    sendRaer = new QComboBox(this);
    receiveHead = new QComboBox(this);
    receiveRaer = new QComboBox(this);
    AFTNTelegram = new QComboBox(this);
}

void TelegramCFG::setComBoxGeometry()
{
    int sWidth = width() - 8;
    int sHeight = height() - 16;
    int fram1Start = 4;
    int fram2Start = 8 + sHeight * 4 / 11;
    int fram3Start = 12 + sHeight * 9 / 11;
    flowSequence->setGeometry(100 + sWidth / 4,fram1Start + 130,sWidth / 4 - 110,30);
    separator->setGeometry(100,fram1Start + 130,sWidth / 4 - 110,30);
    sendHead->setGeometry(100,fram2Start + 50,200,30);
    sendRaer->setGeometry(100,fram2Start + 90,200,30);
    receiveHead->setGeometry(100,fram2Start + 130,200,30);
    receiveRaer->setGeometry(100,fram2Start + 170,200,30);
    AFTNTelegram->setGeometry(100,fram3Start + 50,200,30);
}

void TelegramCFG::setComBoxInitValues()
{
    for(int i = 1;i < 15;i++){
        if(i < 4){
            AFTNTelegram->addItem(AFTNTelegramMap[i]);
        }
        if(i < 5){
            separator->addItem(separatorMap[i]);
        }
        if(i < 7){
            flowSequence->addItem(flowSequenceMap[i]);
        }
        if(i < 13){
            sendHead->addItem(sendHeadMap[i]);
            receiveHead->addItem(receiveHeadMap[i]);
        }
        if(i < 15){
            sendRaer->addItem(sendRaerMap[i]);
            receiveRaer->addItem(receiveRaerMap[i]);
        }
    }
}

void TelegramCFG::setComBoxBackGroundColor()
{
    flowSequence->setStyleSheet("background:#EEEEE0");
    separator->setStyleSheet("background:#EEEEE0");
    sendHead->setStyleSheet("background:#EEEEE0");
    sendRaer->setStyleSheet("background:#EEEEE0");
    receiveHead->setStyleSheet("background:#EEEEE0");
    receiveRaer->setStyleSheet("background:#EEEEE0");
    AFTNTelegram->setStyleSheet("background:#EEEEE0");
    return ;
}

void TelegramCFG::initComBoxCurrentSignalConnections()
{
    if(separator && flowSequence && sendHead && sendRaer
            && receiveHead && receiveRaer && AFTNTelegram)
    {
        connect(separator,SIGNAL(currentTextChanged(QString)),SLOT(separatorSlot(QString)));
        connect(flowSequence,SIGNAL(currentTextChanged(QString)),SLOT(flowSequenceSlot(QString)));
        connect(sendHead,SIGNAL(currentTextChanged(QString)),SLOT(sendHeadSlot(QString)));
        connect(sendRaer,SIGNAL(currentTextChanged(QString)),SLOT(sendRaerSlot(QString)));
        connect(receiveHead,SIGNAL(currentTextChanged(QString)),SLOT(receiveHeadSlot(QString)));
        connect(receiveRaer,SIGNAL(currentTextChanged(QString)),SLOT(receiveRaerSlot(QString)));
        connect(AFTNTelegram,SIGNAL(currentTextChanged(QString)),SLOT(AFTNTelegramSlot(QString)));
    }
}

void TelegramCFG::installComBoxEventFilter()
{
    flowSequence->installEventFilter(this);
    separator->installEventFilter(this);
    sendHead->installEventFilter(this);
    sendRaer->installEventFilter(this);
    receiveHead->installEventFilter(this);
    receiveRaer->installEventFilter(this);
    AFTNTelegram->installEventFilter(this);

}

void TelegramCFG::updateAFTNValues()
{
    qDebug()<<"cancel metar set";
    QString value;
    emit AFTNAddress->editingFinished();
    //    emit STIAAdrreseditingFinished();
    emit cresrt->editingFinished();
    emit signalChannel->editingFinished();
    emit remoteAddress->editingFinished();
    value = separator->currentText();
    emit separator->currentTextChanged(value);
    value = flowSequence->currentText();
    emit flowSequence->currentTextChanged(value);
    value = sendHead->currentText();
    emit sendHead->currentTextChanged(value);
    value = sendRaer->currentText();
    emit sendRaer->currentTextChanged(value);
    value = receiveHead->currentText();
    emit receiveHead->currentTextChanged(value);
    value = receiveRaer->currentText();
    emit receiveRaer->currentTextChanged(value);
    value = AFTNTelegram->currentText();
    emit AFTNTelegram->currentTextChanged(value);
}

void TelegramCFG::initaAllFormValues()
{
    flowSequenceMap[1] = "3";
    flowSequenceMap[2] = "4";
    flowSequenceMap[3] = "5";
    flowSequenceMap[4] = "6";
    flowSequenceMap[5] = "7";
    flowSequenceMap[6] = "8";

    separatorMap[1] = "None";
    separatorMap[2] = "<<≡<<≡<<≡<<≡";
    separatorMap[3] = "<≡<≡<≡<≡";
    separatorMap[4] = "≡≡≡≡";


    sendHeadMap[1]  = "ZCZC→";
    sendHeadMap[2]  = "<<≡ZCZC→";
    sendHeadMap[3]  = "<≡ZCZC→";
    sendHeadMap[4]  = "SOH";
    sendHeadMap[5]  = "SOH<<≡";
    sendHeadMap[6]  = "SOH→";
    sendHeadMap[7]  = "STX";
    sendHeadMap[8]  = "STX<<≡";
    sendHeadMap[9]  = "STX<≡";
    sendHeadMap[10] = "STX→";
    sendHeadMap[11] = "ZCZC<<≡";
    sendHeadMap[12] = "ZCZC<≡";

    sendRaerMap[1]  = "<≡≡≡≡≡≡≡≡NNNN";
    sendRaerMap[2]  = "≡≡≡≡≡≡≡≡NNNN";
    sendRaerMap[3]  = "↓<<≡≡≡≡≡≡≡≡NNNN";
    sendRaerMap[4]  = "<≡≡≡≡NNNN";
    sendRaerMap[5]  = "<<≡VT ETX";
    sendRaerMap[6]  = "<≡ETX";
    sendRaerMap[7]  = "<≡VT ETX";
    sendRaerMap[8]  = "ETX";
    sendRaerMap[9]  = "EOT";
    sendRaerMap[10] = "VT EOT";
    sendRaerMap[11] = "<≡ETX EOT";
    sendRaerMap[12] = "<≡＝<≡≡≡≡≡≡≡≡NNNN";
    sendRaerMap[13] = "<≡≡≡≡≡≡≡≡ETX";
    sendRaerMap[14] = "<≡≡≡≡≡≡≡≡EOT";

    receiveHeadMap[1]  = "ZCZC→";
    receiveHeadMap[2]  = "<<≡ZCZC→";
    receiveHeadMap[3]  = "<≡ZCZC→";
    receiveHeadMap[4]  = "SOH";
    receiveHeadMap[5]  = "SOH<<≡";
    receiveHeadMap[6]  = "SOH→";
    receiveHeadMap[7]  = "STX";
    receiveHeadMap[8]  = "STX<<≡";
    receiveHeadMap[9]  = "STX<≡";
    receiveHeadMap[10] = "STX→";
    receiveHeadMap[11] = "ZCZC<<≡";
    receiveHeadMap[12] = "ZCZC<≡";

    receiveRaerMap[1]  = "<≡≡≡≡≡≡≡≡NNNN";////|xxxx
    receiveRaerMap[2]  = "≡≡≡≡≡≡≡≡NNNN";
    receiveRaerMap[3]  = "↓<<≡≡≡≡≡≡≡≡NNNN";
    receiveRaerMap[4]  = "<≡≡≡≡NNNN";
    receiveRaerMap[5]  = "<<≡VT ETX";
    receiveRaerMap[6]  = "<≡ETX";
    receiveRaerMap[7]  = "<≡VT ETX";
    receiveRaerMap[8]  = "ETX";
    receiveRaerMap[9]  = "EOT";
    receiveRaerMap[10] = "VT EOT";
    receiveRaerMap[11] = "<≡ETX EOT";
    receiveRaerMap[12] = "<≡＝<≡≡≡≡≡≡≡≡NNNN";
    receiveRaerMap[13] = "<≡≡≡≡≡≡≡≡ETX";
    receiveRaerMap[14] = "<≡≡≡≡≡≡≡≡EOT";

    AFTNTelegramMap[1] = "0";////|xxxx
    AFTNTelegramMap[2] = "1";
    AFTNTelegramMap[3] = "2";
}

void TelegramCFG::initButtonBool()
{
    m_metarSetConfirm = false;
    m_metarSetCancel = false;
    releaseDo = false;
}

void TelegramCFG::initSize()
{
    wSize = 0;
    hSize = 0;
}
