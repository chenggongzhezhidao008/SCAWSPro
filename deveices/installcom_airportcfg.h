#ifndef INSTALLCOM_AIRPORTCFG_H
#define INSTALLCOM_AIRPORTCFG_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QScrollArea>
#include "deveices/glablecom_handinfor.h"
#include "deveices/glablecom_selectbutton.h"
typedef QMap<QString,QString> DataMap;
typedef QMap<QString,DataMap> SensorMap;
typedef QMap<int,QString> InforMap;

class AirportCFGCom : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString idAirportId READ idAirportId WRITE setIdAirportId NOTIFY idAirportIdChanged)

public:
    explicit AirportCFGCom(QWidget *parent = 0);
    QString idAirportId() const;

protected:
    void paintEvent(QPaintEvent *e);

signals:
    void idAirportIdChanged();
    void MenuOptionSlot(QString option);

public slots:
    void setIdAirportId(QString value);

    //3616 自身配置文档V10.(根据合肥机场的信息调整的3616的配置)
    void backAirInfoSlot(SensorMap map);
    void backRunwayInfoSlot(SensorMap map);
    void backMatchInfoSlot(SensorMap map);

private slots:

private:
    QString m_idAairportId;
    void initIdAairportId();

    InforMap m_airpotMap;
    InforMap m_runwayMap;

    int inforAirportRows;
    int inforRunWayRows;
    void initRowsValue();

    glableHandInfor *inforAirport; // show airport datas lines UI
    glableHandInfor *inforRunWay; // show runway datas lines UI
    void initInforCom();
    void setHandInforGeomerty();
    void initCustomMenus();
    void initMenuDealsConnection();


    QScrollArea  *ScrollAreaAirport;
    QScrollArea  *ScrollAreaRunWay;
    void initScrollArea();
    void addSubWidget();
    void setInforComGeometry();

    GlableSelectButton *UpAirportInfor;
    GlableSelectButton *UpRunWayInfor;
    void initButton();
    void setButtonGeometry();

    int comWidth;
    int comHeight;
    void initsizeValue();
};

#endif // INSTALLCOM_AIRPORTCFG_H
