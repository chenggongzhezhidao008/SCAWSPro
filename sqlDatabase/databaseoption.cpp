#include "databaseoption.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QTime>

//data due thread

DataDueWorkerThread::DataDueWorkerThread(DataBaseOption *option, QObject *)
{
    exitFlag = false;
    dataOption = option;
    //dataOption->initDatabase();
}

void DataDueWorkerThread::run()
{
    qDebug()<<"Data Store thread id:"<<QThread::currentThreadId();
    dataOption->initDatabase();
    m_i = 0;
    while (!this->exitFlag){
        QCoreApplication::processEvents(QEventLoop::AllEvents,30);
        msleep(20);
        if(dataOption){
            //qDebug()<<QString("%1write data%2")
                      //.arg(QTime::currentTime().toString("hh:mm:ss"))
                      //.arg(m_i);
            dataOption->insertData();
            m_i ++;
            if(m_i > 9999){ // 调整计数器
                m_i = 0;
            }
        }
    }
}

//data due object.
DataBaseOption::DataBaseOption(QObject *parent) :
    QObject(parent)
{
    initFlag = false;
    dataDueWorker = new DataDueWorkerThread(this);
    moveToThread(dataDueWorker);
    dataDueWorker->start();
}

bool DataBaseOption::dataBaseExist()
{
    QFile dbFile;
    if(dbFile.exists("./database/awosdatabase.db"))
    {
        return true;
    }
    else
    {
        qDebug()<<"buiding database file.";
        return false;
    }
}

void DataBaseOption::initDatabase()
{
    if(!initFlag){
        sqlite = QSqlDatabase::addDatabase("QSQLITE","new_db");
        sqlite.setDatabaseName("./database/awosdatabase.db");
        if(sqlite.open()){
            sqlite.close();
        }
        else
        {
            qDebug()<<"SC sqlite database open faild";
        }
        initFlag = true;
    }
}

void DataBaseOption::createTableSlot(QString tableName, QString createSqlStr)
{
    qDebug()<<"QDatabase Qthread create table is:"<<QThread::currentThreadId();
    if(!dataBaseExist()){
        return;
    }
    if(tableName.trimmed() == "")
    {
        return ;
    }
    if(this->sqlite.open())
    {
        QSqlQuery query(this->sqlite);
        bool flag = query.exec(QString("create table %1(%2)").arg(tableName).arg(createSqlStr));
        if(flag)
        {
            qDebug()<<tr("SC create table %1 succee").arg(tableName);
        }
        else
        {
            qDebug()<<tr("SC create table %1 faild").arg(tableName);
        }
        this->sqlite.close();
    }
    return ;
}

void DataBaseOption::addDataToSql(QString tableName, QString dataStr)
{
    slock.lock();
    qDebug()<<"QDatabase Qthread add data to database:"<<QThread::currentThreadId();
    if(sqlStr.length() > 999){
        //sqlStr.clear();
        //出队一条消息，减轻缓存压力
        int len = sqlStr.length() - 999;
        for(int i = 0;i < len; i++){
            qDebug()<<"delete data from the queue:"<<sqlStr.dequeue();
        }
    }
    sqlStr.enqueue(QString("insert into %1 values(%2)").arg(tableName).arg(dataStr));
    qDebug()<<QString("data list:%1").arg(sqlStr.length());
    slock.unlock();
}

void DataBaseOption::addDataToSql(QString tableName, QString fieldStr, QString dataStr)
{
    slock.lock();
    qDebug()<<"QDatabase Qthread add data is:"<<QThread::currentThreadId();
    if(sqlStr.length() > 999){
        //sqlStr.clear();
        //出队一条消息，减轻缓存压力
        int len = sqlStr.length() - 999;
        for(int i = 0;i < len; i++){
            qDebug()<<"delete data from the queue:"<<sqlStr.dequeue();
        }
    }
    sqlStr.enqueue(QString("insert into %1(%2) values(%3)").arg(tableName).arg(fieldStr).arg(dataStr));
    qDebug()<<QString("data list:%1").arg(sqlStr.length());
    slock.unlock();
}

void DataBaseOption::insertData()
{
    slock.lock();
    if(this->sqlStr.length() > 0){
        if(!dataBaseExist()){
            qDebug()<<"database is not exist!";
            slock.unlock();
            return ;
        }
        if(!sqlite.isValid()){
            slock.unlock();
            qDebug()<<"sqlite database is not exist!";
            return ;
        }
        if(this->sqlite.open()){
            QSqlQuery query(sqlite);
//            while (sqlStr.length() > 0){
                qDebug()<<"list leng:"<<sqlStr.length();
                bool flag = query.exec(sqlStr.dequeue());
                if(flag){
                    qDebug()<<"SC data insert into succeed!";
                }
                else{
                    qDebug()<<"SC insert into faild!";
                }
//            }
            this->sqlite.close();
        }
    }
    slock.unlock();
    return ;
}

QList<lineData> DataBaseOption::selectData(QString tableName,QStringList columns)
{
    slock.lock();
    qDebug()<<"QDatabase Qthread select data is:"<<QThread::currentThreadId();
    QList<lineData> list;
    if(!dataBaseExist()){
        qDebug()<<"the database file not exisit";
        slock.unlock();
        return list;
    }
    lineData mapRecord;
    if(this->sqlite.open())
    {
        int columnsLength = columns.length();
        QSqlQuery query(this->sqlite);
        QString sqlstr = "select ";
        bool single = false;
        if(columnsLength == 1 && columns.value(0) == "*")
        {
            sqlstr = sqlstr + columns.value(0);
            single = true;
        }
        else
        {
            for(int i = 0; i < columnsLength; i++)
            {
                if(i == 0)
                {
                    sqlstr = sqlstr + QString(" SC_%1 ").arg(columns.value(i));
                }
                else
                {
                    sqlstr = sqlstr + QString(",SC_%1 ").arg(columns.value(i));
                }
            }
        }

        sqlstr = sqlstr + QString(" from %1").arg(tableName);
        qDebug()<< "sql str:" << sqlstr;
        bool flag = query.exec( sqlstr);
        qDebug()<<"sql execute info:"<<query.lastError();
        if(flag)
        {
            if(single/*columnsLength == 1 && columns.value(0) == "*"*/)
            {
                columns.clear();
                int colNum = query.record().count();
                columnsLength = colNum;
                for(int ic = 0; ic < colNum; ic++){
                    columns.push_back(query.record().fieldName(ic));
                }
                qDebug()<<"cloum:"<<columns;
            }
            while(query.next())
            {
                for(int j = 0; j < columnsLength;j++)
                {
                    if(single){
                        mapRecord[columns.value(j)] = query.value(columns.value(j));
                        qDebug()<<"meate:"<<query.value(columns.value(j)).toString();
                    }
                    else{
                        mapRecord[columns.value(j)] = query.value("SC_" + columns.value(j));
                        qDebug()<<"meate:"<<query.value("SC_" + columns.value(j)).toString();
                    }
                }
                list.push_back(mapRecord);
            }
        }
        this->sqlite.close();
    }
    slock.unlock();
    return list;
}

QStringList DataBaseOption::selectUserDatabyName(QString name)
{
    slock.lock();
    qDebug()<<"QDatabase Qthread select user by name is:"<<QThread::currentThreadId();
    QStringList usrDataList;
    if(!dataBaseExist()){
        qDebug()<<"the database file not exisit";
        slock.unlock();
        return QStringList();
    }
    if(this->sqlite.open()){
        QSqlQuery logQuery(this->sqlite);
        QString  sqlStr;
        sqlStr = QString("select SC_password,SC_loginClass from admin where SC_username = '%1'").arg(name);
        bool flag = logQuery.exec(sqlStr);
        if(flag){
            while(logQuery.next())
            {
                usrDataList.push_back(QString("password:%1/class:%2")
                                      .arg(logQuery.value(0).toString())
                                      .arg(logQuery.value(1).toString()));
            }
            this->sqlite.close();
            slock.unlock();
            return usrDataList;
        }
    }
    slock.unlock();
    return QStringList();
}

void DataBaseOption::selet_by_table_name(QSqlQueryModel *model,QString tableName,QStringList hearNames)
{
    slock.lock();
    qDebug()<<"QDatabase Qthread select data by table is:"<<QThread::currentThreadId();
    QSqlQueryModel *_table_model = model;
    int len = hearNames.length();
    if(!dataBaseExist()){
        for(int n = 0;n < len;n++){
            _table_model->setHeaderData(n,Qt::Horizontal, tr("%1").arg(hearNames.value(n)));
        }
        slock.unlock();
        return;
    }
    if(this->sqlite.open()){
        QString sqlStr;
        sqlStr = QString("select * from %1").arg(tableName);
        _table_model->setQuery(sqlStr,this->sqlite);
        this->sqlite.close();
    }
    for(int n = 0;n < len;n++){
        _table_model->setHeaderData(n,Qt::Horizontal, tr("%1").arg(hearNames.value(n)));
    }
    slock.unlock();
    qDebug()<<"VVVV1"<<_table_model;
    return ;
}

void DataBaseOption::add_data_to_table(QString tableName,QStringList data)
{
    qDebug()<<"QDatabase Qthread add data:"<<QThread::currentThreadId();
    slock.lock();
    if(!dataBaseExist()){
        qDebug()<<"the database file not exisit";
        slock.unlock();
        return ;
    }
    if(this->sqlite.open()){
        QSqlQuery addQuery(this->sqlite);
        QString  sqlStr;
        sqlStr = QString("insert into %1 values('%2','%3','%4')")
                .arg(tableName)
                .arg(data.value(0))
                .arg(data.value(1))
                .arg(data.value(2));
        addQuery.exec(sqlStr);
        this->sqlite.close();
    }
    slock.unlock();
}

void DataBaseOption::delete_data_from_table(QString tableName, QStringList data)
{
    qDebug()<<"QDatabase Qthread delete data is:"<<QThread::currentThreadId();
    slock.lock();
    if(!dataBaseExist()){
        qDebug()<<"the database file not exisit";
        slock.unlock();
        return ;
    }
    if(this->sqlite.open()){
        QSqlQuery deleteQuery(this->sqlite);
        QString  sqlStr;
        sqlStr = QString("delete from %1 where SC_username = '%2'and SC_password = '%3'and SC_loginClass = '%4'")
                .arg(tableName)
                .arg(data.value(0))
                .arg(data.value(1))
                .arg(data.value(2));
        qDebug()<<"xxxxxxxxxxxxx"<<sqlStr;
        deleteQuery.exec(sqlStr);
        this->sqlite.close();
    }
    slock.unlock();
}

