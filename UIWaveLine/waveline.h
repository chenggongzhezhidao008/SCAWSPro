#ifndef WAVELINE_H
#define WAVELINE_H

#include <QWidget>
#include <QTime>
#include <QDateTime>
#include <QStringList>
#include <QMap>

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

typedef QMap<QString,QColor> LColorMap;
typedef QMap<QString,QStringList> LDataMap;

//显示选择曲线
typedef int LineFlag;
typedef QString LineLocation;
typedef QMap<LineFlag,LineLocation> LineNames;
typedef QMap<LineLocation,bool> ShowList;

//传入数据结构
typedef QString OnePointData;
typedef QMap<LineLocation,OnePointData> OneData;
typedef QMap<LineLocation,QStringList> dataMap;

//选择时间
typedef int HourFlag;
typedef QString TimeStr;
typedef bool Select;
typedef QMap<HourFlag,TimeStr> TimeList;
typedef QMap<TimeStr,Select> TimeSelect;

class WaveLine : public QWidget
{
    Q_OBJECT
    Q_PROPERTY( QString graphName READ graphName WRITE setGraphName NOTIFY graphNameChanged)
    Q_PROPERTY( LineNames lineNames READ lineNames WRITE setLineNames NOTIFY lineNamesChanged)
    Q_PROPERTY( LColorMap linesColor READ linesColor WRITE setLinesColor NOTIFY linesColorChanged)
    Q_PROPERTY(OneData wavesDatas  WRITE setWavesDatas NOTIFY wavesDatasChanged)/*READ wavesDatas*/

public:
    explicit WaveLine(QWidget *parent = 0);
    QString graphName() const { return this->m_graphname; }
    LineNames lineNames() const { return this->m_lineNames; }
    LColorMap linesColor() const { return this->m_linesColor; }

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void drawBackground(QPainter *painter);
    void drawName(QPainter *painter);
    void drawLineNames(QPainter *painter);
    void drawScaleLines(QPainter *painter);
    void drawTimeLines(QPainter *painter);
    void drawPushButton(QPainter *painter);
    void drawWaves(QPainter *painter);
    void drawLine(QPainter *&painter,int timeLength);

signals:
   void lineNamesChanged();
   void linesColorChanged();
   void graphNameChanged();
   void wavesDatasChanged();

public slots:
   void setGraphName(QString graphName);
   void setLineNames(LineNames lines);
   void setLinesColor(QMap<QString,QColor> colors);
   void setWavesDatas(OneData waveData);

private:
   QDateTime newDateTime;
   qreal m_x;
   qreal m_y;
   void deleteAndAddData(dataMap &hoursdata,OneData oneData,qint64 secs,QStringList keys);
   void selectTrack();
   bool m_track;
   void selectLines(int i);
   void selectHours(int i);
   LineNames m_lineNames;
   ShowList showWaves;
   TimeList m_timeList;
   TimeSelect m_slectTimeList;
   int hourSelected;
   QString m_graphname;
   LColorMap m_linesColor;
   dataMap m_waveData1Hour;
   dataMap m_waveData2Hour;
   dataMap m_waveData3Hour;
   dataMap m_waveData6Hour;
   dataMap m_waveData12Hour;
   dataMap m_waveData24Hour;
   dataMap m_waveData48Hour;
   dataMap m_waveData72Hour;
};

#endif // WAVELINE_H
