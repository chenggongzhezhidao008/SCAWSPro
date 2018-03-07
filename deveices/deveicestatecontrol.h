#ifndef DEVEICESTATECONTROL_H
#define DEVEICESTATECONTROL_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>


typedef QMap<int,QString> SerialMap;

class deveiceStateControl : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int deveice3616ID READ getDeveice3616ID WRITE setDeveice3616ID NOTIFY deveice3616IDChanged)
    Q_PROPERTY(SerialMap modleNameList READ getModleNameList WRITE setModleNameList NOTIFY modleNameListChanged)
    Q_PROPERTY(SerialMap sensorsNameMap READ getSensorsNameMap WRITE setSensorsNameMap NOTIFY sensorsNameMapChanged)

public:
    explicit deveiceStateControl(QWidget *parent = 0);
    int getDeveice3616ID() const { return this->m_3616Id; }
    SerialMap getModleNameList() const { return this->m_modelMap; }
    SerialMap getSensorsNameMap() const { return this->m_sensorNameMap; }

protected:
    void paintEvent(QPaintEvent *e);

public slots:
    void setDeveice3616ID(int id){ this->m_3616Id = id; }
    void setModleNameList(SerialMap modleNameMap){
        this->m_modelMap.clear();
        this->m_modelMap = modleNameMap;
        update();
    }
    void setSensorsNameMap(SerialMap nameMap){
        this->m_sensorNameMap.clear();
        this->m_sensorNameMap = nameMap;
        update();
    }

signals:
    void deveice3616IDChanged();
    void modleNameListChanged();
    void sensorsNameMapChanged();

private:
    int m_3616Id;
    SerialMap titleMap;
    SerialMap cardMap;
    SerialMap m_modelMap;
    SerialMap m_sensorNameMap;
    SerialMap modeStateMap;
    SerialMap sensorStateMap;
    SerialMap sensorIdMap;
    SerialMap beyonRunWayMap;
};

#endif // DEVEICESTATECONTROL_H
