#ifndef AWOSCOMM_H
#define AWOSCOMM_H

#include "objectFactiry/objectFctory.h"//object factory
#include "AwosConfig/prodata.h"//awos config data
#include "AwosAdmin/awosadmin.h"//awos login config
#include "distanceTransfer/setupthread.h"// 4G commit
#include "Communicate/rvr_zmq_worker.h"//zmq commit
#include "DataParse/messageparse.h"//message parse
#include "awosworkstationmin.h"//init min Awos system UI
#include "sqlDatabase/rvr_data_due.h"//init Awos Database
#include "DataSend/messagesend.h"//init messgae data send
#include "AFFIX9Message/affix9mesage.h"//init AFFIX 9 Message Deal
#include "UIForCaster/forcastertrend.h" //init trend Metar
#include "AwosAdmin/usermanager.h"//init user Manage
#include "rvrConfg/rvrcfg.h"//rvr 补偿参数配置

extern ProData *proData;
extern AwosAdmin *user;
extern SetupThread *remote4G;
extern RVR_Zmq_Worker *zmqworker;
extern MessageParse *messageParse;
extern QWidget *AwosUI;
extern RVR_Data_Due *database;
extern MessageSend *dataSend;
extern AFFIX9Mesage *AFFIX9mess;
extern ForCasterTrend *trendMetar;
extern UserManager * _user_Manage;
extern RVRCFG *rvrPolluteCfg;

#endif // AWOSCOMM_H
