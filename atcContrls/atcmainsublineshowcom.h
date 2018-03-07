#ifndef ATCMAINSUBLINESHOWCOM_H
#define ATCMAINSUBLINESHOWCOM_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class atcMainSubLineShowCom : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int fontSize READ getFontSize WRITE setFontSize NOTIFY fontSizeChanged)
    Q_PROPERTY(bool waring READ getWaring WRITE setWaring NOTIFY waringChanged)
    Q_PROPERTY(QString unit READ getUnit WRITE setUnit NOTIFY unitChanged)

public:
    explicit atcMainSubLineShowCom(QWidget *parent = 0);
    QString getValue() const {return this->m_Text;}
    int getFontSize() const {return this->m_fontSize;}
    bool getWaring() const{return this->m_Waring;}
    QString getUnit() const {return this->m_unit;}

protected:
    void paintEvent(QPaintEvent *e);

signals:
    void valueChanged();
    void fontSizeChanged();
    void waringChanged();
    void unitChanged();

public slots:
    void setValue(QString valuestr){
        this->m_Text = valuestr;
        update();
    }
    void setFontSize(int size){
        this->m_fontSize = size;
        update();
    }
    void setWaring(bool waring){
        this->m_Waring = waring;
        update();
    }
    void setUnit(QString unit){
        this->m_unit = unit;
        update();
    }

private:
    int m_count;
    void initCountValue();

    QString m_Text;
    void initVlaueStr();

    int m_fontSize;
    void initValueSize();

    bool m_Waring;
    void initWaringValue();

    QString m_unit;
    void initUnit();
};

#endif // ATCMAINSUBLINESHOWCOM_H
