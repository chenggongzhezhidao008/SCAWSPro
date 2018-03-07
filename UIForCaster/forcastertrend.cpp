#include "forcastertrend.h"

ForCasterTrend::ForCasterTrend(QWidget *parent) :
    QWidget(parent)
{
    inittren();
    initBoxOption();
    initTrend();
    initButton();
    initXY();
    updateSize();
    m_ctx = "";
}

void ForCasterTrend::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    if(x != width() || y != height()){
        x = width();
        y = height();
        updateSize();
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate(width()/2,height()/2);
    painter.save();
    painter.restore();
}

void ForCasterTrend::setNoTrendMetarCtx(QString Str)
{
    trend->setMetarCtx(Str);
}

void ForCasterTrend::auto_updateCtxSlot(QString str)
{
    updateCtxSlot();
}
void ForCasterTrend::updateCtxSlot()
{
  m_ctx = selectBox->currentText();
  m_ctx = m_ctx + "=";
  if(m_ctx != "NOSIG="){
      m_ctx = m_ctx + trendEidt->text().trimmed();
  }
  trend->setTrendCtx(m_ctx);
}

void ForCasterTrend::sendTrendSlot()
{
    emit sendMetarTrend("forCaster:SendTrend>"+ m_ctx);
}

void ForCasterTrend::inittren()
{
    trend = new TrendUI(this);
}

void ForCasterTrend::updateSize()
{
    trend->setGeometry(20,0,width()-80,height()-80);
    selectBox->setGeometry(24,height()- 70,120,20);
    trendEidt->setGeometry(154,height()- 70,width() - 230,20);
    update->setGeometry(width() - 280,height()- 40,100,30);
    send->setGeometry(width() - 176,height()- 40,100,30);
}

void ForCasterTrend::initXY()
{
    x = 0;
    y = 0;
}

void ForCasterTrend::initBoxOption()
{
    selectBox = new QComboBox(this);
    list.push_back("NOSIG");
    list.push_back("BECMG");
    list.push_back("TEMPO");
    selectBox->addItems(list);
}

void ForCasterTrend::initTrend()
{
    trendEidt = new QLineEdit(this);
    connect(trendEidt,SIGNAL(textChanged(QString)),
            SLOT(auto_updateCtxSlot(QString)));
}

void ForCasterTrend::initButton()
{
    update = new QPushButton(this);
    send = new QPushButton(this);
    connect(update,SIGNAL(clicked())
            ,SLOT(updateCtxSlot()));
    connect(send,SIGNAL(clicked())
            ,SLOT(sendTrendSlot()));
    update->setText("更新趋势");
    send->setText("发送趋势报");
}
