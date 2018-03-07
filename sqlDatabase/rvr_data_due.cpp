#include "rvr_data_due.h"
#include <QDebug>

RVR_Data_Due::RVR_Data_Due(QObject *parent) :
    QObject(parent)
{
    initDataDue();
}

//配置数据库表格
bool RVR_Data_Due::configDatabaseTable(QString tableName,QStringList columnNames)
{
   QString fieldStr = "SC_" + columnNames.value(0).replace(":"," ");
   for(int i = 1; i < columnNames.length();i++){
       fieldStr = fieldStr + ","+ "SC_" + columnNames.value(i).replace(":"," ");
   }
   //qDebug()<<"最终数据库字段名称:"<<fieldStr;
   emit createTable(tableName,fieldStr);
   return true;//2017.3.1
}

//添加数据
void RVR_Data_Due::addData(QString tableName, QVariantList datalist)
{
    QString dataStr,sub;
    for(int i = 0; i < datalist.length();i++){
        if(QVariant::String == (datalist.value(i)).type()){
            sub = datalist.at(i).toString();
            sub = "'" + sub + "'";
        }
        else{
            sub = datalist.value(i).toString();
        }
        if(i == 0) dataStr = sub;
        else{
            dataStr = dataStr + " , "+ sub;
        }
    }
    qDebug()<<"SC table name:"<<tableName<<"table field str"<<dataStr;
    emit addDataNotField(tableName,dataStr);
}

void RVR_Data_Due::addData(QString tableName, QString tablefieldStr, QString tableDataStr)
{
    emit addDataHaveField(tableName,tablefieldStr,tableDataStr);
}

//查询整个表格数据
QList<lineData> RVR_Data_Due::getData(QString tableName)
{
    QStringList columnNameStr;
    columnNameStr<<"*";
    QList<lineData> tableList = option->selectData(tableName,columnNameStr);
    for(int i = 0; i < tableList.length();i++){
        qDebug()<<QString("return datas %1:").arg(i)<<tableList.value(i);
    }
    return tableList;
}

//查询某个数据
QStringList RVR_Data_Due::getUserData(QString userName)
{
        QStringList userData;
        userData = option->selectUserDatabyName(userName);
        return userData;
}

void RVR_Data_Due::select_table_View(QSqlQueryModel *model
                                     ,QString tableName
                                     ,QStringList hearNames)
{
    //QSqlQueryModel *model;
    /*model = */
    option->selet_by_table_name(model,tableName,hearNames);
    //qDebug()<<"VVVV2"<<model;
    emit _table_View(/*model*/);
}

void RVR_Data_Due::add_user_To_table(QString tableName, QStringList valueList)
{
    option->add_data_to_table(tableName,valueList);
}

void RVR_Data_Due::delete_user_From_table(QString tableName, QStringList valueList)
{
    option->delete_data_from_table(tableName,valueList);
}

void RVR_Data_Due::initDataDue()
{
     option = new DataBaseOption();
     connect(this,SIGNAL(createTable(QString,QString))
             ,option,SLOT(createTableSlot(QString,QString))
             ,Qt::QueuedConnection);
     connect(this,SIGNAL(addDataNotField(QString,QString))
             ,option,SLOT(addDataToSql(QString,QString))
             ,Qt::QueuedConnection);
     connect(this,SIGNAL(addDataHaveField(QString,QString,QString))
             ,option,SLOT(addDataToSql(QString,QString,QString))
             ,Qt::QueuedConnection);

}


