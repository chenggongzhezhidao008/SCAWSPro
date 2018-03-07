#ifndef SUBTESTINFORSHOW_H
#define SUBTESTINFORSHOW_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>

typedef QMap<int,QString> InforMap;

class GlableCom_InforShow : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int subWidth READ getSubWidth WRITE setSubWidth NOTIFY subWidthChanged)
    Q_PROPERTY(int subHeight READ getSubHeight WRITE setSubHeight NOTIFY subHeightChanged)
    Q_PROPERTY(InforMap dataMap READ getDataMap WRITE setDataMap NOTIFY dataMapChanged)

public:
    explicit GlableCom_InforShow(QWidget *parent = 0);
    int getSubWidth() const { return m_width; }
    int getSubHeight() const { return m_height; }
    InforMap getDataMap() const { return m_DataMap; }
    int returnDataIndex() const { return m_index; }

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

signals:
    void subWidthChanged();
    void subHeightChanged();
    void dataMapChanged();

public slots:
    void setSubWidth(int value){
      if( m_width != value){
          m_width = value;
          this->setGeometry(0,0,m_width,m_height);
          update();
      }
    }

    void setSubHeight(int value){
       if(m_height != value){
           m_height = value;
           this->setGeometry(0,0,m_width,m_height);
           update();
       }
    }

    void setDataMap(InforMap data){
        m_DataMap.clear();
        m_DataMap = data;
        m_num = m_DataMap.count();
        update();
        qDebug()<<"a";
    }

private:
    int m_width;
    int m_height;
    void initValues();

    InforMap m_DataMap;
    int m_num;
    void initNumValue();

    //标记选中背景索引
    int m_index;
    void initIndexValue();
};

#endif // SUBTESTINFORSHOW_H
