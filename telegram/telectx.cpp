#include "telectx.h"

TelegramContextDealUI::TelegramContextDealUI(QWidget *parent) :
    QWidget(parent)
{
    initAllContrls();
    setAllContrlsReadOnly();
    m_Update = false;
    m_Comfirm = false;
    m_send = false;
    m_metComfirm = false;
    m_spacComfirm = false;
    releaseDo = false;

    met_modifytTelegramFlag = false;

    sizeFirstUpdate = false;

    m_contextNameStr = "TELEGRAM";
}

void TelegramContextDealUI::mousePressEvent(QMouseEvent *e)
{
    bool flag = false;
    if(e->button() == Qt::LeftButton){//判断鼠标事件的按钮名称
        int posY = e->pos().y();
        int posX = e->pos().x();
        int sHeight = height(); // V drection 4 * 4 - 100
        int sWidth = width(); // H drection 3 * 4

        // qDebug()<<"on metar1 page sub options";

        if(posX > sWidth * 4 / 5 && posX < sWidth - 6 &&
                posY > 9 && posY < (sHeight / 2 - 11) / 3 + 4)
        {
            qDebug()<<"--->update";
            updateTelegram();
            m_Update = true;
            flag = true;
            releaseDo = true;
        }

        if(posX > sWidth * 4 / 5 && posX < sWidth - 6 &&
                posY > (sHeight / 2 - 11) / 3 + 9
                && posY < (sHeight / 2 - 11) * 2 / 3 + 4)
        {
            qDebug()<<"--->modify";
            comfirmTelegram();
            m_Comfirm = true;
            flag = true;
            releaseDo = true;
        }

        if(posX > sWidth * 4 / 5 && posX < sWidth - 6 &&
                posY > (sHeight / 2 - 11) * 2 / 3 + 9 && posY < sHeight / 2 - 7){
            qDebug()<<"--->send";
            sendTelegram();
            m_send = true;
            flag = true;
            releaseDo = true;
        }

        if(posX > (width() / 2) * 4 / 5 && posX < width() / 2 - 6 &&
                posY > sHeight / 2 + 5 && posY < sHeight - 7){
            qDebug()<<"--->update";
            metarComfirm();
            m_metComfirm = true;
            flag = true;
            releaseDo = true;
        }

        if(posX > width() * 9 / 10 && posX < width() - 6 &&
                posY > sHeight / 2 + 5 && posY < sHeight - 7){
            qDebug()<<"--->update";
            spacComfirm();
            m_spacComfirm = true;
            flag = true;
            releaseDo = true;
        }
        e->accept();
        if(flag){
            update();
        }
    }
}
void TelegramContextDealUI::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_Update){
        m_Update = false;
    }
    if(m_Comfirm){
        m_Comfirm = false;
    }
    if(m_send){
        m_send = false;
    }
    if(m_metComfirm){
        m_metComfirm = false;
    }
    if(m_spacComfirm){
        m_spacComfirm = false;
    }
    if(releaseDo){
        update();
        releaseDo = false;
    }
    e->accept();
}

void TelegramContextDealUI::setTelegramContextStr(QString telegramStr)
{
    this->m_telegramCtx.clear();
    this->m_telegramCtx = telegramStr;
    this->m_telegramContext->setText(m_telegramCtx);
    return ;
}

void TelegramContextDealUI::setMetarWaringList(QStringList waringList)
{
    this->m_MetarWaringList.clear();
    this->m_MetarWaringList = waringList;
    return ;
}

void TelegramContextDealUI::setSpacaiWaringList(QStringList waringList)
{
    this->m_SapciWaringList.clear();
    this->m_SapciWaringList = waringList;
    return ;
}

void TelegramContextDealUI::updateTelegram()
{
    emit queryUpdateTelegramCotext();
    return ;
}

void TelegramContextDealUI::comfirmTelegram()
{
    if(!met_modifytTelegramFlag){
        m_telegramContext->setReadOnly(false);
        met_modifytTelegramFlag = true;
    }
    else{
        m_telegramContext->setReadOnly(true);
        met_modifytTelegramFlag = false;
    }
    return ;
}

QString TelegramContextDealUI::removeFeild(QString str)
{
    QString tempStr = str;
    tempStr = tempStr.replace(":"," ");
    tempStr = tempStr.replace(";","");
    return tempStr;
}

QString TelegramContextDealUI::constituteMetarContext(SerialWarMap serialMap)
{
    QString metarReportStr;
    int number = serialMap.count();
    for(int num = 1; num <= number; num++)
    {
        if(serialMap[num].trimmed() == "")
        {
            continue;
        }
        if(num == number)
        {
            metarReportStr = metarReportStr + removeFeild(serialMap[num]);
        }
        else{
            metarReportStr = metarReportStr + removeFeild(serialMap[num]) + " ";
        }
    }
    return metarReportStr;
}

void TelegramContextDealUI::sendTelegram()
{
    //判断是否修改
    if(met_modifytTelegramFlag){
        //emit waringShowSignal("告警提示！","请先确认修改后再发送METAR报。");
        return ;
    }
    SerialWarMap metMap;
    // used map variable to constitute metar Str
    QString metString = m_telegramContext->toPlainText().replace("\n","");
    QStringList metSerial = metString.split(" ",QString::SkipEmptyParts);
    for(int index = 0;index < metSerial.length();index++){
        metMap[index + 1] = metSerial.value(index);
    }
    QString telegramContextStr = constituteMetarContext(metMap);

    //提示发修改的报还是原报
    qDebug()<<"metar context:"<<telegramContextStr;
    emit sendTelegramContext(telegramContextStr);
    return ;
}

void TelegramContextDealUI::metarComfirm()
{
    return ;
}

void TelegramContextDealUI::spacComfirm()
{
    return ;
}

void TelegramContextDealUI::initAllContrls()
{
    m_telegramContext  = new QTextEdit(this);
    Met_metarWaringInform  = new QTextEdit(this);
    Met_spacilWaringInform = new QTextEdit(this);
    return ;
}

void TelegramContextDealUI::setAllContrlsReadOnly()
{
    m_telegramContext->setReadOnly(true);
    Met_metarWaringInform->setReadOnly(true);
    Met_spacilWaringInform->setReadOnly(true);
    return ;
}

void TelegramContextDealUI::setAllContrlGeometry()
{
    m_telegramContext->setGeometry(6 + 80,8,width() * 4 / 5 - 92,height() / 2 - 14);
    Met_metarWaringInform->setGeometry(6,height() / 2 + 6,width() * 2 / 5 - 8,height() / 2 - 14);
    Met_spacilWaringInform->setGeometry(width() / 2,height() / 2 + 6,width() * 2 / 5 - 4 ,height() / 2 - 14);
    return ;
}

void TelegramContextDealUI::setAllContrlsValue()
{
    return ;
}
