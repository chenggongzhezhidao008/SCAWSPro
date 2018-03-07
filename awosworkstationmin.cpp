#include "awosworkstationmin.h"
#include "ui_workstation.h"
#include <QDebug>
#include <QList>
#include <QMenu>
#include <QCursor>
#include <QPushButton>
#include  "atcContrls/atcrosecontrl.h"
/*  ------------------------
 *  MVC 模式下的 control
 *  封装 用户各个业务操作类
 *  主要涉及界面切换，发报，系统配置的各个用户操作功能。
 *
 */
WorkStation::WorkStation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkStation)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background:#EEEEE0");
    setAwosSize(1300,740);
    m_fullScreen = false;
    oneSecondTimer = new QTimer(this);
    connect(oneSecondTimer,SIGNAL(timeout()),this,SLOT(oneSecondUpdate()));
    oneSecondTimer->start(1000);

    m_scaleUI = false;
    m_firstFunction = false;
    m_secondFunction = false;
    m_thirdFunction = false;
    m_fourFunction = false;
    m_fiveFunction = false;

    m_metOne = false;
    m_metTwo = false;
    m_metThree = false;
    m_metFour = false;
    m_metFive = false;

    m_metUpdate = false;
    m_cavokCheck = false;
    m_cavok = false;
    m_metModify = false;
    met_modifyFlag = false;
    m_metSend = false;
    m_metarComfire = false;
    m_spacilComfire = false;
    m_clickLastMetar = false;
    m_clickLastSpaci = false;
    m_spaciUpdate = false;
    m_spaciModify = false;
    m_spaciSend = false;
    spaci_modifyFlag = false;

    //dealSequence = -1;

    funcMap[1] = true;
    funcMap[2] = false;
    funcMap[3] = false;
    funcMap[4] = false;
    funcMap[5] = false;

    // ATC begin
    init_m_atcPage();
    initAtcMetarReport();
    setAtcMetarReportGeometry();
    initMetarReportBool();
    installMetReportEventFilter();
    initAtcMainObj();
    setAtcMainGeometry();
    initAtcMainBool();
    installAtcMainEventFilter();
    initAtcMainDataConnections();
    // ATC end


    // metar page select
    m_metar[1] = true;
    m_metar[2] = false;
    m_metar[3] = false;
    m_metar[4] = false;
    m_metar[5] = false;

    // config page select
    m_configPage[1] = true;
    m_configPage[2] = false;
    m_configPage[3] = false;
    m_configPage[4] = false;
    m_configPage[5] = false;

    releaseDo = false;///
    moveUI = true;

    // metar partment
    metarSenAddresses = new QLineEdit(this);
    spaciSenAddresses = new QLineEdit(this);
    _metar_Realdata_contrl =  new RealTimeData(this);
    _spaci_Realdata_contrl =  new RealTimeData(this);
    _metar_Report_Realdata_contrl = new RealTimeData(this);
    _spacial_Report_Realdata_contrl = new RealTimeData(this);
    MetarEcodecContrl = new teleSubDataModCtl(this);
    connect(this,SIGNAL(enbaleCavokCheck(bool))
            ,MetarEcodecContrl,SLOT(setEnableCavokSlot(bool)));
    SpaciEcodecContrl = new teleSubDataModCtl(this);
    MetarReportEcodecContrl = new teleSubDataModCtl(this);
    SpaciReportEcodecContrl = new teleSubDataModCtl(this);

    connect(metarSenAddresses,SIGNAL(textChanged(QString))
            ,SLOT(metarAddressesDeal(QString)));
    connect(spaciSenAddresses,SIGNAL(textChanged(QString))
            ,SLOT(spaciAddressesDeal(QString)));

    // metar partment
    MetarEcodecContrl->installEventFilter(this);
    metarSenAddresses->installEventFilter(this);

    // Metar Report partment
    MetarReportEcodecContrl->installEventFilter(this);

    // Spaci Report partment
    SpaciReportEcodecContrl->installEventFilter(this);

    // install real time data  events
    SpaciEcodecContrl->installEventFilter(this);
    spaciSenAddresses->installEventFilter(this);
    _metar_Realdata_contrl->installEventFilter(this);
    _spaci_Realdata_contrl->installEventFilter(this);
    _metar_Report_Realdata_contrl->installEventFilter(this);
    _spacial_Report_Realdata_contrl->installEventFilter(this);

    // set real time data only read
    metarClasses    = new QComboBox(this);
    spaciClasses    = new QComboBox(this);

    initAFTNCFG();
    setAFTNCFGGeomerty();
    initAFTNCFGSignalConnection();
    installAftnCFGEventFilter();

    initLocaCFG();
    setLocaCFGGeomerty();
    initLocaCFGSignalConnection();
    installLocaCFGEventFilter();

    metarContext  = new QTextEdit(this);
    spaciContext  = new QTextEdit(this);

    metarCtxConfirm = new QTextEdit(this);
    spaciCtxConfirm = new QTextEdit(this);
    Met_metarWaringInform = new QTextEdit(this);
    Met_spacilWaringInform = new QTextEdit(this);
    Spaci_metarWaringInform = new QTextEdit(this);
    Spaci_spacilWaringInform = new QTextEdit(this);
    MetarReportTelegramContextUI = new TelegramContextDealUI(this);
    MetarReportTelegramContextUI->setTelegramName("MetarReport");
    SpaciReportTelegramContextUI = new TelegramContextDealUI(this);
    SpaciReportTelegramContextUI->setTelegramName("Spacial");

    // telegram configs;
    _m_init_telegram_cfg();
    _m_set_telegram_cfg_geometry();

    // ********** DEVEICE *************
    initDeveiceSate();
    installDeveiceEventFilter();
    initInstallCFG();
    initLogObj();
    initWaringObj();

    installInstallFilter();
    installWaringEventFilter();
    installLogEventFilter();

    initMetar();
    connect(this,SIGNAL(waringShowSignal(QString,QString))
            ,SLOT(waringShowSlot(QString,QString)));

    // deceive config partment
    m_mserver = false;
    m_mCollect  = false;
    m_mServerConfig  = false;
    m_mCollectConfig  = false;
    m_mDataConfig  = false;
    m_mLocaConfig = false;

    // init telegram connections
    initTelegramOptionConnections();
    initQNFValue();//***
    _init_grade();
    _m_init_war_Value();

    // init locate config settings
    init_config_settings();
}

WorkStation::~WorkStation()
{
    delete ui;
}

void WorkStation::setAwosSize(int width, int height)
{
    this->setGeometry(160,6,width,height);
}

void WorkStation::mousePressEvent(QMouseEvent *e)
{
    bool flag = false;
    if(e->button() == Qt::LeftButton){// 判断鼠标事件的按钮名称
        // 标题栏按钮
        int posY = e->pos().y();
        int posX = e->pos().x();
        int widtH = this->width();

        // 隐藏
        if(posX > (widtH - 90)
                && posX < (widtH - 66)
                && posY > 3
                && posY < 27)
        {
            flag = true;
            this->showMinimized();
        }
        // 缩放
        else if(posX > (widtH - 60)
                && posX < (widtH - 36)
                && posY > 3
                && posY < 27)
        {
            flag = true;
            m_scaleUI = true;
            releaseDo = true;
            m_fullScreen = !m_fullScreen;
        }

        // 退出
        else if(posX > (widtH - 30)
                && posX < (widtH - 6)
                &&posY > 3
                && posY < 27)
        {
            this->close();
        }

        // 功能一
        else if(posX > 8
                && posX < 78
                && posY > 75
                && posY < 155)
        {
            m_firstFunction = true;
            functionSelectDo(5,1);
            flag = true;
            releaseDo = true;
        }

        // 功能二
        else if(posX > 8
                && posX < 78
                && posY > 165
                && posY < 245)
        {
            m_secondFunction = true;
            functionSelectDo(5,2);
            flag = true;
            releaseDo = true;
        }

        // 功能三
        else if(posX > 8
                && posX < 78
                && posY > 255
                && posY < 335)
        {
            m_thirdFunction = true;
            functionSelectDo(5,3);
            flag = true;
            releaseDo = true;
        }
        // 功能四
        else if(posX > 8
                && posX < 78
                && posY > 350
                && posY < 430)
        {
            m_fourFunction = true;
            functionSelectDo(5,4);
            flag = true;
            releaseDo = true;
        }
        // 功能五
        //        else if(posX >  && posX <  &&
        //                posY >  && posY < ){
        //            m_fiveFunction = true;
        //            functionSelectDo(5,5);
        //            flag = true;
        //            releaseDo = true;
        //        }

        // 移动
        else if(posX > 1
                && posX < (widtH - 90)
                && posY > 0
                && posY < 27){
            if(moveUI){
                point = e->globalPos() - this->pos();
                mousePressed = true;
            }
        }

        // 以上皆为全局操作，一下皆为局部操作

        // 1 . 功能一下的子功能
        else if(funcMap[1]){
            //qDebug()<<"sub function 1";
        }

        // 2 . 功能二下的子功能
        else if(funcMap[2]){
            //qDebug()<<"sub function 2";

            // metar 报的 五个二级操作
            if(posX > 96
                    && posX < 196
                    && posY > 79
                    && posY < 105)
            {
                qDebug()<<"met report1";
                m_metOne = true;
                metarSelectDo(5,1);
                flag = true;
                releaseDo = true;
            }
            else if(posX > 197
                    && posX < 357
                    && posY > 79
                    && posY < 105)
            {
                qDebug()<<"met report2";
                m_metTwo = true;
                metarSelectDo(5,2);
                flag = true;
                releaseDo = true;
            }
            else if(posX > 358
                    && posX < 498
                    &&posY > 79
                    && posY < 105)
            {
                qDebug()<<"met report3";
                m_metThree = true;
                metarSelectDo(5,3);
                flag = true;
                releaseDo = true;
            }
            else if(posX > 499
                    && posX < 609
                    &&posY > 79
                    && posY < 105)
            {
                qDebug()<<"met report4";
                m_metFour = true;
                metarSelectDo(5,4);
                flag = true;
                releaseDo = true;
            }
            else if(posX > 610
                    && posX < 810
                    &&posY > 79
                    && posY < 105)
            {
                qDebug()<<"met report5";
                m_metFive = true;
                metarSelectDo(5,5);
                flag = true;
                releaseDo = true;
            }

            // 第一个操作下的子操作
            if(m_metar[1]){
                qDebug()<<"on metar1 page sub options";
                if(posX > (( width() - 182) * 4 / 5 + 178)
                        && posX < (103 + (width() - 112) * 9 / 10)
                        && posY > (height() - 199)
                        && posY < (height() - 173))
                {
                    qDebug()<<"--->update";
                    automaticMetarTelegramData();
                    updateMetar();
                    m_metUpdate = true;
                    flag = true;
                    releaseDo = true;/*103 +  sWidth* 9 / 10*/
                }
                else if(posX > ((width() - 112) * 9 / 10 + 109)
                        && posX < (width() - 19)
                        && posY > (height() - 199)
                        && posY < (height() - 173))
                {
                    qDebug()<<"--->cavok check";
                    m_cavokCheck = true;
                    flag = true;
                    releaseDo = true;
                }
                else if(posX > (( width() - 182) * 4 / 5 + 178)
                        && posX < (width() - 14)
                        && posY > (height() - 170)
                        && posY < (height() - 144))
                {
                    qDebug()<<"--->modify";
                    modifyMetar();
                    m_metModify = true;
                    flag = true;
                    releaseDo = true;
                }
                else if(posX > ((width() - 112) * 4 / 5 + 122)
                        && posX < ((width() - 112) * 9 / 10 + 109)
                        &&posY > (height() - 134)
                        && posY < (height() - 108))
                {
                    qDebug()<<"--->send Request Trend";
                    sendMetarAskTrend();
                    m_metTrend = true;
                    flag = true;
                    releaseDo = true;
                }
                else if(posX > ((width() - 112) * 9 / 10 + 112)
                        && posX < (width() - 14)
                        &&posY > (height() - 134)
                        && posY < (height() - 108))
                {
                    qDebug()<<"--->send";
                    sendMetar();
                    m_metSend = true;
                    flag = true;
                    releaseDo = true;
                }
                else if(posX > (7 + (width() - 112) / 2)
                        && posX <  (97 + (width() - 112) / 2)
                        && posY > (height() - 102)
                        && posY < (height() - 8))
                {
                    qDebug()<<"--->metar report comfire";
                    m_metarComfire = true;
                    flag = true;
                    releaseDo = true;
                }
                else if(posX > (width() - 105)
                        && posX <  (width() - 15)
                        && posY > (height() - 102)
                        && posY < (height() - 8)){
                    qDebug()<<"--->spacil report comfire";
                    m_spacilComfire = true;
                    flag = true;
                    releaseDo = true;
                }
            }

            // 第二个操作下的子操作
            else if(m_metar[2]){
                qDebug()<<"on metar2 page sub options";

                if(posX > (( width() - 182) * 4 / 5 + 178)
                        && posX < (width() - 14)
                        && posY > (height() - 199)
                        && posY < (height() - 173)){
                    qDebug()<<"--->update";
                    automaticSpaciTelegramData();
                    updateSpaci();
                    m_spaciUpdate = true;
                    flag = true;
                    releaseDo = true;
                }

                else if(posX > (( width() - 182) * 4 / 5 + 178)
                        && posX < (width() - 14)
                        && posY > (height() - 170)
                        && posY < (height() - 144))
                {
                    qDebug()<<"--->modify";
                    modifySpaci();
                    m_spaciModify = true;
                    flag = true;
                    releaseDo = true;
                }

                else if(posX > (( width() - 182) * 4 / 5 + 178)
                        && posX < (width() - 14)
                        &&posY > (height() - 134)
                        && posY < (height() - 108))
                {
                    qDebug()<<"--->send";
                    sendSpaci();
                    m_spaciSend = true;
                    flag = true;
                    releaseDo = true;
                }
                else if(posX > (7 + (width() - 112) / 2)
                        && posX <  (97 + (width() - 112) / 2)
                        && posY > (height() - 102)
                        && posY < (height() - 8))
                {
                    qDebug()<<"--->metar report comfire";
                    m_metarComfire = true;
                    flag = true;
                    releaseDo = true;
                }
                else if(posX > (width() - 105)
                        && posX <  (width() - 15)
                        && posY > (height() - 102)
                        && posY < (height() - 8))
                {
                    qDebug()<<"--->spacil report comfire";
                    m_spacilComfire = true;
                    flag = true;
                    releaseDo = true;
                }

                // last metar report
                else if(posX > ((width() - 112) * 4.8 / 8 + 120)
                        && posX <  (width() - 112) * 6.3 / 8 + 120
                        && posY > ((height() - 351) * 12.06 / 13 + 146)
                        && posY < (height() - 351) * 13.06 / 13 + 138)
                {
                    qDebug()<<"--->last metar report";
                    m_clickLastMetar = true;
                    showLastMetarReport();
                    flag = true;
                    releaseDo = true;
                }

                // last spaci report
                else if(posX > ((width() - 112) * 6.3 / 8 + 124)
                        && posX <  (width() - 112) * 7.8 / 8 + 124
                        && posY > ((height() - 351) * 12.06 / 13 + 146)
                        && posY < ((height() - 351) * 13.06 / 13 + 138))
                {
                    qDebug()<<"--->last spaci report";
                    m_clickLastSpaci = true;
                    showLastSpaciReport();
                    flag = true;
                    releaseDo = true;
                }
            }

            // 第三个操作下的子操作
            else if(m_metar[3]){
                qDebug()<<"on metar3 page sub options";
            }

            // 第四个操作下的子操作
            else if(m_metar[4]){
                qDebug()<<"on metar4 page sub options";
            }

            // 第五个操作下的子操作
            else if(m_metar[5]){
                //qDebug()<<"on metar5 page sub options";
            }
        }

        // 3 . 功能三下的子功能
        else if(funcMap[3]){
            qDebug()<<"sub function 3 ";
            // 设备配置下的五个二级操作
            int threeWidth = width() - 100;
            if(posX > 96
                    && posX <  (threeWidth / 10 + 95)
                    &&posY > 79
                    && posY < 109)
            {
                qDebug()<<"deceive config 1";
                m_mserver = true;
                configSelectDo(6,1);
                flag = true;
                releaseDo = true;
            }
            else if(posX > (96 + threeWidth / 10)
                    && posX <  (95 + threeWidth / 5)
                    && posY > 79
                    && posY < 109)
            {
                qDebug()<<"deceive config 2";
                m_mCollect = true;
                configSelectDo(6,2);
                flag = true;
                releaseDo = true;
            }
            else if(posX > (threeWidth/ 5 + 96)
                    && posX < (95 + threeWidth * 3 / 10)
                    &&posY > 79
                    && posY < 109)
            {
                qDebug()<<"deceive config 3";
                m_mServerConfig = true;
                configSelectDo(6,3);
                flag = true;
                releaseDo = true;
            }
            else if(posX > (threeWidth * 3 / 10 + 96)
                    && posX <  (95 + threeWidth * 2 / 5)
                    &&posY > 79
                    && posY < 109)
            {
                qDebug()<<"deceive config 4";
                m_mCollectConfig = true;
                configSelectDo(6,4);
                flag = true;
                releaseDo = true;
            }
            else if(posX > (threeWidth * 2 / 5 + 96)
                    && posX < (95 + threeWidth / 2 )
                    &&posY > 79
                    && posY < 109)
            {
                qDebug()<<"deceive config 5";
                m_mDataConfig = true;
                configSelectDo(6,5);
                flag = true;
                releaseDo = true;
            }
            else if(posX > (threeWidth / 2 + 96)
                    && posX < (95 + threeWidth * 3 / 5 )
                    && posY > 79
                    && posY < 109)
            {
                qDebug()<<"deceive config 5";
                m_mLocaConfig = true;
                configSelectDo(6,6);
                qDebug()<<"本地配置操作！";
                flag = true;
                releaseDo = true;
            }
        }
        else if(funcMap[4])
        {
            if(posX > 93
                    && posX < 158
                    && posY > 75
                    && posY < 165)
            {
                qDebug()<<"ATC MAIN";
                //m_mserver = true;
                atcSelectDo(4,1);
                flag = true;
                releaseDo = true;
            }
            if(posX > 93
                    && posX < 158
                    && posY > 167
                    && posY < 287)
            {
                qDebug()<<"ATC REPORT";
                //m_mserver = true;
                atcSelectDo(4,2);
                flag = true;
                releaseDo = true;
            }
            if(posX > 93
                    && posX < 158
                    && posY > 289
                    && posY < 359)
            {
                qDebug()<<"RWYn";
                //m_mserver = true;
                atcSelectDo(4,3);
                flag = true;
                releaseDo = true;
            }
            if(posX > 93
                    && posX < 158
                    && posY > 361
                    && posY < 431)
            {
                qDebug()<<"03-21";
                //m_mserver = true;
                atcSelectDo(4,4);
                flag = true;
                releaseDo = true;
            }
        }
        else if(funcMap[5]){
        }
    }
    e->accept();// 接收事件
    if(flag){
        update();
        qDebug()<<"press ......";
    }
    // qDebug()<<"funcMap:"<<funcMap<<"m_metar"<<m_metar;
}

void WorkStation::mouseMoveEvent(QMouseEvent *e)
{
    if(moveUI){
        if(e->buttons() == Qt::LeftButton && this->mousePressed){
            // 判断鼠标事件的所有按钮被按下状态的按钮
            this->move(e->globalPos() - this->point);
        }
        //        qDebug()<<"mouseMove......";
    }
    e->accept();
}

void WorkStation::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){//判断鼠标事件的按钮名称
        this->mousePressed = false;
    }
    if(m_scaleUI){
        if(m_fullScreen){
            this->showFullScreen();
            moveUI = false;
        }
        else{
            this->showNormal();
            moveUI = true;
        }
        emit sacleSubContrl();
        updateSize();
        m_scaleUI = false;
    }
    if(m_firstFunction){
        m_firstFunction = false;
    }
    if(m_secondFunction){
        m_secondFunction = false;
    }
    if(m_thirdFunction){
        m_thirdFunction = false;
    }
    if(m_fourFunction){
        m_fourFunction = false;
    }
    if (m_fiveFunction){
        m_fiveFunction = false;
    }
    if(funcMap[1]){
    }
    if(funcMap[2]){
        if(m_metOne){
            m_metOne = false;
        }
        if(m_metUpdate){
            m_metUpdate = false;
        }
        if(m_cavokCheck){
            m_cavok = !m_cavok;
            emit enbaleCavokCheck(m_cavok);
            updateMetar();
            m_cavokCheck = false;
        }
        if(m_metModify){
            m_metModify = false;
        }
        if(m_metTrend){
            m_metTrend = false;
        }
        if(m_metSend){
            m_metSend = false;
        }
        if(m_metarComfire){
            m_metarComfire = false;
        }
        if(m_spacilComfire){
            m_spacilComfire = false;
        }
        if(m_clickLastMetar){
            m_clickLastMetar = false;
        }
        if(m_clickLastSpaci){
            m_clickLastSpaci = false;
        }
        if(m_metTwo){
            m_metTwo = false;
        }
        if(m_spaciUpdate){
            m_spaciUpdate = false;
        }
        if(m_spaciModify){
            m_spaciModify = false;
        }
        if(m_spaciSend){
            m_spaciSend = false;
        }
        if(m_metThree){
            m_metThree = false;
        }
        if(m_metFour){
            m_metFour = false;
        }
        if(m_metFive){
            m_metFive = false;
        }
    }
    if(funcMap[3]){
        if(m_mserver){
            m_mserver = false;
        }
        if(m_mCollect){
            m_mCollect  = false;
        }
        if(m_mServerConfig){
            m_mServerConfig  = false;
        }
        if(m_mCollectConfig){
            m_mCollectConfig  = false;
        }
        if(m_mDataConfig){
            m_mDataConfig = false;
        }
        if(m_mLocaConfig){
            m_mLocaConfig = false;
        }
    }
    if(funcMap[4]){

    }
    if(funcMap[5]){

    }
    if(releaseDo){
        update();
        qDebug()<<"release ........";
        releaseDo = false;
    }
    e->accept();
}

bool WorkStation::eventFilter(QObject *obj, QEvent *event)
{
    //    qDebug()<<"SC sub object:"<<obj->objectName();
    if (event->type() == QEvent::MouseButtonPress
            || event->type() == QEvent::MouseMove
            || event->type() == QEvent::HoverEnter
            || event->type() == QEvent::HoverLeave
            || event->type() == QEvent::HoverMove )
    {
        event->accept();
        return true;
    }
    else{
        return QWidget::eventFilter(obj, event);
    }
}

void WorkStation::showOrCloseTelegramCFG(bool show)
{
    if(show != teleCFGBool){
        qDebug()<<"show --7";
        teleCFGBool = show;
        if(show){
            teleCFG->show();
        }
        else{
            teleCFG->hide();
        }
    }
}

void WorkStation::showOrCloseAFTNContrls(bool show)
{
    if(show != metarSetBool){
        qDebug()<<"show --6";
        metarSetBool = show;
        if(show){
            aftnCFG->show();
        }
        else{
            aftnCFG->hide();
        }
    }
}

void WorkStation::showOrCloseLocaCFGContrl(bool show)
{
    if(show != locaCFgBool){
        qDebug()<<"show --6";
        locaCFgBool = show;
        if(show){
            locaCFG->show();
        }
        else{
            locaCFG->hide();
        }
    }
}

void WorkStation::showOrCloseMetarContrls(bool show)
{
    if(metarBool != show){
        qDebug()<<"show --5";
        metarBool = show;
        if(show){
            // metar partment
            MetarEcodecContrl->show();

            // metar real data partment
            _metar_Realdata_contrl->show();
            metarSenAddresses->show();
            metarClasses->show();
            metarContext->setReadOnly(true);
            Met_metarWaringInform->setReadOnly(true);
            Met_spacilWaringInform->setReadOnly(true);
            metarContext->show();
            Met_metarWaringInform->show();
            Met_spacilWaringInform->show();
            metarCtxConfirm->show();
        }
        else{

            MetarEcodecContrl->hide();
            _metar_Realdata_contrl->hide() ;
            metarSenAddresses->hide();
            metarContext->hide();
            Met_metarWaringInform->hide();
            Met_spacilWaringInform->hide();
            metarCtxConfirm->hide();
            metarClasses->hide();
        }
    }
    return ;
}

void WorkStation::showOrCloseSpaciContrls(bool show)
{
    if(spaciBool != show){
        qDebug()<<"show --4";
        spaciBool = show;
        if(show){
            SpaciEcodecContrl->show();
            _spaci_Realdata_contrl->show();
            spaciSenAddresses->show();
            spaciClasses->show();
            spaciContext->setReadOnly(true);
            spaciContext->show();
            spaciCtxConfirm->show();
            Spaci_metarWaringInform->setReadOnly(true);
            Spaci_spacilWaringInform->setReadOnly(true);
            Spaci_metarWaringInform->show();
            Spaci_spacilWaringInform->show();
        }
        else{
            SpaciEcodecContrl->hide();
            _spaci_Realdata_contrl->hide() ;
            spaciSenAddresses->hide();
            spaciClasses->hide();
            spaciContext->hide();
            Spaci_metarWaringInform->hide();
            Spaci_spacilWaringInform->hide();
            spaciCtxConfirm->hide();
        }
    }
}

void WorkStation::showOrCloseMetarReportContrl(bool show)
{
    if(metarReportBool != show){
        qDebug()<<"show --3";
        metarReportBool = show;
    }
    if(show){
        _metar_Report_Realdata_contrl->show();
        MetarReportEcodecContrl->show();
        MetarReportTelegramContextUI->show();
    }
    else{
        _metar_Report_Realdata_contrl->hide();
        MetarReportEcodecContrl->hide();
        MetarReportTelegramContextUI->hide();
    }
}

void WorkStation::showOrCloseSpacialReportContrl(bool show)
{
    if(spacialReportBool != show){
        qDebug()<<"show --2";
        spacialReportBool = show;
    }
    if(show){
        SpaciReportEcodecContrl->show();
        _spacial_Report_Realdata_contrl->show();
        SpaciReportTelegramContextUI->show();
    }
    else{
        SpaciReportEcodecContrl->hide();
        _spacial_Report_Realdata_contrl->hide();
        SpaciReportTelegramContextUI->hide();
    }
}

void WorkStation::showOrCloseDeveiceContrl(bool show)
{
    if(deveiceBool != show){
        qDebug()<<"show --1";
        deveiceBool = show;
        showOrCloseDeveice(show);
    }
    return ;
}

void WorkStation::showOrCloseInfomationContrl(bool show)
{
    if(informationBool != show){
        qDebug()<<"show --8";
        informationBool = show;
        showOrCloseInstall(show);
    }
    return ;
}

void WorkStation::showOrCloseLogContrl(bool show)
{
    if(logBool != show){
        qDebug()<<"show --999";
        logBool = show;
        showOrCloseLog(show);
    }
    return ;
}

void WorkStation::showOrCloseWaringContrl(bool show)
{
    if(waringBool != show){
        qDebug()<<"show --111";
        waringBool = show;
        showOrCloseWaring(show);
    }
    return ;
}

void WorkStation::showOrCloseMainWaringContrl(bool show)
{
    if(mainWarBool != show){
        mainWarBool = show;
        showOrclosedMainWar(show);
    }
}

void WorkStation::updateSize()
{
    _m_set_telegram_cfg_geometry();
    setAFTNCFGGeomerty();
    setLocaCFGGeomerty();
    int sHeight = height() - 351; // V drection 4 * 4
    int sWidth = width() - 112; // H drection 3 * 4

    // metar
    _metar_Realdata_contrl->setGeometry(97 + sWidth * 4 / 8,115,sWidth * 4 / 8,height() - 357);
    _spaci_Realdata_contrl->setGeometry(97 + sWidth * 4 / 8,115,sWidth * 4 / 8,height() - 357);
    MetarEcodecContrl->setGeometry(97,115,(width() - 112) * 4 / 8,height() - 357);
    metarContext->setGeometry(165,152 + sHeight,(sWidth - 70) * 3 / 5 - 8,89);
    spaciContext->setGeometry(165,152 + sHeight,(sWidth - 70) * 3 / 5 - 8,89);
    metarCtxConfirm->setGeometry(165 + (sWidth - 70) * 3 / 5 + 8,152 + sHeight - 2,(sWidth - 70) / 5,92);
    spaciCtxConfirm->setGeometry(165 + (sWidth - 70) * 3 / 5 + 8,152 + sHeight - 2,(sWidth - 70) / 5,92);
    Met_metarWaringInform->setGeometry(103 ,height() - 99,(width() - 112) / 2 - 100,88);
    Met_spacilWaringInform->setGeometry(103 + (width() - 112) / 2,height() - 99,(width() - 112) / 2 - 100,88);
    metarClasses->setGeometry(170,height() - 251 + sHeight / 26,120,24);
    metarSenAddresses->setGeometry(sWidth * 1.5 / 8 + 177,height() - 239 + (sHeight / 13) / 2 - 12 ,width() - sWidth * 1.5 / 8 - 194,24);

    // spaci
    SpaciEcodecContrl->setGeometry(97,115,(width() - 112) * 4 / 8,height() - 357);
    spaciClasses->setGeometry(170,height() - 251 + sHeight / 26,120,24);
    spaciSenAddresses->setGeometry(sWidth * 1.5 / 8 + 177,height() - 251 + sHeight / 26,sWidth * 2.9 / 8,24);
    Spaci_metarWaringInform->setGeometry(103 ,height() - 99,(width() - 112) / 2 - 100,88);
    Spaci_spacilWaringInform->setGeometry(103 + (width() - 112) / 2,height() - 99,(width() - 112) / 2 - 100,88);

    // metar report
    MetarReportEcodecContrl->setGeometry(97,115,(width() - 112) * 4 / 8,height() - 357);
    _metar_Report_Realdata_contrl->setGeometry(97 + sWidth * 4 / 8,115,sWidth * 4 / 8,height() - 357);

    MetarReportTelegramContextUI->setGeometry(97,115 + height() - 358,width() - 112,238);
    MetarReportTelegramContextUI->setAllContrlGeometry();

    // spacial report
    SpaciReportEcodecContrl->setGeometry(97,115,(width() - 112) * 4 / 8,height() - 357);
    _spacial_Report_Realdata_contrl->setGeometry(97 + sWidth * 4 / 8,115,sWidth * 4 / 8,height() - 357);

    SpaciReportTelegramContextUI->setGeometry(97,115 + height() - 358,width() - 112,238);
    SpaciReportTelegramContextUI->setAllContrlGeometry();

    // Deveice partment
    setDeveiceGeometrySize();
    setInstallGeomerty();

    setWaringGeomerty();
    setLogGeomerty();

    // ATC begin
    setAtcMetarReportGeometry();
    setAtcMainGeometry();
    // ATC end

    // main user waring
     _m_set_geometry();
}

void WorkStation::initMetarReportBool()
{
    atcMetarReportBool = false;
}

void WorkStation::showOrCloseAtcMetarReport(bool show)
{
    if(atcMetarReportBool != show){
        atcMetarReportBool = show;
    }
    if(show){
        metReport->show();
    }
    else{
        metReport->hide();
    }
}

void WorkStation::initAtcMainBool()
{
    atcAtcMainBool = false;
}

void WorkStation::showOrCloseAtcMain(bool show)
{
    if(atcAtcMainBool != show){
        atcAtcMainBool = show;
    }
    if(show){
        atcMain->show();
    }
    else{
        atcMain->hide();
    }
}

bool WorkStation::getMinShow() const
{
    return m_fullScreen;
}

void WorkStation::setMinShow(bool value)
{
    m_fullScreen = value;
}

void WorkStation::initMetar()
{
    metarContextMap[1]  = "ZGHA:140000;Z";
    metarContextMap[2]  = "170;03;MPS:100;V;210";
    metarContextMap[3]  = "9000";// 机场能见度值
    metarContextMap[4]  = "";// 跑道视程
    metarContextMap[5]  = "-RA";
    metarContextMap[6]  = "BKN050";
    metarContextMap[7]  = "24;/;20";
    metarContextMap[8]  = "Q;1007";
    metarContextMap[9]  = "";// 近时天气
    metarContextMap[10] = "";// 道面状况
    metarContextMap[11] = "NOSIG";
    metarContextMap[12] = "";// 备注

    //spaci报
    spaciContextMap[1]  = "ZGHA:140000;Z";
    spaciContextMap[2]  = "170;03;MPS:100;V;210";
    spaciContextMap[3]  = "9000";// 机场能见度值
    spaciContextMap[4]  = "";// 跑道视程
    spaciContextMap[5]  = "-RA";
    spaciContextMap[6]  = "BKN050";
    spaciContextMap[7]  = "24;/;20";
    spaciContextMap[8]  = "Q;1007";
    spaciContextMap[9]  = "";// 近时天气
    spaciContextMap[10] = "";// 道面状况
    spaciContextMap[11] = "NOSIG";
    spaciContextMap[12] = "";// 备注

    QStringList teleGrade;
    teleGrade<<"DD"<<"FF"<<"GG"<<"JJ"<<"KK"<<"LL"<<"SS";
    metarClasses->addItems(teleGrade);
    spaciClasses->addItems(teleGrade);

    teleCFGBool = false;
    metarSetBool = false;
    locaCFgBool = false;
    metarBool = false;
    spaciBool = false;
    metarReportBool = false;
    spacialReportBool = false;
    deveiceBool = false;
    informationBool = false;
    logBool = false;
    waringBool = false;
    mainWarBool = true;

    int sHeight = height() - 351; // V drection 4 * 4
    int sWidth = (width() - 112); // H drection 3 * 4

    // metar geometry
    MetarEcodecContrl->setGeometry(97,115,width()/2 - 56,height() - 357);
    metarContext->setGeometry(165,152 + sHeight,(sWidth - 70) * 3 / 5 - 8,89);
    spaciContext->setGeometry(165,152 + sHeight,(sWidth - 70) * 3 / 5 - 8,89);
    metarCtxConfirm->setGeometry(165 + (sWidth - 70) * 3 / 5 + 8,150 + sHeight,sWidth / 5 - 14,92);
    spaciCtxConfirm->setGeometry(165 + (sWidth - 70) * 3 / 5 + 8,150 + sHeight,sWidth/ 5 - 14,92);

    Met_metarWaringInform->setGeometry(103,height() - 99,width()/ 2 - 156,88);
    Met_spacilWaringInform->setGeometry(47 + width()/ 2 ,height() - 99,width()/ 2 - 156,88);
    metarSenAddresses->setGeometry(sWidth * 1.5 / 8 + 177,height() - 251 + sHeight / 26,
                                   width() - sWidth * 1.5 / 8 - 194,24);
    metCodeShow();

    MetarEcodecContrl->hide();
    metarContext->hide();
    spaciContext->hide();
    Met_metarWaringInform->hide();
    Met_spacilWaringInform->hide();

    MetarReportTelegramContextUI->hide();
    SpaciReportTelegramContextUI->hide();

    metarCtxConfirm->hide();
    spaciCtxConfirm->hide();
    metarSenAddresses->hide();
    metarClasses->setGeometry(170,height() - 251 + sHeight / 26,120,24);

    metarClasses->hide();
    connect(metarClasses,SIGNAL(currentTextChanged(QString))
            ,SLOT(metarClassesSlot(QString)));

    // metar
    MetarReportEcodecContrl->hide();
    MetarReportEcodecContrl->setGeometry(97,115,width()/2 - 56,height() - 357);

    //spaci
    SpaciEcodecContrl->setGeometry(97,115,width()/2 - 56,height() - 357);
    spaciSenAddresses->setGeometry(sWidth * 1.5 / 8 + 177,height() - 251 + sHeight / 26,sWidth * 2.9 / 8,24);

    Spaci_metarWaringInform->setGeometry(103,height() - 99,width()/ 2 - 156,88);
    Spaci_spacilWaringInform->setGeometry(47 + width()/ 2,height() - 99,width()/ 2 - 156,88);

    // Spaci
    SpaciReportEcodecContrl->hide();
    SpaciReportEcodecContrl->setGeometry(97,115,(width() - 112) * 4 / 8,height() - 357);

    // metar partment
    _metar_Realdata_contrl->setGeometry(97 + sWidth / 2,115,sWidth / 2,height() - 357);

    // Spaci partment
    _spaci_Realdata_contrl->setGeometry(97 + sWidth / 2,115,sWidth / 2,height() - 357);

    // metar report partment
    _metar_Report_Realdata_contrl->setGeometry(97 + sWidth / 2,115,sWidth / 2,height() - 357);
    MetarReportTelegramContextUI->setGeometry(97,115 + height() - 358,width() - 112,238);
    MetarReportTelegramContextUI->setAllContrlGeometry();

    // spacial report
    _spacial_Report_Realdata_contrl->setGeometry(97 + sWidth / 2,115,sWidth / 2,height() - 357);
    SpaciReportTelegramContextUI->setGeometry(97,115 + height() - 358,width() - 112, 238);
    SpaciReportTelegramContextUI->setAllContrlGeometry();

    spaciCodeShow();
    SpaciEcodecContrl->hide();

    spaciSenAddresses->hide();
    Spaci_metarWaringInform->hide();
    Spaci_spacilWaringInform->hide();

    // metar report prtment
    _metar_Realdata_contrl->hide();
    _spaci_Realdata_contrl->hide();
    _metar_Report_Realdata_contrl->hide();
    _spacial_Report_Realdata_contrl->hide();
    spaciClasses->setGeometry(170,height() - 251 + sHeight / 26,120,24/*170,147 + sHeight * 12 / 13,120,sHeight / 13 - 8*/);
    spaciClasses->hide();
    connect(spaciClasses,SIGNAL(currentTextChanged(QString)),
            SLOT(spaciClassesSlot(QString)));

    // Deveice partment
    setDeveiceGeometrySize();
    setInstallGeomerty();
    showOrCloseDeveice(false);
    showOrCloseInstall(false);
    showOrCloseLog(false);
    showOrCloseWaring(false);

    setWaringGeomerty();
    setLogGeomerty();

    initBackInstallConnections();
    init36selfCFGConnection();
    initCFGAffix9MessageOptionsSignals();
}

void WorkStation::initTelegramOptionConnections()
{
    if(MetarReportTelegramContextUI){
        connect(MetarReportTelegramContextUI
                ,SIGNAL(queryUpdateTelegramCotext())
                ,SLOT(updateMetarReport()));
        connect(MetarReportTelegramContextUI
                ,SIGNAL(sendTelegramContext(QString))
                ,SLOT(metarReportsender(QString)));
    }
    if(SpaciReportTelegramContextUI){
        connect(SpaciReportTelegramContextUI
                ,SIGNAL(queryUpdateTelegramCotext())
                ,SLOT(updateSpaciReport()));
        connect(SpaciReportTelegramContextUI
                ,SIGNAL(sendTelegramContext(QString))
                ,SLOT(spaciReportsender(QString)));
    }
}

void WorkStation::_m_init_telegram_cfg()
{
    teleCFG = new TeleConfig(this);
    teleCFG->hide();
}

void WorkStation::_m_set_telegram_cfg_geometry()
{
    if(teleCFG){
        teleCFG->setGeometry(96,115,width()-104,height()-121);
    }
}

void WorkStation::_m_install_teleDFG()
{
    //teleCFG->installEventFilter(this);
}

void WorkStation::initAFTNCFG()
{
    aftnCFG = new TelegramCFG(this);
    aftnCFG->hide();
}

void WorkStation::setAFTNCFGGeomerty()
{
    if(aftnCFG){
        aftnCFG->setGeometry(96 /*100*/,/*111*/ 114,width() - /*109*/ 105,height() - 120);
    }
}

void WorkStation::initAFTNCFGSignalConnection()
{
    if(aftnCFG){
        connect(aftnCFG,SIGNAL(AFTNConfigSet(MeaagseQueue))
                ,SIGNAL(AFTNConfigSet(MeaagseQueue)));
    }
}

void WorkStation::installAftnCFGEventFilter()
{
    //    aftnCFG->installEventFilter(this);
}

void WorkStation::initLocaCFG()
{
    locaCFG = new WorkeStationCFG(this);
    locaCFG->hide();
}

void WorkStation::setLocaCFGGeomerty()
{
    if(locaCFG){
        locaCFG->setGeometry(96 ,114,width() - 105,height() - 120);
    }
}

void WorkStation::initLocaCFGSignalConnection()
{

}

void WorkStation::installLocaCFGEventFilter()
{
//    locaCFG->installEventFilter(this);
}

void WorkStation::initDeveiceSate()
{
    statue = new deveiceStateControl(this);
    connect(statue,SIGNAL(cofg_rvr_values()),SIGNAL(pollute_Show()));
}

void WorkStation::setDeveiceGeometrySize()
{
    statue->setGeometry(96 /*100*/,/*111*/ 114,width() - /*109*/ 105,height() - 120);
}

void WorkStation::installDeveiceEventFilter()
{
    //statue->installEventFilter(this);  // 2018.1.4 不安装过滤器，rvr补偿操作需要
}

void WorkStation::showOrCloseDeveice(bool option)
{
    if(option){
        statue->show();
    }
    else{
        statue->hide();
    }
}

void WorkStation::setDeveiceValues()
{

}

void WorkStation::initLogObj()
{
    log =  new DataLog(this);
}

void WorkStation::setLogGeomerty()
{
    log->setGeometry(96 /*100*/,/*111*/ 114,width() - /*109*/ 105,height() - 120);
}

void WorkStation::installLogEventFilter()
{
    log->installEventFilter(this);
}

void WorkStation::showOrCloseLog(bool option)
{
    if(option){
        log->show();
    }
    else{
        log->hide();
    }
}

void WorkStation::initWaringObj()
{
    waring =  new WaringShow(this);
}

void WorkStation::setWaringGeomerty()
{
    waring->setGeometry(96 /*100*/,/*111*/ 114,width() - /*109*/ 105,height() - 120);
}

void WorkStation::installWaringEventFilter()
{
    waring->installEventFilter(this);
}

void WorkStation::showOrCloseWaring(bool option)
{
    if(option){
        waring->show();
    }
    else{
        waring->hide();
    }
}

void WorkStation::initInstallCFG()
{
    install = new InstallCFG(this);
}

void WorkStation::setInstallGeomerty()
{
    install->setGeometry(96 /*100*/,/*111*/ 114,width() - /*109*/ 105,height() - 120);
}

void WorkStation::installInstallFilter()
{
    install->installEventFilter(this);
}

void WorkStation::showOrCloseInstall(bool option)
{
    if(option){
        install->show();
    }
    else{
        install->hide();
    }
}

void WorkStation::initBackInstallConnections()
{
    if(install){
        //        connect(this,SIGNAL(airBackInforSignal(SensorMap)),deveiceConfig,SIGNAL(backAirInfo(SensorMap)));
        //        connect(this,SIGNAL(runWayBackInforSignal(SensorMap)),deveiceConfig,SIGNAL(backRunwayInfo(SensorMap)));
        connect(this,SIGNAL(airBackInforSignal(SensorMap))
                ,install,SIGNAL(backAirInfoSignal(SensorMap)));
        connect(this,SIGNAL(runWayBackInforSignal(SensorMap))
                ,install,SIGNAL(backRunwayInfoSignal(SensorMap)));
        connect(this,SIGNAL(matchBackInforSignal(SensorMap))
                ,install,SIGNAL(backMatchInfoSignal(SensorMap)));
    }
}

void WorkStation::init36selfCFGConnection()
{
    if(install){
        // 3616 自身配置返回信息链接函数
        connect(this,SIGNAL(Configure3616Signal(SensorMap))
                ,install,SIGNAL(Configure3616Signal(SensorMap)));
        connect(this,SIGNAL(sensorStatusSignal(SensorMap))
                ,install,SIGNAL(sensorStatusSignal(SensorMap)));
        connect(this,SIGNAL(sensorLIBsSignal(SensorMap))
                ,install,SIGNAL(sensorLIBsSignal(SensorMap)));
        connect(this,SIGNAL(serialCardParamersSignal(SensorMap))
                ,install,SIGNAL(serialCardParamersSignal(SensorMap)));
        connect(this,SIGNAL(ExternSensorInfoListSignale(SensorMap)),
                install,SIGNAL(ExternSensorInfoListSignale(SensorMap)));
    }
}

void WorkStation::initCFGAffix9MessageOptionsSignals()
{
    if(install){
        // 系统设置部分的安装操作AFFIX9的信号链接
        connect(install,SIGNAL(CFGOptions(QString))
                ,SIGNAL(Affix9MessageSignals(QString)));
        connect(this,SIGNAL(backRequeryAFFIX9menberSignal(QString,InforData))
                ,install,SIGNAL(backRequeryAFFIX9menberSignal(QString,InforData)));
        // 发往传感器的
        connect(this,SIGNAL(AFFIX9NewMessageSendUp(QString,InforData))
                ,install,SIGNAL(AFFIX9NewMessageSendUp(QString,InforData)));
    }
    if(statue){
        // 发往状态的
        connect(this,SIGNAL(AFFIX9NewMessageSendUp(QString,InforData))
                ,statue,SLOT(AFFIX9NewMessageSendUp(QString,InforData)));
    }
    if(waring){
        connect(this,SIGNAL(AFFIX9NewMessageSendUp(QString,InforData))
                ,waring,SLOT(AFFIX9NewMessageSendUp(QString,InforData)));
    }
}

void WorkStation::init_m_atcPage()
{
    m_atcPage[1] = true;
    m_atcPage[2] = false;
    m_atcPage[3] = false;
    m_atcPage[4] = false;
}

void WorkStation::initAtcMetarReport()
{
    metReport =  new ATCREPORT(this);
    metReport->hide();
}

void WorkStation::setAtcMetarReportGeometry()
{
    if(metReport){
        metReport->setGeometry(158,75,width() - 165,height()- 79);
        metReport->setShowOutGeometry();
    }
}

void WorkStation::installMetReportEventFilter()
{
    metReport->installEventFilter(this);
}

void WorkStation::initAtcMainObj()
{
    atcMain =  new ATCMAIN(this);
    atcMain->hide();
}

void WorkStation::setAtcMainGeometry()
{
    if(atcMain){
        atcMain->setGeometry(158,75,width() - 165,height()- 79);
        atcMain->setShowOutGeometry();
    }
}

void WorkStation::installAtcMainEventFilter()
{
    atcMain->installEventFilter(this);
}

void WorkStation::initAtcMainDataConnections()
{
    if(atcMain){
        connect(this,SIGNAL(AtcDataSignal(QString,QString))
                ,atcMain,SLOT(setDataValue(QString,QString)));
    }
}

void WorkStation::initQNFValue()
{
    m_qnf = "0000";
}

void WorkStation::_init_grade()
{
    _m_user_type = "Not User";
}

void WorkStation::_m_init_war_Value()
{
    _m_war = new WarShow(this);
    connect(this,SIGNAL(addWaring(QString))
            ,_m_war,SLOT(_m_add_waring_Slot(QString)));
    _m_war->_m_select_waring(false);
    _m_set_geometry();
}

void WorkStation::_m_set_geometry()
{
    _m_war->setGeometry(95,height()- 98,width() - 102,93);
}

void WorkStation::showOrclosedMainWar(bool show)
{
    if(show){
        _m_war->show();
    }
    else{
        _m_war->hide();
    }
}

void WorkStation::init_config_settings()
{
    m_runwayInfor = NULL;
    m_usedRunWay = NULL;
    m_sensor = NULL;
    m_telegramSensor = NULL;
}

void WorkStation::metarClassesSlot(QString str)
{
    //qDebug()<<"metar report class:"<<str;
    Met_rankStr = str;
}

void WorkStation::spaciClassesSlot(QString str)
{
    Spaci_rankStr = str;
}

void WorkStation::metarAddressesDeal(QString address)
{
    QString tempAddress = address;
    tempAddress = tempAddress.replace(" ","");
    int step = 0;
    int len = tempAddress.length() / 8;
    bool endEdit = true;
    if((len * 8)< tempAddress.length())
    {
        len++;
        endEdit = false;
    }
    for(int num = 0 ;num < len;num++)
    {
        if(num == 0) continue;
        tempAddress = tempAddress.insert(num * 8 + step,"  ");
        step += 2;
    }
    tempAddress = tempAddress.toUpper();
    metarSenAddresses->setText(tempAddress);

    if(endEdit){
        AddressStr = tempAddress;
    }
    else {
        if(len == 1){
            AddressStr = "";
        }
        else{
            AddressStr = tempAddress.mid(0,(len - 1) * 8 + step);
        }
    }
    //qDebug()<<"address are:"<<AddressStr;
}

void WorkStation::spaciAddressesDeal(QString address)
{
    QString tempAddress = address;
    tempAddress = tempAddress.replace(" ","");
    int step = 0;
    int len = tempAddress.length() / 8;
    bool endEdit = true;
    if((len * 8)< tempAddress.length())
    {
        len++;
        endEdit = false;
    }
    for(int num = 0 ;num < len;num++)
    {
        if(num == 0) continue;
        tempAddress = tempAddress.insert(num * 8 + step,"  ");
        step += 2;
    }
    tempAddress = tempAddress.toUpper();
    spaciSenAddresses->setText(tempAddress);

    if(endEdit){
        AddressStr = tempAddress;
    }
    else {
        if(len == 1){
            AddressStr = "";
        }
        else{
            AddressStr = tempAddress.mid(0,(len - 1) * 8 + step);
        }
    }
    qDebug()<<"address are:"<<AddressStr;
}

/* -------------------------------
 * function description
 * 将编好的METAR报数据显示到发报控件中
 * 并且加上METAR报的标志头 "METAR"
 * ---------------------------------
 */
// show metar telegraph-code in control;
void WorkStation::metCodeShow()
{
    QString metarStr = "METAR  ";
    int number = metarContextMap.count();
    int step = 0;
    for(int num = 1; num <= number; num++)
    {
        if(metarContextMap[num].trimmed() == "")
        {
            continue;
        }
        if(num == number)
        {
            metarStr = metarStr + removeFeild(metarContextMap[num]);
        }
        else{
            metarStr = metarStr + removeFeild(metarContextMap[num]) + "  ";
            if(step % 8 == 0)
            {
                metarStr = metarStr + "\n" ;
            }
        }
        step ++;
    }
    metarContext->setText(metarStr);
}

void WorkStation::spaciCodeShow()
{
    QString spaciStr = "SPACI  ";
    int number = spaciContextMap.count();
    int step = 0;
    for(int num = 1; num <= number; num++)
    {
        if(spaciContextMap[num].trimmed() == "")
        {
            continue;
        }
        if(num == number)
        {
            spaciStr = spaciStr + removeFeild(spaciContextMap[num]);
        }
        else{
            spaciStr = spaciStr + removeFeild(spaciContextMap[num]) + "  ";
            if(step % 8 == 0)
            {
                spaciStr = spaciStr + "\n" ;
            }
        }
        step ++;
    }
    spaciContext->setText(spaciStr);
}

QString WorkStation::MetarReportTranslateContext(SerialWarMap telegramCtx)
{
    QString MetarReportStr = "METAR REPORT  ";
    int number = telegramCtx.count();
    int step = 0;
    for(int num = 1; num <= number; num++)
    {
        if(telegramCtx[num].trimmed() == "")
        {
            continue;
        }
        if(num == number)
        {
            MetarReportStr = MetarReportStr + removeFeild(telegramCtx[num]);
        }
        else{
            MetarReportStr = MetarReportStr + removeFeild(telegramCtx[num]) + "  ";
            if(step % 8 == 0)
            {
                MetarReportStr = MetarReportStr + "\n" ;
            }
        }
        step ++;
    }
    return MetarReportStr;
}

QString WorkStation::SpaciReportTranslateContext(SerialWarMap telegramCtx)
{
    QString spaciReportStr = "SPACI REPOT  ";
    int number = telegramCtx.count();
    int step = 0;
    for(int num = 1; num <= number; num++)
    {
        if(telegramCtx[num].trimmed() == "")
        {
            continue;
        }
        if(num == number)
        {
            spaciReportStr = spaciReportStr + removeFeild(telegramCtx[num]);
        }
        else{
            spaciReportStr = spaciReportStr + removeFeild(telegramCtx[num]) + "  ";
            if(step % 8 == 0)
            {
                spaciReportStr = spaciReportStr + "\n" ;
            }
        }
        step ++;
    }
    return spaciReportStr;
}

SerialWarMap WorkStation::getMetarControlsText()
{
    SerialWarMap  subMap;
    subMap =  MetarEcodecContrl->getTelegramCtx();
    qDebug()<<"subMap:"<<subMap;
    return  subMap;
}

/*   --------------------
 *   function description
 *   （预报员）解析未加趋势的Metar报数据内容
 *   格式：dataName=vlue/dataName2=vlaue2/........
 *   --------------------
 */
QString WorkStation::getTrendMetarStr()
{
    QString metarStr;
    TrendMetar metarCtx;
    metarCtx = MetarEcodecContrl->getTrendRequestMetarCtx();
    QStringList list;
    list = metarCtx.keys();
    int len;
    len = list.length();
    for(int n = 0;n < len;n++){
        if(n == len - 1){
            metarStr = metarStr + QString("%1=%2")
                    .arg(list.value(n))
                    .arg(metarCtx[list.value(n)]);
            break;
        }
        metarStr = metarStr + QString("%1=%2/")
                .arg(list.value(n))
                .arg(metarCtx[list.value(n)]);
    }
    return metarStr;
}

SerialWarMap WorkStation::getMetarReportControlsText()
{
    SerialWarMap  subMap;
    subMap =  MetarReportEcodecContrl->getTelegramCtx();
    return  subMap;
}

SerialWarMap WorkStation::getSpaciControlsText()
{
    SerialWarMap  subMap;
    subMap =  SpaciEcodecContrl->getTelegramCtx();
    return  subMap;
}

SerialWarMap WorkStation::getSpaciReportControlsText()
{
    SerialWarMap  subMap;
    subMap =  SpaciReportEcodecContrl->getTelegramCtx();
    return  subMap;
}

/*   ----------------------
 *   function description
 *   将电报链接成一个字符串内容
 *   并返回这个字符串
 *   ------------------------
 */
QString WorkStation::constituteMetarContext(SerialWarMap serialMap)
{
    QString metarReportStr;

    //1 . 不从map中更新。
    int number = serialMap.count();
    for(int num = 1; num <= number; num++)
    {
        if(serialMap[num].trimmed() == "")
        {
            continue;
        }
        if(num == number)
        {
            metarReportStr = metarReportStr
                    + removeFeild(serialMap[num]);
        }
        else{
            metarReportStr = metarReportStr
                    + removeFeild(serialMap[num]) + " ";
        }
    }
    return metarReportStr;
}


QString WorkStation::constituteSpaciContext(SerialWarMap serialMap)
{
    QString spaciReportStr ;

    //1 . 不从map中更新。
    int number = serialMap.count();
    for(int num = 1; num <= number; num++)
    {
        if(serialMap[num].trimmed() == "")
        {
            continue;
        }
        if(num == number)
        {
            spaciReportStr = spaciReportStr + removeFeild(serialMap[num]);
        }
        else{
            spaciReportStr = spaciReportStr + removeFeild(serialMap[num]) + " ";
        }
    }
    return spaciReportStr;
}
/* ----------------------------
 * function description
 * 将Metar报中的冒号和分号去掉
 */
QString WorkStation::removeFeild(QString str)
{
    QString tempStr = str;
    tempStr = tempStr.replace(":"," ");
    tempStr = tempStr.replace(";","");
    return tempStr;
}

void WorkStation::updateMetar() // 更新 电报 最终内容
{
    //get controls contexts into map
    metarContextMap = getMetarControlsText(); //METAR 报接入数据

    // used map variable to show in the metar context control
    metCodeShow();
}
/*  --------------------------
 *  function descrption
 *  观测员发送趋势报请求
 *  以便从预报员处得到气象变化趋势。
 *
 */
void WorkStation::sendMetarAskTrend()
{
    QString MetarCtxStr;
    MetarCtxStr = getTrendMetarStr();
    //提示发修改的报还是原报
    MeaagseQueue queue;
    Met_rankStr = metarClasses->currentText();
    qDebug()<<"address:"<<AddressStr
           <<"rankStr:"<<Met_rankStr
          <<"metar context:"<<MetarCtxStr;
    queue.enqueue(MetarCtxStr);
    queue.enqueue(Met_rankStr);
    queue.enqueue(AddressStr);
    emit sendMetarTrendReqeust(queue);
}

void WorkStation::modifyMetar()
{
    if(!met_modifyFlag){
        metarContext->setReadOnly(false);
        met_modifyFlag = true;
    }
    else{
        metarContext->setReadOnly(true);
        met_modifyFlag = false;
    }
}

/* ---------------------
 * function description
 * 从PainTextEdit 中获取METAR的内容并生成标准metar报格式
 *
 */
void WorkStation::sendMetar()
{
    //判断是否修改
    if(met_modifyFlag){
        emit waringShowSignal("告警提示！","请先确认修改后再发送METAR报。");
        return ;
    }

    SerialWarMap metMap;
    // used map variable to constitute metar Str
    QString metString = metarContext->toPlainText().replace("\n","");
    QStringList metSerial = metString.split(" ",QString::SkipEmptyParts);
    for(int index = 0;index < metSerial.length();index++){
        metMap[index + 1] = metSerial.value(index);
    }
    Met_rankStr = metarClasses->currentText();
    metarContextStr = constituteMetarContext(metMap);
    QString AllMetarCtx;
    AllMetarCtx = "Metar:sendOkMetar>" + metarContextStr;
    emit sendOkMetarSignal(AllMetarCtx + "+"+ Met_rankStr + "+" + AddressStr);

    // 保存发的最近一份完整的Metar报信息
    QString lastMetarStr;
    lastMetarStr = "Address:  "
            + AddressStr + "\n";
    lastMetarStr = lastMetarStr + "Rank:  "
            + Met_rankStr + "\n";
    lastMetarStr = lastMetarStr + "Context:  "
            + metarContextStr + "\n";
    metraStackBuff.push_back(lastMetarStr);
    qDebug()<<"Last metar :"<<metraStackBuff;
}

void WorkStation::updateSpaci()
{
    //get controls contexts into map
    spaciContextMap = getSpaciControlsText();

    // used map variable to show in the metar context control
    spaciCodeShow();
}

void WorkStation::modifySpaci()
{
    if(!spaci_modifyFlag)
    {
        spaciContext->setReadOnly(false);
        spaci_modifyFlag = true;
    }
    else
    {
        spaciContext->setReadOnly(true);
        spaci_modifyFlag = false;
    }
}

/// \brief WorkStation::sendSpaci
///  send Spaci
///
void WorkStation::sendSpaci()
{
    //判断是否修改
    if(spaci_modifyFlag)
    {
        emit waringShowSignal("告警提示！","请先确认修改后再发送SPACI报。");
        return ;
    }
    SerialWarMap spaciMap;
    // used map variable to constitute metar Str
    QString spaciString = spaciContext->toPlainText().replace("\n","");
    QStringList spaciSerial = spaciString.split(" ",QString::SkipEmptyParts);
    for(int index = 0;index < spaciSerial.length();index++){
        spaciMap[index + 1] = spaciSerial.value(index);
    }
    spaciContextStr = constituteSpaciContext(spaciMap);

    //提示发修改的报还是原报
    MeaagseQueue queue;
    Spaci_rankStr = spaciClasses->currentText();
    qDebug()<<"address:"<<AddressStr<<"rankStr"<<Spaci_rankStr<<"metar context:"<<spaciContextStr;
    queue.enqueue(spaciContextStr);
    queue.enqueue(Spaci_rankStr);
    queue.enqueue(AddressStr);

    // 需在此处建立SPACI报的发报信号
    //emit (queue);

    // 保存最近发的一份Spaci报信息
    QString lastSpaciStr;
    lastSpaciStr = "Address:  " + AddressStr + "\n";
    lastSpaciStr = lastSpaciStr + "Rank:  "
            + Spaci_rankStr + "\n";
    lastSpaciStr = lastSpaciStr + "Context:  "
            + spaciContextStr + "\n";
    spaciStackBuff.push_back(lastSpaciStr);
    qDebug()<<"Spaci report :"<<spaciStackBuff;
}

void WorkStation::showLastSpaciReport()
{
    if(!metraStackBuff.isEmpty())
    {
        QString lastMetar = metraStackBuff.pop();
        qDebug()<<"last metar:"<<lastMetar;
        metraStackBuff.push_back(lastMetar);
    }
}

void WorkStation::showLastMetarReport()
{
    if(!spaciStackBuff.isEmpty()){
        QString lastSpaci = spaciStackBuff.pop();
        qDebug()<<"last Spaci"<<lastSpaci;
        spaciStackBuff.push_back(lastSpaci);
    }
}

void WorkStation::waringShowSlot(QString title, QString context)
{
    QMessageBox::warning(this,title,context);
}

void WorkStation::atcSelectDo(int count, int index)
{
    for(int i = 1; i<= count;i++)
    {
        if(i == index)
        {
            m_atcPage[i] = true;
        }
        else
        {
            m_atcPage[i] = false;
        }
    }
}

