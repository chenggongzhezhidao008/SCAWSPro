#ifndef ATCREPORT_H
#define ATCREPORT_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QEvent>
#include <QMouseEvent>
#include <QLineEdit>
#include <QTextEdit>
#include <QStringList>


class ATCREPORT : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString metReportCtx READ getmetReportCtx WRITE setMetReportCtx NOTIFY metReportCtxChanged)

public:
    explicit ATCREPORT(QWidget *parent = 0);
    QString getmetReportCtx() const { return this->m_reportCtx;}
    void setShowOutGeometry();

protected:
    void paintEvent(QPaintEvent *event);

    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void metReportCtxChanged();

public slots:
    void setMetReportCtx(QString metReportCtx);

private:
    QString m_reportCtx;
    QLineEdit *m_WIND_edit;
    QLineEdit *m_VIS_edit;
    QLineEdit *m_RVR_edit;
    QLineEdit *m_W_W_edit;
    QLineEdit *m_CLOUD_edit;
    QLineEdit *m_TA_TD_edit;
    QLineEdit *m_QNH_edit;
    QLineEdit *m_QFE_edit;
    QLineEdit *m_SUPP_INFO_edit;
    QLineEdit *m_REw_w_edit;
    QLineEdit *m_TREND_edit;
    QLineEdit *m_RMK_edit;
    QTextEdit *m_LAST_LOCAL_REPORT_edit;
    void initShowOutContrls();
    void setShowOutCtx();
    void contrlsSetReadOnly();
    void installEdit();

    QStringList titleList;
    void setLabelTitles();

};

#endif // ATCREPORT_H
