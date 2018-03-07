#include "informationcfg.h"

InformationCFG::InformationCFG(QWidget *parent) :
    QWidget(parent)
{
    initBoolvalue();
    initsetVlues();
    initButtonOption();

    initInstallCom();
    initshowInstallBool();
    setInstallComGeomerty();
    init36selfCfgConnection();
    initAirPortCFGBackConnections();

    initRunCom();
    initShowRunBool();
    setRunComGeomerty();

    initTestCom();
    initShowTestBool();
    setTestGeometry();
    initTestCFGInforBackConnections();

    initSubSize();
    initIndex();
}
void InformationCFG::initBoolvalue()
{
    setInstallDeveice = false;
    setRun = false;
    setAirPort = false;
}

void InformationCFG::initsetVlues()
{
    set[1] = true;
    set[2] = false;
    set[3] = false;
}

void InformationCFG::initIndex()
{
    memeryIndex = 1;
}

void InformationCFG::selectVlues(int count,int index)
{
    Q_UNUSED(count)
    if(memeryIndex == index){
        return ;
    }
    set[memeryIndex] = false;
    set[index] = true;
    memeryIndex = index;
    return ;
}

void InformationCFG::initButtonOption()
{
    buttonRelease = false;
}

void InformationCFG::initInstallCom()
{
   installCom = new SubInstallCFG(this);
   installCom->hide();
}

void InformationCFG::setInstallComGeomerty()
{
    installCom->setGeometry(2,32,width()- 4,height() - 34);
}

void InformationCFG::initshowInstallBool()
{
    showInstallBool = false;
}

void InformationCFG::showOrcloseInstallCom(bool show)
{
//    qDebug()<<"receive: Test Com";
    if(showInstallBool != show){
        showInstallBool = show;
    }
    else{
        return;
    }
    if(show){
        installCom->show();
    }
    else{
        installCom->hide();
    }
}

void InformationCFG::init36selfCfgConnection()
{
    if(installCom){
        connect(this,SIGNAL(Configure3616Signal(SensorMap)),installCom,SIGNAL(Configure3616Signal(SensorMap)));
        connect(this,SIGNAL(sensorStatusSignal(SensorMap)),installCom,SIGNAL(sensorStatusSignal(SensorMap)));
        connect(this,SIGNAL(sensorLIBsSignal(SensorMap)),installCom,SIGNAL(sensorLIBsSignal(SensorMap)));
        connect(this,SIGNAL(serialCardParamersSignal(SensorMap)),installCom,SIGNAL(serialCardParamersSignal(SensorMap)));
    }
}

void InformationCFG::initAirPortCFGBackConnections()
{
    if(installCom){
        connect(this,SIGNAL(backAirInfo(SensorMap)),installCom,SIGNAL(backAirInfoSignal(SensorMap)));
        connect(this,SIGNAL(backRunwayInfo(SensorMap)),installCom,SIGNAL(backRunwayInfoSignal(SensorMap)));
        connect(this,SIGNAL(backMatchInfo(SensorMap)),installCom,SIGNAL(backMatchInfoSignal(SensorMap)));
    }
}

void InformationCFG::initRunCom()
{
   runCom = new SubRunCFG(this);
   runCom->hide();
}

void InformationCFG::setRunComGeomerty()
{
    runCom->setGeometry(2,32,width()- 4,height() - 34);
}

void InformationCFG::initShowRunBool()
{
    showRunBool = false;
}

void InformationCFG::showOrcloseRunCom(bool show)
{
//    qDebug()<<"receive: Test Com";
    if(showRunBool != show){
        showRunBool = show;
    }
    else{
        return;
    }
    if(show){
        runCom->show();
    }
    else{
        runCom->hide();
    }
}

void InformationCFG::initTestCom()
{
    testCom = new subTestCfg(this);
    testCom->hide();
}

void InformationCFG::setTestGeometry()
{
    testCom->setGeometry(2,32,width()- 4,height() - 34);
}

void InformationCFG::initShowTestBool()
{
    showTestBool = false;
}

void InformationCFG::showOrcloseTestCom(bool show)
{
//    qDebug()<<"receive: Test Com";
    if(showTestBool != show){
        showTestBool = show;
    }
    else{
        return;
    }
    if(show){
        testCom->show();
    }
    else{
        testCom->hide();
    }
}

void InformationCFG::initTestCFGInforBackConnections()
{
    if(testCom){
        connect(this,SIGNAL(backAirInfo(SensorMap)),testCom,SLOT(backAirInfoSlot(SensorMap)));
        connect(this,SIGNAL(backRunwayInfo(SensorMap)),testCom,SLOT(backRunwayInfoSlot(SensorMap)));
        connect(this,SIGNAL(backMatchInfo(SensorMap)),testCom,SLOT(backMatchInfoSlot(SensorMap)));
    }
}

void InformationCFG::initSubSize()
{
    subWidth = 0;
    subHeight = 0;
}
