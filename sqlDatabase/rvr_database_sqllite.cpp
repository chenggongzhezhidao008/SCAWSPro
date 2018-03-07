#include "rvr_database_sqllite.h"
#include <QDebug>

RVR_database_sqllite *RVR_database_sqllite::RVR_sql = 0;

RVR_database_sqllite::RVR_database_sqllite(QObject *) :
    QObject(qApp)
{
    initFlag = false;
}
QSqlDatabase RVR_database_sqllite::getConnection()
{
    return this->sqlite;
}

void RVR_database_sqllite::initDatabase()
{
    if(!initFlag){
        QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE","new_db");
        database.setDatabaseName("./database/awosdatabase.db");
        if(database.open()){
            //qDebug()<<"SC sqlite database open succeed!";
            database.close();
        }
        else
        {
             qDebug()<<"SC sqlite database open faild";
        }
        sqlite = database;
        initFlag = true;
    }
}

