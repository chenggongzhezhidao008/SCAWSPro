/*******
 * ========= 设备配置部分 =======
 * 1.安装配置;
 * 2.运行配置;      此类已遗弃2017.8.29
 * 3.测试配置;
 * ========== end ==========
 ******/

#ifndef INFORMATIONCFG_H
#define INFORMATIONCFG_H

#include "deveices/subtestcfg.h"
#include "deveices/subinstallcfg.h"
#include "deveices/subruncfg.h"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

#include <QMouseEvent>
#include <QEvent>
#include <QMap>

typedef QMap<QString,QString> DataMap;
typedef QMap<QString,DataMap> SensorMap;

typedef QMap<int,bool> DeceiveSet;

class InformationCFG : public QWidget
{
    Q_OBJECT
public:
    explicit InformationCFG(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

signals:
    //3616 自身配置文档V10.(根据合肥机场的信息调整的3616的配置)
    void backAirInfo(SensorMap dataMap);
    void backRunwayInfo(SensorMap dataMap);
    void backMatchInfo(SensorMap dataMap);

    //3616 自身配置文档V10.
    void Configure3616Signal(SensorMap senMap);
    void sensorStatusSignal(SensorMap senMap);
    void sensorLIBsSignal(SensorMap senMap);
    void serialCardParamersSignal(SensorMap senMap);

public slots:

private:
    bool setInstallDeveice;
    bool setRun;
    bool setAirPort;
    void initBoolvalue();

    DeceiveSet set;
    void initsetVlues();
    int memeryIndex;
    void initIndex();
    void selectVlues(int count,int index);

    bool buttonRelease;
    void initButtonOption();

    // 1.install CFG
    SubInstallCFG *installCom;  //安装数据配置
    void initInstallCom();
    void setInstallComGeomerty();
    bool showInstallBool;
    void initshowInstallBool();
    void showOrcloseInstallCom(bool show);
    void init36selfCfgConnection();
    void initAirPortCFGBackConnections();

    // 2.RunTime CFG
    SubRunCFG *runCom;     //运行数据数据配置
    void initRunCom();
    void setRunComGeomerty();
    bool showRunBool;
    void initShowRunBool();
    void showOrcloseRunCom(bool show);

    // 3.test port CFG
    subTestCfg *testCom;   // 测试数据端口配置
    void initTestCom();
    void setTestGeometry();
    bool showTestBool;
    void initShowTestBool();
    void showOrcloseTestCom(bool show);
    void initTestCFGInforBackConnections();

    int subWidth;
    int subHeight;
    void initSubSize();
};

#endif // INFORMATIONCFG_H
