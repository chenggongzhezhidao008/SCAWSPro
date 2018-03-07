#-------------------------------------------------
#.57128
# Project created by QtCreator 2017-02-08T11:35:58
# 5074
#-------------------------------------------------

QT  += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AwosWorkstation
TEMPLATE = app

SOURCES += main.cpp\
    UiSensorRvr/rvrsensoruot.cpp \
    UISensorHumid/humidsensorout.cpp \
    UiSensorWind/MeterDrawingFunctions.cpp \
    UiSensorWind/windmeter.cpp \
    UiSensorRunWay/runway.cpp \
    UiSensorRunWay/runwayfunction.cpp \
    UiSensorRvr/rvrsensoroutfunction.cpp \
    UISensorTemp/tempsensorshow.cpp \
    UISensorTemp/tempsensorfunction.cpp \
    UISensorHumid/humiditysensorfunction.cpp \
    Communicate/rvr_zmq_worker.cpp \
    DataParse/messageparse.cpp \
    UiSensorWind/MeterMoveFunction.cpp \
    UISensorTemp/TempSensorMoveFunction.cpp \
    UISensorHumid/HumSensorMoveFunction.cpp \
    UiSensorRvr/RVRsensorOutMoveFunction.cpp \
    UiSensorRunWay/RunWayMoveFunction.cpp \
    UIOtherCom/hidepushbutton.cpp \
    AwosConfig/prodata.cpp \
    Awosstartsetupfunction.cpp \
    UiStateLabel/statelabel.cpp \
    UITestLabel/textlabel.cpp \
    sqlDatabase/databaseoption.cpp \
    sqlDatabase/rvr_data_due.cpp \
    sqlDatabase/rvr_database_sqllite.cpp \
    DataCombination/messagecombinate.cpp \
    UIWaveLine/waveline.cpp \
    UIWaveLine/drawFunction.cpp \
    UIWaveLine/waveLineMovefunction.cpp \
    DataSend/messagesend.cpp \
    DataSend/windMessageDue.cpp \
    DataSend/HumiTempMessageDue.cpp \
    DataSend/RainMessageDue.cpp \
    DataSend/CloudMessageDue.cpp \
    DataSend/VISMessageDue.cpp \
    DataSend/Unit3616MessageDue.cpp \
    DataSend/pressMessageDue.cpp \
    AwosAdmin/awosadmin.cpp \
    AwosModelSacn/awosmodelsan.cpp \
    AwosSensorScan/awossensorscan.cpp \
    awoscomm.cpp \
#    awosmainfram.cpp \
#    awosmainfunction.cpp \
#    awosmainpainter.cpp \
    awosstartsetup.cpp \
    awosworkstationmin.cpp \
    awosWorkStationMinPainter.cpp \
    awosWorkStationMinFounctions.cpp \
    windRoseArea/windrosearea.cpp \
    windRoseArea/windRoseAreaPainter.cpp \
    windRoseArea/runwaydataarea.cpp \
    windRoseArea/runWayDataAreaPainter.cpp \
    UISensorClold/awossensorcloud.cpp \
    UISensorClold/CloudPianter.cpp \
    deveices/deveicestatecontrol.cpp \
    atcContrls/atcrosecontrl.cpp \
    atcContrls/atcrunwaycontrl.cpp \
    atcContrls/atcreport.cpp \
    atcContrls/atcmain.cpp \
    AFTN/telegramcfg.cpp \
    AFTN/telegramcfgPainter.cpp \
#    deveices/informationcfg.cpp \ #abandon 2017.8.29
#    deveices/informatiomcfgpainter.cpp \ #abandon 2017.8.29
#    deveices/subruncfg.cpp \  #abandon 2017.8.29
#    deveices/subtestcfg.cpp \  #abandon 2017.8.29
    atcContrls/atcmainwindrose.cpp \
    atcContrls/atcmainsublineshowcom.cpp \
    atcContrls/atcmainack.cpp \
    AFTN/aftnhurdle.cpp \
#    deveices/testcom_inputvalue.cpp \   #abandon 2017.8.29
    deveices/installcom_airportcfg.cpp \
    deveices/installcom_sensorcfg.cpp \
    deveices/installcom_unit3616cfg.cpp \
#    deveices/glablecom_inforshow.cpp \  #abandon 2017.8.29
    deveices/glablecom_selectbutton.cpp \
    deveices/glablecom_handinfor.cpp \
    AFTN/awosCodec.cpp \
    deveices/installcom_testportcfg.cpp \
    IpEdit/ip36edit.cpp \
    deveices/installcfg.cpp \
    AFFIX9Message/affix9mesage.cpp \
    AFFIX9Message/affix9addsensor.cpp \
    AFFIX9Message/affix9communicateset.cpp \
    distanceTransfer/cdmatransport.cpp \
    distanceTransfer/setupthread.cpp \
    deveices/datalog.cpp \
    deveices/deveicestate.cpp \
    deveices/waring.cpp \
    telegram/realtimedata.cpp \
    telegram/realTimeDataDraw.cpp \
    telegram/telectx.cpp \
    telegram/telectxDraw.cpp \
    telegram/telepopfram.cpp \
    telegram/telesubdatamoddraw.cpp \
    telegram/telesubdatamod.cpp \
    waring/userwaring.cpp \
    UIPress/press.cpp \
    UIWeather/weather.cpp \
    part6TeleCodes/telegramcodes.cpp \
    UIForCaster/forcastertrend.cpp \
    UIForCaster/trendUi.cpp \
    UIForCaster/trendUIDraw.cpp \
    AwosAdmin/usermanager.cpp \
    AwosAdmin/adminDraw.cpp \
    AFFIX9Message/affix9addoutsensor.cpp \
    UIMainWar/waringshow.cpp \
    UIMainWar/inforCtx.cpp \
    systemLog/loginforCtx.cpp \
    systemLog/logshow.cpp \
    telegram/teleconfig.cpp \
    telegram/telecfgsubcom.cpp \
    rvrConfg/rvrcfg.cpp \
    locaConfig/workestationcfg.cpp \
    locaConfig/runwaycfg.cpp \
    systemWaring/waringlog.cpp \
    systemWaring/waringloginforCtx.cpp \
    deveices/devicesketchmap.cpp \
    UI3616/ui_power.cpp \
    UI3616/ui_network.cpp \
    UI3616/ui_sensorcard.cpp \
    UI3616/dealcenter3616.cpp

HEADERS  += awosstartsetup.h \
    awoscomm.h \
#   awosmainfram.h \
    UiSensorRvr/rvrsensoruot.h \
    UISensorHumid/humidsensorout.h \
    UiSensorWind/windmeter.h \
    UiSensorRunWay/runway.h \
    UISensorTemp/tempsensorshow.h \
    Communicate/rvr_zmq_worker.h \
    DataParse/messageparse.h \
    UIOtherCom/hidepushbutton.h \
    AwosConfig/prodata.h \
    UiStateLabel/statelabel.h \
    UITestLabel/textlabel.h \
    sqlDatabase/databaseoption.h \
    sqlDatabase/rvr_data_due.h \
    sqlDatabase/rvr_database_sqllite.h \
    DataCombination/messagecombinate.h \
    UIWaveLine/waveline.h \
    DataSend/messagesend.h \
    AwosAdmin/awosadmin.h \
    AwosModelSacn/awosmodelsan.h \
    AwosSensorScan/awossensorscan.h \
    awosworkstationmin.h \
    windRoseArea/windrosearea.h \
    windRoseArea/runwaydataarea.h \
    UISensorClold/awossensorcloud.h \
    atcContrls/atcrosecontrl.h \
    atcContrls/atcrunwaycontrl.h \
    atcContrls/atcreport.h \
    atcContrls/atcmain.h \
    AFTN/telegramcfg.h \
#    deveices/informationcfg.h \#abandon 2017.8.29
#    deveices/subruncfg.h \ #abandon 2017.8.29
#    deveices/subtestcfg.h \ #abandon 2017.8.29
    atcContrls/atcmainwindrose.h \
    atcContrls/atcmainsublineshowcom.h \
    atcContrls/atcmainack.h \
    AFTN/aftnhurdle.h \
#    deveices/testcom_inputvalue.h \ #abandon 2017.8.29
    deveices/installcom_airportcfg.h \
    deveices/installcom_sensorcfg.h \
    deveices/installcom_unit3616cfg.h \
#    deveices/glablecom_inforshow.h \ #abandon 2017.8.29
    deveices/glablecom_selectbutton.h \
    deveices/glablecom_handinfor.h \
    deveices/installcom_testportcfg.h \
    deveices/deveicestate.h \
    IpEdit/ip36edit.h \
    deveices/installcfg.h \
    AFFIX9Message/affix9mesage.h \
    AFFIX9Message/affix9communicateset.h \
    AFFIX9Message/affix9addsensor.h \
    distanceTransfer/cdmatransport.h \
    distanceTransfer/setupthread.h \
    deveices/datalog.h \
    deveices/waring.h \
    telegram/realtimedata.h \
    telegram/telectx.h \
    telegram/telepopfram.h \
    telegram/telesubdatamod.h \
    waring/userwaring.h \
    UIPress/press.h \
    UIWeather/weather.h \
    part6TeleCodes/telegramcodes.h \
    UIForCaster/forcastertrend.h \
    UIForCaster/trendUI.h \
    AwosAdmin/usermanager.h \
    AFFIX9Message/affix9addoutsensor.h \
    UIMainWar/waringshow.h \
    UIMainWar/inforCtx.h \
    systemLog/loginforCtx.h \
    systemLog/logshow.h \
    telegram/teleconfig.h \
    telegram/telecfgsubcom.h \
    rvrConfg/rvrcfg.h \
    locaConfig/workestationcfg.h \
    locaConfig/runwaycfg.h \
    systemWaring/waringlog.h \
    systemWaring/waringloginforCtx.h \
    deveices/devicesketchmap.h \
    UI3616/ui_power.h \
    UI3616/ui_network.h \
    UI3616/ui_sensorcard.h \
    UI3616/dealcenter3616.h

FORMS    += \
    workstation.ui
#    awosmainfram.ui

#INCLUDEPATH += E:\ZeroMQx86\include

#LIBS += E:\ZeroMQx86\lib\libzmq-v90-mt-4_0_4.lib



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../ZeroMQx86/lib/ -llibzmq-v90-mt-4_0_4
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../ZeroMQx86/lib/ -llibzmq-v90-mt-4_0_4d
else:unix: LIBS += -L$$PWD/../../ZeroMQx86/lib/ -llibzmq-v90-mt-4_0_4

INCLUDEPATH += $$PWD/../../ZeroMQx86/include
DEPENDPATH += $$PWD/../../ZeroMQx86/include

RC_FILE += res.rc

OTHER_FILES +=

