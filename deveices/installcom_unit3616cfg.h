#ifndef INSTALLCOM_UNIT3616CFG_H
#define INSTALLCOM_UNIT3616CFG_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QScrollArea>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>

#include "deveices/glablecom_handinfor.h"
#include "deveices/glablecom_selectbutton.h"

typedef QMap<QString,QString> DataMap;
typedef QMap<QString,DataMap> SensorMap;
typedef QMap<int,QString> InforMap;
typedef QString InforName;
typedef QString InforCtx;
typedef QMap<InforName,InforCtx> InforData;


class Unit3616CFGCom : public QWidget
{
    Q_OBJECT
     Q_PROPERTY(QString idAirportId READ idAirportId WRITE setIdAirportId NOTIFY idAirportIdChanged)

public:
    explicit Unit3616CFGCom(QWidget *parent = 0);
    QString idAirportId() const;

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

signals:
    void idAirportIdChanged();
    void MenuOptionSlot(QString option);

public slots:
    void setIdAirportId(QString value);

    //3616 自身配置文档V10.
    void Configure3616Slot(SensorMap senMap);
    void sensorStatusSlot(SensorMap senMap);
    void sensorLIBsSlot(SensorMap senMap);
    void serialCardParamersSlot(SensorMap senMap);

    // Affix 9 返回的数据
     void AFFIX9NewMessageSendUp(QString dCtx,InforData data);

private slots:

private:
    QString m_idAairportId;
    void initIdAairportId();

    int infor36Rows;
    int lib36Rows;
    int statue36Rows;
    int cardParameter36Rows;
    void initRowsValue();

    InforMap m_infor36Map;
    InforMap m_lib36Map;
    InforMap m_statue36Map;
    InforMap m_cardParam36Map;
    QString communiteDeal(QString option,int index);

    glableHandInfor *infor36;
    glableHandInfor *lib36;
    glableHandInfor *statue36;
    glableHandInfor *cardParameter36;
    void initInforCom();
    void setHandInforGeomerty();
    void initCustomMenus();
    void initMenuDealsConnection();

    QScrollArea  *ScrollAreaInfor36;
    QScrollArea  *ScrollAreacardParameter36;
    QScrollArea  *ScrollAreastatue36;
    QScrollArea  *ScrollArealib36;
    void initScrollArea();
    void addSubWidget();
    void setInforComGeometry();

    GlableSelectButton *Up36Infor;
    GlableSelectButton *Up36Lib;
    GlableSelectButton *Up36Statue;
    GlableSelectButton *Up36CardParameter;
    void initButton();
    void setButtonGeometry();

    int comWidth;
    int comHeight;
    void initsizeValue();
};

#endif // INSTALLCOM_UNIT3616CFG_H
