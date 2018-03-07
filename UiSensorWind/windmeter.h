#ifndef WINDMETER_H
#define WINDMETER_H

#include <Qt>
#include <QPainter>
#include <QWidget>
#include <qmath.h>
#include <QDebug>
#include <QLinearGradient>
#include <QMouseEvent>
#include <QTimer>

#define PI 3.1415926535

class WindMeter : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString windName READ windName WRITE setWindName NOTIFY windNameChanged)
    Q_PROPERTY(int sensorId READ sensorId WRITE setSensorId NOTIFY sensorIdChanged)
    Q_PROPERTY(int flag READ flag WRITE setFlag NOTIFY flagChanged)
    Q_PROPERTY(int windCurrentAngle READ windCurrentAngle WRITE setWindCurrentAngle NOTIFY currentWindAngleChanged)
    Q_PROPERTY(QString windCurrentSpeed READ windCurrentSpeed WRITE setWindCurrentSpeed NOTIFY windCurrentSpeedChanged)
    Q_PROPERTY(int tenWindMaxAngle READ tenWindMaxAngle WRITE setTenWindMaxAngle NOTIFY tenMaxValueChanged)
    Q_PROPERTY(int tenWindMinAngle READ tenWindMinAngle WRITE setTenWindMinAngle NOTIFY tenMinValueChanged)
    Q_PROPERTY(QString runUpAngle READ runUpAngle WRITE setRunUpAngle NOTIFY runUpAngleChanged)
    Q_PROPERTY(int twoWindAvAngle READ twoWindAvAngle WRITE setTwoWindAvAngle NOTIFY twoWindAvAngleChanged)
    Q_PROPERTY(bool enable READ enable WRITE setEnable NOTIFY enableChanged)
    //Q_PROPERTY(int lastTowWindAvangle READ lastTowWindAvangle WRITE setLastTowWindAvangle NOTIFY lastTowWindAvangleChanged)

public:
    explicit WindMeter(QWidget *parent = 0);
    //wind name
    QString windName() const{ return this->m_name;}
    void setWindName(QString name);

    //UI控件标识
    int flag() const { return m_flag;}
    void setFlag(int flag);

    int sensorId() const { return m_id;}
    void setSensorId(int id);

    int windCurrentAngle() const { return m_windCurrentAngle;}
    QString windCurrentSpeed() const {return m_windCurrentSpeed;}
    int tenWindMaxAngle() const { return m_tenWindMaxAngle;}
    int tenWindMinAngle() const { return m_tenWindMinAngle;}
    QString runUpAngle() const { return m_runUpAngle;}
    int twoWindAvAngle() const {return m_twoAvAngle;}
    //int lastTowWindAvangle() const { return m_lastTowAvangle;}
    bool enable() const {return m_enable;}


signals:
    void windNameChanged();
    void flagChanged();
    void sensorIdChanged();
    void currentWindAngleChanged();
    void windCurrentSpeedChanged();
    void tenMaxValueChanged();
    void tenMinValueChanged();
    void runUpAngleChanged();
    void twoWindAvAngleChanged();
    void enableChanged();
    //void lastTowWindAvangleChanged();

public slots:
    void setWindCurrentAngle(int angle);
    void setWindCurrentSpeed(QString speed);
    void setTenWindMaxAngle(int angle);
    void setTenWindMinAngle(int angle);
    void setRunUpAngle(QString angle);
    void setTwoWindAvAngle(int angle);
    void setEnable(bool able);
    //void setLastTowWindAvangle(int lastTowAngale);

private slots:
    void updatePlugin();

protected:
    int m_windCurrentAngle;
    QString m_windCurrentSpeed;
    int m_tenWindMaxAngle;
    int m_tenWindMinAngle;
    int m_twoAvAngle;
    QString m_runUpAngle;
    void paintEvent(QPaintEvent *event);
    void drawAngleScale(QPainter *painter);
    void drawCurrentWindAngle(QPainter *painter);
    void drawAngleScaleText(QPainter *painter);
    void drawInsideEllipse(QPainter *painter);
    void drawRunUpRect(QPainter *painter);
    void drawUnitLabelArea(QPainter *painter);
    void drawWindAngle(QPainter *painter);
    void drawWindSpeed(QPainter *painter);
    void drawWindPointer(QPainter *painter);

    //以下三个事件使风表盘界面可移动
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
//    QPainter *painter;
    QString m_name;
    int m_flag;//UI控件id
    int m_id;
    int y;
    bool m_enable;
    //int m_lastTowAvangle;

    QPoint point;      //保存鼠标按下的点全局位置坐标与局部坐标的差向量
    bool mousePressed;//保存鼠标按下状态
    int triangle[3][2];
};

#endif // WINDMETER_H
