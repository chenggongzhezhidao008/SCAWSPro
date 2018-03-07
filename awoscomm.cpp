#include "awoscomm.h"
ProData *proData = NULL;
AwosAdmin *user = NULL;
SetupThread *remote4G = NULL;
RVR_Zmq_Worker *zmqworker = NULL;
MessageParse  *messageParse = NULL;
QWidget *AwosUI = NULL;
RVR_Data_Due   *database = NULL;
MessageSend    *dataSend = NULL;
AFFIX9Mesage   *AFFIX9mess = NULL;
ForCasterTrend *trendMetar = NULL;
UserManager * _user_Manage = NULL;
RVRCFG *rvrPolluteCfg = NULL;
