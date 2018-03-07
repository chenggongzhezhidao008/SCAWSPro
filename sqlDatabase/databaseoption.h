#ifndef DATABASEOPTION_H
#define DATABASEOPTION_H

#include <QThread>
#include <QCoreApplication>
#include <QQueue>
#include <QMutex>
#include <QDebug>

#include <QObject>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QApplication>
#include <QStringList>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QMap>
#include <QList>
#include <QVariant>

typedef QMap<QString,QVariant> lineData;

class DataDueWorkerThread;
class DataBaseOption : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseOption(QObject *parent = 0);
    bool initFlag;
    bool dataBaseExist();
    void initDatabase();
    void insertData();
    QSqlDatabase sqlite;
    DataDueWorkerThread *dataDueWorker;
    QQueue<QString> sqlStr;

private:
    QMutex slock;

signals:
    void errorMessage(QString errorName,QString errrorContext);
    void returnDatas(QString optionNane,QList<lineData> tableData);

public slots:
    void createTableSlot(QString tableName,QString createSqlStr);
    void addDataToSql(QString tableName,QString dataStr);
    void addDataToSql(QString tableName,QString fieldStr,QString dataStr);
    QList<lineData> selectData(QString tableName,QStringList columns = QStringList());
    QStringList selectUserDatabyName(QString name);

    /*QSqlQueryModel **/
    void selet_by_table_name(QSqlQueryModel *model,QString tableName,QStringList hearNames);
    void add_data_to_table(QString tableName,QStringList data);
    void delete_data_from_table(QString tableName,QStringList data);
};

//thread class
class DataDueWorkerThread : public QThread
{
    Q_OBJECT
public:
    DataDueWorkerThread(DataBaseOption *option,QObject *parent = 0);
    bool exitFlag;

private:
    DataBaseOption *dataOption;
    virtual void run();
    int m_i;
};

#endif // DATABASEOPTION_H
