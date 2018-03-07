#ifndef INPUTVALUECOM_H
#define INPUTVALUECOM_H

#include <QWidget>
#include <Map>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVector>
typedef QVector<QLabel *> Labellist;
typedef QVector<QLineEdit *> Linelist;

typedef int ValueIndex;
typedef QString NanmeAndValue;
typedef QMap<ValueIndex,NanmeAndValue> InputChangMap;

class InputValueCom : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int classIndex READ getClassIndex WRITE setClassIndex NOTIFY classIndexChanged)
    Q_PROPERTY(InputChangMap optionValueMap READ getOptionValueMap WRITE setoptionValueMap NOTIFY optionValueMapChanged)

public:
    explicit InputValueCom(QWidget *parent = 0);
    int getClassIndex() const { return this->m_Index;}
    InputChangMap getOptionValueMap() const { return this->m_ValueMap;}

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void classIndexChanged();
    void optionValueMapChanged();

public slots:
    void setClassIndex(int Index){
        this->m_Index = Index;
        initSubContrls(m_Index);
    }

    void setoptionValueMap(InputChangMap valueMap){
        this->m_ValueMap.clear();
        this->m_ValueMap = valueMap;
    }

private:
    int m_Index;
    InputChangMap m_ValueMap;

    Labellist labelVEC;
    Linelist  lineVEC;
    void clearVEC();
    void addLabelComs(QString infor,int index,int comWidth,int comheight);
    void addEditComs(QString infor,int index,int comWidth,int comheight);
    void initSubContrls(int Index);

    InputChangMap airportAdd;
    InputChangMap runWayAdd;
    InputChangMap sensorAdd;
    void initAddValue();

    bool confirm;
    bool release;
    void initConfirmValue();
};

#endif // INPUTVALUECOM_H
