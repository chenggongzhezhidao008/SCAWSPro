#include "telepopfram.h"

TelegramPop::TelegramPop(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("电报提示");
    m_sendTelegram = false;
    m_updateTelegram = false;
    m_releaseDo = false;
    updateBool = true;
    initCotextEdit();
    initNameList();
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

QString TelegramPop::removeFeild(QString str)
{
    QString tempStr = str;
    tempStr = tempStr.replace(":"," ");
    tempStr = tempStr.replace(";","");
    return tempStr;
}

void TelegramPop::updateTelegramContextStr()
{
    QString metarStr = "METAR  ";
    int number = m_telegramCtx.count();
    int step = 0;
    for(int num = 1; num <= number; num++)
    {
        if(m_telegramCtx[num].trimmed() == "")
        {
            continue;
        }
        if(num == number)
        {
            metarStr = metarStr + removeFeild(m_telegramCtx[num]);
        }
        else{
            metarStr = metarStr + removeFeild(m_telegramCtx[num]) + "  ";
            if(step % 8 == 0)
            {
                metarStr = metarStr + "\n" ;
            }
        }
        step ++;
    }
    ContextEdit->setText(metarStr);
}
void TelegramPop::setCtxMap(TelegramCtx ctx)
{
    m_ctx.clear();
    m_ctx = ctx;
    // 接入标题数据
//    this->m_NameList.clear();
    this->m_telegramCtx.clear();
    if(this->telegramContextList.count() > 0){
        for (int i = 0; i < telegramContextList.count(); ++i) {
            delete telegramContextList.value(i);
        }
    }
    this->telegramContextList.clear();
    if(this->telegramNameUpdateList.count() > 0){
        for (int i = 0; i < telegramNameUpdateList.count(); ++i) {
            delete telegramNameUpdateList.value(i);
        }
    }
    this->telegramNameUpdateList.clear();
    this->m_telegramCtx = ctx;
    int length = this->m_telegramCtx.count();
    int rowIndex,columuIdex;
    int cellWidth = (width() - 5) / 3 - 5;
    int cellheight = (height() - 5 - 32) / 5 - 2;
    int sizeWidth = (width() - 5) / 3;
    int sizeHeight = (height() - 5 - 32) / 5;
    for(int i = 0; i < length;i++){
        QLineEdit *lineEdit = new QLineEdit(this);
        QLineEdit *nameEdit = new QLineEdit(this);
        rowIndex = i / 3;
        columuIdex = i % 3;
        nameEdit->setGeometry(5 + sizeWidth * columuIdex,5 + sizeHeight * rowIndex,
                              60,cellheight);
        nameEdit->setText(m_NameList.value(i + 1));
        nameEdit->setReadOnly(true);
        nameEdit->hide();
        telegramNameUpdateList.push_back(nameEdit);
        lineEdit->setGeometry(5 + sizeWidth * columuIdex + 62,5 + sizeHeight * rowIndex,
                              cellWidth - 62,cellheight);
        lineEdit->setText(m_telegramCtx[i + 1]);
        lineEdit->setObjectName(QString("%1").arg(i+1)/*m_NameList.value(i + 1)*/);
        lineEdit->hide();
        telegramContextList.push_back(lineEdit);
    }
    ContextEdit->setGeometry(5,5,width()- 10,height()- 37);
    updateTelegramContextStr();
}

void TelegramPop::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    int popWidth = width();
    int popHeight = height();
    if(widthSize != popWidth || heightSize != popHeight){
        updateSize();
        widthSize = popWidth;
        heightSize = popHeight;
    }
    int left = - popWidth / 2;
    int top = - popHeight / 2;
    int buttom = popHeight / 2;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(popWidth / 2,popHeight / 2);

    painter.save();
    painter.setPen(QPen(Qt::gray,3));
    painter.setBrush(QColor("#D9D9D9"));
    painter.drawRect(left + 2,top + 2,popWidth - 4,popHeight - 4);

    QPoint startPos(0,buttom - 32);
    QPoint endPos(0,buttom - 2);
    QLinearGradient startGrad(startPos,endPos);
    startGrad.setColorAt(0,QColor("#4A708B"));
    startGrad.setColorAt(1,QColor("#00688B"));
    QLinearGradient endGrad(startPos,endPos);
    endGrad.setColorAt(0,QColor("#4A708B"));
    endGrad.setColorAt(1,QColor("#5A988B"));
    if(!m_updateTelegram){
        painter.setBrush(startGrad);
    }
    else{
        painter.setBrush(endGrad);
    }
    painter.drawRoundRect(left + 2,buttom - 32,popWidth / 2 - 2 - 1,30,5,5);

    if(!m_sendTelegram){
        painter.setBrush(startGrad);
    }
    else{
        painter.setBrush(endGrad);
    }
    painter.drawRoundRect(1,buttom - 32,popWidth / 2 - 2 - 1,30,5,5);

    painter.setPen(QPen(Qt::white,3));
    QString optionStr;
    if(updateBool){
        optionStr = "修改电报";
    }else{
        optionStr = "确认修改";
    }
    painter.drawText(left + 2,buttom - 32,popWidth / 2 - 2 - 1,30,Qt::AlignCenter,optionStr);
    painter.drawText(1,buttom - 32,popWidth / 2 - 2 - 1,30,Qt::AlignCenter,"发送电报");
    painter.restore();
}

void TelegramPop::mousePressEvent(QMouseEvent *e)
{
    bool flag = false;
    if(e->button() == Qt::LeftButton){
        int posY = e->pos().y();
        int posX = e->pos().x();
        int widtH = this->width();
        int heighT = this->height();

        if(posX > 2 && posX < (widtH / 2 - 1)
                && posY > (heighT - 32) && posY < (heighT - 2)){
            m_updateTelegram = true;
            modifypopTelegram();
            m_releaseDo = true;
            flag = true;
        }

        else if(posX > (widtH / 2 + 1)&& posX < widtH - 2
                && posY > (heighT - 32) && posY < (heighT - 2)){
            m_sendTelegram = true;
            sendpopTelegram();
            m_releaseDo = true;
            flag = true;
        }
    }
    if(flag){
        update();
    }
}

void TelegramPop::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    if(m_sendTelegram){
        m_sendTelegram = false;
    }
    if(m_updateTelegram){
        m_updateTelegram = false;
    }
    if(m_releaseDo){
        update();
        m_releaseDo = false;
    }
}

void TelegramPop::updateSize()
{
    int rowIndex,columuIdex;
    int cellWidth = (width() - 5) / 3 - 5;
    int cellheight = (height() - 5 - 32) / 5 - 2;
    int sizeWidth = (width() - 5) / 3;
    int sizeHeight = (height() - 5 - 32) / 5;
    int len = telegramNameUpdateList.length();
    for(int i = 0; i < len;i++){
        rowIndex = i / 3;
        columuIdex = i % 3;
        telegramNameUpdateList.value(i)->setGeometry(5 + sizeWidth * columuIdex,5 + sizeHeight * rowIndex,
                              60,cellheight);
    }
    len = telegramContextList.length();
    for(int f = 0; f < len;f++){
        rowIndex = f / 3;
        columuIdex = f % 3;
        telegramContextList.value(f)->setGeometry(5 + sizeWidth * columuIdex + 62,5 + sizeHeight * rowIndex,
                              cellWidth - 62,cellheight);
    }
    ContextEdit->setGeometry(5,5,width()- 10,height()- 37);
}

void TelegramPop::modifypopTelegram()
{
    // deal update telegram
    int len = telegramNameUpdateList.length();
    for(int i = 0; i < len;i++){
        if(updateBool){
            telegramNameUpdateList.value(i)->show();
        }
        else{
            telegramNameUpdateList.value(i)->hide();
        }
    }
    len = telegramContextList.length();
    for(int i = 0; i < len;i++){
        if(updateBool){
            telegramContextList.value(i)->show();
        }
        else{
            telegramContextList.value(i)->hide();
        }
    }

    dealChangCtx();
    updateTelegramContextStr();

    if(updateBool){
        ContextEdit->hide();
    }
    else{
        ContextEdit->show();
    }
    updateBool = !updateBool;
    update();
    return ;
}

void TelegramPop::sendpopTelegram()
{
    // deal send telegram
    emit popTelegramSendSignal(this->m_telegramCtx);
    return ;
}

void TelegramPop::dealChangCtx()
{
  TelegramCtx temp_telegramCtx;
  int len = telegramContextList.length();
  QString nameStr;
  for (int n = 0; n < len; n++){
      nameStr.clear();
      nameStr = telegramContextList.value(n)->objectName();
      temp_telegramCtx[nameStr.toInt()] = telegramContextList.value(n)->text().trimmed();
  }
  m_telegramCtx.clear();
  m_telegramCtx = temp_telegramCtx;
}

void TelegramPop::initNameList()
{
    m_NameList[1] = "报头";
    m_NameList[2] = "风";
    m_NameList[3] = "能见度";
    m_NameList[4] = "跑道视程";
    m_NameList[5] = "现在天气";
    m_NameList[6] = "云量云高";
    m_NameList[7] = "温湿度";
    m_NameList[8] = "修正海压";
    m_NameList[9] = "近时天气";
    m_NameList[10] = "道面状况";
    m_NameList[11] = "趋势报";
    m_NameList[12] = "备注";
}

void TelegramPop::initCotextEdit()
{
    ContextEdit = new QTextEdit(this);
    ContextEdit->setGeometry(5,5,width()- 10,height()- 37);
    ContextEdit->setReadOnly(true);
    ContextEdit->show();
}
