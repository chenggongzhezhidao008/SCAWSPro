#include "awosstartsetup.h"
#include <QDir>
#include <QSettings>

AwosStartSetup::AwosStartSetup(QObject *parent) :
    QObject(parent)
{
    QDir::setCurrent(QApplication::applicationDirPath());
    initSetpValue();
    i = 0 ; //test
    initVocies();
    _init_User_Infromations();
}

int AwosStartSetup::startLogin() //login workersataton system
{
    initDatabaseObj();
    initLogin();
    initLoginConnect();
    return 1;
}

void AwosStartSetup::initStartSystem() // steup workerSataton system
{
    switch (setp){
    case 0:
        emit loginPassSate("initInfor: start init system");
        break;
    case 1:
        emit loginPassSate("initInfor:init system use data.");
        initSetupInfo();
        break;
    case 2:
        emit loginPassSate("initInfor:init system network Zmq.");
        setupZmq();
        break;
    case 3:
        emit loginPassSate("initInfor:init remote 4G.");
        setupRemote4G();
        break;
    case 4:
        emit loginPassSate("initInfor:start ASCII message Parse");
        setupMessageParse();
        break;
    case 5:
        emit loginPassSate("initInfor:create awos main widget.");
        initAwosUIObject();
        break;
    case 6:
        emit loginPassSate("initInfor:create awos system all Contrls.");
        //initAllControls();
        break;
    case 7:
        emit loginPassSate("initInfor:load awos system UI data.");
        loadAwosUiFile();
        break;
    case 8:
        emit loginPassSate("initInfor:init MEssage Compox object.");
        initMessageComplex();
        break;
    case 9:
        emit loginPassSate("initInfor:init Remote 4G message connections.");
        init4GMessageSendSignal();
        break;
    case 10:
        emit loginPassSate("initInfor:init Zmq transfer ASCII message Connection.");
        initZmqMessageSendSignal();
        break;
    case 11:
        emit loginPassSate("initInfor:init sensor comm state.");
        initCommunicateStateUieditDataparseSignals();
        break;
    case 12:
        emit loginPassSate("initInfor:init kinds of sensor data tables.");
        initAllSensorDataTables();
        break;
    case 13:
        emit loginPassSate("initInfor:init all sensors collect data stroe connection.");
        initSensorDataStoreSignals();
        break;
    case 14:
        emit loginPassSate("initInfor:init sub contrls scale.");
        initScaleSubContrlConnection();
        break;
    case 15:
        emit loginPassSate("initInfor:init all contrls max or min size adjust.");
        optionContrlShowOrCloseConnection();
        break;
    case 16:
        emit loginPassSate("initInfor:init ASCII message compose.");
        initMessagesSendConnection();
        break;
    case 17:
        emit loginPassSate("initInfor:init telegram system real time data connections");
        initTelegramRealTimeSystemDatas();
        break;
    case 18:
        emit loginPassSate("initInfor:init Mater & spacil telegarm connections.");
        initTelegramSystemDataConnection();
        break;
    case 19:
        emit loginPassSate("initInfor:init system Devices connection.");
        initDeviceCFGConnection();
        break;
    case 20:
        emit loginPassSate("initInfor:init Tset Data config connections.");
        initTestPortCFGConnection();
        break;
    case 21:
        emit loginPassSate("initInfor:init 3616 self config docment v10 file.");
        init36CFGConnection();// 3616自身配置文档v10 链接函数
        break;
    case 22:
        emit loginPassSate("initInfor:init Affix 9 Message");
        initAFFIX9Message();
        break;
    case 23:
        emit loginPassSate("initInfor:init Affix 9 data parse connection");
        initAffix9MessagesCommandConnetion();
        break;
    case 24:
        emit loginPassSate("initInfor:test buttn connections");
        break;
    case 25:
        emit loginPassSate("initInfor:start system heartbeat contrl.");
        initHeartbeatContrlConnect();
        break;
    case 26:
        emit loginPassSate("initInfor:setup system main widget fram.");
        setupAwosSystemUI();
        break;
    case 27:
        emit loginPassSate("initInfor:update awos system informations.");
        updateAllSystemInformations();
        break;
    case 28:
        emit loginPassSate("initInfor:init trend metar.");
        initTrendMetarOption();
        break;
    case 30:
        emit loginPassSate("initInfor:init All sensors data.");
        break;
    case 31:
        emit loginPassSate("initInfor:init user Manage.");
        _init_user_Manage();
        break;
    case 32:
        emit loginPassSate("initInfor:Allot User Power.");
        allotUserPower();
        //emit messageParse->notTrendMetar("wind=3333333/rvr=p2000");
        break;
    case 33:
        break;
    case 34:
        break;
    case 35:
        emit
        init_rvrPolluteCfg();
        break;

    case 37:
        emit loginPassSate("initInfor:Start system succeed.loging will close.");
        break;

    case 38:
        emit loginPassSate("end");
        break;

    default:
        rebootZmqChick();
        break;
    }
    if(setp < 1000){
        setp++;
    }
    else{
        setp = 100;
    }
}

void AwosStartSetup::initSetupInfo()
{
    if(!proData){
        proData = new ProData();
    }
    //qDebug()<<"load system every everything config data。";
}

void AwosStartSetup::initLogin()
{
    if(!user){
        user = new AwosAdmin();
        user->setGeometry(220,220,520,260);
        user->drawInputLine();
        user->show();
    }
}

void AwosStartSetup::initLoginConnect()
{
    if(user && database){
        connect(user,SIGNAL(searchUser(QString,LoginQueue))
                ,this,SLOT(userDataSearch(QString,LoginQueue)));
        connect(this,SIGNAL(loginPassSate(QString))
                ,user,SLOT(loginResult(QString)));
        connect(user,SIGNAL(setupSystem(bool))
                ,this,SLOT(initSetupTimer(bool)));
    }
}

int AwosStartSetup::loadAwosUiFile()
{
    //加载 area.ini 配置文件
    int areaNum = proData->awosDataModel->inUsedWay->awosRunwayAreasSet->value("runWayNum/Num").toInt();
    int heigh = AwosUI->height() - 95 - 60;
    int roseHeigh = heigh * 5 / 12;
    int roseWidth = (AwosUI->width() - 106) / 3;
    for(int num = 1;num <= areaNum; num++){
        WindRoseArea *windarea = new  WindRoseArea(AwosUI);
        RunWayDataArea *dataArea = new RunWayDataArea(AwosUI);
        int runwayFlag,airportId,runWayId,visId,windId,cloudId,humitempId;
        int presId,weatherId,morMax,rvrMax,morMin,rvrMin;
        QString location,nameStr;
        bool showFlag;
        runwayFlag = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1Flag").arg(num)).toInt();
        airportId = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1AirportId").arg(num)).toInt();
        runWayId = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1Id").arg(num)).toInt();
        visId = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1VisId").arg(num)).toInt();
        windId = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1WindId").arg(num)).toInt();
        cloudId = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1CloudId").arg(num)).toInt();
        humitempId = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1HumiTempId").arg(num)).toInt();
        presId = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1PressId").arg(num)).toInt();
        weatherId = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1WeatherId").arg(num)).toInt();
        location = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1location").arg(num)).toString();
        nameStr = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1Name").arg(num)).toString();
        showFlag = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1show").arg(num)).toBool();
        morMax = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1MorWaringMaxValue").arg(num)).toInt();
        rvrMax = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1RvrWaringMaxValue").arg(num)).toInt();
        morMin = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1MorWaringMinValue").arg(num)).toInt();
        rvrMin = proData->awosDataModel->inUsedWay->awosRunwayAreasSet
                ->value(QString("runWays/runWay%1RvrWaringMinValue").arg(num)).toInt();
        if(nameStr.split("-",QString::SkipEmptyParts).length() >= 2)
        { //中间区域
            nameStr = nameStr.mid(0,5);
            qDebug()<<"run way mid:"<<nameStr;
            windarea->setRunwayName(nameStr);
            windarea->setEnablecloudCtl(false);
            windarea->setGeometry(94 + 1 + roseWidth + 1,96 - 20,roseWidth,roseHeigh - 1);
            dataArea->setRunwayName(nameStr);
            dataArea->setGeometry(94 + 1 + roseWidth + 1,heigh * 7 / 12 + 95 - 20 - 20 + 1
                                  ,roseWidth,roseHeigh - 2);

            // 中间区域的天气现象仪安装处理。
            Weather *sensorweather = new Weather();
            sensorweather->setRunFlag(runwayFlag);
            sensorweather->setAirportId(airportId);
            sensorweather->setRunWayId(runWayId);
            sensorweather->setweatherId(weatherId);
            sensorweather->setRunwayName(nameStr);
            sensorweather->setLocation(location);
            proData->awosDataModel->inUsedWay->weatherList.push_back(sensorweather);
        }
        else
        {  //左侧区域
            //跑道
            nameStr = nameStr.mid(0,2);
            int runNumber = nameStr.toInt();
            if(runNumber < 18 || runNumber == 36){

                //显示左侧区域 0~17
                windarea->setRunwayName(nameStr);
                windarea->setGeometry(94 + 1,96 - 20,roseWidth,roseHeigh - 1);
                dataArea->setRunwayName(nameStr);
                dataArea->setGeometry(94 + 1,heigh * 7 / 12  + 95 - 20 - 20 + 1
                                      ,roseWidth,roseHeigh - 2);

                //跑道
                RunWay *runway = new RunWay(AwosUI);
                runway->setFlag(runwayFlag);
                runway->setAirportId(airportId);
                runway->setRunWayId(runWayId);
                runway->setGeometry(98 + 200,(AwosUI->height() - 155) * 5 / 12 + 89
                                    ,AwosUI->width() - 110 - 400
                                    ,(AwosUI->height() - 155) / 6 - 48 );
                runway->setHeadName(QString("%1").arg(runNumber));
                runway->setRearName(QString("%1").arg(runNumber + 18));
                if(runNumber == 36){
                    runway->setRearName(QString("%1").arg(18));
                    runway->setHeadName(QString("%1").arg(0));
                }
                runway->installEventFilter(AwosUI);
                //bool showFlag = proData->awosDataModel->runWay->awosRunwayAreasSet
                //                ->value(QString("runWays/runWay%1show").arg(num)).toBool();
                if(showFlag){
                    runway->show();
                    currentShowRunWayID = runWayId;//保存当前打开的跑道
                }
                else{
                    runway->hide();
                }
                proData->awosDataModel->inUsedWay->runwaylist.push_back(runway);

                //云高
                AwosSensorCloud *sensorCloud = new AwosSensorCloud(AwosUI);
                sensorCloud->setRunFlag(runwayFlag);
                sensorCloud->setAirportId(airportId);
                sensorCloud->setRunWayId(runWayId);
                sensorCloud->setCloudId(cloudId);
                sensorCloud->setRunwayName(nameStr);
                sensorCloud->setLocation(location);
                sensorCloud->setGeometry(97,(AwosUI->height() - 155) * 5 / 12 + 77
                                         ,188,(AwosUI->height() - 155) / 6 - 24);
                sensorCloud->installEventFilter(AwosUI);
                if(showFlag){
                    qDebug()<<"show or closed Cloud Sensor Com UI:"
                           <<QString("%1").arg(runNumber);
                    sensorCloud->show();
                }
                else{
                    sensorCloud->hide();
                }
                proData->awosDataModel->inUsedWay->cloudSensorList.push_back(sensorCloud);

                //气压
                Press *sensorPress = new Press();
                sensorPress->setRunFlag(runwayFlag);
                sensorPress->setAirportId(airportId);
                sensorPress->setRunWayId(runWayId);
                sensorPress->setPressId(presId);
                sensorPress->setRunwayName(nameStr);
                sensorPress->setLocation(location);
                proData->awosDataModel->inUsedWay->pressList.push_back(sensorPress);

                // 天气
                Weather *sensorweather = new Weather();
                sensorweather->setRunFlag(runwayFlag);
                sensorweather->setAirportId(airportId);
                sensorweather->setRunWayId(runWayId);
                sensorweather->setweatherId(weatherId);
                sensorweather->setRunwayName(nameStr);
                sensorweather->setLocation(location);
                proData->awosDataModel->inUsedWay->weatherList.push_back(sensorweather);
            }
            else{ //右侧区域

                //显示右侧区域 18~35 跑道
                windarea->setRunwayName(nameStr);
                windarea->setGeometry(94 + 1 + (AwosUI->width() - 106)  * 2 / 3 + 2,
                                      76,roseWidth,roseHeigh - 1);//调整 - 20
                dataArea->setRunwayName(nameStr);
                dataArea->setGeometry(94 + 1 + (AwosUI->width() - 106)  * 2 / 3 + 2,
                                      heigh * 7 / 12  + 56,roseWidth,roseHeigh - 2);//调整 - 20 - 20

                //云高
                AwosSensorCloud *sensorCloud = new AwosSensorCloud(AwosUI);
                sensorCloud->setRunFlag(runwayFlag);
                sensorCloud->setAirportId(airportId);
                sensorCloud->setRunWayId(runWayId);
                sensorCloud->setCloudId(cloudId);
                sensorCloud->setRunwayName(nameStr);
                sensorCloud->setLocation(location);
                sensorCloud->setGeometry(AwosUI->width() - 199,(AwosUI->height() - 155) * 5 / 12  + 77,188,(AwosUI->height() - 155) / 6 - 24);
                sensorCloud->installEventFilter(AwosUI);
                if(showFlag){
                    sensorCloud->show();
                }
                else{
                    sensorCloud->hide();
                }
                proData->awosDataModel->inUsedWay->cloudSensorList.push_back(sensorCloud);

                //气压
                Press *sensorPress = new Press();
                sensorPress->setRunFlag(runwayFlag);
                sensorPress->setAirportId(airportId);
                sensorPress->setRunWayId(runWayId);
                sensorPress->setPressId(presId);
                sensorPress->setRunwayName(nameStr);
                sensorPress->setLocation(location);
                proData->awosDataModel->inUsedWay->pressList.push_back(sensorPress);

                // 天气
                Weather *sensorweather = new Weather();
                sensorweather->setRunFlag(runwayFlag);
                sensorweather->setAirportId(airportId);
                sensorweather->setRunWayId(runWayId);
                sensorweather->setweatherId(weatherId);
                sensorweather->setRunwayName(nameStr);
                sensorweather->setLocation(location);
                proData->awosDataModel->inUsedWay->weatherList.push_back(sensorweather);
            }
            qDebug()<<"run number:"<<runNumber;
        }
        windarea->setRunFlag(runwayFlag);
        windarea->setAirportId(airportId);
        windarea->setRunWayId(runWayId);
        windarea->setVisId(visId);
        windarea->setWindId(windId);
        windarea->setCloudId(cloudId);
        windarea->setLocation(location);
        dataArea->setRunFlag(runwayFlag);
        dataArea->setAirportId(airportId);
        dataArea->setRunWayId(runWayId);
        dataArea->setWindId(windId);
        dataArea->setHumitempId(humitempId);
        dataArea->setLocation(location);
        windarea->showSubContrl();
        dataArea->showSubContrl();
        if(showFlag){
            windarea->show();
            dataArea->show();
            currentwindareaFlag = runWayId;
            currentdataAreaFlag = runWayId;
        }
        else{
            windarea->hide();
            dataArea->hide();
        }
        windarea->setMorMax(morMax);
        windarea->setRvrMax(rvrMax);
        windarea->setMorMin(morMin);
        windarea->setRvrMin(rvrMin);
        windarea->installEventFilter(AwosUI);
        dataArea->installEventFilter(AwosUI);
        proData->awosDataModel->inUsedWay->runwayNameAndIdList.push_back(nameStr);
        proData->awosDataModel->inUsedWay->roseAreaList.push_back(windarea);
        proData->awosDataModel->inUsedWay->dataAreaList.push_back(dataArea);
    }
    return 1;
}


void AwosStartSetup::initMessageComplex()
{
    if(!dataSend){
        dataSend = new MessageSend();
    }
}

void AwosStartSetup::init4GMessageSendSignal()
{
    if(remote4G && dataSend){
        connect(dataSend,SIGNAL(sendMessage(QByteArray))
                ,remote4G,SIGNAL(writeCDMA(QByteArray)));
    }
}

void AwosStartSetup::initZmqMessageSendSignal()
{
    if(zmqworker && dataSend){
        connect(dataSend,SIGNAL(sendMessage(QByteArray))
                ,zmqworker,SLOT(writezmq(QByteArray))
                ,Qt::QueuedConnection);
    }
}

void AwosStartSetup::setupZmq()
{
    if(!zmqworker){
        zmqworker =  new RVR_Zmq_Worker();
        connect(this,SIGNAL(setupZmqThread())
                ,zmqworker,SLOT(initZmq())
                ,Qt::QueuedConnection);
        connect(this,SIGNAL(setupZmqComm(QString,int,int))
                ,zmqworker,SLOT(setPort(QString,int,int))
                ,Qt::QueuedConnection);
        connect(this,SIGNAL(rebootZmq())
                ,zmqworker,SLOT(rebootZmq())
                ,Qt::QueuedConnection);
    }
    emit setupZmqThread();
    emit setupZmqComm(proData->comm->ip
                      ,proData->comm->reciPort
                      ,proData->comm->sendPort);
    qDebug()<<"SC zmq ip:"<<proData->comm->ip;
}

void AwosStartSetup::setupRemote4G()
{
    if(!remote4G){
        remote4G = new SetupThread();
    }
}

void AwosStartSetup::setupMessageParse()
{
    //qDebug()<<"init message object。";
    if(!messageParse){
        messageParse = new MessageParse();
    }
}

void AwosStartSetup::initAwosUIObject()
{
    minAwos = new WorkStation();
    AwosUI = (QWidget*) minAwos;
}

void AwosStartSetup::initCommunicateStateUieditDataparseSignals()
{
    //qDebug()<<"init communication ，message and sensor's staus signal and so on。";
    // internet data communicate and data parse
    if(zmqworker && messageParse){
        connect(zmqworker,SIGNAL(newData(QByteArray))
                ,messageParse,SLOT(getMessageBarry(QByteArray))
                ,Qt::QueuedConnection);
    }
    // 4G data communicate and data parse
    if(remote4G && messageParse){
        connect(remote4G,SIGNAL(reciMessage(QByteArray))
                ,messageParse,SLOT(getMessageBarry(QByteArray)));
    }

    if(messageParse){

        //awos subcontrls datas
        connect(messageParse,SIGNAL(windDataSignal(SensorMap))
                ,this,SLOT(awosWindData(SensorMap)));
        connect(messageParse,SIGNAL(humiTempDataSignal(SensorMap))
                ,this,SLOT(awosHumiTempData(SensorMap)));
        connect(messageParse,SIGNAL(rvrDataSignal(SensorMap))
                ,this,SLOT(awosRvrData(SensorMap)));
        connect(messageParse,SIGNAL(cloudDataSignal(SensorMap))
                ,this,SLOT(awosCloudData(SensorMap)));
        connect(messageParse,SIGNAL(atmospherePressDataSignal(SensorMap))
                ,this,SLOT(awosAtmospherePressData(SensorMap)));
        connect(messageParse,SIGNAL(rainDataSignal(SensorMap))
                ,this,SLOT(awosRainData(SensorMap)));
        connect(messageParse,SIGNAL(phenomenaWeatherDataSignal(SensorMap))
                ,this,SLOT(awosPhenomenaWeatherData(SensorMap)));
        connect(messageParse,SIGNAL(prevailingVisibilityDataSignal(SensorMap))
                ,this,SLOT(awosPrevailingVisibilityData(SensorMap)));
        connect(messageParse,SIGNAL(manualInputDataDataSignal(SensorMap))
                ,this,SLOT(awosManualInputDataData(SensorMap)));
    }
}

void AwosStartSetup::initDatabaseObj()
{
    if(!database){
        database = new RVR_Data_Due();
    }
}

void AwosStartSetup::initAllSensorDataTables()
{
    //qDebug()<<"init database tables.";
    if(!database){
        qDebug()<<"Awos数据库初始化启动失败,数据将无法保存到数据库中。";
        return ;
    }
    //***数据库不支持3616ID这样以数字开头的命名方式做数据字段名称(已改 字段域加上“SC_”解决)

    //user data store
    int userTableNum = proData->user->tableUser->value("tablesUser/tableNum").toInt();
    for(int i = 1;i <= userTableNum;i++){
        QString userTableName = proData->user->tableUser
                ->value(QString("tables/table%1Name").arg(i)).toString().trimmed();
        QStringList userFielStr = ((proData->user->tableUser
                                    ->value(QString("tables/table%1Field")
                                            .arg(i)).toString()).trimmed()).split(",");
        database->configDatabaseTable(userTableName,userFielStr);
    }

    //hum and temp data's tables store
    int humTempTableNum = proData->databaseTables->tablesHumTemp
            ->value("tablesHumTemp/tableNum").toInt();

    //qDebug()<<"hum and temp tables -->Num:"<<humTempTableNum;
    //qDebug()<<"hum and temp tables -->keys:"<<proData->databaseTables->tablesHumTemp->allKeys();

    for(int i = 1;i <= humTempTableNum;i++){
        QString humTempTableName = proData->databaseTables->tablesHumTemp
                ->value(QString("tables/table%1Name").arg(i)).toString();
        QStringList  humTempFieldStr = ((proData->databaseTables->tablesHumTemp
                                         ->value(QString("tables/table%1Field").arg(i))
                                         .toString()).trimmed()).split(",");
        //qDebug()<<"table name:"<<humTempTableName<<"table fieldStr:"<<humTempFieldStr;
        database->configDatabaseTable(humTempTableName,humTempFieldStr);
    }

    //wind data store
    int windTableNum = proData->databaseTables->tablesWind
            ->value("tablesWind/tableNum").toInt();
    for(int i = 1;i <= windTableNum;i++){
        QString windTableName = proData->databaseTables->tablesWind
                ->value(QString("tables/table%1Name").arg(i)).toString();
        QStringList  windFieldStr = ((proData->databaseTables->tablesWind
                                      ->value(QString("tables/table%1Field").arg(i)).toString()).trimmed()).split(",");
        database->configDatabaseTable(windTableName,windFieldStr);
    }

    //vis data store
    int visTableNum = proData->databaseTables->tablesVIS
            ->value("tablesVIS/tableNum").toInt();
    for(int i = 1;i <= visTableNum;i++){
        QString visTableName = proData->databaseTables->tablesVIS
                ->value(QString("tables/table%1Name").arg(i)).toString();
        QStringList  visFieldStr = ((proData->databaseTables->tablesVIS->value(QString("tables/table%1Field").arg(i))
                                     .toString()).trimmed()).split(",");
        database->configDatabaseTable(visTableName,visFieldStr);
    }

    //cloud data store
    int cloudTableNum = proData->databaseTables->tablesCloud
            ->value("tablesCloud/tableNum").toInt();
    for(int i = 1;i <= cloudTableNum;i++){
        QString cloudTableName = proData->databaseTables->tablesCloud
                ->value(QString("tables/table%1Name").arg(i)).toString();
        QStringList  cloudFieldStr = ((proData->databaseTables->tablesCloud->value(QString("tables/table%1Field").arg(i))
                                       .toString()).trimmed()).split(",");
        database->configDatabaseTable(cloudTableName,cloudFieldStr);
    }

    //press data store
    int pressTableNum = proData->databaseTables->tablesPress
            ->value("tablesPress/tableNum").toInt();
    for(int i = 1;i <= pressTableNum;i++){
        QString pressTableName = proData->databaseTables->tablesPress
                ->value(QString("tables/table%1Name").arg(i)).toString();
        QStringList  pressFieldStr = ((proData->databaseTables->tablesPress->value(QString("tables/table%1Field").arg(i))
                                       .toString()).trimmed()).split(",");
        database->configDatabaseTable(pressTableName,pressFieldStr);
    }

    //pv data store
    int pvTableNum = proData->databaseTables->tablesPV
            ->value("tablesPV/tableNum").toInt();
    for(int i = 1;i <= pvTableNum;i++){
        QString pvTableName = proData->databaseTables->tablesPV
                ->value(QString("tables/table%1Name").arg(i)).toString();
        QStringList  pvFieldStr = ((proData->databaseTables->tablesPV->value(QString("tables/table%1Field").arg(i))
                                    .toString()).trimmed()).split(",");
        database->configDatabaseTable(pvTableName,pvFieldStr);
    }

    //BIASLIGHT data store
    int BIASLIGHTTableNum = proData->databaseTables->tablesBIASLIGHT
            ->value("tablesBIASLIGHT/tableNum").toInt();
    for(int i = 1;i <= BIASLIGHTTableNum;i++){
        QString BIASLIGHTTableName = proData->databaseTables->tablesBIASLIGHT
                ->value(QString("tables/table%1Name").arg(i)).toString();
        QStringList  BIASLIGHTFieldStr = ((proData->databaseTables->tablesBIASLIGHT->value(QString("tables/table%1Field").arg(i))
                                           .toString()).trimmed()).split(",");
        database->configDatabaseTable(BIASLIGHTTableName,BIASLIGHTFieldStr);
    }

    //pw data store
    int pwTableNum = proData->databaseTables->tablesPW
            ->value("tablesPW/tableNum").toInt();
    for(int i = 1;i <= pwTableNum;i++){
        QString pwTableName = proData->databaseTables->tablesPW
                ->value(QString("tables/table%1Name").arg(i)).toString();
        QStringList  pwFieldStr = ((proData->databaseTables->tablesPW->value(QString("tables/table%1Field").arg(i))
                                    .toString()).trimmed()).split(",");
        database->configDatabaseTable(pwTableName,pwFieldStr);
    }

    //rain data store
    int vrainTableNum = proData->databaseTables->tablesRain
            ->value("tablesRain/tableNum").toInt();
    for(int i = 1;i <= vrainTableNum;i++)
    {
        QString rainTableName = proData->databaseTables->tablesRain
                ->value(QString("tables/table%1Name").arg(i)).toString();
        QStringList  rainFieldStr = ((proData->databaseTables->tablesRain->value(QString("tables/table%1Field").arg(i))
                                      .toString()).trimmed()).split(",");
        database->configDatabaseTable(rainTableName,rainFieldStr);
    }

    //waring store create
    int warTableNum = proData->databaseTables->tableWaringIfo
            ->value("tablesWaring/tableNum").toInt();
    for(int war = 1;war <= warTableNum;war++){
        QString waringName = proData->databaseTables->tableWaringIfo
                ->value(QString("tables/table%1Name").arg(war)).toString();
        QStringList waringFieldStr = (proData->databaseTables->tableWaringIfo
                                      ->value(QString("tables/table%1Field").arg(war))
                                      .toString()).trimmed().split(",");
        database->configDatabaseTable(waringName,waringFieldStr);
    }

    //other sensor User table
    int outSensorUserTableNum = proData->databaseTables->tableOtherSensorUser
            ->value("tablesOutSeonser/tableNum").toInt();
    for(int sensorOut = 1;sensorOut <= outSensorUserTableNum;sensorOut++){
        QString sensorName = proData->databaseTables->tableOtherSensorUser
                ->value(QString("tables/table%1Name").arg(sensorOut)).toString();
        QStringList outSensorFieldStr = (proData->databaseTables->tableOtherSensorUser
                                         ->value(QString("tables/table%1Field").arg(sensorOut))
                                         .toString()).trimmed().split(",");
        database->configDatabaseTable(sensorName,outSensorFieldStr);
    }
}

void AwosStartSetup::initSensorDataStoreSignals()
{
    //init sensor datas store
    if(messageParse){
        connect(messageParse,SIGNAL(windDataSignal(SensorMap))
                ,this,SLOT(windDataStore(SensorMap)));
        connect(messageParse,SIGNAL(humiTempDataSignal(SensorMap))
                ,this,SLOT(humiTempDataStore(SensorMap)));
        connect(messageParse,SIGNAL(rvrDataSignal(SensorMap))
                ,this,SLOT(rvrDataStore(SensorMap)));
        connect(messageParse,SIGNAL(cloudDataSignal(SensorMap))
                ,this,SLOT(cloudDataStore(SensorMap)));
        connect(messageParse,SIGNAL(atmospherePressDataSignal(SensorMap))
                ,this,SLOT(atmospherePressDataStore(SensorMap)));
        connect(messageParse,SIGNAL(rainDataSignal(SensorMap))
                ,this,SLOT(rainDataStore(SensorMap)));
        connect(messageParse,SIGNAL(phenomenaWeatherDataSignal(SensorMap))
                ,this,SLOT(phenomenaWeatherDataStore(SensorMap)));
        connect(messageParse,SIGNAL(prevailingVisibilityDataSignal(SensorMap))
                ,this,SLOT(prevailingVisibilityDataStore(SensorMap)));
        connect(messageParse,SIGNAL(BIASLIGHTDataSignal(SensorMap))
                ,this,SLOT(BIASLIGHTDataSignalDataStore(SensorMap)));
        connect(messageParse,SIGNAL(manualInputDataDataSignal(SensorMap))
                ,this,SLOT(manualInputDataDataStore(SensorMap)));
    }

    //init waring datas store
    if(messageParse){
        connect(this,SIGNAL(waringMessageStr(SensorMap))
                ,this,SLOT(waringDatastore(SensorMap)));
    }
}

void AwosStartSetup::setupAwosSystemUI()
{
    if(minAwos){
        minAwos->set_runWays_setting(proData->awosDataModel->runwayInfor->awosRunWaySet);
        minAwos->set_usedWay_setting(proData->awosDataModel->inUsedWay->awosRunwayAreasSet);
        minAwos->set_sensors_setting(proData->awosDataModel->sensorList->awosSensorListSet);
        minAwos->set_telegram_setting(proData->awosDataModel->telegram->awosTelegrmSet);
        minAwos->show();
    }
    qDebug()<<"启动工作站。";
    return ;
}

void AwosStartSetup::initScaleSubContrlConnection()
{
    if(minAwos){
        connect(minAwos,SIGNAL(sacleSubContrl())
                ,this,SLOT(scaleSubContrls()));
    }
}

void AwosStartSetup::initWaringConnection()
{
    if(minAwos){

    }
}

void AwosStartSetup::optionContrlShowOrCloseConnection()
{
    if(minAwos){
        connect(minAwos,SIGNAL(openOrClosedContrls(bool))
                ,this,SLOT(openOrcloseContrls(bool)));
    }
}

void AwosStartSetup::initMessagesSendConnection()
{
    if(minAwos){
        connect(minAwos,SIGNAL(AFTNConfigSet(MeaagseQueue))
                ,SLOT(AFTNSetSlot(MeaagseQueue)));
        connect(minAwos,SIGNAL(sendMetarTrendReqeust(MeaagseQueue))
                ,SLOT(sendMetarTrandRequestSlot(MeaagseQueue)));
    }
}

void AwosStartSetup::initTelegramRealTimeSystemDatas()
{
    telegramData["groupLeftAngle"]  = "      ///" ;
    telegramData["groupLeftSpeed1"] = "      ///" ;
    telegramData["groupLeftSpeed2"] = "      ///" ;
    telegramData["groupLeftAngleMin"] = "      ///" ;
    telegramData["groupLeftAngleMax"] = "      ///" ;
    telegramData["groupMIDIAngle"]    = "      ///" ;
    telegramData["groupMIDISpeed1"]   = "      ///" ;
    telegramData["groupMIDISpeed2"]   = "      ///" ;
    telegramData["groupMIDIAngleMin"] = "      ///" ;
    telegramData["groupMIDIAngleMax"] = "      ///" ;
    telegramData["groupRightAngle"]  = "      ///" ;
    telegramData["groupRightSpeed1"] = "      ///" ;
    telegramData["groupRightSpeed2"] = "      ///" ;
    telegramData["groupRightAngleMin"] = "      ///" ;
    telegramData["groupRightAngleMax"] = "      ///" ;
    telegramData["groupVisTenAvg"] = "      ///" ;
    telegramData["groupVisTenMin"] = "      ///" ;
    telegramData["groupVisTenDirection"]     = "      ///" ;
    telegramData["groupLeftRVRTenAvgValue"]  = "      ///" ;
    telegramData["groupLeftRVRTenMaxValue"] = "      ///";
    telegramData["groupLeftRVRTenMinValue"] = "      ///";
    telegramData["groupLeftRVRTendency"]     = "      ///" ;
    telegramData["groupMIDIRVRTenAvgValue"]  = "      ///" ;
    telegramData["groupMIDRVRTenMaxValue"] = "      ///";
    telegramData["groupMIDRVRTenMinValue"] = "      ///";
    telegramData["groupMIDIRVRTendency"]     = "      ///" ;
    telegramData["groupRightRVRTenAvgValue"] = "      ///" ;
    telegramData["groupRightRVRTenMaxValue"] = "      ///";
    telegramData["groupRightRVRTenMinValue"] = "      ///";
    telegramData["groupRightRVRTendency"]    = "      ///" ;
    telegramData["groupLeft1CloudCount"] = "      ///" ;
    telegramData["groupLeft1CloudHight"] = "      ///" ;
    telegramData["groupLeft2CloudCount"] = "      ///" ;
    telegramData["groupLeft2CloudHight"] = "      ///" ;
    telegramData["groupLeft3CloudCount"] = "      ///" ;
    telegramData["groupLeft3CloudHight"] = "      ///" ;
    telegramData["groupLeftIsSkyClear"] =  "      ///" ;
    telegramData["groupLeftIsVerVis"] =  "      ///" ;
    telegramData["groupLeftCloudBase"] =  "      ///" ;
    telegramData["groupRight1CloudCount"] = "      ///" ;
    telegramData["groupRight1CloudHight"] = "      ///" ;
    telegramData["groupRight2CloudCount"] = "      ///" ;
    telegramData["groupRight2CloudHight"] = "      ///" ;
    telegramData["groupRight3CloudCount"] = "      ///" ;
    telegramData["groupRight3CloudHight"] = "      ///" ;
    telegramData["groupRightIsSkyClear"] =  "      ///" ;
    telegramData["groupRightIsVerVis"] =  "      ///" ;
    telegramData["groupRightCloudBase"] =  "      ///" ;
    telegramData["groupLeftTem"]  = "      ///" ;
    telegramData["groupLeftDew"]  = "      ///" ;
    telegramData["groupLeftHum"]  = "      ///" ;
    telegramData["groupRightTem"] = "      ///" ;
    telegramData["groupRightDew"] = "      ///" ;
    telegramData["groupRightHum"] = "      ///" ;
    telegramData["groupPress"]    = "      ///" ;
    telegramData["groupCurrentWeather"]   = "      ///" ;
    telegramData["groupCloseTimeWeather"] = "      ///" ;
}

void AwosStartSetup::initTelegramSystemDataConnection()
{
    if(messageParse && minAwos){

        // real time data update
        connect(this,SIGNAL(updateTelegramRealTimeData(realDataMap,QString))
                ,minAwos,SLOT(setTelegramReportValuesSlot(realDataMap,QString)));

        // ask telegram data
        connect(messageParse,SIGNAL(telegramAskSubSignal(SensorMap))
                ,minAwos,SLOT(telegramAskSubSlot(SensorMap)));

        // show telegram data
        connect(messageParse,SIGNAL(telegramShowSubSignal(SensorMap))
                ,minAwos,SLOT(telegramShowSubSlot(SensorMap)));

        // 发给观测员的趋势报字符串
        connect(messageParse,SIGNAL(trendTrendMetar(QString))
                ,minAwos,SLOT(setTreandMetar(QString)));
    }
}

void AwosStartSetup::initDeviceCFGConnection()
{
    if(messageParse){
        connect(messageParse,SIGNAL(allModlesInformationSignal(SensorMap))
                ,minAwos,SLOT(dusSupplyModlesSlot(SensorMap)));
        connect(messageParse,SIGNAL(allSensorsInformationSignal(SensorMap))
                ,minAwos,SLOT(allSensorsInformationSlot(SensorMap)));
    }
}

void AwosStartSetup::initTestPortCFGConnection()
{
    if(messageParse && minAwos){
        connect(messageParse,SIGNAL(airportBackInfor(SensorMap))
                ,minAwos,SIGNAL(airBackInforSignal(SensorMap)));
        connect(messageParse,SIGNAL(runWayBackInfor(SensorMap))
                ,minAwos,SIGNAL(runWayBackInforSignal(SensorMap)));
        connect(messageParse,SIGNAL(MatchBackInfor(SensorMap))
                ,minAwos,SIGNAL(matchBackInforSignal(SensorMap)));
    }
}

void AwosStartSetup::init36CFGConnection()
{
    if(messageParse && minAwos){
        // 3616 自身配置返回信息链接函数
        connect(messageParse,SIGNAL(Configure3616Signal(SensorMap))
                ,minAwos,SIGNAL(Configure3616Signal(SensorMap)));
        connect(messageParse,SIGNAL(sensorStatusSignal(SensorMap))
                ,minAwos,SIGNAL(sensorStatusSignal(SensorMap)));
        connect(messageParse,SIGNAL(sensorLIBsSignal(SensorMap))
                ,minAwos,SIGNAL(sensorLIBsSignal(SensorMap)));
        connect(messageParse,SIGNAL(serialCardParamersSignal(SensorMap))
                ,minAwos,SIGNAL(serialCardParamersSignal(SensorMap)));
        connect(messageParse,SIGNAL(ExternSensorInfoListSignale(SensorMap))
                ,minAwos,SIGNAL(ExternSensorInfoListSignale(SensorMap)));
    }
}

void AwosStartSetup::initAFFIX9Message()
{
    AFFIX9mess = new AFFIX9Mesage(this);
    connect(messageParse,SIGNAL(Configure3616Signal(SensorMap)),
            AFFIX9mess,SLOT(_Store_3616_Deceive_Infor(SensorMap)));
    connect(AFFIX9mess,SIGNAL(storeAffix9ToDatabaseSignal(QString,QString))
            ,database,SIGNAL(addDataNotField(QString,QString)));
    connect(AFFIX9mess,SIGNAL(update_all_sensor_devices(QString)),
            this,SLOT(updataAllSensorDatas(QString)));
}

void AwosStartSetup::initAffix9MessagesCommandConnetion()
{
    if(minAwos && AFFIX9mess){
        connect(minAwos,SIGNAL(Affix9MessageSignals(QString))
                ,AFFIX9mess,SLOT(AFFIX9CommandOptions(QString)));
        // 完整metar报发送链接
        connect(minAwos,SIGNAL(sendOkMetarSignal(QString))
                ,AFFIX9mess,SLOT(AFFIX9CommandOptions(QString)));
    }
    //all the config information set Messages
    if(AFFIX9mess && dataSend){
        connect(AFFIX9mess,SIGNAL(AFFIX9Message(QString,SC_COMMD))
                ,dataSend,SLOT(dataUnit3616MessageDue(QString,SC_COMMD)));
    }
    if(AFFIX9mess && minAwos){
        connect(AFFIX9mess,SIGNAL(backRequeryAFFIX9menberSignal(QString,InforData))
                ,minAwos,SIGNAL(backRequeryAFFIX9menberSignal(QString,InforData)));

        connect(AFFIX9mess,SIGNAL(AFFIX9NewMessageSendUp(QString,InforData))
                ,minAwos,SIGNAL(AFFIX9NewMessageSendUp(QString,InforData)));
    }
    if(messageParse && AFFIX9mess){
        connect(messageParse,SIGNAL(openModelSignal(QString))
                ,AFFIX9mess,SLOT(AFFIX9CommandOptions(QString)));
        connect(messageParse,SIGNAL(state36Signal(QString))
                ,AFFIX9mess,SLOT(AFFIX9CommandOptions(QString)));
        connect(messageParse,SIGNAL(backLightSignal(QString))
                ,AFFIX9mess,SLOT(AFFIX9CommandOptions(QString)));
    }
}

void AwosStartSetup::initHeartbeatContrlConnect()
{
    connect(messageParse,SIGNAL(state36Signal(QString))
            ,SLOT(heartbeatContrl(QString)));
}

void AwosStartSetup::updateAllSystemInformations()
{ // 根据数据查询过程需提供的数据顺序要求。首次刷新必须有序进行
    if(minAwos){
        emit minAwos->Affix9MessageSignals("airport:刷新");
        emit minAwos->Affix9MessageSignals("runWay:刷新");
        emit minAwos->Affix9MessageSignals("infor36:刷新");
        emit minAwos->Affix9MessageSignals("cardParameter36:刷新");
        emit minAwos->Affix9MessageSignals("statue36:刷新");
        emit minAwos->Affix9MessageSignals("lib36:刷新");
        emit minAwos->Affix9MessageSignals("testAirport:刷新");
        emit minAwos->Affix9MessageSignals("testRunWay:刷新");
        emit minAwos->Affix9MessageSignals("testSensor:刷新");
    }
}

void AwosStartSetup::updataAllSensorDatas(QString type)
{
    if(type == "all" || type == "initSensorInfoShow")
    {
        emit minAwos->Affix9MessageSignals("wind:find");
        emit minAwos->Affix9MessageSignals("RVR:find");
        emit minAwos->Affix9MessageSignals("tempHumi:find");
        emit minAwos->Affix9MessageSignals("custom:find");
    }
    else if(type == "wind")
    {
        emit minAwos->Affix9MessageSignals("wind:find");
    }
    else if(type == "RVR")
    {
        emit minAwos->Affix9MessageSignals("RVR:find");
    }
    else if(type == "tempHumi")
    {
        emit minAwos->Affix9MessageSignals("tempHumi:find");
    }
    else if(type == "custom")
    {
        emit minAwos->Affix9MessageSignals("custom:find");
    }
}

void AwosStartSetup::initTrendMetarOption()
{
    trendMetar = new ForCasterTrend();

    //预报员界面显示Metar报（没有趋势）
    connect(messageParse,SIGNAL(notTrendMetar(QString))
            ,SLOT(showForCasterTrendUI(QString)));
    connect(this,SIGNAL(noTrendMetarCtxSignal(QString))
            ,trendMetar,SLOT(setNoTrendMetarCtx(QString)));
    connect(this,SIGNAL(noTrendMetarCtxSignal(QString))
            ,minAwos->MetarEcodecContrl
            ,SLOT(_update_Forcaster_Sub_Telegram_Ctx(QString)));
    //预报员界面发送趋势报
    connect(trendMetar,SIGNAL(sendMetarTrend(QString))
            ,minAwos,SIGNAL(Affix9MessageSignals(QString)));
    trendMetar->setWindowTitle("请求添加趋势");
    trendMetar->setGeometry(200,100,800,400);
    trendMetar->hide();
}
/*  ---------------------------
 *  function description
 *  set user power。
 *  ---------------------------
 */

void AwosStartSetup::_init_user_Manage()
{
    _user_Manage = new UserManager();
    connect(database
            ,SIGNAL(_table_View())
            ,_user_Manage
            ,SLOT(_set_user_table_Model()));
    connect(_user_Manage,SIGNAL(user_options_signal(QString))
            ,SLOT(_set_options_(QString)));
    _user_Manage->setGeometry(100,100,800,400);
    _user_Manage->setWindowTitle("用户管理");
    _user_Manage->hide();
}

void AwosStartSetup::init_rvrPolluteCfg()
{
    rvrPolluteCfg = new RVRCFG();
    connect(messageParse,SIGNAL(VR800CFGBack(QString)),rvrPolluteCfg
            ,SLOT(m_config_message(QString)));
    connect(rvrPolluteCfg,SIGNAL(dataCommandOptions(QString)),AFFIX9mess
            ,SLOT(AFFIX9CommandOptions(QString)));
    connect(messageParse,SIGNAL(VR800CorrectBack(DataMap)),rvrPolluteCfg
            ,SLOT(m_set_all_values(DataMap)));
    connect(minAwos,SIGNAL(pollute_Show()),rvrPolluteCfg,SLOT(show_cfg()));
    rvrPolluteCfg->setGeometry(400,400,600,500);
    rvrPolluteCfg->setMinimumSize(600,500);
    rvrPolluteCfg->setMaximumSize(600,500);
    rvrPolluteCfg->hide();
}

void AwosStartSetup::allotUserPower()
{
    if(_grade == "管理"){
        _user_Manage->show();
        _user_Manage->_get_user_infor();
    }
    messageParse->setUserType(_grade);
    minAwos->_set_user_typeStr(_grade);
}

void AwosStartSetup::scaleSubContrls()
{
    int heigh = AwosUI->height() - 95 - 60;
    int roseHeigh = heigh * 5 / 12;// -1 向下1个pix
    int awosW106 = AwosUI->width() - 106;
    int roseWidth = awosW106 / 3;
    int awosH155 = AwosUI->height() - 155;
    int awosW199 = AwosUI->width() - 199;
    int awosW110 = AwosUI->width() - 110;

    QString runName;
    int roseNumber = proData->awosDataModel->inUsedWay->roseAreaList.length();
    for(int rose = 0; rose < roseNumber;rose++){
        runName = proData->awosDataModel->inUsedWay->roseAreaList.value(rose)->runwayName();
        //qDebug()<<"name:"<<runName;
        if(runName.split("-",QString::SkipEmptyParts).length() >= 2){
            proData->awosDataModel->inUsedWay->roseAreaList.value(rose)
                    ->setGeometry(94 + 1 + roseWidth + 1,96 - 20,roseWidth,roseHeigh - 1);
            proData->awosDataModel->inUsedWay->roseAreaList.value(rose)->showSubContrl();
        }
        else{
            if(runName.trimmed().toInt() < 18){
                proData->awosDataModel->inUsedWay->roseAreaList.value(rose)
                        ->setGeometry(94 + 1,96 - 20,roseWidth,roseHeigh - 1);
                proData->awosDataModel->inUsedWay->roseAreaList.value(rose)->showSubContrl();
            }
            else{
                proData->awosDataModel->inUsedWay->roseAreaList.value(rose)
                        ->setGeometry(94 + 1 + awosW106  * 2 / 3 + 2
                                      ,96 - 20,roseWidth,roseHeigh - 1);
                proData->awosDataModel->inUsedWay->roseAreaList.value(rose)->showSubContrl();
            }
        }
    }
    int dataNumber = proData->awosDataModel->inUsedWay->dataAreaList.length();
    for(int data = 0;data < dataNumber;data++){
        runName = proData->awosDataModel->inUsedWay->dataAreaList.value(data)->runwayName();
        //qDebug()<<"name:"<<runName;
        if(runName.split("-",QString::SkipEmptyParts).length() >= 2){
            proData->awosDataModel->inUsedWay->dataAreaList.value(data)
                    ->setGeometry(94 + 1 + roseWidth + 1,heigh * 7 / 12 + 95 - 20 - 20 + 1
                                  ,roseWidth,roseHeigh - 2);
            proData->awosDataModel->inUsedWay->dataAreaList.value(data)->showSubContrl();
        }
        else{
            if(runName.trimmed().toInt() < 18){
                proData->awosDataModel->inUsedWay->dataAreaList.value(data)
                        ->setGeometry(94 + 1,heigh * 7 / 12  + 95 - 20 - 20 + 1
                                      ,roseWidth,roseHeigh - 2);
                proData->awosDataModel->inUsedWay->dataAreaList.value(data)->showSubContrl();
            }
            else{
                proData->awosDataModel->inUsedWay->dataAreaList.value(data)
                        ->setGeometry(94 + 1 + awosW106  * 2 / 3 + 2
                                      ,heigh * 7 / 12  + 95 - 20 - 20 + 1
                                      ,roseWidth,roseHeigh - 2);
                proData->awosDataModel->inUsedWay->dataAreaList.value(data)->showSubContrl();
            }
        }
    }

    int runNumber = proData->awosDataModel->inUsedWay->runwaylist.length();
    for(int run = 0; run < runNumber; run++){
        proData->awosDataModel->inUsedWay->runwaylist.value(run)
                ->setGeometry(98 + 200
                              ,awosH155 * 5 / 12 + 95 + 20 - 20 - 6
                              ,awosW110 - 400
                              ,awosH155 / 6 - 40 - 8 );
    }

    int cloudNumber = proData->awosDataModel->inUsedWay->cloudSensorList.length();
    for(int run = 0; run < cloudNumber; run++){
        int runnumberdata = proData->awosDataModel->inUsedWay->cloudSensorList.value(run)
                ->runwayName().trimmed().toInt();
        qDebug()<<"scale cloud:"<<QString("%1").arg(runnumberdata);
        if(runnumberdata < 18){
            proData->awosDataModel->inUsedWay->cloudSensorList.value(run)
                    ->setGeometry(97,awosH155 * 5 / 12 + 77
                                  ,188,awosH155 / 6 - 24);
        }
        else{
            proData->awosDataModel->inUsedWay->cloudSensorList.value(run)
                    ->setGeometry( awosW199
                                  ,awosH155 * 5 / 12  + 77,188
                                  ,awosH155 / 6 - 24);
        }
    }
}

void AwosStartSetup::heartbeatContrl(QString str)
{
    QString command;
    command = str.split(":").value(0);
    if(command == "Data_36heartBeat"){
        //qDebug()<<"beat contrls str:"<<str;
        heartbeatNumber = 0;
    }
    return ;
}

void AwosStartSetup::rebootZmqChick()
{
    heartbeatNumber++;
    //qDebug()<<"heartbeart number:"<<heartbeatNumber<<"setp:"<<setp;
    if(heartbeatNumber > 100){
        heartbeatNumber = 0;
        emit rebootZmq();
        emit minAwos->addWaring("system disconnect to 3616");
    }
}

void AwosStartSetup::_set_options_(QString data)
{
    QString _option,_data,_sub_option,_sub_data;
    _option = data.split(":").value(0).trimmed();
    _data = data.split(":").value(1).trimmed();
    if(_option == "update"){ //update:tableName=admin
        _sub_option = _data.split("=").value(0);
        _sub_data = _data.split("=").value(1);
        if(_sub_option == "tableName"){
            QStringList list;
            list<<"用户"<<"密码"<<"权限";
            database->select_table_View(_user_Manage->_get_Model_object()
                                        ,_sub_data,list);
        }
    }
    else if(_option == "add")
    {
        userMap map;
        QStringList _list,sqlList;
        _list = _data.split("/");
        int v_len = _list.length();
        QString v_value;
        for(int v = 0;v < v_len;v++){
            v_value.clear();
            v_value = _list.value(v);
            map[v_value.split("=").value(0)] = v_value.split("=").value(1);
        }
        //add:name=%1/password=%2/grade=%3
        sqlList<<map["name"]<<map["password"]<<map["grade"];
        database->add_user_To_table("admin",sqlList);
    }
    else if(_option == "delete"){
        //QString("delete:v1=%1/v2=%2/v3=%3")
        userMap map2;
        QStringList _list2,sqlList2;
        _list2 = _data.split("/");
        int v_len2 = _list2.length();
        QString v_value2;
        for(int v = 0;v < v_len2;v++){
            v_value2.clear();
            v_value2 = _list2.value(v);
            map2[v_value2.split("=").value(0)] = v_value2.split("=").value(1);
        }
        sqlList2<<map2["v1"]<<map2["v2"]<<map2["v3"];
        database->delete_user_From_table("admin",sqlList2);
    }
    else if(_option == ""){

    }
}


















































































































































































































































































































































































































































































































































































































