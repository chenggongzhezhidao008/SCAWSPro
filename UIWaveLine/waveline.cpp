#include "waveline.h"
#include <QDebug>
#include <QList>

WaveLine::WaveLine(QWidget *parent) :
    QWidget(parent)
{
    m_graphname = "NAME";
    m_timeList[1] = "1h";
    m_timeList[2] = "2h";
    m_timeList[3] = "3h";
    m_timeList[4] = "6h";
    m_timeList[5] = "12h";
    m_timeList[6] = "24h";
    m_timeList[7] = "48h";
    m_timeList[8] = "72h";
    selectHours(1);

    m_lineNames[1] = "湿度06";
    m_lineNames[2] = "湿度24";
    m_lineNames[3] = "湿度09";
    m_lineNames[4] = "湿度27";
    m_lineNames[5] = "湿度03";
    m_track = false;
}
void WaveLine::setGraphName(QString graphName)
{
    this->m_graphname = graphName;
    update();
}

void WaveLine::setLineNames(LineNames lines)
{
    this->m_lineNames.clear();
    this->m_lineNames = lines;
    update();
}

void WaveLine::setLinesColor(QMap<QString, QColor> colors)
{
    this->m_linesColor.clear();
    this->m_linesColor = colors;
    update();
}

void WaveLine::setWavesDatas(OneData waveData)
{
    QStringList keys = waveData.keys();
    if(keys.length() >1){
        qDebug()<<"传入多个点值，请代码处理。";
        for(int i = 0 ;i < keys.length();i++){
            return ;
        }
    }
    else if(keys.length() == 1)
    {
        deleteAndAddData(m_waveData1Hour,waveData,1 * 3600,keys);
        deleteAndAddData(m_waveData2Hour,waveData,2 * 3600,keys);
        deleteAndAddData(m_waveData3Hour,waveData,3 * 3600,keys);
        deleteAndAddData(m_waveData6Hour,waveData,6 * 3600,keys);
        deleteAndAddData(m_waveData12Hour,waveData,12 * 3600,keys);
        deleteAndAddData(m_waveData24Hour,waveData,24 * 3600,keys);
        deleteAndAddData(m_waveData48Hour,waveData,48 * 3600,keys);
        deleteAndAddData(m_waveData72Hour,waveData,72 * 3600,keys);
    }
    else{
        return ;
    }
    update();
}

void WaveLine::deleteAndAddData(dataMap &hoursdata,OneData oneData,qint64 secs,QStringList keys)
{
    QStringList list = oneData[keys.value(0)].split(":");
    QDateTime dateTime2;
    newDateTime = QDateTime::fromString(list.value(0),"yyyy'/'MM'/'dd'/'hh'/'mm'/'ss");
    //以最新的数据为更新数据时间，要以现在时间为更新时间以后修改此处
    QString timeStr;
    int deleteIndex = 0;
    int length;
    length = hoursdata[keys.value(0)].length();
    for(int len = 0;len < length; len++){
        timeStr = (hoursdata[keys.value(0)].at(len).split(":")).at(0);
        dateTime2 = QDateTime::fromString(timeStr,"yyyy'/'MM'/'dd'/'hh'/'mm'/'ss");
        //qDebug()<<"secs is:"<<dateTime2.secsTo(newDateTime);
        if(dateTime2.secsTo(newDateTime) < secs){
            //qDebug()<<dateTime2.toString("yyyy/MM/dd/hh/mm/ss");
            //qDebug()<<"index:"<<len;
            deleteIndex = len;
            break ;
        }
    }
    for(int deleteNum = 0; deleteNum < deleteIndex; deleteNum++){
        //qDebug()<<QString("%1 secs do one").arg(secs);
        (hoursdata[keys.value(0)]).removeFirst();
    }
    hoursdata[keys.value(0)].push_back(oneData[keys.value(0)]);
    //qDebug()<<"hours map data:"<<hoursdata;
}

void WaveLine::selectTrack()
{
    if(m_track){
        m_track = false;
    }
    else{
        m_track = true;
    }
    update();
}

void WaveLine::selectLines(int i)
{
    qDebug()<<"按钮名称："<<QString("曲线%1").arg(i);
    QString location = m_lineNames[i];
    QStringList keys = showWaves.keys();
    for(int var = 0; var < keys.length(); ++var) {
        if(keys.at(var) == location){
            if(showWaves[location]){
                showWaves[location] = false;
                update();
                qDebug()<<"show waves:"<<this->showWaves;
                return ;
            }
            else{
                showWaves[location] = true;
                update();
                qDebug()<<"show waves:"<<this->showWaves;
                return ;
            }
        }
    }
    showWaves[location] = true;
    qDebug()<<"show waves:"<<this->showWaves;
    update();
}

void WaveLine::selectHours(int i)
{
    QString timeStr;                                   //qDebug()<<"index: hours:"<<QString("%1").arg(i)<<this->m_timeList[i];
    QList<int> keys = this->m_timeList.keys();
    int timeNum = keys.length();
    for(int t = 0; t < timeNum ; t++){
        timeStr = this->m_timeList[t+1];
        if((t + 1) == i){
            this->m_slectTimeList[timeStr] = true;
            this->hourSelected = (timeStr.mid(0,timeStr.length() - 1)).toInt();
            qDebug()<<"selected hours:"<<this->hourSelected;
        }
        else{
            this->m_slectTimeList[timeStr] = false;
        }
    }
    update();
}
