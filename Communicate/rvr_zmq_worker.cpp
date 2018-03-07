#include <QDebug>
#include <QTime>
#include "rvr_zmq_worker.h"
#include <QMutexLocker>
//test begin
typedef QList<QByteArray> DataList;
//test end

//Zmq Worker Thread
Zmq_Worker_Thread::Zmq_Worker_Thread(RVR_Zmq_Worker *zmqWork,QObject *)
{
    exitFlag = false;
    worker = zmqWork;
}

Zmq_Worker_Thread::~Zmq_Worker_Thread()
{
}

void Zmq_Worker_Thread::run()
{
    qDebug()<<"zmq pthread Id is:"<<currentThreadId();
    qDebug()<<"exit:"<<exitFlag;
    while (!exitFlag){
        QCoreApplication::processEvents(QEventLoop::AllEvents,200);
        msleep(30);
//        qDebug()<<"线程运行!";
        if(worker){
            worker->loopZmq();
//            qDebug()<<"thread id:"<<currentThreadId();
        }
    }
    qDebug()<<"线程退出";
}

//Zmq Worker
RVR_Zmq_Worker::RVR_Zmq_Worker(QObject *parent) :
    QObject(parent)
{
    initRebootValue();
    workerThread = new Zmq_Worker_Thread(this);
    moveToThread(workerThread);
    workerThread->start();// start thread
    count = 0;//test
}

RVR_Zmq_Worker::~RVR_Zmq_Worker()
{
}

void RVR_Zmq_Worker::initZmq()
{
    qDebug()<<"option:initZmq....sub threadid:"<<QThread::currentThreadId();
    if(((pCtx = zmq_ctx_new()) == NULL)
            ||((sCtx = zmq_ctx_new()) == NULL))
    {
        qDebug()<<"SC ctx create faild!";
        return ;
    }

    if((pSocket = zmq_socket(pCtx,ZMQ_PUSH)) == NULL)
    {
        qDebug()<<"SC Psocket create faild!";
        zmq_ctx_destroy(pCtx);
        return ;
    }

    if((sSocket = zmq_socket(pCtx,ZMQ_SUB)) == NULL)
    {
        qDebug()<<"SC Ssocket create faild!";
        zmq_ctx_destroy(pCtx);
        return ;
    }
    return ;
}

void RVR_Zmq_Worker::setPort(QString ip, int reciPort, int sendPort)
{
    m_ip = ip;
    m_reciPort = reciPort;
    m_sendPort = sendPort;
    qDebug()<<"option:setZmqPort....subThreadid:"<<QThread::currentThreadId();
    //sub
    int flage;
    QString subAddr = QString("tcp://%1:%2").arg(ip).arg(reciPort);
    QByteArray ba = subAddr.toLatin1();
    char * sAddr= ba.data();
    if((flage = zmq_connect(sSocket,sAddr)) < 0)
    {
        qDebug()<<"SC connect to sub faild!";
        zmq_close(sSocket);
        zmq_ctx_destroy(sCtx);
        return ;
    }

    int iRcvTimeout = 200;
    if(zmq_setsockopt(sSocket,ZMQ_RCVTIMEO,&iRcvTimeout,sizeof(iRcvTimeout)) < 0)
    {
        printf("ZMq connect out time ,will be faild!");
        return ;
    }

    char data_flag = 0x01;
    if((flage = zmq_setsockopt(sSocket,ZMQ_SUBSCRIBE,&data_flag,0)) < 0)
    {
        qDebug()<<"SC set socket faild!";
    }

    //pub
    QString pubAddr = QString("tcp://%1:%2").arg(ip).arg(sendPort);
    QByteArray p_ba = pubAddr.toLatin1();
    char *pAddr = p_ba.data();
    if((flage = zmq_connect(pSocket,pAddr))< 0)
    {
        qDebug()<<"SC connect to push faild!";
        return ;
    }
    return ;
}

void RVR_Zmq_Worker::writezmq(QByteArray barr)
{
    Rlock.lock();
    if(commdQueue.length() > 30){
        commdQueue.clear();
    }
    else{
        commdQueue.enqueue(barr);
    }
    Rlock.unlock();
}

int RVR_Zmq_Worker::readData()
{
    Rlock.lock();
    char buf[3096] = {0};
    QByteArray bArr;
    int size = 0;
    if((size = zmq_recv(sSocket,buf,2048,0))> 0){
        //qDebug()<<"recv data";
        for(int i = 0 ;i < size;i++){
            //            printf("%c",buf[i]);
            bArr.push_back((uchar)buf[i]);
        }
        //        printf("\n");
    }
    else{
        Rlock.unlock();
        return 0;
    }

    // 测试结果：1.当速度大于7倍速率接受数据时，
    // sqlite数据库存储速度跟不上
    // 2.数据库缓存超过999条时自动丢弃缓存时间最长的一条
    // 3.以5倍速率输入所有数据，数据库缓存最大不超过40条
    // 最小是0条。

    emit newData(bArr);
    bArr.clear();
    Rlock.unlock();
    return 1;
}

bool RVR_Zmq_Worker::writeData()
{
    Rlock.lock();
    char sendBuff[3096];
    if(commdQueue.length() != 0){
        QByteArray barr = commdQueue.dequeue();
        int len = barr.length();
        // qDebug()<<QString("send dataxx %1:").arg(count)<<barr.toHex();
        count++;
        for(int b = 0; b < len;b++){
            sendBuff[b] = barr.at(b);
        }
        int flage = zmq_send(pSocket,sendBuff,len,0);
        if(flage < 0){
            qDebug()<<"SC add data faild!";
        }
        else {
            qDebug()<<"SC send data succeed!";// test satrt
            barr.remove(0,1);
            barr.remove(((barr.length())-2),2);
            char before[] = { 0x03, 0x02};
            QByteArray beforeBarry(before,2);
            char after[] = { 0x03};
            QByteArray afterBarry(after,1);
            barr.replace(beforeBarry,afterBarry);
            DataList dataList = barr.split(char(0x03));
            for(int j = 0;j < dataList.length(); j++){
                DataList headDataList = (dataList.value(j)).split(char(0x7c));
                for (int var = 0; var < headDataList.length(); ++var)
                {
                    // qDebug()<<QString("%1:").arg(j)<<(QString)(headDataList.value(var));
                }
            }
        }
    }
    Rlock.unlock();
    return true;
}

void RVR_Zmq_Worker::initRebootValue()
{
    reboot = false;
}

void RVR_Zmq_Worker::closedZmq()
{
    if(pSocket){
        qDebug()<<"zmq close psocket";
        zmq_close(pSocket);
    }
    if(sSocket){
        qDebug()<<"zmq close ssocket";
        zmq_close(sSocket);
    }
    if(pCtx){
        qDebug()<<"zmq destry psocket";
        zmq_ctx_destroy(pCtx);
    }
    if(sCtx){
        qDebug()<<"zmq destry ssocket";
        zmq_ctx_destroy(sCtx);
    }
    qDebug()<<"reboot zmq:";
    //return ;
}

void RVR_Zmq_Worker::rebootZmq()
{
    Rlock.lock();
    reboot = true;
    qDebug()<<"获得重启锁";
    qDebug()<<"closed & destory zmq function.";
    closedZmq();
    qDebug()<<"create zmq function.";
    initZmq();
    qDebug()<<"rebooting zmq function.";
    setPort(m_ip,m_reciPort,m_sendPort);
    Rlock.unlock();
    reboot = false;
    qDebug()<<"释放重启锁";
}

void RVR_Zmq_Worker::loopZmq()
{
    if(!reboot){
        readData();
        writeData();
    }
}

