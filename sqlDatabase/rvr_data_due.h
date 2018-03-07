#ifndef RVR_DATA_DUE_H
#define RVR_DATA_DUE_H

#include <QObject>
#include "sqlDatabase/databaseoption.h"
#include <QMap>
#include <QVariant>
#include <QList>
#include <QSqlQueryModel>

typedef QMap<QString,QVariant> lineData;

class RVR_Data_Due : public QObject
{
    Q_OBJECT

public:
    explicit RVR_Data_Due(QObject *parent = 0);
    bool configDatabaseTable(QString tableName,QStringList columnNames);
    void addData(QString tableName = QString()
            ,QVariantList datalist = QVariantList());
    void addData(QString tableName = QString()
            ,QString tablefieldStr = QString()
            ,QString tableDataStr= QString());
    QList<lineData> getData(QString tableName);
    QStringList getUserData(QString userName);
    void select_table_View(QSqlQueryModel *model
                           ,QString tableName
                           ,QStringList hearNames);
    void add_user_To_table(QString tableName,QStringList valueList);
    void delete_user_From_table(QString tableName,QStringList valueList);

signals:
    void createTable(QString tableName,QString createSqlStr);
    void addDataNotField(QString tableName,QString dataStr);
    void addDataHaveField(QString tableName,QString fieldStr,QString dataStr);
    void _table_View(/*QSqlQueryModel *model*/);

public slots:

private:
    void initDataDue();
    DataBaseOption *option;
};

#endif // RVR_DATA_DUE_H
