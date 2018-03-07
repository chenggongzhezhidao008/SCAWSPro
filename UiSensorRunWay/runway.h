#ifndef RUNWAY_H
#define RUNWAY_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class RunWay : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int flag READ flag WRITE setFlag NOTIFY flagChanged)
    Q_PROPERTY(int airportId READ airportId WRITE setAirportId NOTIFY airportIdChanged)
    Q_PROPERTY(int runWayId READ runWayId WRITE setRunWayId NOTIFY runWayIdChanged)
    Q_PROPERTY(QString headName READ headName WRITE setHeadName NOTIFY headNameChanged)
    Q_PROPERTY(QString rearName READ rearName WRITE setRearName NOTIFY rearNameChanged)
    Q_PROPERTY(QString weather READ weather WRITE setWeather NOTIFY weatherChanged)

public:
    explicit RunWay(QWidget *parent = 0);

    //UI控件标识
    int flag() const { return m_flag;}
    void setFlag(int flag);

    int airportId() const { return m_airportId;}
    void setAirportId(int airportid);

    int runWayId() const { return m_runwayId;}
    void setRunWayId(int id);

    QString headName() const { return this->m_head;}
    void setHeadName(QString head);

    QString rearName() const { return this->m_rear;}
    void setRearName(QString rear);

    QString weather() const { return this->m_weather;}
    void setWeather(QString weather);

signals:
   void flagChanged();
   void airportIdChanged();
   void runWayIdChanged();
   void headNameChanged();
   void rearNameChanged();
   void weatherChanged();

protected:
   void paintEvent(QPaintEvent *event);
   void drawBackgroud(QPainter *painter);
   void drawTwoTuochPoint(QPainter *painter);
   void drawRunWayText(QPainter *painter);

   //以下三个事件使风表盘界面可移动
   void mousePressEvent(QMouseEvent *e);
   void mouseMoveEvent(QMouseEvent *e);
   void mouseReleaseEvent(QMouseEvent *e);

public slots:

private:
//   QPainter *painter;
   int m_flag;//UI控件id
   int m_airportId;
   int m_runwayId;
   int runWayWidth;
   int runWayHeiht;
   QString m_head;
   QString m_rear;
   QString m_weather;
   QString m_drection;

   //确定跑道方向
   bool estimateWidthHeight;
   bool isCrosswise;

   QPoint point;//保存鼠标按下的点全局位置坐标与局部坐标的差向量
   bool mousePressed;//保存鼠标按下状态
};

#endif // RUNWAY_H
