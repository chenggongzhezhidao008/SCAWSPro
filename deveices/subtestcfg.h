#ifndef SUBTESTCFG_H
#define SUBTESTCFG_H

#include "deveices/glablecom_inforshow.h"

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QComboBox>
#include <QMouseEvent>
#include "testcom_inputvalue.h"
#include <QMap>
#include <QStringList>
#include <QScrollArea>


typedef QMap<int,QString> InforMap;
typedef QMap<QString,QString> DataMap;
typedef QMap<QString,DataMap> SensorMap;

class subTestCfg : public QWidget
{
    Q_OBJECT

public:
    explicit subTestCfg(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
    void backAirInfoSlot(SensorMap map);
    void backRunwayInfoSlot(SensorMap map);
    void backMatchInfoSlot(SensorMap map);

private slots:

private:
    bool addAirpot;
    bool deleAirpot;
    bool modiAirpot;
    bool addRunWay;
    bool deleRunWay;
    bool modRunWay;
    bool addSensor;
    bool deleSensor;
    bool modSeneor;
    void initContrlBool();

    bool releaseBool;
    void initReleaseBool();

    InputValueCom *input;
    void initInputCom();
    void setInputValueComGeometry();
    void selectShowInformation(int classIndex);

    int parentWidth;
    int parentHeight;
    void initMemerySizeParent();

    QStringList m_airportList;
    void initairportList();
    QString m_airInfor;
    InforMap m_runwayInfor;
    InforMap m_matchInfor;

    int runWayNum;
    int matchNum;
    void initNumValue();

    QScrollArea *m_AirArea;
    QScrollArea *m_RunWayArea;
    QScrollArea *m_MatchArea;

    void initScrollAreaOBject();
    void setScrollGeometry();
    void setScrollMInHeightSize();
    void setScrollPolicy();


    GlableCom_InforShow *airWidget;
    GlableCom_InforShow *runwayWidget;
    GlableCom_InforShow *matchWidget;

    void initsubWidgets();
    void setsubWidgetsSize();
};

#endif // SUBTESTCFG_H
