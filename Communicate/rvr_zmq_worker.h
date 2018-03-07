#ifndef RVR_ZMQ_WORKER_H
#define RVR_ZMQ_WORKER_H
#include <QCoreApplication>
#include <QByteArray>
#include <QThread>
#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QMutexLocker>
#include "zmq.h"
#include "time.h"

class Zmq_Worker_Thread;

class RVR_Zmq_Worker : public QObject
{
    Q_OBJECT

public:
    explicit RVR_Zmq_Worker(QObject *parent = 0);
    virtual ~RVR_Zmq_Worker();
    void loopZmq();

signals:
    void newData(QByteArray bytes);

public slots:
    void  initZmq();
    void  setPort(QString ip = "",int reciPort  = 0,int sendPort = 0);
    void  writezmq(QByteArray barr);
    void  closedZmq();
    void  rebootZmq();

private:
    void * pCtx;
    void * sCtx;
    void * pSocket;
    void * sSocket;
    Zmq_Worker_Thread *workerThread;
    QQueue<QByteArray> commdQueue;
    QMutex Rlock;
    int  readData();
    bool writeData();
    int count;//test

    QString m_ip;
    int m_reciPort;
    int m_sendPort;
    bool reboot;
    void initRebootValue();
};

class Zmq_Worker_Thread : public QThread
{
    Q_OBJECT
public:
    Zmq_Worker_Thread(RVR_Zmq_Worker *zmqWork,QObject *parent = 0);
    virtual ~Zmq_Worker_Thread();
    bool exitFlag;

protected:
    virtual void run() Q_DECL_OVERRIDE;

private:
    RVR_Zmq_Worker *worker;

};
#endif // RVR_ZMQ_WORKER_H
