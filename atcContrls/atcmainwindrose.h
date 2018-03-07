#ifndef ATCMAINWINDROSE_H
#define ATCMAINWINDROSE_H
#include "UiSensorWind/windmeter.h"
#include "atcContrls/atcmainsublineshowcom.h"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class ATCMainWindRose : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString runWayname READ getRunWayname WRITE setRunWayname NOTIFY runWaynameChanged)
    Q_PROPERTY(bool enableCloud READ getenableCloud WRITE setEnableCloud NOTIFY enableCloudChanged)

public:
    explicit ATCMainWindRose(QWidget *parent = 0);
    QString getRunWayname() const { return this->m_runWayStr; }
    bool getenableCloud() const { return this->m_enable;}

protected:
    void paintEvent(QPaintEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void runWaynameChanged();
    void enableCloudChanged();

public slots:
     void setRunWayname(QString name);
     void setEnableCloud(bool enable);
     void setData(QString value);

private:
    WindMeter * meter;
    void initRose();
    void installWindRose();
    void setRoseGeometry();

    atcMainSubLineShowCom *m_RVR;
    atcMainSubLineShowCom *m_VIS;
    atcMainSubLineShowCom *m_CLD;
    atcMainSubLineShowCom *m_GUST;
    void initLineContrls();
    void installLineContrl();
    void setLineGeometry();

    int sWidth;
    int sHeght;
    void initSizeValue();

    QString m_runWayStr;
    void initrunWayStrVlaue();

    bool m_enable;
    void initenable();
};

#endif // ATCMAINWINDROSE_H
