#include "atcreport.h"

ATCREPORT::ATCREPORT(QWidget *parent) :
    QWidget(parent)
{
    initShowOutContrls();
    setShowOutCtx();
    setLabelTitles();
    contrlsSetReadOnly();
    installEdit();
}

void ATCREPORT::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    int left = - width() / 2;
    int top  = - height() / 2;
    int uiWidth = width() ;
    int uiHeight = height() ;
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.translate( width() / 2,height() / 2);
    painter.save();
    painter.setPen(QPen(QColor("#889999"),2));
    painter.setBrush(Qt::gray);
    painter.drawRect(left,top,uiWidth,uiHeight);
    painter.restore();

    painter.save();
    int widthCtl = width() / 5;
    int heightCtl = (height() * 2 / 3 - 40) / 12;

    if(!titleList.isEmpty()){
        for(int i = 0;i < titleList.length() - 1;i++){
            painter.drawText(left + 20 + 40,top + 40 + heightCtl * i,widthCtl - 40,heightCtl - 8,
                             Qt::AlignVCenter | Qt::AlignLeft,titleList.value(i).trimmed());
        }
    }
     painter.drawText(left + 20 + 40,top + height() * 5 / 6,widthCtl - 40,heightCtl - 8,
                      Qt::AlignVCenter | Qt::AlignLeft,titleList.value(titleList.length() - 1).trimmed());
     painter.restore();
}

bool ATCREPORT::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove
            || event->type() == QEvent::HoverEnter || event->type() == QEvent::HoverLeave
            || event->type() == QEvent::HoverMove ) {
        event->accept();
        return true;
    }
    else{
        return QWidget::eventFilter(obj, event);
    }
}

void ATCREPORT::setMetReportCtx(QString metReportCtx)
{
    this->m_reportCtx.clear();
    this->m_reportCtx = metReportCtx;
    update();
}

void ATCREPORT::initShowOutContrls()
{
    m_WIND_edit = new QLineEdit(this);
    m_VIS_edit= new QLineEdit(this);
    m_RVR_edit= new QLineEdit(this);
    m_W_W_edit= new QLineEdit(this);
    m_CLOUD_edit= new QLineEdit(this);
    m_TA_TD_edit= new QLineEdit(this);
    m_QNH_edit= new QLineEdit(this);
    m_QFE_edit= new QLineEdit(this);
    m_SUPP_INFO_edit= new QLineEdit(this);
    m_REw_w_edit= new QLineEdit(this);
    m_TREND_edit= new QLineEdit(this);
    m_RMK_edit= new QLineEdit(this);
    m_LAST_LOCAL_REPORT_edit= new QTextEdit(this);
}

void ATCREPORT::setShowOutGeometry()
{
    int left = this->width() / 5;
    int top  = 40;
    int widthCtl = width() * 3 / 5;
    int heightCtl = (height() * 2 / 3 - 40) / 12;

    m_WIND_edit->setGeometry(left,top + heightCtl * 0,widthCtl,heightCtl - 8);
    m_VIS_edit->setGeometry(left,top + heightCtl * 1,widthCtl,heightCtl - 8);
    m_RVR_edit->setGeometry(left,top + heightCtl * 2,widthCtl,heightCtl - 8);
    m_W_W_edit->setGeometry(left,top + heightCtl * 3,widthCtl,heightCtl - 8);
    m_CLOUD_edit->setGeometry(left,top + heightCtl * 4,widthCtl,heightCtl - 8);
    m_TA_TD_edit->setGeometry(left,top + heightCtl * 5,widthCtl,heightCtl - 8);
    m_QNH_edit->setGeometry(left,top + heightCtl * 6,widthCtl,heightCtl - 8);
    m_QFE_edit->setGeometry(left,top + heightCtl * 7,widthCtl,heightCtl - 8);
    m_SUPP_INFO_edit->setGeometry(left,top + heightCtl * 8,widthCtl,heightCtl - 8);
    m_REw_w_edit->setGeometry(left,top + heightCtl * 9,widthCtl,heightCtl - 8);
    m_TREND_edit->setGeometry(left,top + heightCtl * 10,widthCtl,heightCtl - 8);
    m_RMK_edit->setGeometry(left,top + heightCtl * 11,widthCtl,heightCtl - 8);
    m_LAST_LOCAL_REPORT_edit->setGeometry(left * 2.8 / 3,height() * 2 / 3, width() * 4 / 5 - 40,height() / 3 - 10);
}

void ATCREPORT::setShowOutCtx()
{
    m_WIND_edit->setText("value");
    m_VIS_edit->setText("value");
    m_RVR_edit->setText("value");
    m_W_W_edit->setText("value");
    m_CLOUD_edit->setText("value");
    m_TA_TD_edit->setText("value");
    m_QNH_edit->setText("value");
    m_QFE_edit->setText("value");
    m_SUPP_INFO_edit->setText("value");
    m_REw_w_edit->setText("value");
    m_TREND_edit->setText("value");
    m_RMK_edit->setText("value");
    m_LAST_LOCAL_REPORT_edit->setText("met Report Context ...........");
}

void ATCREPORT::contrlsSetReadOnly()
{
    m_WIND_edit->setEnabled(false);
    m_VIS_edit->setEnabled(false);
    m_RVR_edit->setEnabled(false);
    m_W_W_edit->setEnabled(false);
    m_CLOUD_edit->setEnabled(false);
    m_TA_TD_edit->setEnabled(false);
    m_QNH_edit->setEnabled(false);
    m_QFE_edit->setEnabled(false);
    m_SUPP_INFO_edit->setEnabled(false);
    m_REw_w_edit->setEnabled(false);
    m_TREND_edit->setEnabled(false);
    m_RMK_edit->setEnabled(false);
    m_LAST_LOCAL_REPORT_edit->setEnabled(false);
}

void ATCREPORT::installEdit()
{
    m_WIND_edit->installEventFilter(this);
    m_VIS_edit->installEventFilter(this);
    m_RVR_edit->installEventFilter(this);
    m_W_W_edit->installEventFilter(this);
    m_CLOUD_edit->installEventFilter(this);
    m_TA_TD_edit->installEventFilter(this);
    m_QNH_edit->installEventFilter(this);
    m_QFE_edit->installEventFilter(this);
    m_SUPP_INFO_edit->installEventFilter(this);
    m_REw_w_edit->installEventFilter(this);
    m_TREND_edit->installEventFilter(this);
    m_RMK_edit->installEventFilter(this);
    m_LAST_LOCAL_REPORT_edit->installEventFilter(this);
}

void ATCREPORT::setLabelTitles()
{
    titleList.push_back("WIND");
    titleList.push_back("VIS");
    titleList.push_back("RVR");
    titleList.push_back("W＇W＇");
    titleList.push_back("CLOUD");
    titleList.push_back("TA/TD");
    titleList.push_back("QNH");
    titleList.push_back("QFE");
    titleList.push_back("SUPP.INFO");
    titleList.push_back("REw＇w＇");
    titleList.push_back("TREND");
    titleList.push_back("RMK");
    titleList.push_back("LAST LOCAL REPORT");
}

